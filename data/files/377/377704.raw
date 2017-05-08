module myModule

# Import these functions so we can add more methods for our new type.

import Base: promote_rule, convert, *

export FixedPoint 

type FixedPoint <: Real

	exponent::Int8
	mantissa::Int64	

end

FixedPoint(x::Int64, y:: Int64) = FixedPoint(Base.convert(Int8,x),y)

convert(::Type{Float64}, x::FixedPoint) = x.mantissa*(10^Base.convert(Float64,x.exponent))
convert(::Type{FixedPoint}, x::Rational{Int64}) = FixedPoint(-6, Base.convert(Int64,div(1000000*x.num,x.den)) ) 

promote_rule(::Type{Int64}, ::Type{FixedPoint}) = Float64
promote_rule(::Type{Float64}, ::Type{FixedPoint}) = Float64
promote_rule(::Type{Rational}, ::Type{FixedPoint}) = Float64

*(a::FixedPoint,b::FixedPoint) = FixedPoint(a.exponent+b.exponent,a.mantissa*b.mantissa)

end
