# A first pass at programming the direct boundary element method (DBEM).
# For now, only constant elements are implemented.

using FastGaussQuadrature
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

function get_nodes(segment::Simplex, order::Int64)
    if order == 1 # Constant element special case
        nodes = Node((segment[1] + segment[2])/2.0)
    else
        delta = (segment[2] - segment[1])/(order - 1)
        points = Point[]
        for i in 1:order
            push!(points, Point(segment[1] + (i - 1)*delta))
        end
        nodes = Node(points...)
    end
end

function discretize(model::Model, res::Array{Int64})
    elements = BoundaryElement[]
    bc_ids = Int64[]
    connectivity = Connect[]
    for i in 1:length(res)
        delta = model.vertices[model.faces[i]][2] -
                model.vertices[model.faces[i]][1]
        id = model.bcids[i]
        for j in 1:res[i]
            p1 = model.vertices[model.faces[i]][1] + (j - 1)/res[i]*delta
            p2 = model.vertices[model.faces[i]][1] + j/res[i]*delta
            segment = Simplex(p1, p2)
            nodes = get_nodes(segment, model.element_order)
            normal = model.normals[i]
            push!(elements, BoundaryElement(segment, nodes, normal))
            push!(bc_ids, id)
            if length(elements) == 1
                push!(connectivity, Connect(sum(res), 2))
            elseif length(elements) == sum(res)
                push!(connectivity, Connect(sum(res) - 1, 1))
            else
                push!(connectivity, Connect(length(elements) - 1,
                                            length(elements) + 1))
            end
        end
    end
    dis_model = DiscreteBoundary(elements, connectiviy, bc_ids, model.bcs)
    return dis_model
end

# G kernel
#function kernel_integral(coll::Point, element::ConstantElement,
#                         ::PotentialKernel)
#    # Geometry calculations
#    r1_x = element.p1.x - coll.x
#    r1_y = element.p1.y - coll.y
#    r2_x = element.p2.x - coll.x
#    r2_y = element.p2.y - coll.y
#    R_x = r2_x - r1_x
#    R_y = r2_y - r1_y
#    r1_dot_R = r1_x*R_x + r1_y*R_y
#    r2_dot_R = r2_x*R_x + r2_y*R_y
#    R_dot_R = R_x^2 + R_y^2
#    norm_r1 = sqrt(r1_x^2 + r1_y^2)
#    norm_r2 = sqrt(r2_x^2 + r2_y^2)
#    norm_R = sqrt(R_dot_R)

#    T1 = r1_dot_R/norm_R
#    T2 = r2_dot_R/norm_R
#    d_x = r1_x - r1_dot_R/R_dot_R*R_x
#    d_y = r1_y - r1_dot_R/R_dot_R*R_y
#    norm_d = sqrt(d_x^2 + d_y^2)
#    theta1 = asin(r1_dot_R/(norm_r1*norm_R))
#    theta2 = asin(r2_dot_R/(norm_r2*norm_R))
#    return 1/(2*pi)*(-1*(theta2 - theta1)*norm_d +
#           abs(T2 - T1) - T2*log(norm_r2) + T1*log(norm_r1))
#end

# F kernel
#function kernel_integral(coll::Point, element::ConstantElement,
#                         ::FluxKernel)
    # Geometry calculations
#    r1_x = element.p1.x - coll.x
#    r1_y = element.p1.y - coll.y
#    r2_x = element.p2.x - coll.x
#    r2_y = element.p2.y - coll.y
#    R_x = r2_x - r1_x
#    R_y = r2_y - r1_y
#    r1_dot_R = r1_x*R_x + r1_y*R_y
#    r2_dot_R = r2_x*R_x + r2_y*R_y
#    R_dot_R = R_x^2 + R_y^2
#    norm_r1 = sqrt(r1_x^2 + r1_y^2)
#    norm_r2 = sqrt(r2_x^2 + r2_y^2)
#    norm_R = sqrt(R_dot_R)

#    theta1 = asin(r1_dot_R/(norm_r1*norm_R))
#    theta2 = asin(r2_dot_R/(norm_r2*norm_R))
#    return -1/(2*pi)*(theta2 - theta1)
#end

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

#function build_system(mesh::Array{ConstantElement,1}, A::Array{Float64,2},
#                      B::Array{Float64,2}, bc_vec::Array{Float64,1})
#    n = length(mesh)
#    for i in 1:n
#        coll = mesh[i].node
#        bc_vec[i] = mesh[i].bc_node.val
#        for j in 1:n
#            if typeof(mesh[j].bc_node) <: Dirichlet
#                A[i,j] = -1.0*kernel_integral(coll, mesh[j], FluxKernel())
#                B[i,j] = -1.0*kernel_integral(coll, mesh[j], PotentialKernel())
#                if i == j
#                    A[i,j] += 0.5
#                end
#            else
#                A[i,j] = kernel_integral(coll, mesh[j], PotentialKernel())
#                B[i,j] = kernel_integral(coll, mesh[j], FluxKernel())
#                if i == j
#                    B[i,j] -= 0.5
#                end
#            end
#        end
#    end
#    b = B*bc_vec
#    return A, b
#end

#function boundary_values!(u::Array{Float64}, q::Array{Float64},
#                          x::Array{Float64}, mesh::Array{ConstantElement,1})
#    n = length(mesh)
#    for i in 1:n
#        if typeof(mesh[i].bc_node) <: Dirichlet
#            u[i] = mesh[i].bc_node.val
#            q[i] = x[i]
#        else
#            u[i] = x[i]
#            q[i] = mesh[i].bc_node.val
#        end
#    end
#    return u, q
#end

#function field_values!(u_field::Array{Float64,2}, u_point::Array{Point,2},
#                       u::Array{Float64}, q::Array{Float64},
#                       mesh::Array{ConstantElement,1})
#    n1 = size(u_point)[1]
#    n2 = size(u_point)[2]
#    m = length(mesh)
#    for i in 1:n1
#        for j in 1:n2
#            coll = u_point[i,j]
#            u_sum = 0.0
#            q_sum = 0.0
#            for k in 1:m
#                u_sum += u[k]*kernel_integral(coll, mesh[k], FluxKernel())
#                q_sum += q[k]*kernel_integral(coll, mesh[k], PotentialKernel())
#            end
#            u_field[i,j] = u_sum - q_sum
#        end
#    end
#    return u_field
#end

#function dbem(m)
#    bndy, u_point = model()
#    bc1 = Dirichlet(0.0)
#    bc2 = Dirichlet(100.0)
#    bc3 = Neumann(0.0)
#    bcs = [bc1, bc3, bc2, bc3]
#    res = [m, m, m, m]
#    mesh = ConstantElement[]
#    mesh = discretize!(mesh, bndy, bcs, res)

#    n = length(mesh)
#    A = Array{Float64}(n,n)
#    B = Array{Float64}(n,n)
#    bc_vec = Array{Float64}(n)
#    A, b = build_system(mesh, A, B, bc_vec)
#    x = A\b
    #u = Array{Float64}(n)
    #q = Array{Float64}(n)
    #u, q = boundary_values!(u, q, x, mesh)
    #u_field = Array{Float64}(size(u_point))
    #u_field = field_values!(u_field, u_point, u, q, mesh)
    #return u_field, u, q
#end
