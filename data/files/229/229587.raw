type Point1D{T<:Real} <: Point{T}
  x :: T
end
zero{T}(::Type{Point1D{T}}) = Point1D(zero(T))

-(p :: Point1D) = typeof(p)(-p.x)
+{T}(lhs :: Point1D{T}, rhs :: Point1D{T}) = Point1D{T}(lhs.x + rhs.x)
-{T}(lhs :: Point1D{T}, rhs :: Point1D{T}) = Point1D{T}(lhs.x - rhs.x)
*(p :: Point1D, a :: Real) = typeof(p)(a*p.x)
/(p :: Point1D, a :: Real) = typeof(p)(p.x/a)

norm2(p :: Point1D) = p.x^2

function rand{T}(::Type{Point1D{T}}) 
  if rand() < 0.5
    Point1D(one(T))
  else
    Point1D(-one(T))
  end
end

function update!(p::Point1D) 
  p2 = rand(typeof(p))
  p.x += p2.x
  return p
end

plotstr(p::Point1D) = "$(p.x)"

