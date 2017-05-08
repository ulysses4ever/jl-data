# Functions for calculating exact overlap between shapes.
#
# Original cython version by Thomas Robitaille released under a
# 3-clause BSD-style license.

# Return area of a circle arc between (x1, y1) and (x2, y2) with radius r
# reference: http://mathworld.wolfram.com/CircularSegment.html
function area_arc(x1, y1, x2, y2, r)
  a = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))
  theta = 2. * asin(0.5 * a / r)
  return 0.5 * r * r * (theta - sin(theta))
end

# Area of a triangle defined by three verticies
area_triangle(x1, y1, x2, y2, x3, y3) =
    0.5 * abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2))

# Core of circular overlap routine.
# Assumes that xmax >= xmin >= 0.0, ymax >= ymin >= 0.0.
# (can always modify input to conform to this).
function circoverlap_core(xmin, ymin, xmax, ymax, r)

  xmin2 = xmin * xmin
  ymin2 = ymin * ymin
  r2 = r * r
  (xmin2 + ymin2 > r2) && return 0.0

  xmax2 = xmax * xmax
  ymax2 = ymax * ymax
  (xmax2 + ymax2 < r2) && return (xmax-xmin) * (ymax-ymin)

  a = xmax2 + ymin2  # (corner 1 distance)^2
  b = xmin2 + ymax2  # (corner 2 distance)^2

  if (a < r2 && b < r2)
      x1 = sqrt(r2 - ymax2)
      y1 = ymax
      x2 = xmax
      y2 = sqrt(r2 - xmax2)
      return ((xmax - xmin) * (ymax - ymin) -
	      area_triangle(x1, y1, x2, y2, xmax, ymax) +
	      area_arc(x1, y1, x2, y2, r))

  elseif (a < r2)
      x1 = xmin
      y1 = sqrt(r2 - xmin2)
      x2 = xmax
      y2 = sqrt(r2 - xmax2)
      return (area_arc(x1, y1, x2, y2, r) +
	      area_triangle(x1, y1, x1, ymin, xmax, ymin) +
	      area_triangle(x1, y1, x2, ymin, x2, y2))

  elseif (b < r2)
      x1 = sqrt(r2 - ymin2)
      y1 = ymin
      x2 = sqrt(r2 - ymax2)
      y2 = ymax
      return (area_arc(x1, y1, x2, y2, r) +
	      area_triangle(x1, y1, xmin, y1, xmin, ymax) +
	      area_triangle(x1, y1, xmin, y2, x2, y2))

  else
      x1 = sqrt(r2 - ymin2)
      y1 = ymin
      x2 = xmin
      y2 = sqrt(r2 - xmin2)
      return (area_arc(x1, y1, x2, y2, r) +
              area_triangle(x1, y1, x2, y2, xmin, ymin))
  end
end


# Area of overlap of a rectangle and a circle
function circoverlap(xmin, ymin, xmax, ymax, r)

  # some subroutines demand that r > 0
  (r <= 0.0) && return 0.0

  if (0.0 <= xmin)
      (0.0 <= ymin) && return circoverlap_core(xmin, ymin, xmax, ymax, r)
      (0.0 >= ymax) && return circoverlap_core(-ymax, xmin, -ymin, xmax, r)
      return (circoverlap(xmin, ymin, xmax, 0.0, r) +
              circoverlap(xmin, 0.0, xmax, ymax, r))

  elseif (0.0 >= xmax)
      (0.0 <= ymin) && return circoverlap_core(-xmax, ymin, -xmin, ymax, r)
      (0.0 >= ymax) && return circoverlap_core(-xmax, -ymax, -xmin, -ymin, r)
      return (circoverlap(xmin, ymin, xmax, 0.0, r) +
              circoverlap(xmin, 0.0, xmax, ymax, r))

  else
      (0.0 <= ymin) && return (circoverlap(xmin, ymin, 0.0, ymax, r) +
                              circoverlap(0.0, ymin, xmax, ymax, r))
      (0.0 >= ymax) && return (circoverlap(xmin, ymin, 0.0, ymax, r) +
                              circoverlap(0.0, ymin, xmax, ymax, r))
      return (circoverlap(xmin, ymin, 0.0, 0.0, r) +
              circoverlap(0.0, ymin, xmax, 0.0, r) +
              circoverlap(xmin, 0.0, 0.0, ymax, r) +
              circoverlap(0.0, 0.0, xmax, ymax, r))
  end
end


# -----------------------------------------------------------------------------
# ellipse-rectangle overlap

# internal types
immutable Point
    x::Float64
    y::Float64
end

immutable Intersections
    p1::Point
    p2::Point
end

# rotate -> a, b, c = b, c, a

# Check if a point (x,y) is inside a triangle
function in_triangle(x, y, x1, x2, y2, x3, y3)
    c = 0
    c += ((y1 > y) != (y2 > y)) && (x < (x2-x1) * (y-y1) / (y2-y1) + x1)
    c += ((y2 > y) != (y3 > y)) && (x < (x3-x2) * (y-y2) / (y3-y2) + x2)
    c += ((y3 > y) != (y1 > y)) && (x < (x1-x3) * (y-y3) / (y1-y3) + x3)

    return c % 2 == 1
end


# Intersection of a line defined by two points with a unit circle
function circle_line(x1, y1, x2, y2)

    tol = 1.e-10

    dx = x2 - x1
    dy = y2 - y1

    if abs(dx) < tol && abs(dy) < tol
        return Intersections(Point(2.0, 2.0), Point(2.0, 2.0))

    elseif abs(dx) > abs(dy)

        # Find the slope and intercept of the line
        a = dy / dx
        b = y1 - a * x1

        # Find the determinant of the quadratic equation
        delta = 1.0 + a*a - b*b
        if (delta > 0.)  # solutions exist
	    delta = sqrt(delta)
            p1x = (-a*b - delta) / (1. + a*a)
            p2x = (-a*b + delta) / (1. + a*a)
            return Intersections(Point(p1x, a * p1x + b),
                                 Point(p2x, a * p2x + b))
        else             # no solutions exist
            return Intersections(Point(2.0, 2.0), Point(2.0, 2.0))
        end

    else

        # Find the slope and intercept of the line
        a = dx / dy
        b = x1 - a * y1

        # Find the determinant of the quadratic equation
        delta = 1.0 + a*a - b*b
        if (delta > 0.)  # solutions exist
	    delta = sqrt(delta)
	    p1y = (-a*b - delta) / (1. + a*a)
            p2y = (-a*b + delta) / (1.0 + a*a)
            return Intersections(Point(a * p1y + b, p1y),
                                 Point(a * p2y + b, p2y))
        else  # no solution, return values > 1
            return Intersections(Point(2.0, 2.0), Point(2.0, 2.0))
        end
    end
end


# The intersection of a line with the unit circle. The intersection
# closest to (x2, y2) is chosen.
function circle_segment_single2(x1, y1, x2, y2)
    inter = circle_line(x1, y1, x2, y2)

    dx1 = abs(inter.p1.x - x2)
    dy1 = abs(inter.p1.y - y2)
    dx2 = abs(inter.p2.x - x2)
    dy2 = abs(inter.p2.y - y2)

    if (dx1 > dy1)  # compare based on x-axis
        return (dx1 > dx2) ? inter.pt2 : inter.pt1
    else
        return (dy1 > dy2) ? inter.pt2 : inter.pt1
    end
end

# Intersection(s) of a segment with the unit circle. Discard any
# solution not on the segment.
function circle_segment(x1, y1, x2, y2)
    inter = circle_line(x1, y1, x2, y2)
    pt1 = inter.p1
    pt2 = inter.p2

    if ((pt1.x > x1 && pt1.x > x2) || (pt1.x < x1 && pt1.x < x2) ||
        (pt1.y > y1 && pt1.y > y2) || (pt1.y < y1 && pt1.y < y2))
        pt1 = Point(2.0, 2.0)
    end

    if ((pt2.x > x1 && pt2.x > x2) || (pt2.x < x1 && pt2.x < x2) ||
        (pt2.y > y1 && pt2.y > y2) || (pt2.y < y1 && pt2.y < y2))
        pt2 = Point(2.0, 2.0)
    end

    if pt1.x > 1. && pt2.x < 2.
        return Intersections(pt1, pt2)
    else
        return Intersections(pt2, pt1)
    end
end


# Given a triangle defined by three points (x1, y1), (x2, y2), and
# (x3, y3), find the area of overlap with the unit circle.
function triangle_unitcircle_overlap(x1, y1, x2, y2, x3, y3)

    # Find distance of all vertices to circle center
    d1 = x1*x1 + y1*y1
    d2 = x2*x2 + y2*y2
    d3 = x3*x3 + y3*y3

    # Order vertices by distance from origin
    if (d1 < d2)
        
        if (d2 < d3)

        elseif (d1 < d3)
	    x2, x3 = x3, x2
            y2, y3 = y3, y2
            d2, d3 = d3, d2

        else
            # rotate -> a, b, c = b, c, a
            x1, x2, x3 = x3, x1, x2
            y1, y2, y3 = y3, y1, y2
            d1, d2, d3 = d3, d1, d2
        end
    else
        if d1 < d3
            x1, x2 = x2, x1
            y1, y2 = y2, y1
            d1, d2 = d2, d1
        elseif d2 < d3
            x1, x2, x3 = x2, x3, x1
            y1, y2, y3 = y2, y3, y1
            d1, d2, d3 = d2, d3, d1
        else
            x1, x3 = x3, x1
            y1, y3 = y3, y1
            d1, d3 = d3, d1
        end
    end
     
    # Determine number of vertices inside circle
    in1 = d1 < 1.0
    in2 = d2 < 1.0
    in3 = d3 < 1.0

    # Determine which vertices are on the circle
    on1 = abs(d1 - 1.0) < 1e-10
    on2 = abs(d2 - 1.0) < 1e-10
    on3 = abs(d3 - 1.0) < 1e-10

    if (on3 || in3)  # triangle completely within circle
        area = area_triangle(x1, y1, x2, y2, x3, y3)

    elseif (in2 || on2)
        # If vertex 1 or 2 are on the edge of the circle, then we use
        # the dot product to vertex 3 to determine whether an
        # intersection takes place.
        intersect13 = !on1 || (x1*(x3-x1) + y1*(y3-y1) < 0.0)
        intersect23 = !on2 || (x2*(x3-x2) + y2*(y3-y2) < 0.0)

        if (intersect13 && intersect23)
	    pt1 = circle_segment_single2(x1, y1, x3, y3)
	    pt2 = circle_segment_single2(x2, y2, x3, y3)
	    area = (area_triangle(x1, y1, x2, y2, pt1.x, pt1.y) +
		    area_triangle(x2, y2, pt1.x, pt1.y, pt2.x, pt2.y) +
		    area_arc(pt1.x, pt1.y, pt2.x, pt2.y, 1.0))
        elseif (intersect13)
	  pt1 = circle_segment_single2(x1, y1, x3, y3)
	  area = (area_triangle(x1, y1, x2, y2, pt1.x, pt1.y) +
		  area_arc(x2, y2, pt1.x, pt1.y, 1.0))
        elseif (intersect23)
	  pt2 = circle_segment_single2(x2, y2, x3, y3)
	  area = (area_triangle(x1, y1, x2, y2, pt2.x, pt2.y) +
		  area_arc(x1, y1, pt2.x, pt2.y, 1.0))
        else
	    area = area_arc(x1, y1, x2, y2, 1.0)
        end

    elseif in1
        # Check for intersections of far side with circle
        inter = circle_segment(x2, y2, x3, y3)
        pt1 = inter.p1
        pt2 = inter.p2
        pt3 = circle_segment_single2(x1, y1, x2, y2)
        pt4 = circle_segment_single2(x1, y1, x3, y3)

        if pt1.x > 1.0  # indicates no intersection
	
	    # check if the pixel vertex (x1, y2) and the origin are on
	    # different sides of the circle segment. If they are, the
	    # circle segment spans more than pi radians.
	    # We use the formula (y-y1) * (x2-x1) > (y2-y1) * (x-x1)
	    # to determine if (x, y) is on the left of the directed
	    # line segment from (x1, y1) to (x2, y2)
	    if (((0.-pt3.y) * (pt4.x-pt3.x) > (pt4.y-pt3.y) * (0.-pt3.x)) !=
	        ((y1-pt3.y) * (pt4.x-pt3.x) > (pt4.y-pt3.y) * (x1-pt3.x)))
	        area = (area_triangle(x1, y1, pt3.x, pt3.y, pt4.x, pt4.y) +
		        pi - area_arc(pt3.x, pt3.y, pt4.x, pt4.y, 1.0))
	    else
	        area = (area_triangle(x1, y1, pt3.x, pt3.y, pt4.x, pt4.y) +
		        area_arc(pt3.x, pt3.y, pt4.x, pt4.y, 1.0))
	    end
        else
            # ensure that pt1 is the point closest to (x2, y2)
	    if (((pt2.x-x2)*(pt2.x-x2) + (pt2.y-y2)*(pt2.y-y2)) <
	        ((pt1.x-x2)*(pt1.x-x2) + (pt1.y-y2)*(pt1.y-y2)))
                pt1, pt2 = pt2, pt2
            end
	    area = (area_triangle(x1, y1, pt3.x, pt3.y, pt1.x, pt1.y) +
		    area_triangle(x1, y1, pt1.x, pt1.y, pt2.x, pt2.y) +
		    area_triangle(x1, y1, pt2.x, pt2.y, pt4.x, pt4.y) +
		    area_arc(pt1.x, pt1.y, pt3.x, pt3.y, 1.0) +
		    area_arc(pt2.x, pt2.y, pt4.x, pt4.y, 1.0))
	end

    else
        inter = circle_segment(x1, y1, x2, y2)
        pt1 = inter.p1
        pt2 = inter.p2
        inter = circle_segment(x2, y2, x3, y3)
        pt3 = inter.p1
        pt4 = inter.p2
        inter = circle_segment(x3, y3, x1, y1)
        pt5 = inter.p1
        pt6 = inter.p2

        if (pt1.x <= 1.0)
	    xp = 0.5 * (pt1.x + pt2.x)
	    yp = 0.5 * (pt1.y + pt2.y)
	    area = (triangle_unitcircle_overlap(x1, y1, x3, y3, xp, yp) +
		    triangle_unitcircle_overlap(x2, y2, x3, y3, xp, yp))

        elseif (pt3.x <= 1.)
	    xp = 0.5 * (pt3.x + pt4.x)
	    yp = 0.5 * (pt3.y + pt4.y)
	    area = (triangle_unitcircle_overlap(x3, y3, x1, y1, xp, yp) +
		    triangle_unitcircle_overlap(x2, y2, x1, y1, xp, yp))

        elseif (pt5.x <= 1.)
	    xp = 0.5 * (pt5.x + pt6.x)
	    yp = 0.5 * (pt5.y + pt6.y)
	    area = (triangle_unitcircle_overlap(x1, y1, x2, y2, xp, yp) +
		    triangle_unitcircle_overlap(x3, y3, x2, y2, xp, yp))

        else  # no intersections
	  return in_triangle(0., 0., x1, y1, x2, y2, x3, y3) ? pi : 0.0
        end
    end

    return area
end

# exact overlap between a rectangle defined by (xmin, ymin, xmax,
# ymax) and an ellipse with major and minor axes rx and ry
# respectively and position angle theta.
function ellipoverlap(xmin, ymin, xmax, ymax, a, b, theta)
    cos_m_theta = cos(-theta)
    sin_m_theta = sin(-theta)

    scale = a * b  # areas will be shrunk by this scale

    # Reproject rectangle to a frame in which ellipse is a unit circle
    x1 = (xmin * cos_m_theta - ymin * sin_m_theta) / a
    y1 = (xmin * sin_m_theta + ymin * cos_m_theta) / b
    x2 = (xmax * cos_m_theta - ymin * sin_m_theta) / a
    y2 = (xmax * sin_m_theta + ymin * cos_m_theta) / b
    x3 = (xmax * cos_m_theta - ymax * sin_m_theta) / a
    y3 = (xmax * sin_m_theta + ymax * cos_m_theta) / b
    x4 = (xmin * cos_m_theta - ymax * sin_m_theta) / a
    y4 = (xmin * sin_m_theta + ymax * cos_m_theta) / b

    # Divide resulting quadrilateral into two triangles and find
    # intersection with unit circle
    return scale * (triangle_unitcircle_overlap(x1, y1, x2, y2, x3, y3) +
		    triangle_unitcircle_overlap(x1, y1, x4, y4, x3, y3))
end
