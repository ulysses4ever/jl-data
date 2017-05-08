module Units

import Base: +, -, *, /, convert, reduce, promote, promote_rule


type UnitError <: Exception end


abstract Unit
abstract Unitless <: Unit

abstract Length <: Unit
abstract Meter <: Length
abstract AU <: Length
abstract Parsec <: Length

abstract Mass <: Unit
abstract Gram <: Mass
abstract SolarMass <: Mass

abstract Time <: Unit
abstract Second <: Time
abstract Year <: Time

Dimension = Union(Length,
                  Mass,
                  Time,
                  )

ConcreteUnit = begin
    type_arr = vcat([subtypes(D) for D in Dimension.types]...)
    Union(type_arr...)
end


type Quantity
    mag::Number
    unit
    ord::Number
    dim::Dimension

    function Quantity{T<:Unit}(mag::Number, unit::Type{T},
                               ord::Number, dim::Dimension)
        if unit in Dimension
            error(UnitError(), ": Must be a concrete unit.")
        end
        if ord == 0
            unit = Unitless
            dim = Unitless
        else
            dim = super(unit)
        end
        new(mag, unit, ord, dim)
    end
end
Quantity(mag, unit) = Quantity(mag, unit, 1, super(unit))
Quantity(mag, unit, ord) = Quantity(mag, unit, ord, super(unit))


type Composite
    quants::Array{Quantity, 1}

    function Composite(quants::Array{Quantity, 1})
        if length(quants) == 1
            return quants[1]
        end
        new(quants)
    end
end


# Converts unit `x` to unit `y` for units of compatible type.
function convert(y::Quantity, x::Quantity)
    if super(x.unit) != super(y.unit)
        error(UnitError(), ": Units must be of compatible type.")
    elseif x.ord != y.ord
        error(UnitError(), ": Units must be of the same order.")
    else
        return Quantity(x.mag * ud[x.unit] / ud[y.unit], y.unit, x.ord)
    end
end

function convert{T<:Unit}(y::Type{T}, x::Quantity)
    Quantity(ud[x.unit] / ud[y], y, x.ord)
end


# Reduce a composite quantity to the lowest dimensions
function reduce(c::Composite)
    for q in c.quants
        # TODO
    end
end


# Binary addition operator.
function +(x::Quantity, y::Quantity)
    Quantity(x.mag + convert(x, y).mag, x.unit, x.ord)
end

# Binary subtraction operator.
-(x::Quantity, y::Quantity) = x + (-1 * y)

# Binary multiplication operator.
*(x::Number, y::Quantity) = Quantity(x * y.mag, y.unit, y.ord)
*(x::Quantity, y::Number) = Quantity(x.mag * y, x.unit, x.ord)
function *(x::Quantity, y::Quantity)
    Quantity(x.mag * y.mag * convert(x, y).mag, x.unit, x.ord + x.ord)
end
#*{T<:Unit}(x::T, y::Number) = Quantity(y, x)
#*{T<:Unit}(x::Number, y::T) = y * x

# Binary division operator.
/(x::Number, y::Quantity) = Quantity(x / y.mag, y.unit, -1 * y.ord)
/(x::Quantity, y::Number) = x * (1 / y)
function /(x::Quantity, y::Quantity)
    Quantity(x.mag / y.mag * convert(x, y).mag, x.unit, x.ord - y.ord)
end

# Binary exponentiation operator.
#^{T<:Unit}(x::T, y::Number) = Quantity(1, x, y)
#^(x::Quantity, y::Number) = Quantity(x.mag^y, x.unit, x.ord + y)


ud = [
    Unitless => 1.0,
    # Length
    Meter => 1,
    AU => 2.0,
    Parsec => 3.0,
    # Mass
    Gram => 1,
    SolarMass => 2.0,
    # Time
    Second => 1,
    Year => 2.0,
]

end  # module Units
