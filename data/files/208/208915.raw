### file: Arithmetic/src/Arithmetic.jl

## Copyright (c) 2015 Samuel B. Johnson

## Author: Samuel B. Johnson <sabjohnso@yahoo.com>

## This file is lincesed under a two license system. For commercial use
## that is not compatible with the GPLv3, please contact the author.
## Otherwise, continue reading below.

## This file is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3, or (at your option)
## any later version.

## You should have received a copy of the GNU General Public License
## along with this program. If not, see <http://www.gnu.org/licenses/>.

### Code:

module Arithmetic

import Base.+, Base.-, Base.*, Base./, Base.^, Base.%
import Applicator.apply_unary, Applicator.apply_binary

export unary_ops, binary_ops

export @make_unary_op, @make_binary_op, @make_binary_op_alt, @make_binary_op_homog
export @make_unary_ops, @make_binary_ops, @make_binary_ops_alt, @make_binary_ops_homog

export AbstractArithmetic, isArithmetic, apply_unary, apply_binary, +, -, *, /, ^, %

"
unary_ops
---------
An array of unary arithmetic operators.
"
const unary_ops = [+, -]

"
binary_ops
----------
An array of binary arithmetic operators.
"
const binary_ops = [+, -, *, /, ^, %]

"
@make_unary_op
--------------
A macro to define a single unary operator for
the specified type.  The unary operator is
derived by the `apply_unary ` method for that
type.
"
macro make_unary_op( A, op )
    esc(:( $op( a::$A ) = apply_unary( $op, a )))
end

"
@make_binary_op
---------------
A macro to define a single binary operator for
a specified type.  The binary operator is
derived by the `apply_binary` method for that
type.
"
macro make_binary_op( A, op )
    esc(:( $op( a::$A, b::$A ) = apply_binary( $op, a, b )))
end

"
@make_binary_op
---------------
A macro to define a single binary operator for each
subtype of a specified abstract type.  The operator
is *not* defined between the different subtypes.  The
behavior of the operator is derived from the `apply binary`
method for the subtype.
"
macro make_binary_op_homog( T, A, op )
    esc(:( $op{ $T <: $A }( a::$T, b::$T ) = apply_binary( $op, a, b )))
end


"
@make_binary_op_alt
---------------
A macro to define a single binary operator for the specified type and
between the specified type and an alternate type.  The
behavior of the operator is derived from the `apply binary`
method for the subtype.
"
macro make_binary_op_alt( A, Alt, op )

    if (A == :T) || (Alt == :T)
        T = Symbol( string( "T", randstring( 20 )))
    else
        T = :T
    end
    
    esc(quote
        $op( a::$A, b::$A ) = apply_binary( $op, a, b )
        $op{ $T <: $A }( a::$Alt, b::$T ) = apply_binary( $op, a, b )
        $op{ $T <: $A }( a::$T, b::$Alt ) = apply_binary( $op, a, b )
        end)
end
          



"
@make_unary_ops
---------------
Derive each of the unary operators 
(Arithmetic.unary_ops) for the specified
type.  The behavior is derive through the
`apply_unary` method for the specified type.
"
macro make_unary_ops( A )
    esc(:( for op in unary_ops
           @make_unary_op $A op
           end ))
end

"
@make_binary_ops
----------------
Derive each of the binary operators
(Arithmetic.binary_ops) for the specified
type.  The behavior is derived through the
`apply_binary` method for the specified type.
"
macro make_binary_ops( A )
    esc(:( for op in binary_ops
             @make_binary_op $A op
           end ))
end

"
@make_binary_ops_homog <T> <AbstractType>
-----------------------------------------
Derive each of the binary arithmetic operators
(Arithmtic.binary_ops) for the specified 
abstract type.  Here, the behavior is derived
from the `apply_binary` method.  The operators
are not defined between different subtypes of
the abstract type.
"
macro make_binary_ops_homog( T,  A )
    esc(:( for op in binary_ops
           @make_binary_op_homog $T $A op
           end ))
end

"
@make_binary_ops_alt <Type> <AlternateType>
-------------------------------------------
Derive each of the binary arithmetic operators
(Arithmetic.binary_ops) for the specified
type and the alternate type.
"
macro make_binary_ops_alt( A, Alt )
    esc(:( for op in binary_ops
           @make_binary_op_alt $A $Alt op
           end ))
end
          

"
AbstractArithmetic
------------------
An abstract type for deriving arithmetic operators
through inheritance.
"
abstract AbstractArithmetic


isArithmetic{T}( ::Type{T} ) = T <: AbstractArithmetic
isArithmetic{T}( ::T ) = isArithmetic( T )


#
# ... Derive the arithmetic operators for AbstractArithmetic
#
@make_unary_ops AbstractArithmetic
@make_binary_ops_homog T AbstractArithmetic






end # module
