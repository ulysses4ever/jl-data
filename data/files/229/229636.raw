export Point1D,CPoint1D,DPoint1D,update!,update

abstract Point1D{T} <: Point{T}

type CPoint1D{T<:FloatingPoint} <: Point1D{T} # 'C' is "Continuous"
  x :: T
end
CPoint1D() = CPoint1D(0.0)
zero{T}(::Type{CPoint1D{T}}) = CPoint1D{T}(zero(T))

type DPoint1D{T<:Integer} <: Point1D{T} # 'D' is "Discrete"
  x :: T
end
DPoint1D() = DPoint1D(0)
zero{T}(::Type{DPoint1D{T}}) = DPoint1D{T}(zero(T))

-(p::Point1D) = typeof(p)(-p.x)
+(lhs::Point1D, rhs::Point1D) = promote_type(typeof(lhs),typeof(rhs))(lhs.x+rhs.x)
-(lhs::Point1D, rhs::Point1D) = promote_type(typeof(lhs),typeof(rhs))(lhs.x-rhs.x)
*(p::CPoint1D, a::Real) = typeof(p)(p.x*a)
*(p::DPoint1D, a::Integer) = typeof(p)(p.x*a)
/(p::CPoint1D, a::Real) = typeof(p)(p.x/a)
/(p::DPoint1D, a::Real) = CPoint1D{Float64}(p.x/a)

abs2(p::Point1D) = p.x^2

to_plot_str(p::Point1D) = "$(p.x)"

function rand{T}(::Type{DPoint1D{T}})
  if rand() < 0.5
    return DPoint1D(one(T))
  else
    return DPoint1D(-one(T))
  end
end

function rand{T}(::Type{CPoint1D{T}})
  if rand() < 0.5
    return CPoint1D(one(T))
  else
    return CPoint1D(-one(T))
  end
end

function update!(p::Point1D)
  p2=rand(typeof(p))
  p.x+=p2.x
  return p
end

convert{T}(::Type{DPoint1D{T}}, p::Point1D) = DPoint1D{T}(convert(T,p.x))
convert{T}(::Type{CPoint1D{T}}, p::Point1D) = CPoint1D{T}(convert(T,p.x))

promote_rule{T,U}(::Type{DPoint1D{T}}, ::Type{DPoint1D{U}}) = DPoint1D{promote_type(T,U)}
promote_rule{T,U}(::Type{CPoint1D{T}}, ::Type{CPoint1D{U}}) = CPoint1D{promote_type(T,U)}
promote_rule{T,U}(::Type{CPoint1D{T}}, ::Type{DPoint1D{U}}) = CPoint1D{promote_type(T,U)}

