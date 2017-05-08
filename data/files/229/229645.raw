export Point2D,CPoint2D,DPoint2D

abstract Point2D{T} <: Point{T}

type CPoint2D{T<:FloatingPoint} <: Point2D{T} # 'C' is "Continuous"
  x :: T
  y :: T
end
CPoint2D() = CPoint2D(0.0,0.0)
zero{T}(::Type{CPoint2D{T}}) = CPoint2D(zero(T),zero(T))

type DPoint2D{T<:Integer} <: Point2D{T} # 'D' is "Discrete"
  x :: T
  y :: T
end
DPoint2D() = DPoint2D(0,0)
zero{T}(::Type{DPoint2D{T}}) = DPoint2D{T}(zero(T),zero(T))

-(p::Point2D) = typeof(p)(-p.x,-p.y)
+(lhs::Point2D, rhs::Point2D) = promote_type(typeof(lhs),typeof(rhs))(lhs.x+rhs.x, lhs.y+rhs.y)
-(lhs::Point2D, rhs::Point2D) = promote_type(typeof(lhs),typeof(rhs))(lhs.x-rhs.x, lhs.y-rhs.y)
*(p::CPoint2D, a::Real) = typeof(p)(p.x*a, p.y*a) 
*(p::DPoint2D, a::Integer) = typeof(p)(p.x*a, p.y*a) 
/(p::CPoint2D, a::Real) = typeof(p)(p.x/a, p.y/a) 
/(p::DPoint2D, a::Real) = CPoint2D{Float64}(p.x/a, p.y/a) 

abs2(p::Point2D) = p.x^2+p.y^2

to_plot_str(p::Point2D) = "$(p.x) $(p.y)"

function rand{T}(::Type{DPoint2D{T}})
  r = rand(1:4)
  if r == 1
    return DPoint2D(one(T),zero(T))
  elseif r == 2
    return DPoint2D(-one(T),zero(T))
  elseif r == 3
    return DPoint2D(zero(T),one(T))
  else
    return DPoint2D(zero(T),-one(T))
  end
end

function rand{T}(::Type{CPoint2D{T}})
  theta :: T = 2pi*rand(T)
  return CPoint2D(cos(theta),sin(theta))
end

function update!(p::Point2D)
  p2=rand(typeof(p))
  p.x+=p2.x
  p.y+=p2.y
  return p
end

function convert{T}(::Type{DPoint2D{T}}, p::Point2D)
  DPoint2D{T}(convert(T,p.x),convert(T,p.y))
end
function convert{T}(::Type{CPoint2D{T}}, p::Point2D)
  CPoint2D{T}(convert(T,p.x),convert(T,p.y))
end

promote_rule{T,U}(::Type{DPoint2D{T}}, ::Type{DPoint2D{U}}) = DPoint2D{promote_type(T,U)}
promote_rule{T,U}(::Type{CPoint2D{T}}, ::Type{CPoint2D{U}}) = CPoint2D{promote_type(T,U)}
promote_rule{T,U}(::Type{CPoint2D{T}}, ::Type{DPoint2D{U}}) = CPoint2D{promote_type(T,U)}


