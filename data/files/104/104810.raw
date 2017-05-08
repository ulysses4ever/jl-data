################################################################################
# Define the geometry of the model. For now, this is directly input here.
# Later on, this will read from a file and return a list of geometry points
# that define the model boundary.
################################################################################
function model()
    # Outer boundary points
    p1 = Point(0.0, 0.0)
    p2 = Point(1.0, 0.0)
    p3 = Point(1.0, 2.0)
    p4 = Point(0.0, 2.0)

    # Boundary segments
    n1 = [p2.y - p1.y, p1.x - p2.x]/norm([p2.y - p1.y, p1.x - p2.x])
    n2 = [p3.y - p2.y, p2.x - p3.x]/norm([p3.y - p2.y, p2.x - p3.x])
    n3 = [p4.y - p3.y, p3.x - p4.x]/norm([p4.y - p3.y, p3.x - p4.x])
    n4 = [p1.y - p4.y, p4.x - p1.x]/norm([p1.y - p4.y, p4.x - p1.x])
    b1 = BoundarySegment(p1, p2, n1)
    b2 = BoundarySegment(p2, p3, n2)
    b3 = BoundarySegment(p3, p4, n3)
    b4 = BoundarySegment(p4, p1, n4)

    # Post processing field points
    n = 10
    dy = 2.0/(n + 1)
    dx = 1.0/(n + 1)
    u_point = Point[]
    for j in 1:n
        u_point_col = Point[]
        for i in 1:n
            push!(u_point_col, Point(i*dx, j*dy))
        end
        if j == 1
            u_point = u_point_col
        else
            u_point = hcat(u_point, u_point_col)
        end
    end
    return [b1, b2, b3, b4], u_point
end
