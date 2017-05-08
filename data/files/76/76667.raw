module Units
# TODO
# * typealiases for abbreviations of concrete types
# * Macro to make typealias for SI prefixes
# * Composite quantities
# * Convert function for composite
# * Reduce function

import Base: +, -, *, /, convert, reduce, promote, promote_rule


type UnitError <: Exception end


abstract Unit
abstract Unitless

abstract Length <: Unit
abstract Meter <: Length
abstract AU <: Length
abstract Parsec <: Length
typealias m Meter
typealias pc Parsec

abstract Mass <: Unit
abstract Gram <: Mass
abstract SolarMass <: Mass
typealias msol SolarMass

abstract Time <: Unit
abstract Second <: Time
abstract Year <: Time
typealias s Second
typealias yr Year

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
    Quantity(_ud[x.unit] / _ud[y], y, x.ord)
end
function convert(y::Quantity, x::Quantity)
    assert_compatible(x, y)
    Quantity(x.mag * _ud[x.unit] / _ud[y.unit], y.unit, x.ord)
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


global _ud = [
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

abstract Prefix
abstract Yocto <: Prefix
abstract Zepto <: Prefix
abstract Atto <: Prefix
abstract Femto <: Prefix
abstract Pico <: Prefix
abstract Nano <: Prefix
abstract Micro <: Prefix
abstract Milli <: Prefix
abstract Centi <: Prefix
abstract Deca <: Prefix
abstract Hecto <: Prefix
abstract Kilo <: Prefix
abstract Mega <: Prefix
abstract Giga <: Prefix
abstract Tera <: Prefix
abstract Peta <: Prefix
abstract Exa <: Prefix
abstract Zetta <: Prefix
abstract Yotta <: Prefix

const yocto = 1e-24
const zepto = 1e-21
const atto = 1e-18
const femto = 1e-15
const pico = 1e-12
const nano = 1e-9
const micro = 1e-6
const milli = 1e-3
const centi = 1e-2
const deca = 1e1
const hecto = 1e2
const kilo = 1e3
const mega = 1e6
const giga = 1e9
const tera = 1e12
const peta = 1e15
const exa = 1e18
const zetta = 1e21
const yotta = 1e24


macro add_prefix(prefix, base)
    pbase = symbol(string(prefix, base))
    pcons = symbol(lowercase(string(prefix)))
    return quote
        abstract $pbase <: super($base)
        $_ud[$pbase] = $pcons * $_ud[$base]
    end
end
@add_prefix(Kilo, Meter)
@add_prefix(Kilo, Gram)

# Append prefixes to all concrete units
# TODO doesn't work because of declaring a type inside a local scope
#for prefix=subtypes(Prefix), base=ConcreteUnit.types
#    base = base.parameters[1]
#    @add_prefix(prefix, base)
#end


end  # module Units
