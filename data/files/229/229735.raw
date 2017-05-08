export Point1D,CPoint1D,DPoint1D,update!,update

abstract Point1D{T<:Real} <: Point{T}

type CPoint1D{T<:Real} <: Point1D{T} # 'C' is "Continuous"
  x :: T
end
CPoint1D() = CPoint1D(0.0)
CPoint1D{T}(p::CPoint1D{T}) = deepcopy(p)
zero{T<:Real}(::Type{CPoint1D{T}}) = CPoint1D{T}(zero(T))

type DPoint1D{T<:Real} <: Point1D{T} # 'D' is "Discrete"
  x :: T
end
DPoint1D() = DPoint1D(0.0)
DPoint1D{T}(p::DPoint1D{T}) = deepcopy(p)
zero{T<:Real}(::Type{DPoint1D{T}}) = DPoint1D{T}(zero(T))

-{P<:Point1D}(p :: P) = P(-p.x)
+{P<:Point1D}(lhs::P, rhs::P) = P(lhs.x+rhs.x)
-{P<:Point1D}(lhs::P, rhs::P) = P(lhs.x-rhs.x)
*{P<:Point1D}(p::P, a::Real) = P(p.x*a)
*{P<:Point1D}(a::Real,p::P) = p*a
/{P<:Point1D}(p::P, a::Real) = P(p.x/a)
\{P<:Point1D}(a::Real,p::P) = p/a

abs2{P<:Point1D}(p::P) = p.x^2
abs{P<:Point1D}(p::P) = abs(p.x)
norm2{P<:Point1D}(p::P) = abs2(p)
norm{P<:Point1D}(p::P) = abs(p.x)

function rand{T<:Real}(::Type{DPoint1D{T}})
  if rand() < 0.5
    return DPoint1D(one(T))
  else
    return DPoint1D(-one(T))
  end
end

function rand{T<:Real}(::Type{CPoint1D{T}})
  if rand() < 0.5
    return CPoint1D(one(T))
  else
    return CPoint1D(-one(T))
  end
end

function update!{P<:Point1D}(p::P)
  p2=rand(P)
  p.x+=p2.x
  return p
end

