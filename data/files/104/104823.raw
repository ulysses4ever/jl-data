# A first pass at programming the direct boundary element method (DBEM).
# For now, only constant elements are implemented.

include("BEMTypes.jl")
include("BEMModel.jl")

################################################################################
# Discretize the outer boundary. The methods for discretize() are determined
# by the type of shape function passed. The bcs array contains an expression
# to evaluate the boundary condition on each element as a function of x and y.
# There must be a boundary condition for each boundary segment i.e. the length
# of bcs must equal the length of boundary. The res array contains an integer
# representing the number of subdivisions wanted for each boundary segment.
# Future functionality should incorporate a better way to smoothly grade the
# boundary mesh as this current method can generate abrupt changes in mesh size.
################################################################################
function discretize!{T<:BoundarySegment}(mesh::Array{ConstantElement,1},
                     boundary::Array{T}, bcs::Array{BoundaryCondition,1},
                     res::Array{Int64})
    for i in 1:length(boundary)
        delta_x = boundary[i].p2.x - boundary[i].p1.x
        delta_y = boundary[i].p2.y - boundary[i].p1.y
        for j in 1:res[i]
            dx = delta_x/res[i]
            dy = delta_y/res[i]
            p1 = Point(boundary[i].p1.x + (j-1)*dx, boundary[i].p1.y + (j-1)*dy)
            p2 = Point(boundary[i].p1.x + j*dx, boundary[i].p1.y + j*dy)
            node = Point((p1.x + p2.x)/2.0, (p1.y + p2.y)/2.0)
            n = boundary[i].n
            bc_node = bcs[i]
            push!(mesh, ConstantElement(p1, p2, node, n, bc_node))
        end
    end
    return mesh
end

function discretize!{T<:BoundarySegment}(mesh::Array{LinearElement,1},
                     boundary::Array{T}, bcs_1::Array{BoundaryCondition},
                     bcs_2::Array{BoundaryCondition}, res::Array{Int64})
    for i in 1:length(boundary)
        delta_x = boundary[i].p2.x - boundary[i].p1.x
        delta_y = boundary[i].p2.y - boundary[i].p1.y
        for j in 1:res[i]
            dx = delta_x/res[i]
            dy = delta_y/res[i]
            p1 = Point(boundary[i].p1.x + (j-1)*dx, boundary[i].p1.y + (j-1)*dy)
            p2 = Point(boundary[i].p1.x + j*dx, boundary[i].p1.y + j*dy)
            n = boundary[i].n
            bc_1 = bcs_1[i]
            bc_2 = bcs_2[i]
            push!(mesh, LinearElement(p1, p2, n, bc_1, bc_2))
        end
    end
    return mesh
end

function discretize!{T<:BoundarySegment}(mesh::Array{QuadraticElement,1},
                     boundary::Array{T}, bcs_1::Array{BoundaryCondition},
                     bcs_node::Array{BoundaryCondition},
                     bcs_2::Array{BoundaryCondition}, res::Array{Int64})
    for i in 1:length(boundary)
        delta_x = boundary[i].p2.x - boundary[i].p1.x
        delta_y = boundary[i].p2.y - boundary[i].p1.y
        for j in 1:res[i]
            dx = delta_x/res[i]
            dy = delta_y/res[i]
            p1 = Point(boundary[i].p1.x + (j-1)*dx, boundary[i].p1.y + (j-1)*dy)
            p2 = Point(boundary[i].p1.x + j*dx, boundary[i].p1.y + j*dy)
            node = Point((p1.x + p2.x)/2.0, (p1.y + p2.y)/2.0)
            n = boundary[i].n
            bc_1 = bcs_1[i]
            bc_node = bcs_node[i]
            bc_2 = bcs_2[i]
            push!(mesh, QuadraticElement(p1, p2, node, n, bc_1, bc_node, bc_2))
        end
    end
    return mesh
end

# G kernel
function kernel_integral(coll::Point, element::ConstantElement,
                         ::PotentialKernel)
    # Geometry calculations
    r1_x = element.p1.x - coll.x
    r1_y = element.p1.y - coll.y
    r2_x = element.p2.x - coll.x
    r2_y = element.p2.y - coll.y
    R_x = r2_x - r1_x
    R_y = r2_y - r1_y
    r1_dot_R = r1_x*R_x + r1_y*R_y
    r2_dot_R = r2_x*R_x + r2_y*R_y
    R_dot_R = R_x^2 + R_y^2
    norm_r1 = sqrt(r1_x^2 + r1_y^2)
    norm_r2 = sqrt(r2_x^2 + r2_y^2)
    norm_R = sqrt(R_dot_R)

    T1 = r1_dot_R/norm_R
    T2 = r2_dot_R/norm_R
    d_x = r1_x - r1_dot_R/R_dot_R*R_x
    d_y = r1_y - r1_dot_R/R_dot_R*R_y
    norm_d = sqrt(d_x^2 + d_y^2)
    theta1 = asin(r1_dot_R/(norm_r1*norm_R))
    theta2 = asin(r2_dot_R/(norm_r2*norm_R))
    return 1/(2*pi)*(-1*(theta2 - theta1)*norm_d +
           abs(T2 - T1) - T2*log(norm_r2) + T1*log(norm_r1))
end

# F kernel
function kernel_integral(coll::Point, element::ConstantElement,
                         ::FluxKernel)
    # Geometry calculations
    r1_x = element.p1.x - coll.x
    r1_y = element.p1.y - coll.y
    r2_x = element.p2.x - coll.x
    r2_y = element.p2.y - coll.y
    R_x = r2_x - r1_x
    R_y = r2_y - r1_y
    r1_dot_R = r1_x*R_x + r1_y*R_y
    r2_dot_R = r2_x*R_x + r2_y*R_y
    R_dot_R = R_x^2 + R_y^2
    norm_r1 = sqrt(r1_x^2 + r1_y^2)
    norm_r2 = sqrt(r2_x^2 + r2_y^2)
    norm_R = sqrt(R_dot_R)

    theta1 = asin(r1_dot_R/(norm_r1*norm_R))
    theta2 = asin(r2_dot_R/(norm_r2*norm_R))
    return -1/(2*pi)*(theta2 - theta1)
end

#function kernel_integral(coll::Point, element::LinearElement,
#                         kernel::PotentialKernel)
#end

#function kernel_integral(coll::Point, element::LinearElement,
#                         kernel::FluxKernel)
#end

#function kernel_integral(coll::Point, element::QuadraticElement,
#                         kernel::PotentialKernel)
#end

#function kernel_integral(coll::Point, element::QuadraticElement,
#                         kernel::FluxKernel)
#end

function build_system(mesh::Array{ConstantElement,1}, A::Array{Float64,2},
                      B::Array{Float64,2}, bc_vec::Array{Float64,1})
    n = length(mesh)
    for i in 1:n
        coll = mesh[i].node
        bc_vec[i] = mesh[i].bc_node.val
        for j in 1:n
            if typeof(mesh[j].bc_node) <: Dirichlet
                A[i,j] = -1.0*kernel_integral(coll, mesh[j], FluxKernel())
                B[i,j] = -1.0*kernel_integral(coll, mesh[j], PotentialKernel())
                if i == j
                    A[i,j] += 0.5
                end
            else
                A[i,j] = kernel_integral(coll, mesh[j], PotentialKernel())
                B[i,j] = kernel_integral(coll, mesh[j], FluxKernel())
                if i == j
                    B[i,j] -= 0.5
                end
            end
        end
    end
    b = B*bc_vec
    return A, b
end

function boundary_values!(u::Array{Float64}, q::Array{Float64},
                          x::Array{Float64}, mesh::Array{ConstantElement,1})
    n = length(mesh)
    for i in 1:n
        if typeof(mesh[i].bc_node) <: Dirichlet
            u[i] = mesh[i].bc_node.val
            q[i] = x[i]
        else
            u[i] = x[i]
            q[i] = mesh[i].bc_node.val
        end
    end
    return u, q
end

function field_values!(u_field::Array{Float64,2}, u_point::Array{Point,2},
                       u::Array{Float64}, q::Array{Float64},
                       mesh::Array{ConstantElement,1})
    n1 = size(u_point)[1]
    n2 = size(u_point)[2]
    m = length(mesh)
    for i in 1:n1
        for j in 1:n2
            coll = u_point[i,j]
            u_sum = 0.0
            q_sum = 0.0
            for k in 1:m
                u_sum += u[k]*kernel_integral(coll, mesh[k], FluxKernel())
                q_sum += q[k]*kernel_integral(coll, mesh[k], PotentialKernel())
            end
            u_field[i,j] = u_sum - q_sum
        end
    end
    return u_field
end

function dbem(m)
    bndy, u_point = model()
    bc1 = Dirichlet(0.0)
    bc2 = Dirichlet(100.0)
    bc3 = Neumann(0.0)
    bcs = [bc1, bc3, bc2, bc3]
    res = [m, m, m, m]
    mesh = ConstantElement[]
    mesh = discretize!(mesh, bndy, bcs, res)

    n = length(mesh)
    A = Array{Float64}(n,n)
    B = Array{Float64}(n,n)
    bc_vec = Array{Float64}(n)
    A, b = build_system(mesh, A, B, bc_vec)
    x = A\b
    #u = Array{Float64}(n)
    #q = Array{Float64}(n)
    #u, q = boundary_values!(u, q, x, mesh)
    #u_field = Array{Float64}(size(u_point))
    #u_field = field_values!(u_field, u_point, u, q, mesh)
    #return u_field, u, q
end
