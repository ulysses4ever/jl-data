export Point3D,CPoint3D,DPoint3D

abstract Point3D{T} <: Point{T}

type CPoint3D{T<:FloatingPoint} <: Point3D{T} # 'C' is "Continuous"
  x :: T
  y :: T
  z :: T
end
CPoint3D() = CPoint3D(0.0,0.0,0.0)
zero{T<:FloatingPoint}(::Type{CPoint3D{T}}) = CPoint3D(zero(T),zero(T),zero(T))

type DPoint3D{T<:FloatingPoint} <: Point3D{T} # 'D' is "Discrete"
  x :: T
  y :: T
  z :: T
end
DPoint3D() = DPoint3D(0.0,0.0,0.0)
zero{T<:FloatingPoint}(::Type{DPoint3D{T}}) = DPoint3D(zero(T),zero(T),zero(T))

-(p :: Point3D) = typeof(p)(-p.x,-p.y,-p.z)
+(lhs::Point3D, rhs::Point3D) = typeof(lhs)(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z)
-(lhs::Point3D, rhs::Point3D) = typeof(lhs)(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z)
*(p::Point3D, a::Real) = typeof(p)(p.x*a, p.y*a, p.z*a)
*(a::Real,p::Point3D) = p*a
/(p::Point3D, a::Real) = typeof(p)(p.x/a, p.y/a, p.z/a)
\(a::Real,p::Point3D) = p/a

abs2(p::Point3D) = p.x^2 + p.y^2 + p.z^2

to_plot_str(p::Point3D) = "$(p.x) $(p.y) $(p.z)"

function rand{T<:FloatingPoint}(::Type{DPoint3D{T}})
  r = 6*Random.rand()
  if r < 1.0
    return DPoint3D(one(T),zero(T),zero(T))
  elseif r < 2.0
    return DPoint3D(-one(T),zero(T),zero(T))
  elseif r < 3.0
    return DPoint3D(zero(T),one(T),zero(T))
  elseif r < 4.0
    return DPoint3D(zero(T),-one(T),zero(T))
  elseif r < 5.0
    return DPoint3D(zero(T),zero(T),one(T))
  else
    return DPoint3D(zero(T),zero(T),-one(T))
  end
end

function rand{T<:FloatingPoint}(::Type{CPoint3D{T}})
  theta = acos(1.0-2*rand())
  phi = 2pi*rand()
  return CPoint3D(oftype(T,sin(theta)*cos(phi)),oftype(T,sin(theta)*sin(phi)),oftype(T,cos(theta)))
end

function update!(p::Point3D)
  p2=rand(typeof(p))
  p.x+=p2.x
  p.y+=p2.y
  p.z+=p2.z
  return p
end

