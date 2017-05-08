type Point
    x
    y
end

# 代表与已知点组成无限长线段的无限远点
const INF = 10000

# Given three colinear points p, q, r, the function checks if
# point q lies on line segment 'pr'
function onSegment(p::Point, q::Point, r::Point)
    if q.x>=min(p.x,r.x) && q.x<=max(p.x,r.x) &&
        q.y>=min(p.y,r.y) && q.y<=max(p.y,r.x)
        return true
    else
        return false
    end
end

# To find orientation of ordered triplet (p, q, r).
# The function returns following values
# 0 --> p, q and r are colinear
# 1 --> Clockwise
# 2 --> Counterclockwise
function orientation(p::Point, q::Point, r::Point)
    val = (q.y-p.y)*(r.x-q.x) - (q.x-p.x)*(r.y-q.y)
    # colinear
    if val==0
        return 0
    elseif val>0
        return 1
    else
        return 2
    end
end

# The main function that returns true if line segment 'p1q1'
# and 'p2q2' intersect.
function doIntersect(p1::Point, q1::Point, p2::Point, q2::Point)
    # Find the four orientations needed for general and
    # special cases
    o1 = orientation(p1, q1, p2)
    o2 = orientation(p1, q1, q2)
    o3 = orientation(p2, q2, p1)
    o4 = orientation(p2, q2, q1)

    # General case
    if o1!=o2 && o3!=o4
        return true
    end

    # Special Cases
    # p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if o1==0 && onSegment(p1, p2, q1)
        return true
    end
    # p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if o2==0 && onSegment(p1, q2, q1)
        return true
    end
    # p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if o3==0 && onSegment(p2, p1, q2)
        return true
    end
    # p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if o4==0 && onSegment(p2, q1, q2)
        return true
    end

    return false
end

# Returns true if the point p lies inside the polygon[] with n vertices
function isInside(poly::Array{Point}, p::Point)
    # There must be at least 3 vertices in polygon[]
    n = length(poly)
    if n<3 return false end

    # Create a point for line segment from p to infinite
    extreme = Point(INF, p.y)

    # Count intersections of the above line with sides of polygon
    count = 0
    for i=0:n-1
        # 利用求余算法获得所有边的索引
        # 求余算法具有天然的循环特性，可实现闭合多边形的顺序顶点编号循环
        next = (i+1)%n

        # Check if the line segment from 'p' to 'extreme' intersects
        # with the line segment from 'polygon[i]' to 'polygon[next]'
        if doIntersect(poly[i+1], poly[next+1], p, extreme)
            # If the point 'p' is colinear with line segment 'i-next',
            # then check if it lies on segment. If it lies, return true,
            # otherwise false
            if orientation(poly[i+1], p, poly[next+1]) == 0
                return onSegment(poly[i+1], p, poly[next+1])
            end

            count+=1
        end
    end

    # Return true if count is odd, false otherwise
    return count%2 == 1
end


function test()
    poly = [Point(0, 0),Point(10, 0),
            Point(10, 10),Point(0, 10)]

    p = Point(20,20)
    isInside(poly, p)?println("Yes"):println("No")

    p = Point(5,5)
    isInside(poly, p)?println("Yes"):println("No")

    p = Point(3,3)
    isInside(poly, p)?println("Yes"):println("No")

    p = Point(5,1)
    isInside(poly, p)?println("Yes"):println("No")

    p = Point(-1,10)
    isInside(poly, p)?println("Yes"):println("No")
end
