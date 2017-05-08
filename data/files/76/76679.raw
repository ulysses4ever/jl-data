# TODO
# * typealiases for abbreviations of concrete types
# * Macro to make typealias for SI prefixes
# * Composite quantities
# * Convert function for composite
# * Reduce function
module Units

import Base: +, -, *, /, ^, show, convert, reduce, promote, promote_rule


##############################################################################
# Exceptions
##############################################################################

type UnitError <: Exception
    msg::String

    function UnitError(msg::String="")
        new(msg)
    end
end


##############################################################################
# Unit definitions
##############################################################################

abstract Unit
abstract Unitless

abstract Length <: Unit
abstract Meter <: Length; typealias m Meter
abstract AU <: Length; typealias au AU
abstract Parsec <: Length; typealias pc Parsec

abstract Mass <: Unit
abstract Gram <: Mass
abstract SolarMass <: Mass; typealias msol SolarMass

abstract Time <: Unit
abstract Second <: Time; typealias s Second
abstract Year <: Time; typealias yr Year

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


_ud = [
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

macro add_prefix(prefix, base)
    pbase = symbol(string(prefix, base))
    pcons = symbol(lowercase(string(prefix)))
    return quote
        abstract $pbase <: super($base)
        $_ud[$pbase] = $pcons * $_ud[$base]
    end
end
@add_prefix(Centi, Meter)
@add_prefix(Kilo, Gram)

SiUnit = begin
    tl = [Meter, KiloGram, Second]
    tl = [Type{T} for T in tl]
    Union(tl...)
end

CgsUnit = begin
    tl = [CentiMeter, Gram, Second]
    tl = [Type{T} for T in tl]
    Union(tl...)
end

# Append prefixes to all concrete units
# TODO doesn't work because of declaring a type inside a local scope
#for prefix=subtypes(Prefix), base=ConcreteUnit.types
#    base = base.parameters[1]
#    @add_prefix(prefix, base)
#end


##############################################################################
# Quantity and Composite
##############################################################################

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
    mag::Number
    quants::Array{Quantity, 1}

    function Composite(quants::Array{Quantity, 1})
        if length(quants) == 1
            return quants[1]
        end
        mag = prod([q.mag for q in quants])
        quants = [Quantity(1, q.unit, q.ord) for q in quants]
        new(mag, quants)
    end
end


# Checks if unit quantities are compatible for conversion
function assert_compatible(x::Quantity, y::Quantity)
    if x.base != y.base
        throw(UnitError("$(x.base) != $(y.base) : Units must be compatible."))
    elseif x.ord != y.ord
        throw(UnitError("$(x.ord) != $(y.ord) : Units must be same order."))
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


##############################################################################
# Operators
##############################################################################

# Binary addition operator.
function +(x::Quantity, y::Quantity)
    Quantity(x.mag + convert(x, y).mag, x.unit, x.ord)
end

# Binary subtraction operator.
-(x::Quantity, y::Quantity) = x + (-1 * y)

# Binary multiplication operator.
*(x::ConcreteUnit, y::Number) = Quantity(y, x)
*(x::Number, y::ConcreteUnit) = y * x
*(x::Number, y::Quantity) = Quantity(x * y.mag, y.unit, y.ord)
*(x::Quantity, y::Number) = Quantity(x.mag * y, x.unit, x.ord)
function *(x::Quantity, y::Quantity)
    if x.base == y.base
        Quantity(x.mag * y.mag * convert(x, y).mag, x.unit, x.ord + x.ord)
    else
        Composite([x, y])
    end
end
function *(x::Quantity, y::Composite)
    append!(y.quants, [x])
end
*(x::Composite, y::Quantity) = y * x
# TODO handle operations with promote_rule ?
#*(x::Composite, y::ConcreteUnit) =
#*(x::Composite, y::Number) =

# Binary division operator.
/(x::ConcreteUnit, y::Number) = Quantity(1 / y, x)
/(x::Number, y::ConcreteUnit) = Quantity(x, y, -1)
/(x::Number, y::Quantity) = Quantity(x / y.mag, y.unit, -1 * y.ord)
/(x::Quantity, y::Number) = x * (1 / y)
function /(x::Quantity, y::Quantity)
    if x.base == y.base
        Quantity(x.mag / y.mag * convert(x, y).mag, x.unit, x.ord - y.ord)
    else
        Composite([x, 1 / y])
    end
end

# Binary exponentiation operator.
^(x::ConcreteUnit, y::Number) = Quantity(1, x, y)
# Add integer to avoid method ambiguity with ^(::Any, ::Integer)
^(x::Quantity, y::Integer) = Quantity(x.mag^y, x.unit, x.ord * y)
^(x::Quantity, y::Number) = Quantity(x.mag^y, x.unit, x.ord * y)
#^(x::Composite, y::Integer) =
#^(x::Composite, y::Number) =


##############################################################################
# Printing
##############################################################################

const sup_vals = [
    -1 => "⁻",
    0  => "⁰",
    1  => "¹",
    2  => "²",
    3  => "³",
    4  => "⁴",
    5  => "⁵",
    6  => "⁶",
    7  => "⁷",
    8  => "⁸",
    9  => "⁹",
]

const sub_vals = [
    1 => "₁",
    2 => "₂",
    3 => "₃",
    4 => "₄",
    5 => "₅",
    6 => "₆",
    7 => "₇",
    8 => "₈",
    9 => "₉",
]

function pretty_order(n::Rational)
    if n.den == 1
        return string(n.num)
    end
    num = [sup_vals[int(string(x))] for x in string(abs(n.num))]
    if n.num < 0
        string(sup_vals[-1], num)
    end
    den = [sub_vals[int(string(x))] for x in string(abs(n.den))]
    string(num..., '/', den...)
end
pretty_order(n::Number) = string(n)


function show(io::IO, q::Quantity)
    print("$(q.mag) $(q.unit)^$(pretty_order(q.ord))")
end

function show(io::IO, c::Composite)
    print(c.mag)
    for q in c.quants
        print(" $(q.unit)^$(pretty_order(q.ord))")
    end
end


end  # module Units
