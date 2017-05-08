export Point3D,CPoint3D,DPoint3D

abstract Point3D{T} <: Point{T}

type CPoint3D{T<:FloatingPoint} <: Point3D{T} # 'C' is "Continuous"
  x :: T
  y :: T
  z :: T
end
CPoint3D() = CPoint3D(0.0,0.0,0.0)
zero{T<:FloatingPoint}(::Type{CPoint3D{T}}) = CPoint3D(zero(T),zero(T),zero(T))

type DPoint3D{T<:Integer} <: Point3D{T} # 'D' is "Discrete"
  x :: T
  y :: T
  z :: T
end
DPoint3D() = DPoint3D(0,0,0)
zero{T<:Integer}(::Type{DPoint3D{T}}) = DPoint3D(zero(T),zero(T),zero(T))

-(p :: Point3D) = typeof(p)(-p.x,-p.y,-p.z)
+(lhs::Point3D, rhs::Point3D) = promote_type(typeof(lhs),typeof(rhs))(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z)
-(lhs::Point3D, rhs::Point3D) = promote_type(typeof(lhs),typeof(rhs))(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z)
*(p::CPoint3D, a::Real) = typeof(p)(p.x*a, p.y*a, p.z*a)
*(p::DPoint3D, a::Integer) = typeof(p)(p.x*a, p.y*a, p.z*a)
/(p::CPoint3D, a::Real) = typeof(p)(p.x/a, p.y/a, p.z/a)
/(p::DPoint3D, a::Real) = CPoint3D{Float64}(p.x/a, p.y/a, p.z/a)

abs2(p::Point3D) = p.x^2 + p.y^2 + p.z^2

to_plot_str(p::Point3D) = "$(p.x) $(p.y) $(p.z)"

function rand{T}(::Type{DPoint3D{T}})
  r = Random.rand(1:6)
  if r == 1
    return DPoint3D(one(T),zero(T),zero(T))
  elseif r == 2
    return DPoint3D(-one(T),zero(T),zero(T))
  elseif r == 3
    return DPoint3D(zero(T),one(T),zero(T))
  elseif r == 4
    return DPoint3D(zero(T),-one(T),zero(T))
  elseif r == 5
    return DPoint3D(zero(T),zero(T),one(T))
  else
    return DPoint3D(zero(T),zero(T),-one(T))
  end
end

function rand{T}(::Type{CPoint3D{T}})
  theta :: T = acos(one(T)-2*rand(T))
  phi :: T = 2pi*rand(T)
  return CPoint3D(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta))
end

function update!(p::Point3D)
  p2=rand(typeof(p))
  p.x+=p2.x
  p.y+=p2.y
  p.z+=p2.z
  return p
end

function convert{T}(::Type{DPoint3D{T}}, p::Point3D)
  DPoint3D{T}(convert(T,p.x),convert(T,p.y),convert(T,p.z))
end
function convert{T}(::Type{CPoint3D{T}}, p::Point3D)
  CPoint3D{T}(convert(T,p.x),convert(T,p.y),convert(T,p.z))
end

promote_rule{T,U}(::Type{DPoint3D{T}}, ::Type{DPoint3D{U}}) = DPoint3D{promote_type(T,U)}
promote_rule{T,U}(::Type{CPoint3D{T}}, ::Type{CPoint3D{U}}) = CPoint3D{promote_type(T,U)}
promote_rule{T,U}(::Type{CPoint3D{T}}, ::Type{DPoint3D{U}}) = CPoint3D{promote_type(T,U)}

