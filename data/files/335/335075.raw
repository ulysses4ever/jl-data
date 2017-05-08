module AutoDiff

import Base.+
import Base.-
import Base.*
import Base./

export Dual, u, d, +, -, *, .*, /, ^, one, zero, ⋅, dot, input, indexed_input, input_vector

type Dual{ U, D }
    underlier::U
    derivative::D
end

Dual{T}( x::T ) = Dual( x, zero( x ))

u{U,D}( x::Dual{U,D}) = x.underlier
d{U,D}( x::Dual{U,D}) = x.derivative




+{U1,D1,U2,D2}( x::Dual{U1,D1}, y::Dual{U2,D2} ) = Dual( u(x)+u(y), d(x)+d(y))
+{U,D,T<:Number}( x::Dual{U,D}, y::T) = Dual( u(x)+y, d(x))
+{U,D,T<:Number}( x::T, y::Dual{U,D}) = Dual( x+u(y), d(y))


  

-{U1,D1,U2,D2}( x::Dual{U1,D1}, y::Dual{U2,D2} ) = Dual( u(x)-u(y), d(x)-d(y))
-{U,D,T<:Number}( x::Dual{U,D}, y::T) = Dual( u(x)-y, d(x))
-{U,D,T<:Number}( x::T, y::Dual{U,D}) = Dual( x-u(y), -d(y))



*{U1,D1,U2,D2}( x::Dual{U1,D1}, y::Dual{U2,D2} ) = Dual( u(x)*u(y), d(x)*u(y)+d(y)*u(x) )

*{U,D}( x::Dual{U,D}, y::Bool ) = Dual( u( x )*y, dx( x )*y )
*{U,D}( x::Bool, y::Dual{U,D} ) = Dual( x*u(y), x*d(y))

*{U,D,T<:Number}( x::Dual{U,D}, y::T ) = Dual( u(x)*y, d(x)*y)
*{U,D,T<:Number}( x::T, y::Dual{U,D} ) = Dual( x*u(y), x*d(y))

.*{U,D,T<:Number}( x::Vector{Dual{U,D}}, y::T ) = map( xi->xi*y, x )
.*{U,D,T<:Number}( x::T, y::Vector{Dual{U,D}} ) = map( yi->x*yi, y )
.*{U,D,T<:Number}( x::Dual{U,D}, y::AbstractVector{T} ) = map( yi->x*yi, y )
.*{U,D,T<:Number}( x::AbstractVector{T}, y::Dual{U,D} ) = map( xi->xi*y, x )

*{U,D,T<:Number}( x::Dual{U,D}, y::AbstractVector{T} ) = x.*y
*{U,D,T<:Number}( x::AbstractVector{T}, y::Dual{U,D} ) = x.*y
*{U,D,T<:Number}( x::AbstractVector{Dual{U,D}}, y::T ) = x.*y
*{U,D,T<:Number}( x::T, y::AbstractVector{Dual{U,D}} ) = x.*y



/{U1,D1,U2,D2}( x::Dual{U1,D1}, y::Dual{U2,D2} ) = Dual( u(x)/u(y), ( d(x)*u(y)-d(y)*u(x))/( u(y)^2 ))

/{U,D,T<:Real}( x::Dual{U,D}, y::T ) = Dual( u(x)/y, d(x)/y )
/{U,D,T<:Real}( x::T, y::Dual{U,D} ) = Dual( x/u(y), -d(y)*x/( u(y)^2 ))

./{U,D,T<:Number}( x::AbstractVector{Dual{U,D}}, y::T ) = map( xi->xi*y, x )
./{U,D,T<:Number}( y::T, x::AbstractVector{Dual{U,D}} ) = map( yi->x*yi, y )
./{U,D,T<:Number}( x::Dual{U,D}, y::AbstractVector{T} ) = map( yi->x*yi, y )
./{U,D,T<:Number}( x::AbstractVector{T}, y::Dual{U,D}, ) = map( xi->xi*y, x )


/{U,D,T<:Number}( x::AbstractVector{Dual{U,D}}, y::T ) = x./y
/{U,D,T<:Number}( y::T, x::AbstractVector{Dual{U,D}} ) = x./y
/{U,D,T<:Number}( x::Dual{U,D}, y::AbstractVector{T} ) = x./y
/{U,D,T<:Number}( x::AbstractVector{T}, y::Dual{U,D} ) = x./y







^{U1,D1,U2,D2}( x::Dual{U1,D1}, y::Dual{U2,D2} ) = Dual( u( x )^u( y ), d( x )*u( x )^( u( y ))*u( y )/u( x )+d( y )*u( x )^u( y )*log( u( x )))

^{U,D,I<:Integer}( x::Dual{U,D}, y::Rational{I}) = Dual( u( x )^y, d( x )*u( x )^( y - 1 ))
^{U,D,I<:Integer}( x::Rational{I}, y::Dual{U,D} ) = Dual( x^u( y ), d( y )*x^u( y )*log( x ))
^{U,D}( x::MathConst{:e}, y::Dual{U,D} ) = exp( y )

^{U,D}( x::Dual{U,D}, y::Integer ) = Dual( u( x )^y, d( x )*u( x )^( y - 1 ))
^{U,D,T<:Real}( x::Dual{U,D}, y::T) = Dual( u( x )^y, d( x )*u( x )^( y - 1 ))
^{U,D,T<:Real}( x::T, y::Dual{U,D} ) = Dual( x^u( y ), d( y )*x^u( y )*log( x ))
#^{U,D,T,N}( x::Dual{U,D}, y::AbstractArray{T,N} ) = map( yi->x^yi, y )
#^{U,D,T,N}( x::AbstractArray{T,N}, y::Dual{U,D} ) = map( xi->xi^y, x )

zero{U,D}( x::Dual{U,D} ) = Dual( zero( u( x )), zero( d( x )))
one{U,D}( x::Dual{U,D} ) = Dual( one( u( x )), zero( d( x )))



#dot{U1,D1,U2,D2}( x::AbstractVector{Dual{U1,D1}}, y::AbstractVector{Dual{U2,D2}} ) = x .* y
#dot{U,D,T}( x::AbstractVector{Dual{U,D}}, y::AbstractVector{T} ) = x .* y
#dot{U,D,T}( x::AbstractVector{T}, y::AbstractVector{Dual{U,D}} ) = x .* y

#⋅{U1,D1,U2,D2}( x::AbstractVector{Dual{U1,D1}}, y::AbstractVector{Dual{U2,D2}} ) = x .* y
#⋅{U,D,T}( x::AbstractVector{Dual{U,D}}, y::AbstractVector{T} ) = x .* y
#⋅{U,D,T}( x::AbstractVector{T}, y::AbstractVector{Dual{U,D}} ) = x .* y


input{T}( x::T ) = Dual( x, T( 1 ))
indexed_input{T<:Real,I}( x::T, i::I ) = Dual( x, sparsevec([ i ],[ T( 1 )]))
input_vector{T<:Real}( x::AbstractVector{T} ) = map( ( i )-> indexed_input( x[i], i ), 1:size( x, 1 ))

sin{U,D}( x::Dual{U,D} ) = Dual( sin( u( x )),  d( x )*cos( u( x )))
cos{U,D}( x::Dual{U,D} ) = Dual( cos( u( x )), -d( x )*sin( u( x )))
tan{U,D}( x::Dual{U,D} ) = Dual( tan( u( x )),  d( x )*( tan( u( x ))^2+1 ))

acos{U,D}( x::Dual{U,D} ) = Dual( acos( u( x )), -d( x )/sqrt( 1 - u( x )^2 ))
asin{U,D}( x::Dual{U,D} ) = Dual( asin( u( x )),  d( x )/sqrt( 1 - u( x )^2 ))
atan{U,D}( x::Dual{U,D} ) = Dual( atan( u( x )),  d( x )/( 1 + u( x )^2))

sinh{U,D}( x::Dual{U,D} ) = Dual( sinh( u( x )), d( x )*cosh( u( x )))
cosh{U,D}( x::Dual{U,D} ) = Dual( cosh( u( x )), d( x )*sinh( u( x )))
tanh{U,D}( x::Dual{U,D} ) = Dual( tanh( u( x )), d( x )*( 1 - tanh( u( x ))^2 ))

asinh{U,D}( x::Dual{U,D} ) = Dual( asinh( u( x )), d( x )/sqrt( 1+u( x )^2 ))
acosh{U,D}( x::Dual{U,D} ) = Dual( acosh( u( x )), d( x )/sqrt( u( x )^2-1 ))
atanh{U,D}( x::Dual{U,D} ) = Dual( atanh( u( x )), d( x )/( 1-u( x )^2 ))

sqrt{U,D}( x::Dual{U,D} ) = Dual( sqrt( u( x )), d( x )/( 2*sqrt( u( x ))))
exp{U,D}( x::Dual{U,D} ) = Dual( exp( u( x )), d( x )*( exp( u( x ))))
log{U,D}( x::Dual{U,D} ) = Dual( log( u( x )), d( x )/u( x ))

end # module
