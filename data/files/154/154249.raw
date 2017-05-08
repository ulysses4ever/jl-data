"""
This module provides a framework for defining systems of units.
"""
module units
import Base: +, -, *, ^, /
import Base: convert, show, string, promote_rule

"""
Represents the unit (e.g. seconds, meters) of a quantity.
"""
abstract BaseUnit <: Number

"""
Represents a whole system of units.
"""
type UnitSystem
    baseunits::Array{AbstractString}
    abbreviations::Array{AbstractString}
end

"""
Convenience "constructor."
"""
function *{T<:BaseUnit}(x::Number, ::Type{T})
    T{typeof(x), 1}(x)
end

"""
Adjust power before constructing an instance (e.g. 5m^2).
"""
^{T<:BaseUnit}(::Type{T}, n::Int) = T{Float64, n}


# The SI system of units
SI = UnitSystem([], [])
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
            $unit{promote_type(T, S), n}
        end
        function convert{n, T, S}(::Type{$unit{T, n}}, x::$unit{S, n})
            $unit{T, n}(x.val)
        end
        function convert{n, T, S<:Number}(::Type{$unit{T, n}}, x::S)
            $unit{T, 0}(x)
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

function unitstring{T<:BaseUnit}(x::T)
    unittype = unit(x)
    n = pow(x)
    powerstring = n == 1 ? "" : "^$n"
    string(unittype, powerstring)
end

"""
Represents a general combination of different base units.

The representation is lazy: quantities that are multiplied together
retain their separate values. Those values are only combined upon
printing using the `show` function and on retrieving the value using the
`value` function.

Unit objects have a type invariant which is enforced through all of the
operations defined below, so don't try to hack it by treating them as
tuples on your own! The invariant is that each BaseUnit type appears at
most once in the tuple. This is what you'd expect—although technicaly
units like seconds per second exist, I don't want them to show up here.
"""
typealias Unit Tuple{Vararg{BaseUnit}}

function types(x::Unit)
    map(y->(unit(y), numtype(y), pow(y)), x)
end

function show(io::IO, x::Unit)
    value = mapreduce(y->y.val, *, 1, x)
    unitsstring = mapreduce(
        y->unitstring(y),
        (a, b)->string(a, " ", b),
        "", x)
    print(io, string(value, " ", unitsstring))
end

function *(x::BaseUnit, y::BaseUnit)
    (x, y)
end

function *(x::BaseUnit, y::Unit)

    xsearch = (unit(x), pow(x))
    ylist = types(y)
    ylist = map(x->(x[1], x[3]), ylist)
    xiny = findin(ylist, (xsearch,))
    if length(xiny) == 0
        result = (y..., x)
    elseif length(xiny) == 1
        index = xiny[1]
        firstpart = y[1:index-1]
        updatedpart = y[index] * x
        lastpart = y[index+1:end]
        result = (firstpart..., updatedpart, lastpart...)
    else
        error("Corrupted Unit object: $y")
    end
    result
end

function *(x::Unit, y::Unit)
    result = y
    for quantity in x
        result = quantity * result
    end
    result
end

end
