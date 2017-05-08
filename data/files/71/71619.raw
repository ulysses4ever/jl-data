type Point
    x
    y
end

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

function test()
    p1 = Point(1, 1)
    q1 = Point(10, 1)
    p2 = Point(1, 2)
    q2 = Point(10, 2)

    doIntersect(p1, q1, p2, q2)?println("Yes"):println("No")

    p1 = Point(10, 0)
    q1 = Point(0, 10)
    p2 = Point(0, 0)
    q2 = Point(10, 10)

    doIntersect(p1, q1, p2, q2)?println("Yes"):println("No")

    p1 = Point(-5, -5)
    q1 = Point(0, 0)
    p2 = Point(1, 1)
    q2 = Point(10, 10)

    doIntersect(p1, q1, p2, q2)?println("Yes"):println("No")
end
