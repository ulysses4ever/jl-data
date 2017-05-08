"""
This module provides a framework for defining systems of units.
"""
module units
import Base: +, -, *, ^
import Base: convert, show, string

"""
Represents the unit (e.g. seconds, meters) of a quantity.
"""
abstract Unit

"""
Represents a whole system of units.
"""
type UnitSystem
    units::Array{AbstractString}
    abbreviations::Array{AbstractString}
end

"""
Convenience "constructor."
"""
function *{T<:Unit}(x::Number, ::Type{T})
    T(x)
end

"""
Adjust power before constructing an instance (e.g. 5m^2).
"""
^{T<:Unit}(::Type{T}, n::Int) = T{Float64, n}


# The SI system of units
SI = UnitSystem([], [])
push!(SI.units, "Meter")
push!(SI.units, "Second")
push!(SI.abbreviations, "m")
push!(SI.abbreviations, "s")

for unitabbr in zip(SI.units, SI.abbreviations)
    unit = symbol(unitabbr[1])
    abbrtext = unitabbr[2]
    abbr = symbol(abbrtext)

    @eval begin
        immutable $unit{T<:Number, n} <: Unit
            val::T
        end
        pow{T<:Number, n}(quantity::$unit{T, n}) = n
        pow{T<:Number, n}(::Type{$unit{T, n}}) = n
        pow(::Type{$unit}) = 1
        $abbr = $unit
        function show{T<:Number, n}(io::IO, quantity::$unit{T, n})
            powerstring = n == 1 ? "" : "^$n"
            print(io, string(quantity.val, " ", $abbrtext, powerstring))
        end
    end
end

function +{T<:Unit}(x::T, y::T)
    T(x.val + y.val)
end
function -{T<:Unit}(x::T, y::T)
    T(x.val - y.val)
end
end
