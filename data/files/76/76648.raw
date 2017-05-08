module Units
# TODO
# * typealiases for abbreviations of concrete types
# * Macro to make typealias for SI prefixes

import Base: +, -, *, /, convert, reduce, promote, promote_rule


type UnitError <: Exception end


abstract Unit
abstract Unitless

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

abstract Energy <: Unit
abstract ElectricCharge <: Unit
abstract ElectricResistance <: Unit


BaseUnit = begin
    tl = [Type{T} for T in subtypes(Unit)]
    Union(tl...)
end

ConcreteUnit = begin
    tl = vcat([subtypes(D) for D in subtypes(Unit)]...)
    tl = [Type{T} for T in tl]
    Union(tl...)
end

SiUnit = begin
    tl = [Meter, Gram, Second]
    tl = [Type{T} for T in tl]
    Union(tl...)
end


immutable Quantity
    mag::Number
    unit::ConcreteUnit
    ord::Number
    base::BaseUnit

    function Quantity(mag::Number, unit::ConcreteUnit, ord::Number)
        if ord == 0
            unit = Unitless
            base = Unitless
        else
            base = super(unit)
        end
        new(mag, unit, ord, base)
    end
end
Quantity(mag, unit) = Quantity(mag, unit, 1)


type Composite
    quants::Array{Quantity, 1}

    function Composite(quants::Array{Quantity, 1})
        if length(quants) == 1
            return quants[1]
        end
        new(quants)
    end
end


# Checks if unit quantities are compatible for conversion
function assert_compatible(x::Quantity, y::Quantity)
    if x.base != y.base
        error(UnitError(), " $(x.base) != $(y.base) : Units must be compatible.")
    elseif x.ord != y.ord
        error(UnitError(), " $(x.ord) != $(y.ord) : Units must be same order.")
    end
end

# Converts unit `x` to unit `y` for units of compatible type.
function convert(y::ConcreteUnit, x::Quantity)
    assert_compatible(x, Quantity(1, y))
    Quantity(ud[x.unit] / ud[y], y, x.ord)
end
function convert(y::Quantity, x::Quantity)
    assert_compatible(x, y)
    Quantity(x.mag * ud[x.unit] / ud[y.unit], y.unit, x.ord)
end
# TODO
# function convert(y::Composite, x::Composite) = nothing
# function convert(y::Quantity, x::Composite) = nothing
# function convert(y::ConcreteUnit, x::Composite) = nothing


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
*(x::ConcreteUnit, y::Number) = Quantity(y, x)
*(x::Number, y::ConcreteUnit) = y * x

# Binary division operator.
/(x::Number, y::Quantity) = Quantity(x / y.mag, y.unit, -1 * y.ord)
/(x::Quantity, y::Number) = x * (1 / y)
function /(x::Quantity, y::Quantity)
    Quantity(x.mag / y.mag * convert(x, y).mag, x.unit, x.ord - y.ord)
end

# Binary exponentiation operator.
^(x::ConcreteUnit, y::Number) = Quantity(1, x, y)
# Add integer to avoid method ambiguity with ^(::Any, ::Integer)
^(x::Quantity, y::Integer) = Quantity(x.mag^y, x.unit, x.ord * y)
^(x::Quantity, y::Number) = Quantity(x.mag^y, x.unit, x.ord * y)


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

# Prefixes
const Yocto = 1e-24
const Zepto = 1e-21
const Atto = 1e-18
const Femto = 1e-15
const Pico = 1e-12
const Nano = 1e-9
const Micro = 1e-6
const Milli = 1e-3
const Centi = 1e-2
const Deca = 1e1
const Hecto = 1e2
const Kilo = 1e3
const Mega = 1e6
const Giga = 1e9
const Tera = 1e12
const Peta = 1e15
const Exa = 1e18
const Zetta = 1e21
const Yotta = 1e24


end  # module Units
