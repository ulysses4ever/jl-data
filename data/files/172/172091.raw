#=
 @module - MBR
 @description - minimum bounding this
 @author: titus
 @after - inspired by JTS Envelope - http://www.vividsolutions.com/jts/JTSHome.htm
=#
import Base.show

#=
 * @description MBR
 * @type MBR
 =#
type MBR
  minx::Float64
  maxx::Float64
  miny::Float64
  maxy::Float64
  function MBR(x1::Float64, x2::Float64, y1::Float64, y2::Float64) 
  	this = new()
    if (x1 < x2) 
      this.minx = x1
      this.maxx = x2
    else 
      this.minx = x2
      this.maxx = x1
    end

    if (y1 < y2) 
      this.miny = y1
      this.maxy = y2
    else 
      this.miny = y2
      this.maxy = y1
    end
    return this
  end
end

#construct mbr from two points
function MBR(p1::Vector{Real}, p2::Vector{Real})
  x1, y1 = float(p1[1]), float(p1[2])
  x2, y2 = float(p2[1]), float(p2[2])
  return MBR(x1, x2, y1, y2)
end 
#copy mbr
function MBR(box::MBR)
  return MBR(box.minx, box.maxx, box.miny, box.maxy)
end


#=
 * @description make mbr null zero height and width
 =#
function null(this::MBR) 
  this.minx = 0.0
  this.maxx = 0.0
  this.miny = 0.0
  this.maxy = 0.0
  return this
end
#=
 * @description equals
 * @return Bool
 =#
function equals(this::MBR , other::MBR) 
  return floatequal(this.maxx, other.maxx) &&
         floatequal(this.maxy, other.maxy) &&
         floatequal(this.minx, other.minx) &&
         floatequal(this.miny, other.miny)
end
#=
 * @description is mbr null ?
 * @return Bool
 =#
function isnull(this::MBR) 
  return floatequal(height(this), 0.0) &&
         floatequal(width(this), 0.0)
end
#=
 * @description returns the difference between
 *  the maximum and minimum x values.
 * @return Float64
 =#
function width(this::MBR) 
  return this.maxx - this.minx
end
#=
 * @description  returns the difference between
 *  the maximum and minimum y values.
 * @return Float64
 =#
function height(this::MBR) 
  return this.maxy - this.miny
end
#=
 * @description area
 * @returns Float64
 =#
function area(this::MBR) 
  return height(this) * width(this)
end
#=
 * @description computes the intersection
 * between this and other mbr
 * @return MBR
 =#
function intersection(this::MBR, other::MBR) 
  minx, miny, maxx , maxy = (0.0, 0.0, 0.0, 0.0)
  if (intersects(this, other)) 
    minx = this.minx > other.minx ? this.minx : other.minx
    miny = this.miny > other.miny ? this.miny : other.miny
    maxx = this.maxx < other.maxx ? this.maxx : other.maxx
    maxy = this.maxy < other.maxy ? this.maxy : other.maxy
  end
  return MBR(minx, maxx, miny, maxy)
end
#=
 * @description true if the given point lies in or on the mbr.
 * @return Bool
 =#
function contains(this::MBR, x::Real, y::Real)
  return (x >= box.minx) &&
         (x <= box.maxx) &&
         (y >= box.miny) &&
         (y <= box.maxy)
end
#=
 * @description true if the given point lies in or on the mbr.
 * @return Bool
 =#
function contains(this::MBR, x::Vector{Real})
  return contains(this, x[1], x[2])
end
function contains(this::MBR, x::(Real,Real))
  return contains(this, x[1], x[2])
end
#=
 * @description contains mbr
 * @returns Bool
 =#
function contains(box::MBR, other::MBR) 
  return  (other.minx >= box.minx) &&
          (other.maxx <= box.maxx) &&
          (other.miny >= box.miny) &&
          (other.maxy <= box.maxy)
end

#=
 * @description true if the given point lies in or on the mbr.
 * @return Bool
 =#
function completely_contains(box::MBR, x::Real, y::Real) 
  return (x > box.minx) &&
         (x < box.maxx) &&
         (y > box.miny) &&
         (y < box.maxy)
end
#=
 * @description intersect two mbrs.
 * @return Bool
 =#
function completely_contains(this::MBR, x::Vector{Real})
  return completely_contains(this, x[1], x[2])
end
function completely_contains(this::MBR, x::(Real,Real))
  return completely_contains(this, x[1], x[2])
end
#=
 * @description contains completely other mbr (no boundary touch)
 * @returns Bool
 =#
function completely_contains(box::MBR, other::MBR) 
  return   (other.minx > box.minx) &&
           (other.maxx < box.maxx) &&
           (other.miny > box.miny) &&
           (other.maxy < box.maxy)
end

#=
 * @description disjoint query
 * @param p1MBR|Array
 * @param [p2]Array
 * @param [q1]Array
 * @param [q2]Array
 =#
disjoint(this::MBR, other::MBR)       =  !intersects(this, other)
disjoint(box::MBR, pnt::Vector{Real}) =  !intersects(box, pnt)
disjoint(box::MBR, pnt::(Real, Real)) =  !intersects(box, pnt)

function disjoint(box::MBR, q1::Vector{Real}, q2::Vector{Real})
  return !intersects(box, q1, q2)
end

function disjoint(p1::Vector{Real}, p2::Vector{Real}, q1::Vector{Real})
  return !intersects(p1, p2, q1)
end

function disjoint(
  p1::Vector{Real}, p2::Vector{Real}, 
  q1::Vector{Real}, q2::Vector{Real})
  return !intersects(p1, p2, q1, q2) 
end

function disjoint(
    p1::(Real,Real), p2::(Real,Real), 
    q1::(Real,Real), q2::(Real,Real))
  return !intersects(p1, p2, q1, q2) 
end

#=
 * @description check if the region defined by <code>other</code
 * overlaps (intersects) the region of this <code>box</code>.
 * @param boxMBR
 * @param otherMBR the <code>mbr</code> which this
 * <code>box</code> is being checked for overlap
 * @return Bool
 =#
function intersects(this::MBR, other::MBR) 
  #not disjoint
  return !(other.minx > box.maxx ||
           other.maxx < box.minx ||
           other.miny > box.maxy ||
           other.maxy < box.miny)
end

#=
 @description intersects the mbr box by pnt
 @param boxMBR
 @param q the point to test for intersection
 @return Bool - if q intersects the mbr
 @private
 =#
function intersects(box::MBR, pnt::Vector{Real}) 
  return contains(box, pnt[1], pnt[2])
end
function intersects(box::MBR, pnt::(Real, Real)) 
  return contains(box, pnt[1], pnt[2])
end
#=
 * @description test the mbr defined by box intersects
 * with the mbr defined by q1-q2
 * @param boxMBR
 * @param q1 one extremal point of the mbr Q
 * @param q2 another extremal point of the mbr Q
 * @return Bool - box intersects P
 * @private
 =#
function intersects(box::MBR, q1::Vector{Real}, q2::Vector{Real}) 
  x, y = 1, 2
  minq = min(q1[x], q2[x])
  maxq = max(q1[x], q2[x])

  if (box.minx > maxq || box.maxx < minq) 
    return false
  end
  minq = min(q1[y], q2[y])
  maxq = max(q1[y], q2[y])
  #not disjoint
  return !(box.miny > maxq || box.maxy < minq)
end

#=
 @description intersects the mbr (p1-p2) box by q1
 @param p1 one extremal point of the mbr
 @param p2 another extremal point of the mbr
 @param q1 the point to test for intersection
 @return Bool - if q intersects the mbr p1-p2
 @private
 =#
function intersects(p1::Vector{Real}, p2::Vector{Real}, q1::Vector{Real}) 
  x, y = 1, 2
  return (q1[x] >= min(p1[x], p2[x])) &&
         (q1[x] <= max(p1[x], p2[x])) &&
         (q1[y] >= min(p1[y], p2[y])) &&
         (q1[y] <= max(p1[y], p2[y]))
end

#=
 * @description test the mbr defined by p1-p2 for intersection
 * with the mbr defined by q1-q2
 * @param p1 one extremal point of the mbr P
 * @param p2 another extremal point of the mbr P
 * @param q1 one extremal point of the mbr Q
 * @param q2 another extremal point of the mbr Q
 * @return Bool - true if Q (q1, q2) intersects P(p1, p2)
 * @private
 =#
function intersects(
  p1::Vector{Real}, p2::Vector{Real}, 
  q1::Vector{Real}, q2::Vector{Real}) 
  x,y  = 1, 2
  minq = min(q1[x], q2[x])
  maxq = max(q1[x], q2[x])
  minp = min(p1[x], p2[x])
  maxp = max(p1[x], p2[x])

  if minp > maxq || maxp < minq
    return false
  end

  minq = min(q1[y], q2[y])
  maxq = max(q1[y], q2[y])
  minp = min(p1[y], p2[y])
  maxp = max(p1[y], p2[y])
  #not disjoint
  return !(minp > maxq || maxp < minq) 
end
#=
 * @description test the mbr defined by p1-p2 for intersection
 =#
function intersects(
    p1::(Real,Real), p2::(Real,Real), 
    q1::(Real,Real), q2::(Real,Real))
  return intersects([p1...],[p2...],[p3...],[p4...])
end
#=
 * @description enlarges the boundary of the
 * mbr so that it contains other
 * @param box
 * @param other
 * @private
 =#
function expand(box::MBR, other::MBR) 
  other.minx < box.minx && (box.minx = other.minx)
  other.maxx > box.maxx && (box.maxx = other.maxx)
  other.miny < box.miny && (box.miny = other.miny)
  other.maxy > box.maxy && (box.maxy = other.maxy)
end
#=
 @description enlarges the boundary of the <code>mbr</code> so that it contains
 (x,y). Does nothing if (x,y) is already on or within the boundaries.
 =#
function expand(box::MBR, x::Real, y::Real)
  x, y = float(x), float(y)
  x < box.minx && (box.minx = x)
  x > box.maxx && (box.maxx = x)
  y < box.miny && (box.miny = y)
  y > box.maxy && (box.maxy = y)
end

#=
 @description expand mbr to include pnt
 =#
function expand(box::MBR, x::Vector{Real})
  return expand(box, x[1], x[2])
end
 
#=
 * @description expands this mbr by a given distance in all directions.
 * @param dx - change in x
 * @param dy - change in y
 =#
function expandby(this::MBR, dx::Real, dy::Real) 
  this.minx -= dx
  this.maxx += dx
  this.miny -= dy
  this.maxy += dy
  #check for mbr disappearing
  if (this.minx > this.maxx || this.miny > this.maxy) 
    null(this)
  end
end

#=
 * @description  translates this mbr by given
 * amounts in the X and Y direction. Returns a new mbr
 * @param dx - the amount to translate along the X axis
 * @param dy - the amount to translate along the Y axis
 * @return MBR
 =#
function translate(dx::Real, dy::Real) 
  return MBR(
    this.minx + dx,
    this.maxx + dx,
    this.miny + dy,
    this.maxy + dy
  )
end

#=
 * @description computes the coordinate of the centre of
 * this mbr
 * @return Array - [x,y] the centre coordinate of this mbr
 =#
function centre() 
  return [
    (this.minx + this.maxx) / 2.0,
    (this.miny + this.maxy) / 2.0
  ]
end

#=
 * @description  Computes the distance between this and another mbr
 * the distance between overlapping BBoxs is 0.  Otherwise, the
 * distance is the Euclidean distance between the closest points.
 * @param otherMBR
 * @return Float64
 =#
function distance(this::MBR, other::MBR) 
  if intersects(this, other)
    return 0.0
  end

  dx, dy = 0.0, 0.0
  if this.maxx < other.minx
    dx = other.minx - this.maxx
  elseif this.minx > other.maxx
    dx = this.minx - other.maxx
  end

  if this.maxy < other.miny
    dy = other.miny - this.maxy
  elseif this.miny > other.maxy 
    dy = this.miny - other.maxy
  end

  return hypot(dx, dy)
end

#=
 * @description mbr to string
 * @return wkt string
 =#
function show() 
  return "POLYGON ((" * join([
    string(this.minx) * " " * string(this.miny),
    string(this.minx) * " " * string(this.maxy),
    string(this.maxx) * " " * string(this.maxy),
    string(this.maxx) * " " * string(this.miny),
    string(this.minx) * " " * string(this.miny)
  ],",") * "))"
end

