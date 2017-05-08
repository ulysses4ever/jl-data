"""
This module provides a framework for defining systems of units.
"""
module units
import Base: +, -, *, ^, /
import Base: convert, show, string, promote_rule

"""
Represents the unit (e.g. seconds, meters) of a quantity.
"""
abstract BaseUnit
typealias Unit Tuple{Vararg{BaseUnit}}

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
push!(SI.abbreviations, "m")
push!(SI.abbreviations, "s")
push!(SI.abbreviations, "kg")

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
        $abbr = $unit
        function show{T<:Number, n}(io::IO, quantity::$unit{T, n})
            powerstring = n == 1 ? "" : "^$n"
            print(io, string(quantity.val, " ", $abbrtext, powerstring))
        end
        function promote_rule{n, T, S}(::Type{$unit{T, n}},
            ::Type{$unit{S, n}})
            $unit{promote_type(T, S), n}
        end
        function promote_rule{n, m, T, S}(::Type{$unit{T, n}},
            ::Type{$unit{S, m}})
            error("Incompatible powers: $n ≠ $m")
        end
        function convert{n, S, T}(::Type{$unit{S, n}}, x::$unit{T, n})
            $unit{S, n}(x.val)
        end
        function *{T, n}(x::Number, ::Type{$unit{T, n}})
            $unit{T, n}(x)
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

+{T<:BaseUnit, S<:BaseUnit}(x::T, y::S) = +(promote(x, y)...)
-{T<:BaseUnit, S<:BaseUnit}(x::T, y::S) = -(promote(x, y)...)
end
