export Point2D,CPoint2D,DPoint2D

abstract Point2D{T<:Real} <: Point{T}

import Base.zero, Base.abs, Base.abs2, Base.norm
import Base.Random.rand, Base.Random.rand!

type CPoint2D{T<:Real} <: Point2D{T} # 'C' is "Continuous"
  x :: T
  y :: T
end
CPoint2D() = CPoint2D(0.0,0.0)
CPoint2D{T}(p::CPoint2D{T}) = deepcopy(p)
zero{T<:Real}(::Type{CPoint2D{T}}) = CPoint2D{T}(zero(T),zero(T))

type DPoint2D{T<:Real} <: Point2D{T} # 'D' is "Discrete"
  x :: T
  y :: T
end
DPoint2D() = DPoint2D(0.0,0.0)
DPoint2D{T}(p::DPoint2D{T}) = deepcopy(p)
zero{T<:Real}(::Type{DPoint2D{T}}) = DPoint2D{T}(zero(T),zero(T))

-{P<:Point2D}(p :: P) = P(-p.x,-p.y)
+{P<:Point2D}(lhs::P, rhs::P) = P(lhs.x+rhs.x, lhs.y+rhs.y)
-{P<:Point2D}(lhs::P, rhs::P) = P(lhs.x-rhs.x, lhs.y-rhs.y)
*{P<:Point2D}(p::P, a::Real) = P(p.x*a, p.y*a) 
*{P<:Point2D}(a::Real,p::P) = p*a
/{P<:Point2D}(p::P, a::Real) = P(p.x/a, p.y/a) 
\{P<:Point2D}(a::Real,p::P) = p/a

abs2{P<:Point2D}(p::P) = p.x^2+p.y^2
abs{P<:Point2D}(p::P) = sqrt(abs2(p))
norm2{P<:Point2D}(p::P) = abs2(p)
norm{P<:Point2D}(p::P) = abs(p)

to_plot_str{P<:Point2D}(p::P) = "$(p.x) $(p.y)"

function rand{T<:Real}(::Type{DPoint2D{T}})
  r = 4*Random.rand()
  if r < 1.0
    return DPoint2D{T}(one(T),zero(T))
  elseif r < 2.0
    return DPoint2D{T}(-one(T),zero(T))
  elseif r < 3.0
    return DPoint2D{T}(zero(T),one(T))
  else
    return DPoint2D{T}(zero(T),-one(T))
  end
end

function rand{T<:Real}(::Type{CPoint2D{T}})
  theta = 2pi*rand()
  return CPoint2D{T}(cos(theta),sin(theta))
end

function update!{P<:Point2D}(p::P)
  p2=rand(P)
  p.x+=p2.x
  p.y+=p2.y
  return p
end

