module Units
### TODO
# * Macro to make typealias for SI prefixes
# * Composite quantities
# * Convert function for composite
# * Reduce function
# * Generate prefixed units in a seperate file and use on import with function
### Sections
# * Container Types
# * Exceptions
# * Unit Abstracts
# * Prefixes
# * Conversion
# * Operators
# * Printing
###

import Base: +, -, *, /, ^, ==, >, <, <=, >=
import Base: show, showcompact
import Base: convert, promote_rule, promote, reduce


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


immutable UnitDef{U}  # FIXME more rigorous type defintion
    name::String
    abbrev::String
    ref::Number
    dim::Dimension
end
UnitDef(name, ref, dim) = UnitDef(name, name, ref, dim)


immutable Quantity
    unit::UnitDef
    utype::Type
    ord::Number
    base::Type
    dim::Dimension

    function Quantity{U}(unit::UnitDef{U}, ord::Number)
        dim = Dimension((unit.dim.data .* ord)...)
        new(unit, U, ord, super(U), dim)
    end
end
Quantity{U}(unit::UnitDef{U}) = Quantity(unit, 1//1)


type Composite
    mag::Number
    quants::AbstractArray{Quantity, 1}

    function Composite(mag::Number, quants::AbstractArray{Quantity, 1})
        new(mag, quants)
    end
end
Composite(s::String) = eval(parse(s))::Composite


UnitContainer = Union(UnitDef, Quantity, Composite)


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
# Unit abstracts
##############################################################################

abstract Unit
abstract DerivedUnit <: Unit

# Canonical units
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

abstract Temperature <: Unit
abstract Kelvin <: Temperature

abstract ElectricCurrent <: Unit
abstract Ampere <: ElectricCurrent

abstract AmountOfSubstance <: Unit
abstract Mol <: AmountOfSubstance

abstract LuminousIntensity <: Unit
abstract Candela <: LuminousIntensity

# Derived units
abstract Angle <: DerivedUnit
abstract Radian <: Angle

abstract SolidAngle <: DerivedUnit
abstract Steradian <: SolidAngle

abstract Frequency <: DerivedUnit
abstract Hertz <: Frequency

abstract Acceleration <: DerivedUnit
abstract Gal <: Acceleration

abstract Force <: DerivedUnit
abstract Newton <: Force
abstract Dyne <: Force

abstract Pressure <: DerivedUnit
abstract Pascal <: Pressure
abstract Barye <: Pressure

abstract Energy <: DerivedUnit
abstract Joule <: Energy
abstract Erg <: Energy

abstract Power <: DerivedUnit
abstract Watt <: Power

abstract ElectricCharge <: DerivedUnit
abstract Coulomb <: ElectricCharge

abstract Voltage <: DerivedUnit
abstract Volt <: Voltage

abstract ElectricCapacitance <: DerivedUnit
abstract Farad <: ElectricCapacitance

abstract ElectricResistance <: DerivedUnit
abstract Ohm <: ElectricResistance

abstract ElectricConductance <: DerivedUnit
abstract Siemens <: ElectricConductance

abstract MagneticFlux <: DerivedUnit
abstract Weber <: MagneticFlux

abstract MagneticFluxDensity <: DerivedUnit
abstract Tesla <: MagneticFluxDensity

abstract Inductance <: DerivedUnit
abstract Henry <: Inductance

abstract LuminousFlux <: DerivedUnit
abstract Lumen <: LuminousFlux

abstract Illuminance <: DerivedUnit
abstract Lux <: Illuminance

abstract Radioactivity <: DerivedUnit
abstract Becquerel <: Radioactivity

abstract AbsorbedDose <: DerivedUnit
abstract Gray <: AbsorbedDose

abstract EquivalentDose <: DerivedUnit
abstract Sievert <: EquivalentDose

abstract CatalyticActivity <: DerivedUnit
abstract Katal <: CatalyticActivity

abstract DynamicViscosity <: DerivedUnit
abstract Poise <: DynamicViscosity

abstract KinematicViscosity <: DerivedUnit
abstract Stokes <: KinematicViscosity

abstract Wavenumber <: DerivedUnit
abstract Kayser <: Wavenumber

typealias Weight Force
typealias Stress Pressure
typealias Work Energy
typealias Heat Energy
typealias RadiateFlux Power
typealias EMF Voltage
typealias Impedance ElectricResistance
typealias Reactance ElectricResistance
typealias MagneticFieldStrength MagneticFluxDensity


# TODO
# in order for these to work with user defined types, they will have to do:
#     > BaseUnit = Union(BaseUnit, Type{Foo})
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


##############################################################################
# Prefixes
##############################################################################

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
    Micro => "μ",  # Unicde mu
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


# Length
const length_dim = Dimension(1,0,0,0,0,0,0)
const meter = UnitDef{Meter}("Meter", "m", 1, length_dim)
const au = UnitDef{AU}("AU", "au", 2, length_dim)
const parsec = UnitDef{Parsec}("Parsec", "pc", 3, length_dim)
# Mass
const mass_dim = Dimension(0,1,0,0,0,0,0)
const gram = UnitDef{Gram}("Gram", "g", 1, mass_dim)
const solarmass = UnitDef{SolarMass}("SolarMass", "Msun", 2, mass_dim)
# Time
const time_dim = Dimension(0,0,1,0,0,0,0)
const second = UnitDef{Second}("Second", "s", 1, time_dim)
const year = UnitDef{Year}("Year", "yr", 2, time_dim)


macro add_prefix(prefix, base)
    pbase = symbol(string(prefix, base))
    pinst = symbol(lowercase(string(prefix, base)))
    binst = symbol(lowercase(string(base)))
    pcons = symbol(lowercase(string(prefix)))
    #return quote
    @eval begin
        abstract $pbase <: super($base)
        const $pinst = UnitDef{$pbase}(
            string($pbase),
            string(prefix_short_forms[$prefix], $binst.abbrev),
            $pcons * $binst.ref,
            $binst.dim,
        )
    end
end
@add_prefix(Centi, Meter)
@add_prefix(Kilo, Gram)
@add_prefix(Femto, Parsec)

# FIXME add all units for each system
SiUnit = [Meter, KiloGram, Second] |>
         x -> [Type{T} for T in x] |>
         x -> Union(x...)

CgsUnit = [CentiMeter, Gram, Second] |>
          x -> [Type{T} for T in x] |>
          x -> Union(x...)


# Append prefixes to all concrete units.
# FIXME Meta-meta programming, ugly, but until a better way
# is figured out, necessary, because abstracts, exports, and evals
# have to be in the module's top level.
function gen_prefixes()
    open("PrefixUnits.jl", "w") do filen
        write(filen, "module PrefixUnits\n\n")
        write(filen, "import Units: @add_prefix\n\n")
        for prefix=subtypes(Prefix), base=ConcreteUnit.types
            base = base.parameters[1]
            write(filen, "@add_prefix($prefix, $base)\n")
        end
        write(filen, "\nend\n")
    end
end


##############################################################################
# Conversion
##############################################################################

convert{U}(::Type{Quantity}, x::UnitDef{U}) = Quantity(x)
convert(::Type{Composite}, x::Quantity) = Composite([x])

promote_rule{U}(::Type{UnitDef{U}}, ::Type{Quantity}) = Quantity
promote_rule(::Type{Quantity}, ::Type{Composite}) = Composite


function check_base(x::Quantity, y::Quantity)
    if !is(x.base, y.base)
        throw(UnitError("$(x.base) != $(y.base) : Bases must be compatible."))
    end
end

function check_dim(x::Quantity, y::Quantity)
    if x.dim != y.dim
        throw(UnitError("$(x.dim) != $(y.dim) : Dimensions must be compatible."))
    end
end
function check_dim(x::Composite, y::Composite)
    xdim = sum([q.dim for q in x.quants])
    ydim = sum([q.dim for q in y.quants])
    if xdim != ydim
        throw(UnitError("$(xdim) != $(ydim) : Dimensions must be compatible."))
    end
end

function check_order(x::Quantity, y::Quantity)
    if x.ord != y.ord
        throw(UnitError("$(x.ord) != $(y.ord) : Units must be same order."))
    end
end

function check_compatible(x::Quantity, y::Quantity)
    check_dim(x, y)
    check_order(x, y)
end

# Unit conversion from `x` to unit `y` for units of compatible type.
function to(x::Quantity, y::Quantity)
    check_compatible(x, y)
    Quantity(x.mag * y.mag * (y.unit.ref / x.unit.ref),
             y.unit, y.ord)
end
function to(x::Composite, y::Composite)
    # FIXME
end


# Reduce a composite quantity to the lowest dimensions
function reduce(c::Composite)
    for q in c.quants
        # FIXME
        # Group into same base
        # Perform conversion and multiplication for each quantity in base
        # Reassign quantities
    end
end


##############################################################################
# Operators
##############################################################################

# Binary addition operator. Returned in units of the first argument.
function +(x::Quantity, y::Quantity)
    Quantity(x.mag + to(x, y).mag, x.unit, x.ord)
end
function +(x::Composite, y::Composite)
    check_dim(x, y)
    x = reduce(x)
    y = reduce(y)
    # FIXME
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


# Catch-all
+(x::UnitContainer, y::UnitContainer) = +(promote(x, y)...)
-(x::UnitContainer, y::UnitContainer) = -(promote(x, y)...)
*(x::UnitContainer, y::UnitContainer) = *(promote(x, y)...)
/(x::UnitContainer, y::UnitContainer) = /(promote(x, y)...)


# Dimension
-(x::Dimension) = Dimension((-x.data)...)
+(x::Dimension, y::Dimension) = Dimension((x.data .+ y.data)...)
-(x::Dimension, y::Dimension) = Dimension((x.data .- y.data)...)
*(x::Dimension, y::Dimension) = Dimension((x.data .* y.data)...)
/(x::Dimension, y::Dimension) = Dimension((x.data ./ y.data)...)
==(x::Dimension, y::Dimension) = x.data .== y.data
!=(x::Dimension, y::Dimension) = x.data .!= y.data


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
pretty_order(n::Number) = string('^', n)


function show(io::IO, d::Dimension)
    print("Dimension(d=$(d.l), m=$(d.m), t=$(d.t), " *
          "i=$(d.i), θ=$(d.θ), n=$(d.n), j=$(d.j))")
end
showcompact(io::IO, d::Dimension) = print(d.data')

show(io::IO, u::UnitDef) = print(io, u.name)
showcompact(io::IO, u::UnitDef) = print(io, u.abbrev)

function show(io::IO, q::Quantity)
    print(io, "$(q.mag) $(q.unit.name)$(pretty_order(q.ord))")
end

function showcompact(io::IO, q::Quantity)
    print(io, "$(q.mag) $(q.unit.abbrev)$(pretty_order(q.ord))")
end

function show(io::IO, c::Composite)
    print(io, c.mag)
    for q in c.quants
        print(io, " $(q.unit.name)$(pretty_order(q.ord))")
    end
end

function showcompact(io::IO, c::Composite)
    print(io, c.mag)
    for q in c.quants
        print(io, " $(q.unit.abbrev)$(pretty_order(q.ord))")
    end
end


end  # module Units
