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
