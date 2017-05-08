module AutoDiff


import Base.+
import Base.-
import Base.*
import Base./

import Base.sin, Base.cos, Base.tan
import Base.asin, Base.acos, Base.atan
import Base.sinh, Base.cosh, Base.tanh
import Base.asinh, Base.acosh, Base.atanh
import Base.sqrt, Base.exp, Base.log
import Base.erf, Base.erfc
import Base.sinc



export Dual, u, d, +, -, *, .*, /, ^, one, zero, ⋅, dot, input, indexed_input, input_vector

#export abs, abs2
#export sign, sign, signbit, copysign, flipsign
#export round, iround, floor, ifloor, ceil, iceil, trunc, itrunc
#export div, fld, rem, divrem, mod, mod2pi, gcd, lcm



export sin, cos, tan, cot, sec, csc
#export sinpi, cospi
#exprt sind, cosd, tand, cotd, secd, cscd
#export asind, acosd, atand, acotd, asecd, acscd

export asin, acos, atan, acot, asec, acsc
export sinh, cosh, tanh, coth, sech, csch
export asinh, acosh, atanh, acoth
#TODO export asech, acsch
#TODO: export sinc, cosc
#TODO: export atan2

# TODO: export sqrt, cbrt, hypot, exp, expm1, ldexp, log, log2, log10, log1p, exponent, significand

# TODO: export erf, erfc, erfinv, erfcinv, erfi, erfcx, dawson,
# TODO: export gamma, lgamma, lfact, digamma, beta, lbeta, eta, zeta,
# TODO: export airy, airyai
# TODO: export airyprime, airyaiprime
# TODO: export airybi, airybiprime
# TODO: export airyx
# TODO: export besselj, besselj0, besselj1, besseljx
# TODO: export bessely, bessely0, bessely1, besselyx
# TODO: export besselh
# TODO: export hankelh1, hankelh1x, hanklelh2, hankelh2x
# TODO: export besseli, besselix, besselk, besselkx


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
indexed_input{T<:Real,I<:Integer}( x::T, i::I ) = Dual( x, sparsevec([ i ],[ T( 1 )]))
input_vector{T<:Real}( x::AbstractVector{T} ) = map( ( i )-> indexed_input( x[i], i ), 1:size( x, 1 ))

sin{U,D}( x::Dual{U,D} ) = Dual( sin( u( x )),  d( x )*cos( u( x )))
cos{U,D}( x::Dual{U,D} ) = Dual( cos( u( x )), -d( x )*sin( u( x )))
tan{U,D}( x::Dual{U,D} ) = Dual( tan( u( x )),  d( x )*( tan( u( x ))^2+1 ))
sec{U,D}( x::Dual{U,D} ) = Dual( sec( u( x )),  d( x )*tan( u( x ))*sec( u( x )))
csc{U,D}( x::Dual{U,D} ) = Dual( csc( u( x )), -d( x )*cot( u( x ))*csc( u( x )))
cot{U,D}( x::Dual{U,D} ) = Dual( cot( u( x )), -d( x )*( 1+cot( x )^2 ))
                                
acos{U,D}( x::Dual{U,D} ) = Dual( acos( u( x )), -d( x )/sqrt( 1 - u( x )^2 ))
asin{U,D}( x::Dual{U,D} ) = Dual( asin( u( x )),  d( x )/sqrt( 1 - u( x )^2 ))
atan{U,D}( x::Dual{U,D} ) = Dual( atan( u( x )),  d( x )/( 1 + u( x )^2))
asec{U,D}( x::Dual{U,D} ) = Dual( asec( u( x )),  d( x )/( u( x )^2*sqrt( 1-1/u( x )^2 )))
acsc{U,D}( x::Dual{U,D} ) = Dual( acsc( u( x )), -d( x )/( u( x )^2*sqrt( 1-1/u( x )^2 )))

sinh{U,D}( x::Dual{U,D} ) = Dual( sinh( u( x )),  d( x )*cosh( u( x )))
cosh{U,D}( x::Dual{U,D} ) = Dual( cosh( u( x )),  d( x )*sinh( u( x )))
tanh{U,D}( x::Dual{U,D} ) = Dual( tanh( u( x )),  d( x )*( 1 - tanh( u( x ))^2 ))
coth{U,D}( x::Dual{U,D} ) = Dual( coth( u( x )), -d( x )/sinh( u( x ))^2 )
sech{U,D}( x::Dual{U,D} ) = Dual( sech( u( x )), -d( x )*tanh( u( x ))*sech( u( x )))
csch{U,D}( x::Dual{U,D} ) = Dual( csch( u( x )), -d( x )*coth( u( x ))*csch( u( x )))

asinh{U,D}( x::Dual{U,D} ) = Dual( asinh( u( x )), d( x )/sqrt( 1+u( x )^2 ))
acosh{U,D}( x::Dual{U,D} ) = Dual( acosh( u( x )), d( x )/sqrt( u( x )^2-1 ))
atanh{U,D}( x::Dual{U,D} ) = Dual( atanh( u( x )), d( x )/( 1-u( x )^2 ))
acoth{U,D}( x::Dual{U,D} ) = Dual( acoth( u( x )), d( x )/( 1-u( x )^2 ))
# TODO asech{U,D}( x::Dual{U,D} )
# TODO acsch{U,D}( x::Dual{U,D} )

sqrt{U,D}( x::Dual{U,D} ) = Dual( sqrt( u( x )), d( x )/( 2*sqrt( u( x ))))
exp{U,D}( x::Dual{U,D} )  = Dual( exp( u( x )), d( x )*( exp( u( x ))))
log{U,D}( x::Dual{U,D} )  = Dual( log( u( x )), d( x )/u( x ))


atan2{Uy,Dy,Ux,Dx}( y::Dual{Uy,Dy}, x::Dual{Ux,Dx} ) =
    Dual( atan2( u( y ), u( x )), ( d( y )*u( x )-d( x )*u( y ) )/( u( x )^2+u( y )^2 ))

atan2{Uy,Dy,X}( y::Dual{Uy,Dy}, x::X ) =
    Dual( atan2( u( y ), x), ( d( y )*u( x ))/( x^2+u( y )^2 ))


atan2{Y,Ux,Dx}( y::Y, x::Dual{Ux,Dx} ) =
    Dual( atan2( y, u( x )), -d( x )*u( y )/( u( x )^2+u( y )^2 ))



    

=======
# package code goes here
>>>>>>> 5b7dcf86f5a0a3054a83233fb194c0a97db9c3c5

end # module
