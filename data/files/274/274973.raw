module AutoDiff


include( "dictionaries.jl" )


import Base.<, Base.<=, Base.==, Base.>=, Base.>
import Base.+, Base.-, Base.*, Base./, Base.^
import Base.cos, Base.sin, Base. tan, Base.acos, Base.asin, Base.atan
import Base.cosh, Base.sinh, Base.tanh, Base.acosh, Base.asinh, Base.atanh
import Base.sqrt, Base.exp, Base.log, Base.expm1
import Base.erf, Base.erfc
import Base.hypot, Base.atan2

import Base.getindex,Base.map
import Applicator.apply_unary, Applicator.apply_binary

using Identity, Scalar, Comparable, DataWrapper, Elementwise, Arithmetic, SpecFunable

export Dual, ArithmeticArray, AbstractComparable, AbstractDataWrapper, AbstractElementwise, data, unit
export Dual, re, du, <, <=,  ==, eq, neq
export +, -, *, /, ^
export apply_unary, apply_binary

abstract AbstractComparableScalar <: AbstractScalar
abstract AbstractDual <: AbstractComparableScalar





diffu( op ) = unary_diff[ op ]
diffb1( op ) = binary1_diff[ op ]
diffb2( op ) = binary2_diff[ op ]

type Dual{ Re, Du } <: AbstractScalar
    re::Re
    du::Du
end

Dual( x ) = Dual( x, additive_identity )

re( x::Dual ) = x.re
du( x::Dual ) = x.du

apply_unary( op, x::Dual ) = Dual( op( re( x )), du( x )*diffu( op )( re( x )))

apply_binary( op, x::Dual, y::Dual ) =
    Dual( op( re( x ), re( y )),
          du( x )*diffb1( op )( re( x ), re( y ))+
          du( y )*diffb2( op )( re( x ), re( y )))

apply_binary( op, x::Dual, y::Number ) =
    Dual( op( re( x ), y ),
          du( x )*diffb1( op )( re( x ), y ))

apply_binary( op, x::Number, y::Dual ) =
    Dual( op( x, re( y )),
          du( y )*diffb2( op )( x, re( y )))

<( x::Dual, y::Dual ) = re( x ) < re( y )
<( x::Dual, y::Number ) = re( x ) < y
<( x::Number , y::Dual ) = x < re( y )

@make_comparable Dual Number
@make_scalar Dual


for f in unary_function_list
    @eval @make_unary_specfun Dual $f
end

for f in binary_function_list
    @eval @make_binary_specfun Dual Number $f
end







end # module AutoDiff
