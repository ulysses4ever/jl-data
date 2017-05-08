export Point3D,CPoint3D,DPoint3D

abstract Point3D{T<:Real} <: Point{T}

type CPoint3D{T<:Real} <: Point3D{T} # 'C' is "Continuous"
  x :: T
  y :: T
  z :: T
end
CPoint3D() = CPoint3D(0.0,0.0,0.0)
CPoint3D{T}(p::CPoint3D{T}) = deepcopy(p)
zero{T<:Real}(::Type{CPoint3D{T}}) = CPoint3D{T}(zero(T),zero(T),zero(T))

type DPoint3D{T<:Real} <: Point3D{T} # 'D' is "Discrete"
  x :: T
  y :: T
  z :: T
end
DPoint3D() = DPoint3D(0.0,0.0,0.0)
DPoint3D{T}(p::DPoint3D{T}) = deepcopy(p)
zero{T<:Real}(::Type{DPoint3D{T}}) = DPoint3D{T}(zero(T),zero(T),zero(T))

-{P<:Point3D}(p :: P) = P(-p.x,-p.y,-p.z)
+{P<:Point3D}(lhs::P, rhs::P) = P(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z)
-{P<:Point3D}(lhs::P, rhs::P) = P(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z)
*{P<:Point3D}(p::P, a::Real) = P(p.x*a, p.y*a, p.z*a)
*{P<:Point3D}(a::Real,p::P) = p*a
/{P<:Point3D}(p::P, a::Real) = P(p.x/a, p.y/a, p.z/a)
\{P<:Point3D}(a::Real,p::P) = p/a

abs2{P<:Point3D}(p::P) = p.x^2 + p.y^2 + p.z^2
abs{P<:Point3D}(p::P) = sqrt(abs2(p))
norm2{P<:Point3D}(p::P) = abs2(p)
norm{P<:Point3D}(p::P) = sqrt(norm2(p))

to_plot_str{P<:Point3D}(p::P) = "$(p.x) $(p.y) $(p.z)"

function rand{T<:Real}(::Type{DPoint3D{T}})
  r = 6*Random.rand()
  if r < 1.0
    return DPoint3D{T}(one(T),zero(T),zero(T))
  elseif r < 2.0
    return DPoint3D{T}(-one(T),zero(T),zero(T))
  elseif r < 3.0
    return DPoint3D{T}(zero(T),one(T),zero(T))
  elseif r < 4.0
    return DPoint3D{T}(zero(T),-one(T),zero(T))
  elseif r < 5.0
    return DPoint3D{T}(zero(T),zero(T),one(T))
  else
    return DPoint3D{T}(zero(T),zero(T),-one(T))
  end
end

function rand{T<:Real}(::Type{CPoint3D{T}})
  theta = acos(1.0-2*rand())
  phi = 2pi*rand()
  return CPoint3D{T}(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta))
end

function update!{P<:Point3D}(p::P)
  p2=rand(P)
  p.x+=p2.x
  p.y+=p2.y
  p.z+=p2.z
  return p
end

