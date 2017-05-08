module Units
### TODO
# * typealiases for abbreviations of concrete types
# * Macro to make typealias for SI prefixes
# * Composite quantities
# * Convert function for composite
# * Reduce function
# * Generate prefixed units in a seperate file and use on import with function
### Sections
# * Exceptions
# * Unit definitions
# * Container Types
# * Operators
# * Printing
###

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
abstract Unitless <: Number
abstract DerivedUnit <: Unit

# Canonical units
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

abstract Temperature <: Unit
abstract Kelvin <: Temperature; typealias K Kelvin

abstract ElectricCurrent <: Unit
abstract Ampere <: ElectricCurrent; typealias A Ampere

abstract AmountOfSubstance <: Unit
abstract Mol <: AmountOfSubstance

abstract LuminousIntensity <: Unit
abstract Candela <: LuminousIntensity

# Derived units
abstract Angle <: DerivedUnit
abstract SolidAngle <: DerivedUnit
abstract Frequency <: DerivedUnit
abstract Force <: DerivedUnit
abstract Pressure <: DerivedUnit
abstract Energy <: DerivedUnit
abstract Power <: DerivedUnit
abstract ElectricCharge <: DerivedUnit
abstract Voltage <: DerivedUnit
abstract ElectricCapacitance <: DerivedUnit
abstract ElectricResistance <: DerivedUnit
abstract ElectricConductance <: DerivedUnit
abstract MagneticFlux <: DerivedUnit
abstract MagneticFieldStrength <: DerivedUnit
abstract Inductance <: DerivedUnit
abstract LuminousFlux <: DerivedUnit
abstract Illuminance <: DerivedUnit
abstract Radioactivity <: DerivedUnit
abstract AbsorbedDose <: DerivedUnit
abstract EquivalentDose <: DerivedUnit
abstract CatalyticActivity <: DerivedUnit
typealias Weight Force
typealias Stress Pressure
typealias Work Energy
typealias Heat Energy
typealias RadiateFlux Power
typealias EMF Voltage
typealias Impedance ElectricResistance
typealias Reactance ElectricResistance


BaseUnit = begin
    tl = [Type{T} for T in subtypes(Unit)]
    Union(tl...)
end

AbstractUnit = begin
    tl = [Type{T} for T in subtypes(DerivedUnit)]
    Union(BaseUnit, tl...)
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
abstract Deci <: Prefix
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
const deci = 1e-1
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

prefix_short_forms = [
    Yocto => "y",
    Zepto => "z",
    Atto => "a",
    Femto => "f",
    Pico => "p",
    Nano => "n",
    Micro => "μ",
    Milli => "m",
    Centi => "c",
    Deci => "d",
    Deca => "da",
    Hecto => "h",
    Kilo => "k",
    Mega => "M",
    Giga => "G",
    Tera => "T",
    Peta => "P",
    Exa => "E",
    Zetta => "Z",
    Yotta => "Y",
]


macro add_prefix(prefix, base)
    pbase = symbol(string(prefix, base))
    pinst = symbol(lowercase(string(prefix, base)))
    pcons = symbol(lowercase(string(prefix)))
    return quote
        abstract $pbase <: super($base)
        const $pinst = UnitDef{$pbase}(
            string($pbase),
            string(prefix_short_forms[$pcons], $base),
            $pcons * $ud[$base].ref,
            $ud[$base].dim,
        )
    end
end
@add_prefix(Centi, Meter)
@add_prefix(Kilo, Gram)

SiUnit = begin
    tl = [Meter, KiloGram, Second]  # FIXME
    tl = [Type{T} for T in tl]
    Union(tl...)
end

CgsUnit = begin
    tl = [CentiMeter, Gram, Second]  # FIXME
    tl = [Type{T} for T in tl]
    Union(tl...)
end


immutable UnitDef{U}  # FIXME more rigorous type defintion
    name::String
    abbrev::String
    ref::Number
    dim::Dimension
end
UnitDef{U}(name, ref, dim) = UnitDef{U}(name, name, ref, dim)

# Length
const meter = UnitDef{Meter}("Meter", "m", 1, Dimension(l=1))
const au = UnitDef{AU}("AU", "au", 2, Dimension(l=1))
const parsec = UnitDef{Parsec}("Parsec", "pc", 3, Dimension(l=1))
# Mass
const gram = UnitDef{Gram}("Gram", "g", 1, Dimension(m=1))
const solarmass = UnitDef{SolarMass}("SolarMass", "Msun", 2, Dimension(m=1))
# Time
const second = UnitDef{Second}("Second", "s", 1, Dimension(t=1))
const year = UnitDef{Year}("Year", "yr", 2, Dimension(t=1))

ud = [
    # Length
    Meter => UnitDef{Meter}("Meter", "m", 1, Dimension(l=1)),
    AU => UnitDef{AU}("AU", "au", 2, Dimension(l=1)),
    Parsec => UnitDef{Parsec}("Parsec", "pc", 3, Dimension(l=1)),
    # Mass
    Gram => UnitDef{Gram}("Gram", "g", 1, Dimension(m=1)),
    SolarMass => UnitDef{SolarMass}("SolarMass", "Msun", 2, Dimension(m=1)),
    # Time
    Second => UnitDef{Second}("Second", "s", 1, Dimension(t=1)),
    Year => UnitDef{Year}("Year", "yr", 2, Dimension(t=1)),
]


# Append prefixes to all concrete units
# FIXME doesn't work because of declaring a type inside a local scope
# such as this `for` loop
#for prefix=subtypes(Prefix), base=ConcreteUnit.types
#    base = base.parameters[1]
#    @add_prefix(prefix, base)
#end


##############################################################################
# Container Types
##############################################################################

immutable Dimension
    l::Number
    m::Number
    t::Number
    i::Number
    θ::Number
    n::Number
    j::Number
    data::AbstractArray

    function Dimension(l=0, m=0, t=0, i=0, θ=0, n=0, j=0)
        data = [l, m, t, i, θ, n, j]
        new(l, m, t, i, θ, n, j, data)
    end
end
Dimension(data::AbstractArray) = Dimension(data...)
const dimensionless = Dimension()


immutable Quantity
    mag::Number
    unit::ConcreteUnit
    ord::Number
    base::BaseUnit
    dim::Dimension

    function Quantity(mag::Number, unit::ConcreteUnit, ord::Number)
        if ord == 0
            return mag
        else
            base = super(unit)
        end
        dim = dimensionless  # FIXME
        new(mag, unit, ord, base, dim)
    end
end
Quantity(mag::Number, unit::ConcreteUnit) = Quantity(mag, unit, 1)


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
Composite(s::String) = parse_unit_string(s)


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
/(x::Quantity, y::ConcreteUnit) = x / (1 * y)
/(x::ConcreteUnit, y::Quantity) = (1 * x) / y

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
    if n.num == 1 & n.den == 1
        return ""
    end
    if n.den == 1
        return string('^', n.num)
    end
    num = [sup_vals[int(string(x))] for x in string(abs(n.num))]
    if n.num < 0
        string(sup_vals[-1], num)
    end
    den = [sub_vals[int(string(x))] for x in string(abs(n.den))]
    string('^', num..., '/', den...)
end
pretty_order(n::Number) = string(n)


function show(io::IO, q::Quantity)
    print("$(q.mag) $(q.unit)$(pretty_order(q.ord))")
end

function show(io::IO, c::Composite)
    print(c.mag)
    for q in c.quants
        print(" $(q.unit)$(pretty_order(q.ord))")
    end
end


end  # module Units
