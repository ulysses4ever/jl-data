### file: Arithmetic/tools/generate.jl

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

using SymPy

@vars x y



import Base.hypot, Base.expm1, Base.atan2

hypot( x::SymPy.Sym, y::SymPy.Sym ) = sqrt( x^2 + y^2 )
hypot( x::SymPy.Sym, y::Number ) = sqrt( x^2 + y^2 )
hypot( x::Number, y::SymPy.Sym ) = sqrt( x^2 + y^2 )

atan2( y::SymPy.Sym, x::SymPy.Sym ) = atan( y / x )
atan2( y::SymPy.Sym, x::Number ) = atan( y / x )
atan2( y::Number, x::SymPy.Sym ) = atan( y / x )

expm1( x::SymPy.Sym ) = exp( x ) - 1



unary_function_list =
    [:+, :-,
     :cos,   :sin,   :tan,
     :acos,  :asin,  :atan,
     :cosh,  :sinh,  :tanh,
     :acosh, :asinh, :atanh,
     :sqrt,  :exp,   :log,
     :expm1,
     :erf,   :erfc ]


binary_function_list =
    [ :+,     :-,     :*,     :/,    :^,
      :hypot, :atan2 ]

diff_unary( io, f ) = print( io, "($f) => x -> ", :( $(diff( eval(f)( x )))))
diff_unary( f ) = diff_unary( STDOUT, f )

diff_binary1( io, f ) =  print( io, "($f) => ( x, y ) -> ", :( $(diff( eval(f)( x, y ), x))))
diff_binary1( f ) = diff_binary1( STDOUT, f )

diff_binary2( io, f ) =  print( io, "($f) => ( x, y ) -> ", :( $(diff( eval(f)( x, y ), y))))
diff_binary2( f ) = diff_binary2( STDOUT, f )

function print_unary_dict( io )
    print( io, "const unary_diff = Dict(\n" )
    print( io, "    " )
    diff_unary( io, unary_function_list[ 1 ] )
    for op in unary_function_list[ 2:end ]
        print( io, ",\n" )
        print( io, "    " )
        diff_unary( io, op )
    end
    print( io, ")" )
end

print_unary_dict() = print_unary_dict( STDOUT )



function print_binary1_dict( io )
    print( io, "const binary1_diff = Dict(\n" )
    print( io, "    " )
    diff_binary1( io, binary_function_list[ 1 ] )
    for op in binary_function_list[ 2:end ]
        print( io, ",\n" )
        print( io, "    " )
        diff_binary1( io, op )
    end
    print( io, ")" )
end

print_binary1_dict() = print_binary1_dict( STDOUT )




function print_binary2_dict( io )
    print( io, "const binary2_diff = Dict(\n" )
    print( io, "    " )
    diff_binary2( io, binary_function_list[ 1 ] )
    for op in binary_function_list[ 2:end ]
        print( io, ",\n" )
        print( io, "    " )
        diff_binary2( io, op )
    end
    print( io, ")" )
end

print_binary2_dict() = print_binary2_dict( STDOUT )


function print_function_lists( io )
    println( io, "const unary_function_list = ", unary_function_list )
    println( io, "const binary_function_list = ", binary_function_list )
end

print_function_lists() = print_function_lists( STDOUT )




function print_dictionaries( io )
    print_function_lists( io )
    print_unary_dict( io )
    print( io, "\n\n" )
    print_binary1_dict( io )
    print( io, "\n\n" )
    print_binary2_dict( io )
    print( io, "\n\n" )
end
    
print_dictionaries() = print_dictionaries( STDOUT )
