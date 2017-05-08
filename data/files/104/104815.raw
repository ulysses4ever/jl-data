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
    bc_side = BoundaryCondition{Neumann}(0.0)
    bc_top = BoundaryCondition{Dirichlet}(100.0)

    # The boundary segments need to be closed
    s1 = BoundarySegment(p1, p2, bc_bottom)
    s2 = BoundarySegment(p2, p3, bc_side)
    s3 = BoundarySegment(p3, p4, bc_top)
    s4 = BoundarySegment(p4, p1, bc_side)

    boundary = [s1, s2, s3, s4]

    return boundary
end

# Discretize the boundary. The first argment is the model boundary and the
# second argument is the number of boundary elements wanted on each boundary
# segment. For example, if n_elm[1] = 10, the first boundary segment will be
# partitioned into 10 uniform elements. The length of n_elm must equal the
# length of boundary.

function discretize(boundary::Array{BoundarySegment}, n_elm::Array{Int64})
    discrete_boundary = Array{BoundaryElement}(sum(n_elm))
    i = 1 # Current boundary element number
    j = 1 # Current boundary element number
    for segment in boundary
        n = n_elm[i] # Number of boundary elements on segment
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
            k += 1
            j += 1
        end
        i += 1
    end

    return discrete_boundary
end

# For constant boundary elements, we can analystically compute the required
# integrals
function kernel_integral(source::Point, field::BoundaryElement{Dirichlet})
    # Linear equation for boundary element: ax + by + c = 0
    a = field.p2.y - field.p1.y
    b = field.p2.x - field.p1.x
    c = field.p2.x*field.p1.y - field.p2.y*field.p1.x

    # Perpendicular distance between boundary element and source point
    d = abs(a*source.x + b*source.y + c)/sqrt(a^2 + b^2)

    # Projection of source point onto boundary element line
    proj_x = (b*(b*source.x - a*source.y) - a*c)/(a^2 + b^2)
    proj_y = (a*(a*source.y - b*source.x) - b*c)/(a^2 + b^2)

    # Distance between the boundary element end points and the projected point.
    # We want to take into account the sign.
    T1_magnitude = sqrt((field.p1.x - proj_x)^2 + (field.p1.y - projy)^2)
    T2_magnitude = sqrt((field.p2.x - proj_x)^2 + (field.p2.y - projy)^2)
     
end

function kernel_integral(source::Point, field::BoundaryElement{Neumann})
end
