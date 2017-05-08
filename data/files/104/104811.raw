include("BEMTypes.jl")

################################################################################
# Define the geometry of the model. For now, this is directly input here.
# Later on, this will read from a file and return a list of geometry points
# that define the model boundary.
################################################################################
function normal(p::Tuple)
    dx = p[2][1] - p[1][1]
    dy = p[2][2] - p[1][2]
    n = Normal(dy, -1.0*dx)/norm(Normal(dy, -1.0*dx))
    return n
end

function make_model(element_order)
    # Outer boundary points
    p1 = Point(0.0, 0.0)
    p2 = Point(1.0, 0.0)
    p3 = Point(1.0, 2.0)
    p4 = Point(0.0, 2.0)
    vertices = Point[p1, p2, p3, p4]

    # Node ordering
    n1 = Node(1)
    n2 = Node(2)
    n3 = Node(3)
    n4 = Node(4)
    nodes = Node[n1, n2, n3, n4]

    # Boundary faces
    f1 = Face(1, 2)
    f2 = Face(2, 3)
    f3 = Face(3, 4)
    f4 = Face(4, 1)
    faces = Face[f1, f2, f3, f4]

    # Point connectivity.
    c1 = Connect(1, 4)
    c2 = Connect(1, 3)
    c3 = Connect(2, 4)
    c4 = Connect(4, 1)
    connectivity = Connect[c1, c2, c3, c4]

    # Boundary normals
    normals = Normal[]
    for i in 1:length(faces)
        push!(normals, normal(vertices[faces[i]]))
    end

    # Boundary conditions
    homogeneous(p::Point) = 0.0
    hot(p::Point) = 100.0
    bc1 = Dirichlet(homogeneous)
    bc2 = Neumann(homogeneous)
    bc3 = Dirichlet(hot)
    bcs = BoundaryCondition[bc1, bc2, bc3]

    # Boundary condition ids, faces[i] corresponds to bcids[i].
    bcids = [1, 2, 3, 2]

    # Post processing field points
    n = 10
    dy = 2.0/(n + 1)
    dx = 1.0/(n + 1)
    u_point = Point[]
    for j in 1:n
        for i in 1:n
            push!(u_point, Point(i*dx, j*dy))
        end
    end

    model = Model(vertices, faces, connectivity, normals, bcids, bcs,
                  u_point, element_order)
    return model
end
