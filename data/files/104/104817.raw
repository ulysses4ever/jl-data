# A first pass at programming the direct boundary element method (DBEM).
# For now, only constant elements are implemented.

# Type declarations

immutable Dirichlet
end

immutable Neumann
end

immutable BoundaryCondition{T}
    value::Float64 # Value of the boundary condition
end

immutable Point
    x::Float64
    y::Float64
end

immutable BoundarySegment
    p1::Point              # Start point
    p2::Point              # End point
    bc::BoundaryCondition  # Boundary condition on the segment
end

immutable BoundaryElement{T}
    p1::Point
    p2::Point
    node::Point
    value::Float64
end

# Define the geometry of the model. For now, this is directly input here.
# Later on, this will read from a file and return a list of geometry points
# that define the model boundary.
# We test with a 1x1 square domain. The bottom and top have Dirichlet conditions
# of 0 and 100 respectively while the left and right have homogeneous Neumann
# conditions.
function model()
    p1 = Point(0.0, 0.0)
    p2 = Point(1.0, 0.0)
    p3 = Point(1.0, 1.0)
    p4 = Point(0.0, 1.0)

    bc_bottom = BoundaryCondition{Dirichlet}(0.0)
    bc_side1 = BoundaryCondition{Dirichlet}(10.0)
    bc_side2 = BoundaryCondition{Neumann}(0.0)
    bc_top = BoundaryCondition{Neumann}(0.0)

    # The boundary segments need to be closed
    s1 = BoundarySegment(p1, p2, bc_bottom)
    s2 = BoundarySegment(p2, p3, bc_side1)
    s3 = BoundarySegment(p3, p4, bc_top)
    s4 = BoundarySegment(p4, p1, bc_side2)

    boundary = [s1, s2, s3, s4]

    # Field points. These are the points where the potential is calculated
    # using the boundary integral formula after the DBEM system is solved.
    n = 100 # Number of x internal field grid points
    m = 100 # Number of y internal field grid points
    dx = 1.0/(n + 1)
    dy = 1.0/(m + 1)
    field_points = Array{Point}(n,m)
    k = 1
    for i in 1:n
        for j in 1:m
            field_points[i,j] = Point(i*dx, j*dy)
        end
    end

    return boundary, field_points
end

# Discretize the boundary. The first argment is the model boundary and the
# second argument is the number of boundary elements wanted on each boundary
# segment. For example, if n_elm[1] = 10, the first boundary segment will be
# partitioned into 10 uniform elements. The length of n_elm must equal the
# length of boundary.

# Future functionality should allow for the system GMSH uses where an elmement
# size is specified at each geometry point rather than the segments. This would
# allow for a continuous element size transition along segments rather than
# sudden element size transitions.

function discretize(boundary::Array{BoundarySegment}, nelm::Array{Int64})
    discrete_boundary = Array{BoundaryElement}(sum(nelm))
    i = 1 # Current boundary element number
    j = 1 # Current boundary element number
    for segment in boundary
        n = nelm[i] # Number of boundary elements on segment
        dx = (segment.p2.x - segment.p1.x)/n
        dy = (segment.p2.y - segment.p1.y)/n
        for k in 1:n
            p1_x = segment.p1.x + dx*(k - 1)
            p1_y = segment.p1.y + dy*(k - 1)
            p2_x = segment.p1.x + dx*k
            p2_y = segment.p1.y + dy*k
            p1 = Point(p1_x, p1_y)
            p2 = Point(p2_x, p2_y)
            node_x = (p1.x + p2.x)/2
            node_y = (p1.y + p2.y)/2
            node = Point(node_x, node_y)
            value = segment.bc.value
            if typeof(segment.bc) == BoundaryCondition{Dirichlet}
                T = Dirichlet
            else
                T = Neumann
            end
            discrete_boundary[j] = BoundaryElement{T}(p1, p2, node, value)
            j += 1
        end
        i += 1
    end
    return discrete_boundary
end

# G kernel exact integral
function kernel_integral(source::Point, field::BoundaryElement, T::Neumann)
    # Geometry calculations
    r1 = [field.p1.x - source.x, field.p1.y - source.y]
    r2 = [field.p2.x - source.x, field.p2.y - source.y]
    R = r2 - r1
    T1 = dot(r1, R)/norm(R)
    T2 = dot(r2, R)/norm(R)
    d = r1 - dot(r1,R)/dot(R,R)*R
    theta1 = asin(dot(r1, R)/(norm(r1)*norm(R)))
    theta2 = asin(dot(r2, R)/(norm(r2)*norm(R)))

    return 1/(2*pi)*(-1*(theta2 - theta1)*norm(d) +
                         abs((T2 - T1)) - T2*log(norm(r2)) + T1*log(norm(r1)))
end

# F kernel exact integral
function kernel_integral(source::Point, field::BoundaryElement, T::Dirichlet)
    # Geometry calculations
    r1 = [field.p1.x - source.x, field.p1.y - source.y]
    r2 = [field.p2.x - source.x, field.p2.y - source.y]
    R = r2 - r1
    theta1 = asin(dot(r1, R)/(norm(r1)*norm(R)))
    theta2 = asin(dot(r2, R)/(norm(r2)*norm(R)))

    return -1/(2*pi)*(theta2 - theta1)
end

# Form the linear system. After discretizing the boundary integral equations,
# we have a sytem of the form Fu = Gq where F is the matrix of potential kernel
# integrals, u is the vector of potential values on each element, G is the
# matrix of flux kernal integrals and q is the vector of outward normal flux
# values on each element.
#
# In general, we know some of the potential vector
# values from our Dirichlet boundary conditions and some of the flux vector
# values from out Neumann boundary conditions. We enforce the boundary
# conditions by swapping the columns of F and Q such that all the unknowns
# values are on the left hand side and all the known values are on the right
# hand side. The matrix and vector on the right hand side are known, so we can
# directly multiply them to get a right hand side vector b. The matrix on the
# left hand side, A, corresponds to the vector of unknown potential and flux
# values x. Thus, the system we need to solve is Ax = b.

function form_system(discrete_boundary::Array{BoundaryElement})
    c = 0.5 # c(x) value from boundary integral formulation
    n = length(discrete_boundary) # Number of boundary elements

    # Create matrices
    A = Array{Float64}(n, n) # LHS matrix for unknown vector
    B = Array{Float64}(n, n) # RHS matrix for boundary condition vector
    for i in 1:n # Iterate over source points
        source = discrete_boundary[i].node
        for j in 1:n # Iterate over boundary elements
            bc_type = typeof(discrete_boundary[j])
            if bc_type == BoundaryElement{Dirichlet}
                TA = Neumann() # The LHS matrix has an unknown opposite the bc
                TB = Dirichlet() # The RHS matrix corresponds to the known bc
            else
                TA = Dirichlet()
                TB = Neumann()
            end
            A[i,j] = kernel_integral(source, discrete_boundary[j], TA)
            B[i,j] = kernel_integral(source, discrete_boundary[j], TB)
            # We add c(x) to the potential kernal integrals for diagonal entries
            if i == j
                if TA == Dirichlet
                    A[i,j] += 0.5
                else
                    B[i,j] += 0.5
                end
            end
        end
    end

    # Create boundary condition vector
    bc_vec = Array{Float64}(n)
    for i in 1:n
        bc_vec[i] = discrete_boundary[i].value
    end

    # Form RHS vector
    b = B*bc_vec

    return A, b
end

# Take the DBEM solution vector and sort it into a vector of boundary potential
# values and boundary flux values.
function form_vectors(x::Array{Float64},
                      discrete_boundary::Array{BoundaryElement})
    n = length(x)
    u = Array{Float64}(n)
    q = Array{Float64}(n)
    for i in 1:n
        if typeof(discrete_boundary) == BoundaryElement{Dirichlet}
            u[i] = discrete_boundary[i].value
            q[i] = x[i]
        else
            u[i] = x[i]
            q[i] = discrete_boundary[i].value
        end
    end
    return u, q
end

# Calculate the potential using the discrete boundary integral equation
# u is the vector of potential values on the boundary and q is the vector of
# flux values on the boundary.
function field_values(u::Array{Float64}, q::Array{Float64},
                      discrete_boundary::Array{BoundaryElement},
                      field_points::Array{Point})
    n1 = size(field_points,1)
    n2 = size(field_points,2)
    m = length(u)
    f = Array{Float64}(m)
    g = Array{Float64}(m)
    pot_vals = Array{Float64}(size(field_points))
    for i in 1:n1
        for j in 1:n2
            for k in 1:m
                # Discrete potential kernal integrals
                f[k] = kernel_integral(field_points[i,j], discrete_boundary[k],
                                       Dirichlet())
                # Discrete flux kernal integrals
                g[k] = kernel_integral(field_points[i,j], discrete_boundary[k],
                                       Neumann())
                pot_vals[i,j] = dot(q,g) - dot(u,f)
            end
        end
    end
    return pot_vals
end

# Main function
function dbem(nelm)
    boundary, field_points = model()
    discrete_boundary = discretize(boundary, nelm)
    A, b = form_system(discrete_boundary)
    # Direct solve
    x = A\b
    u, q = form_vectors(x, discrete_boundary)
    pot_vals = field_values(u, q, discrete_boundary, field_points)
    return u, q, pot_vals
end
