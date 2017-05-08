"""
This module provides a framework for defining systems of units.
"""
module units
import Base: +, -, *, ^, /
import Base: convert, show, string, promote_rule

export BaseUnit, Unit, Unitful, SI, reciprocal


"""
Represents quantities that have units.
"""
abstract Unitful
*(x::Unitful, y::Number) = *(promote(x, y)...)
*(x::Number, y::Unitful) = *(promote(x, y)...)
*(x::Unitful, y::Unitful) = *(promote(x, y)...)
/(x::Unitful, y::Number) = /(promote(x, y)...)
/(x::Number, y::Unitful) = /(promote(x, y)...)
/(x::Unitful, y::Unitful) = /(promote(x, y)...)

"""
Represents the unit (e.g. seconds, meters) of a quantity.
"""
abstract BaseUnit <: Unitful

"""
Represents a whole system of units.
"""
type UnitSystem
    baseunits::Array{AbstractString}
    abbreviations::Array{AbstractString}
    function UnitSystem()
        s = new([], [])
        push!(s.baseunits, "Dimensionless")
        push!(s.abbreviations, "#")
        s
    end
end

"""
Convenience "constructor."
"""
function *{T<:BaseUnit}(x::Number, ::Type{T})
    T(x)
end

"""
Adjust power before constructing an instance (e.g. 5m^2).
"""
# The first definition is to disambiguate from ^{::Type{Any},
# n::Integer}
^{T<:BaseUnit}(::Type{T}, n::Integer) = unit(T){Float64, n}
^{T<:BaseUnit}(::Type{T}, n::Number) = unit(T){Float64, n}


# The SI system of units
SI = UnitSystem()
push!(SI.baseunits, "Meter")
push!(SI.baseunits, "Second")
push!(SI.baseunits, "Kilogram")
push!(SI.baseunits, "Radian")
push!(SI.abbreviations, "m")
push!(SI.abbreviations, "s")
push!(SI.abbreviations, "kg")
push!(SI.abbreviations, "rad")

# This loop defines all the standard behaviors for units that do not
# involve combinations of different units
for unitabbr in zip(SI.baseunits, SI.abbreviations)
    unit = symbol(unitabbr[1])
    abbrtext = unitabbr[2]
    abbr = symbol(abbrtext)

    @eval begin
        export $unit, $abbr
        """
        The unit.
        """
        immutable $unit{T<:Number, n} <: BaseUnit
            val::T
        end
        """
        Constructor for parameter-less type defaults to parameter n=1.
        """
        function $unit{T<:Number}(x::T)
            $unit{T, 1}(x)
        end
        """
        Extract the base parametric type (i.e. Meter for Meter{Int, 2}).
        """
        function unit(x::$unit)
            $unit
        end
        function unit{T<:$unit}(::Type{T})
            $unit
        end
        """
        Get the power that the unit is raised to (e.g 2 for m^2).
        """
        pow{T<:Number, n}(quantity::$unit{T, n}) = n
        """
        Get the power that the unit is raised to (e.g 2 for m^2).
        """
        pow{T<:Number, n}(::Type{$unit{T, n}}) = n
        """
        Get a power of 1 for parameter-less type.
        """
        pow(::Type{$unit}) = 1
        """
        Get the numeric type of the unit.
        """
        numtype{T<:Number, n}(quantity::$unit{T, n}) = T
        """
        Get the numeric type of the unit.
        """
        numtype{T<:Number, n}(::Type{$unit{T, n}}) = T
        $abbr = $unit
        function string{T<:Number, n}(::Type{$unit{T, n}})
            powerstring = n == 1 ? "" : "^$n"
            string($abbrtext, powerstring)
        end
        function string(::Type{$unit})
            string($abbrtext)
        end
        function string{T<:$unit}(quantity::T)
            string(quantity.val, " ", string(T))
        end
        function show{T<:$unit}(io::IO, quantity::T)
            print(io, string(quantity))
        end
        function show(io::IO, T::Type{$unit})
            print(io, string(T))
        end
        function promote_rule{n, m, T<:Number, S<:Number}(::Type{$unit{T, n}},
            ::Type{$unit{S, m}})
            error("Incompatible powers: $n ≠ $m")
        end
        function promote_rule{n, T<:Number, S<:Number}(::Type{$unit{T, n}},
            ::Type{$unit{S, n}})
            $unit{promote_type(T, S), n}
        end
        function promote_rule{n, T<:Number, S<:Number}(
            ::Type{$unit{T, n}}, ::Type{S})
            $unit
        end
        function convert{n, T, S}(::Type{$unit{T, n}}, x::$unit{S, n})
            $unit{T, n}(x.val)
        end
        function convert{S<:Number}(::Type{$unit}, x::S)
            $unit{S, 0}(x)
        end
        function *{T, S, n, m}(x::$unit{T, n}, y::$unit{S, m})
            $unit{promote_type(T, S), n + m}(x.val * y.val)
        end
        function /{T, S, n, m}(x::$unit{T, n}, y::$unit{S, m})
            $unit{promote_type(T, S), n - m}(x.val / y.val)
        end

    end
end


function +{T<:BaseUnit}(x::T, y::T)
    T(x.val + y.val)
end
function -{T<:BaseUnit}(x::T, y::T)
    T(x.val - y.val)
end


reciprocal(x::BaseUnit) = 1/x

function unitstring{T<:BaseUnit}(x::T)
    string(T)
end

"""
Represents a general combination of different base units.

Unit objects have a type invariant which is enforced through all of
the operations defined below. The invariant is that each BaseUnit
type appears at most once in the type parameter. This is what you'd
expect—although technicaly units like seconds per second exist, I don't
want them to show up here.
"""
typealias CompositeUnit Tuple{Vararg{BaseUnit}}
immutable Unit{T<:CompositeUnit, S<:Number} <: Unitful
    val::S
end

function types{T<:CompositeUnit}(x::Unit{T})
    unittuple = T.types
    map(y->(unit(y), numtype(y), pow(y)), unittuple)
end

function show{T<:CompositeUnit}(io::IO, x::Unit{T})
    unitsstring = mapreduce(
        S->string(S),
        (a, b)->string(a, " ", b),
        "", T.types)
    print(io, string(x.val, " ", unitsstring))
end

function promote_rule{T<:Unitful, S<:Unitful}(::Type{T}, ::Type{S})
    Unit
end
function convert(::Type{Unit}, x::BaseUnit)
    Unit{Tuple{typeof(x)}, numtype(x)}(x.val)
end

function convert{T<:Unit}(::Type{T}, x::T)
    x
end

function convert{T<:Unit, S<:Number}(::Type{T}, x::S)
    Unit{Tuple{Dimensionless{S, 0}}, S}(x)
end

function promote_rule{T<:Unit, S<:Number}(::Type{T}, y::Type{S})
    Unit
end
function *(x::BaseUnit, y::BaseUnit)
    Unit{
        Tuple{typeof(x), typeof(y)},
        promote_type(numtype(x), numtype(y))
        }(x.val * y.val)
end

function *{T<:CompositeUnit, S<:Number}(x::BaseUnit, y::Unit{T, S})
    xsearch = unit(x)
    ylist = types(y)
    ylist = map(x->x[1], ylist)
    xiny = findin(ylist, xsearch)
    numbertype = promote_type(S, numtype(x))
    if length(xiny) == 0
        tupletype = Tuple{T.types...,typeof(x)}
    elseif length(xiny) == 1
        index = xiny[1]
        newtype = unit(x){numbertype, pow(T.types[index]) + 1}
        tupletype = Tuple{T.types[1:index-1]..., newtype,
        T.types[index+1:end]...}
    else
        error("Corrupted Unit object: $y")
    end
    result = Unit{tupletype, numbertype}(x.val * y.val)
end


#=*(x::Unit, y::BaseUnit) = y * x=#

function factors{T<:CompositeUnit, S<:Number}(x::Unit{T, S})
    map(u->1unit(u), T.types)
end

function *{T<:Number, S<:Number, U<:Number, V<:Number, n, m}(
    x::Unit{Tuple{Dimensionless{T, n}}, S},
    y::Unit{Tuple{Dimensionless{U, m}}, V}
)
    Unit{Tuple{Dimensionless{promote_type(T, U), 0}},
        promote_type(S, V)}(x.val * y.val)
end

function *{T<:Number, S<:Number, n}(x::Unit{Tuple{Dimensionless{T, n}}, S}, y::Unit)
    typeof(y)(y.val * x.val)
end
function *{T<:Number, S<:Number, n}(x::Unit, y::Unit{Tuple{Dimensionless{T, n}}, S})
    y * x
end

function *{T<:CompositeUnit, S<:CompositeUnit, U<:Number, V<:Number}(
    x::Unit{T, U}, y::Unit{S, V})
    result = Unit{T, promote_type(U, V)}(x.val * y.val)
    for quantity in factors(y)
        result = quantity * result
    end
    result
end

#=*(x::Unit, y::Number) = *(promote(x, y)...)=#
#=*(x::Number, y::Unit) = *(promote(x, y)...)=#
#=*(x::Unit, y::BaseUnit) = *(promote(x, y)...)=#
#=*(x::BaseUnit, y::Unit) = *(promote(x, y)...)=#

/(x::Unit, y::Unit) = x * reciprocal(y)
#=/(x::BaseUnit, y::BaseUnit) = /(promote(x, y)...)=#

function reciprocal{T<:CompositeUnit, S<:Number}(x::Unit{T, S})
    newtypes = map(U->unit(U){S, -pow(U)}, T.types)
    Unit{Tuple{newtypes...}, S}(one(S)/x.val)
end

end
