module RW
export Point2D,CPoint2D,DPoint2D,update!,update

abstract Point2D{T<:Real}

import Base.zero

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

import Base.Random.rand
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
  return CPoint2D{T}(cos(theta),cos(theta))
end

function update!{P<:Point2D}(p::P)
  p2=rand(P)
  p.x+=p2.x
  p.y+=p2.y
  return p
end

update{P<:Point2D}(p::P) = update!(deepcopy(p))

update!{T}(v::Vector{T}) = map!(update,v)
update{T}(v::Vector{T}) = map(update,v)

end
