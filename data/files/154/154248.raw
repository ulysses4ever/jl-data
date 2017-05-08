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
end
