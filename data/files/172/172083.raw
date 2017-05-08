#mbr.jl

#=
 * @module - MBR
 * @description - minimum bounding this
 * author: titus
 * date: 15/11/14
 * time: 2:02 PM
=#

#=
 * @description MBR
 * @param x1
 * @param x2
 * @param y1
 * @param y2
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

 function MBR(p1::Vector{Real}, p2::Vector{Real})
    x1, y1 = float(p1[1]), float(p1[2])
    x2, y2 = float(p2[1]), float(p2[2])
    MBR(x1, x2, y1, y2)
 end 
MBR(box::MBR) = MBR(box.minx, box.maxx, box.miny, box.maxy)


#=
 * @description make mbr null zero height and width
 =#
function null(this::MBR) 
  this.minx = 0.0
  this.maxx = 0.0
  this.miny = 0.0
  this.maxy = 0.0
end
#=
 * @description equals
 * @param other
 * @return *end
 =#
equals = function (this::MBR , other::MBR) 
  return floatequal(this.maxx, other.maxx) &&
         floatequal(this.maxy, other.maxy) &&
         floatequal(this.minx, other.minx) &&
         floatequal(this.miny, other.miny)
end
#=
 * @description is mbr null ?
 * @return bleanend
 =#
function isnull(this::MBR) 
  return floatequal(height(this), 0.0) &&
         floatequal(width(this), 0.0)
end
#=
 * @description returns the difference between
 *  the maximum and minimum x values.
 * @return numberend
 =#
function width(this::MBR) 
  return this.maxx - this.minx
end
#=
 * @description  returns the difference between
 *  the maximum and minimum y values.
 * @return numberend
 =#
function height(this::MBR) 
  return this.maxy - this.miny
end
#=
 * @description area
 * @returns numberend
 =#
function area(this::MBR) 
  return height(this) * width(this)
end
#=
 * @description computes the intersection
 * between this and other mbr
 * @param other
 * @return MBRend
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
 * @param boxMBRend
 * @param xNumberend
 * @param yNumberend
 * @private
 * @return bleanend
 =#
function _contains(box::MBR, x::Real, y::Real) 
  return (x >= box.minx) &&
         (x <= box.maxx) &&
         (y >= box.miny) &&
         (y <= box.maxy)
end
#=
 * @description contains mbr
 * @param box
 * @param other
 * @returns bleanend
 * @private
 =#
function _contains_mbr(box::MBR, other::MBR) 
  return   (other.minx >= box.minx) &&
           (other.maxx <= box.maxx) &&
           (other.miny >= box.miny) &&
           (other.maxy <= box.maxy)
end
#=
 * @description true if the given point lies in or on the mbr.
 * @param xArray|Number|MBRend
 * @param [y]Numberend
 * @return bleanend
 =#
contains(this::MBR, x::Real, y::Real) =_contains(this, x, y)
contains(this::MBR, x::Vector{Real}) = _contains(this, x[1], x[2])
contains(this::MBR, x::MBR) =  _contains_mbr(this, x)

#=
 * @description true if the given point lies in or on the mbr.
 * @param boxMBRend
 * @param xNumberend
 * @param yNumberend
 * @private
 * @return bleanend
 =#
function _contains_complete(box::MBR, x::Real, y::Real) 
  return (x > box.minx) &&
         (x < box.maxx) &&
         (y > box.miny) &&
         (y < box.maxy)
end
#=
 * @description contains complete other mbr (no boundary touch)
 * @param box
 * @param other
 * @returns bleanend
 * @private
 =#
function _contains_complete_mbr(box::MBR, other::MBR) 
  return   (other.minx > box.minx) &&
           (other.maxx < box.maxx) &&
           (other.miny > box.miny) &&
           (other.maxy < box.maxy)
end
#=
 * @description completely contains point(x, y) or xmbrend
 * @param xArray|Numberend
 * @param [y]Numberend
 * @return bleanend
 =#
completely_contains(this::MBR, x::Real, y::Real) =_contains_complete(this, x, y)
completely_contains(this::MBR, x::Vector{Real}) = _contains_complete(this, x[1], x[2])
completely_contains(this::MBR, x::MBR) =  _contains_complete_mbr(this, x)

#=
 * @description disjoint query
 * @param p1MBR|Array
 * @param [p2]Array
 * @param [q1]Array
 * @param [q2]Array
 =#
function disjoint(this::MBR, p1, p2, q1, q2) 
  return !intersects(this, p1, p2, q1, q2)
end

#=
 * @description intersect query
 * @param p1MBR|Array
 * @param [p2]Array
 * @param [q1]Array
 * @param [q2]Array
 =#
intersects = function (p1, p2, q1, q2) 
  bl = false
  if (arguments.length == 1 && (p1 instanceof MBR)) 
    bl = _intersects1(this, p1)
  end
  else if (arguments.length == 1 && ispoint(p1)) 
    bl = _intersects2(this, p1)
  end
  else if (arguments.length == 2 && (p1 instanceof MBR)) 
    bl = _intersects2(p1, p2)
  end
  else if (arguments.length == 2 && ispoint(p1) && ispoint(p2)) 
    bl = _intersects3_2(this, p1, p2)
  end
  else if (arguments.length == 3 && ispoint(p1)) 
    bl = _intersects3(p1, p2, q1)
  end
  else if (arguments.length == 4 && ispoint(p1)) 
    bl = _intersects4(p1, p2, q1, q2)
  end
  else 
    throw new Error("invalid args mbr - intersects ")
  end
  return bl
end
#=
 * @description check if the region defined by <code>other</code
 * overlaps (intersects) the region of this <code>box</code>.
 * @param boxMBRend
 * @param otherMBRend the <code>mbr</code> which this
 * <code>box</code> is being checked for overlap
 * @return bleanend
 =#
_intersects1 = function (box, other) 
  #not disjoint
  return !(other.minx > box.maxx ||
           other.maxx < box.minx ||
           other.miny > box.maxy ||
           other.maxy < box.miny)
end
#=
 @description intersects the mbr box by q1
 @param boxMBRend
 @param q the point to test for intersection
 @return bleanend - if q intersects the mbr
 @private
 =#
_intersects2 = function (box, q) 
  return _contains(box, q[0], q[1])
end
#=
 @description intersects the mbr (p1-p2) box by q1
 @param p1 one extremal point of the mbr
 @param p2 another extremal point of the mbr
 @param q1 the point to test for intersection
 @return bleanend - if q intersects the mbr p1-p2
 @private
 =#
_intersects3 = function (p1, p2, q1) 
  x = 0, y = 1
  return (q1[x] >= Math.min(p1[x], p2[x])) &&
         (q1[x] <= Math.max(p1[x], p2[x])) &&
         (q1[y] >= Math.min(p1[y], p2[y])) &&
         (q1[y] <= Math.max(p1[y], p2[y]))
end
#=
 * @description test the mbr defined by box intersects
 * with the mbr defined by q1-q2
 * @param boxMBRend
 * @param q1 one extremal point of the mbr Q
 * @param q2 another extremal point of the mbr Q
 * @return bleanend - box intersects P
 * @private
 =#
_intersects3_2 = function (box, q1, q2) 
  x = 0, y = 1
  minq = Math.min(q1[x], q2[x])
  maxq = Math.max(q1[x], q2[x])

  if (box.minx > maxq || box.maxx < minq) 
    return false
  end
  minq = Math.min(q1[y], q2[y])
  maxq = Math.max(q1[y], q2[y])
  #not disjoint
  return !(box.miny > maxq || box.maxy < minq)
end

#=
 * @description test the mbr defined by p1-p2 for intersection
 * with the mbr defined by q1-q2
 * @param p1 one extremal point of the mbr P
 * @param p2 another extremal point of the mbr P
 * @param q1 one extremal point of the mbr Q
 * @param q2 another extremal point of the mbr Q
 * @return bleanend - <code>true</code> if Q intersects P
 * @private
 =#
_intersects4 = function (p1, p2, q1, q2) 
  x = 0, y = 1
  minq = Math.min(q1[x], q2[x])
  maxq = Math.max(q1[x], q2[x])
  minp = Math.min(p1[x], p2[x])
  maxp = Math.max(p1[x], p2[x])

  if (minp > maxq || maxp < minq) 
    return false
  end

  minq = Math.min(q1[y], q2[y])
  maxq = Math.max(q1[y], q2[y])
  minp = Math.min(p1[y], p2[y])
  maxp = Math.max(p1[y], p2[y])

  return !(minp > maxq || maxp < minq) #not disjoint
end

#=
 * @description expand mbr
 * @param x
 * @param y
 =#
expand = function (x, y) 
  if (arguments.length == 1 && ispoint(x)) 
    _expandinclude(this, x[0], x[1])
  end
  else if (arguments.length == 1 && x instanceof MBR) 
    _expandincludembr(this, x)
  end
  else if (arguments.length == 2) 
    _expandinclude(this, x, y)
  end
end
#=
 * @description expands this mbr by a given distance in all directions.
 * @param dx
 * @param dy
 =#
expandby = function (dx, dy) 
  this.minx -= dx
  this.maxx += dx
  this.miny -= dy
  this.maxy += dy
  #check for mbr disappearing
  if (this.minx > this.maxx || this.miny > this.maxy) 
    this.null()
  end
end
#=
 * @description enlarges the boundary of the <code>mbr</code> so that it contains
 (x,y). Does nothing if (x,y) is already on or within the boundaries.
 * @param box
 * @param x
 * @param y
 * @private
 =#
_expandinclude = function (box, x, y) 
  x < box.minx && (box.minx = x)
  x > box.maxx && (box.maxx = x)
  y < box.miny && (box.miny = y)
  y > box.maxy && (box.maxy = y)
end
#=
 * @description enlarges the boundary of the
 * mbr so that it contains other
 * @param box
 * @param other
 * @private
 =#
_expandincludembr = function (box, other) 
  other.minx < box.minx && (box.minx = other.minx)
  other.maxx > box.maxx && (box.maxx = other.maxx)
  other.miny < box.miny && (box.miny = other.miny)
  other.maxy > box.maxy && (box.maxy = other.maxy)
end
#=
 * @description  translates this mbr by given
 * amounts in the X and Y direction. Returns a new mbr
 * @param dx - the amount to translate along the X axis
 * @param dy - the amount to translate along the Y axis
 * @return MBRend
 =#
translate = function (dx, dy) 
  return new MBR(
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
centre = function () 
  return [
    (this.minx + this.maxx) / 2.0,
    (this.miny + this.maxy) / 2.0
  ]
end
#=
 * @description  Computes the distance between this and another mbr
 * the distance between overlapping BBoxs is 0.  Otherwise, the
 * distance is the Euclidean distance between the closest points.
 * @param otherMBRend
 * @return Numberend
 =#
distance = function (other) 
  if (this.intersects(other)) 
    return 0.0
  end

  dx = 0.0, dy = 0.0
  if (this.maxx < other.minx) 
    dx = other.minx - this.maxx
  end
  else if (this.minx > other.maxx) 
    dx = this.minx - other.maxx
  end

  if (this.maxy < other.miny) 
    dy = other.miny - this.maxy
  end
  else if (this.miny > other.maxy) 
    dy = this.miny - other.maxy
  end
  return hypot(dx, dy)
end

#=
 * @description mbr to string
 * @return stringend
 =#
toString = function () 
  return "POLYGON ((" + [
    this.minx + " " + this.miny,
    this.minx + " " + this.maxy,
    this.maxx + " " + this.maxy,
    this.maxx + " " + this.miny,
    this.minx + " " + this.miny
  ].join(",") + "))"
end

