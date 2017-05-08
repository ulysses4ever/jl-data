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

export AbstractArithmetic, isArithmetic, apply_unary, apply_binary, +, -, *, /, ^, %



abstract AbstractArithmetic


isArithmetic{T}( ::Type{T} ) = T <: AbstractArithmetic
isArithmetic{T}( ::T ) = isArithmetic( T )


for op in (:+, :-)
    @eval $op{T <: AbstractArithmetic}( a::T ) = apply_unary( $op, a )
end

for op in ( :+, :-, :*, :/, :^, :%)
    @eval $op{T <: AbstractArithmetic}( a::T, b::T ) = apply_binary( $op, a, b )
end







end # module
