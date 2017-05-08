type Point2D{T<:Real} <: Point{T}
  x :: T
  y :: T
end
zero{T}(::Type{Point2D{T}}) = Point2D(zero(T), zero(T))

-(p :: Point2D) = typeof(p)(-p.x)
+{T}(lhs :: Point2D{T}, rhs :: Point2D{T}) = Point2D{T}(lhs.x + rhs.x, lhs.y + rhs.y)
-{T}(lhs :: Point2D{T}, rhs :: Point2D{T}) = Point2D{T}(lhs.x - rhs.x, lhs.y - rhs.y)
*(p :: Point2D, a :: Real) = typeof(p)(p.x*a, p.y*a)
/(p :: Point2D, a :: Real) = typeof(p)(p.x/a, p.y/a)

norm2(p :: Point2D) = p.x^2+p.y^2

function rand{T}(::Type{Point2D{T}}) 
  r = rand(1:4)
  if r == 1
    Point2D(one(T),zero(T))
  elseif r == 2
    Point2D(-one(T),zero(T))
  elseif r == 3
    Point2D(zero(T),one(T))
  else
    Point2D(zero(T),-one(T))
  end
end

function update!(p::Point2D) 
  p2 = rand(typeof(p))
  p.x += p2.x
  p.y += p2.y
  return p
end

plotstr(p::Point2D) = "$(p.x) $(p.y)"

