export Point2D,CPoint2D,DPoint2D

abstract Point2D{T} <: Point{T}

type CPoint2D{T<:FloatingPoint} <: Point2D{T} # 'C' is "Continuous"
  x :: T
  y :: T
end
CPoint2D() = CPoint2D(0.0,0.0)
zero{T<:FloatingPoint}(::Type{CPoint2D{T}}) = CPoint2D(zero(T),zero(T))

type DPoint2D{T<:FloatingPoint} <: Point2D{T} # 'D' is "Discrete"
  x :: T
  y :: T
end
DPoint2D() = DPoint2D(0.0,0.0)
zero{T<:FloatingPoint}(::Type{DPoint2D{T}}) = DPoint2D{T}(zero(T),zero(T))

-(p :: Point2D) = typeof(p)(-p.x,-p.y)
+(lhs::Point2D, rhs::Point2D) = typeof(lhs)(lhs.x+rhs.x, lhs.y+rhs.y)
-(lhs::Point2D, rhs::Point2D) = typeof(lhs)(lhs.x-rhs.x, lhs.y-rhs.y)
*(p::Point2D, a::Real) = typeof(p)(p.x*a, p.y*a) 
*(a::Real,p::Point2D) = p*a
/(p::Point2D, a::Real) = typeof(p)(p.x/a, p.y/a) 
\(a::Real,p::Point2D) = p/a

abs2(p::Point2D) = p.x^2+p.y^2

to_plot_str(p::Point2D) = "$(p.x) $(p.y)"

function rand{T<:FloatingPoint}(::Type{DPoint2D{T}})
  r = 4*Random.rand()
  if r < 1.0
    return DPoint2D(one(T),zero(T))
  elseif r < 2.0
    return DPoint2D(-one(T),zero(T))
  elseif r < 3.0
    return DPoint2D(zero(T),one(T))
  else
    return DPoint2D(zero(T),-one(T))
  end
end

function rand{T<:FloatingPoint}(::Type{CPoint2D{T}})
  theta = 2pi*rand()
  return CPoint2D(oftype(T,cos(theta)),oftype(T,sin(theta)))
end

function update!(p::Point2D)
  p2=rand(typeof(p))
  p.x+=p2.x
  p.y+=p2.y
  return p
end

