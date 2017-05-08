export Point1D,CPoint1D,DPoint1D,update!,update

abstract Point1D{T} <: Point{T}

type CPoint1D{T<:FloatingPoint} <: Point1D{T} # 'C' is "Continuous"
  x :: T
end
CPoint1D() = CPoint1D(0.0)
zero{T<:FloatingPoint}(::Type{CPoint1D{T}}) = CPoint1D{T}(zero(T))

type DPoint1D{T<:FloatingPoint} <: Point1D{T} # 'D' is "Discrete"
  x :: T
end
DPoint1D() = DPoint1D(0.0)
zero{T<:FloatingPoint}(::Type{DPoint1D{T}}) = DPoint1D{T}(zero(T))

-(p :: Point1D) = typeof(p)(-p.x)
+(lhs::Point1D, rhs::Point1D) = typeof(lhs)(lhs.x+rhs.x)
-(lhs::Point1D, rhs::Point1D) = typeof(lhs)(lhs.x-rhs.x)
*(p::Point1D, a::Real) = typeof(p)(p.x*a)
*(a::Real, p::Point1D) = p*a
/(p::Point1D, a::Real) = typeof(p)(p.x/a)
\(a::Real, p::Point1D) = p/a

abs2(p::Point1D) = p.x^2

to_plot_str(p::Point1D) = "$(p.x)"

function rand{T<:FloatingPoint}(::Type{DPoint1D{T}})
  if rand() < 0.5
    return DPoint1D(one(T))
  else
    return DPoint1D(-one(T))
  end
end

function rand{T<:FloatingPoint}(::Type{CPoint1D{T}})
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

