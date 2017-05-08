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
abstract BaseUnit{n} <: Unitful

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

# This loop defines all the standard behaviors for base units
for unitabbr in zip(SI.baseunits, SI.abbreviations)
    unit = symbol(unitabbr[1])
    abbrtext = unitabbr[2]
    abbr = symbol(abbrtext)

    @eval begin
        export $unit, $abbr
        """
        The unit.
        """
        type $unit{n} <: BaseUnit{n}
        end
        """
        Constructor for parameter-less type defaults to parameter n=1.
        """
        function $unit()
            $unit{1}()
        end
        """
        Extract the base parametric type (i.e. Meter for Meter{2}).
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
        pow{n}(quantity::$unit{n}) = n
        """
        Get the power that the unit is raised to (e.g 2 for m^2).
        """
        pow{n}(::Type{$unit{n}}) = n
        """
        Get a power of 1 for parameter-less type.
        """
        pow(::Type{$unit}) = 1
        $abbr = $unit()
        function string(x::$unit{1})
            string($abbrtext)
        end
        function string{n}(x::$unit{n})
            string($abbrtext, "^$n")
        end
        function show(io::IO, quantity::$unit)
            print(io, string(quantity))
        end
        function *{n, m}(x::$unit{n}, y::$unit{m})
            $unit{n+m}()
        end
        function /{n, m}(x::$unit{n}, y::$unit{m})
            $unit{n-m}()
        end
        function ^{n}(x::$unit{n}, y::Integer)
            $unit{n*y}()
        end
        function ^{n}(x::$unit{n}, y::Number)
            $unit{n*y}()
        end
        reciprocal{n}(x::$unit{n}) = $unit{-n}()
        reciprocal{n}(::Type{$unit{n}}) = $unit{-n}
    end
end


"""
Represents a general combination of different base units.

Unit objects have a type invariant which is enforced through all of
the operations defined below. The invariant is that each BaseUnit
type appears at most once in the type parameter. This is what you'd
expect—although technicaly units like seconds per second exist, I don't
want them to show up here.
"""
typealias BaseUnitTuple Tuple{Vararg{BaseUnit}}
type Unit{T<:BaseUnitTuple} <: Unitful
end

# Constructor out of BaseUnit type
Unit(x::BaseUnit) = convert(Unit, x)

function types{T<:BaseUnitTuple}(x::Unit{T})
    T.types
end

function show{T<:BaseUnitTuple}(io::IO, x::Unit{T})
    unitsstring = mapreduce(
        S->string(S()),
        (a, b)->string(a, " ", b),
        "", T.types)[2:end]
    print(io, unitsstring)
end

function promote_rule{T<:Unitful, S<:Unitful}(::Type{T}, ::Type{S})
    Unit
end
function convert{T<:BaseUnit}(::Type{Unit}, x::T)
    Unit{Tuple{T}}()
end

function *{T<:BaseUnit, S<:BaseUnit}(x::T, y::S)
    tupletypes = (string(x) < string(y) ? (T, S)
        : (S, T))
    Unit{Tuple{tupletypes...}}()
end
function *{T<:BaseUnitTuple}(x::BaseUnit, y::Unit{T})
    xsearch = unit(x)
    ylist = types(y)
    ylist = map(x->unit(x), ylist)
    xiny = findin(ylist, (xsearch,))
    if length(xiny) == 0
        # Find the last index for which typeof(x) comes later in the
        # alphabet than typeof(T.types[index])
        index = indexin([true], map(t->string(t) < string(typeof(x)),
            T.types))[1] + 1
        tupletype = Tuple{T.types[1:index-1]...,typeof(x),
            T.types[index:end]...}
    elseif length(xiny) == 1
        index = xiny[1]
        newtype = unit(x){pow(T.types[index]) + 1}
        tupletype = Tuple{T.types[1:index-1]..., newtype,
        T.types[index+1:end]...}
    else
        error("Corrupted Unit object: $y")
    end
    result = Unit{tupletype}()
end

function *{T<:BaseUnitTuple, S<:BaseUnitTuple}(x::Unit{T}, y::Unit{S})
    result = Unit{T}()
    yfactors = map(x->x(), types(y))
    for factor in yfactors
        result = factor * result
    end
    result
end

/(x::Unit, y::Unit) = x * reciprocal(y)

function reciprocal{T<:BaseUnitTuple}(x::Unit{T})
    newtypes = map(reciprocal, T.types)
    Unit{Tuple{newtypes...}}()
end

end
