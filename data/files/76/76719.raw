module Units
### Sections
# * Container Types
# * Exceptions
# * Unit Abstracts
# * Prefixes
# * Conversion
# * Operators
# * Printing
### TODO
# * Compose units to a set of preferred unit forms
# * Array operators
# * Full type coverage in `Composite` string parsing
# * Add all units
# * Parse CODATA
# * Unit system based `to` method
###

import Base: +, -, *, /, ^, ==, >, <, <=, >=
import Base: zero
import Base: show, showcompact, copy
import Base: convert, promote_rule, promote


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


immutable UnitDef
    utype::Type
    name::String
    abbrev::String
    ref::Number
    dim::Dimension

    function UnitDef(utype::Type, abbrev::String,
                     ref::Number, dim::Dimension)
        new(utype, string(utype), abbrev, ref, dim)
    end
end
function UnitDef(utype::Type, ref::Number, dim::Dimension)
    UnitDef(utype, string(utype), ref, dim)
end


immutable Quantity
    unit::UnitDef
    ord::Number
    base::Type
    dim::Dimension

    function Quantity(unit::UnitDef, ord::Number)
        dim = unit.dim * ord
        new(unit, ord, super(unit.utype), dim)
    end
end
Quantity(unit::UnitDef) = Quantity(unit, 1//1)


type Composite
    mag::Number
    quants::AbstractArray{Quantity, 1}

    function Composite(mag::Number, quants::AbstractArray{Quantity, 1})
        new(mag, quants)
    end
end
Composite(mag::Number, quants::AbstractArray{None, 1}) = mag
Composite(quants::AbstractArray{Quantity, 1}) = Composite(1, quants)
Composite(q::Quantity) = [q] |> Composite
Composite(u::UnitDef) = u |> Quantity |> Composite
Composite(mag::Number, u::UnitDef) = Composite(mag, [Quantity(u)])
Composite(mag::Number, c::Composite) = Composite(mag, c.quants)
Composite(c::Composite) = c
Composite(s::String) = s |> parse |> eval |> Composite


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
abstract StatAmpere <: ElectricCurrent

abstract AmountOfSubstance <: Unit
abstract Mole <: AmountOfSubstance

abstract LuminousIntensity <: Unit
abstract Candela <: LuminousIntensity

# Derived units
abstract Angle <: DerivedUnit
abstract Radian <: Angle
abstract ArcSecond <: Angle
abstract ArcMinute <: Angle
abstract ArcHour <: Angle
abstract Degree <: Angle

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
BaseUnit = subtypes(Unit) |>
    x -> [Type{T} for T in x] |>
    x -> Union(x...)

AbstractUnit = subtypes(DerivedUnit) |>
    x -> [Type{T} for T in x] |>
    x -> Union(BaseUnit, x...)

ConcreteUnit = subtypes(Unit) |>
    x -> [subtypes(D) for D in x] |>
    x -> vcat(x...) |>
    x -> [Type{T} for T in x] |>
    x -> Union(x...)


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
const l_dim = Dimension(1,0,0,0,0,0,0)
const meter = UnitDef(Meter, "m", 1, l_dim)
const au = UnitDef(AU, "au", 2, l_dim)
const parsec = UnitDef(Parsec, "pc", 3, l_dim)
# Mass
const m_dim = Dimension(0,1,0,0,0,0,0)
const gram = UnitDef(Gram, "g", 1e-3, m_dim)
const solarmass = UnitDef(SolarMass, "Msun", 2, m_dim)
# Time
const t_dim = Dimension(0,0,1,0,0,0,0)
const second = UnitDef(Second, "s", 1, t_dim)
const year = UnitDef(Year, "yr", 2, t_dim)
# ElectricCurrent
const i_dim = Dimension(0,0,0,1,0,0,0)
const ampere = UnitDef(Ampere, "A", 1, i_dim)
const statampere = UnitDef(StatAmpere, "statA", 1, i_dim)
# Temperature
const θ_dim = Dimension(0,0,0,0,1,0,0)
const kelvin = UnitDef(Kelvin, "K", 1, θ_dim)
# AmountOfSubstance
const n_dim = Dimension(0,0,0,0,0,1,0)
const mole = UnitDef(Mole, "mol", 1, n_dim)
# LuminousIntensity
const j_dim = Dimension(0,0,0,0,0,0,1)
const candela = UnitDef(Candela, "cd", 1, j_dim)


macro add_prefix(prefix, base)
    pbase = symbol(string(prefix, base))
    pinst = symbol(lowercase(string(prefix, base)))
    binst = symbol(lowercase(string(base)))
    pcons = symbol(lowercase(string(prefix)))
    #return quote
    @eval begin
        abstract $pbase <: super($base)
        const $pinst = UnitDef(
            $pbase,
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
si = {
    Length => meter,
    Mass => kilogram,
    Time => second,
    Temperature => kelvin,
    ElectricCurrent => ampere,
    AmountOfSubstance => mole,
    LuminousIntensity => candela,
}

CgsUnit = [CentiMeter, Gram, Second] |>
    x -> [Type{T} for T in x] |>
    x -> Union(x...)
cgs = {
    Length => centimeter,
    Mass => gram,
    Time => second,
    Temperature => kelvin,
    ElectricCurrent => statampere,
    AmountOfSubstance => mole,
    LuminousIntensity => candela,
}


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

convert(::Type{Quantity}, x::UnitDef) = Quantity(x)
convert(::Type{Composite}, x::UnitDef) = Composite(x)
convert(::Type{Composite}, x::Quantity) = Composite(x)

promote_rule(::Type{UnitDef}, ::Type{Quantity}) = Quantity
promote_rule(::Type{UnitDef}, ::Type{Composite}) = Composite
promote_rule(::Type{Quantity}, ::Type{Composite}) = Composite

copy(q::Quantity) = Quantity(q.unit, copy(q.ord))
copy(c::Composite) = Composite(copy(c.mag), copy(c.quants))

get_dim(u::UnitDef) = u.dim
get_dim(q::Quantity) = q.dim
get_dim(x::Composite) = sum([q.dim for q in x.quants])

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
    xdim = get_dim(x)
    ydim = get_dim(y)
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
check_compatible(x::Composite, y::Composite) = check_dim(x, y)

# Unit conversion from `x` to unit `y` for units of compatible type.
function to(x::Composite, y::Composite)
    check_compatible(x, y)
    xs = sys_decompose(x)
    ys = sys_decompose(y)
    Composite(xs.mag / ys.mag, y.quants)
end
function to(x::UnitContainer, y::UnitContainer)
    x, y, _ = promote(x, y, Composite(meter))
    to(promote(x, y)...)
end

# Decompose a composite quantity to the lowest dimensions
# usys::Dict -> unit system dictionary, default `si`
function decompose(c::Composite; usys::Dict=si)
    bases = unique([q.base for q in c.quants])
    mag = c.mag
    new_quants = Quantity[]
    for base in bases
        usys_pref = usys[base]
        base_quants = filter(q -> q.base == base, c.quants)
        mag *= prod([q.unit.ref^q.ord for q in base_quants])
        ord = sum([q.ord for q in base_quants])
        if ord != 0
            push!(new_quants, Quantity(usys_pref, ord))
        end
    end
    Composite(mag, new_quants)
end


# Decompose a composite quantity to the canonical units
# of the unit system.
# usys::Dict -> unit system dictionary, default `si`
function sys_decompose(c::Composite; usys::Dict=si)
    mag = c.mag
    dim = dimensionless
    new_quants = Quantity[]
    for q in c.quants
        mag *= q.unit.ref^q.ord
        dim += q.dim
    end
    bases = [Length, Mass, Time, Temperature, ElectricCurrent,
        AmountOfSubstance, LuminousIntensity]
    for (b, d) in zip(bases, dim.data)
        if d != 0
            push!(new_quants, Quantity(usys[b], d))
        end
    end
    Composite(mag, new_quants)
end


# Composte a composite quantity to a set of preferred derived
# and canonical units of the unit system.
function compose(c::Composite; usys::Dict=si)
    # FIXME
    # Treat as an eigenvalue problem using the dimensions,
    # with the basis vectors being first the derived units.
    # Then, look at the "left-over" dimensional values,
    # and fill those in with the concrete base units.
end


##############################################################################
# Operators
##############################################################################

# Binary addition operator. Returned in units of the first argument.
function +(x::Composite, y::Composite)
    check_dim(x, y)
    x = decompose(x)
    y = decompose(y)
    Composite(x.mag + y.mag, x.quants)
end

# Unary subtraction operator
-(x::UnitDef) = Composite(-1, [x])
-(x::Composite) = Composite(-x.mag, x.quants)

# Binary subtraction operator.
function -(x::Composite, y::Composite)
    x + Composite(-y.mag, y.quants)
end

# Binary multiplication operator.
*(x::UnitDef, y::Number) = Composite(y, x)
*(x::Number, y::UnitDef) = Composite(x, y)
*(x::Composite, y::Number) = Composite(y * x.mag, x.quants)
*(x::Number, y::Composite) = y * x
function *(x::Composite, y::Composite)
    x = copy(x)
    y = copy(y)
    xlen = length(x.quants)
    mag = x.mag * y.mag
    while length(y.quants) != 0
        yq = pop!(y.quants)
        for ii=[1:xlen]
            if x.quants[ii].unit == yq.unit
                xq = x.quants[ii]
                x.quants[ii] = Quantity(xq.unit, xq.ord + yq.ord)
                break
            else
                push!(x.quants, yq)
                break
            end
        end
    end
    x.quants = filter(q -> q.ord != 0, x.quants)
    Composite(mag, x.quants)
end

# Binary division operator.
/(x::UnitDef, y::Number) = Composite(inv(y), x)
/(x::Number, y::UnitDef) = Composite(x, [Quantity(y, -1)])
/(x::Composite, y::Number) = Composite(x.mag / y, x.quants)
function /(x::Number, y::Composite)
    y = Composite(x * inv(y.mag), [Quantity(q.unit, -q.ord) for q in y.quants])
end
function /(x::Composite, y::Composite)
    y = copy(y)
    y = Composite(y.mag, [Quantity(q.unit, -q.ord) for q in y.quants])
    x * y
end

# Binary exponentiation operator.
# Add `Integer` method to avoid method ambiguity with ^(::Any, ::Integer)
^(x::UnitDef, y::Integer) = x^Rational(y)
^(x::UnitDef, y::Number) = Composite(one(y), [Quantity(x, y)])
^(x::Quantity, y::Integer) = x^Rational(y)
^(x::Quantity, y::Number) = Quantity(x.unit, x.ord * y)
^(x::Composite, y::Integer) = x^Rational(y)
function ^(x::Composite, y::Number)
    x = copy(x)
    mag = x.mag^y
    new_quants = [Quantity(q.unit, q.ord * y) for q in x.quants]
    Composite(mag, new_quants)
end


# Catch-all, force conversion to Composite
function +(x::UnitContainer, y::UnitContainer)
    x, y, _ = promote(x, y, Composite(meter))
    +(promote(x, y)...)
end
function -(x::UnitContainer, y::UnitContainer)
    x, y, _ = promote(x, y, Composite(meter))
    -(promote(x, y)...)
end
function *(x::UnitContainer, y::UnitContainer)
    x, y, _ = promote(x, y, Composite(meter))
    *(promote(x, y)...)
end
function /(x::UnitContainer, y::UnitContainer)
    x, y, _ = promote(x, y, Composite(meter))
    /(promote(x, y)...)
end


# Dimension
convert{T<:Number}(::Type{Dimension}, x::T) = Dimension((dimensionless.data .+ x)...)
promote_rule{T<:Number}(::Type{Dimension}, ::Type{T}) = Dimension

-(x::Dimension) = Dimension((-x.data)...)
+(x::Dimension, y::Dimension) = Dimension((x.data .+ y.data)...)
-(x::Dimension, y::Dimension) = Dimension((x.data .- y.data)...)
*(x::Dimension, y::Dimension) = Dimension((x.data .* y.data)...)
/(x::Dimension, y::Dimension) = Dimension((x.data ./ y.data)...)
^(x::Dimension, y::Integer) = Dimension(x.data .^ y)
^(x::Dimension, y::Number) = Dimension(x.data .^ y)
==(x::Dimension, y::Dimension) = all(x.data .== y.data)
!=(x::Dimension, y::Dimension) = any(x.data .!= y.data)

zero(::Dimension) = dimensionless

NumberOrDim = Union(Dimension, Number)
+(x::NumberOrDim, y::NumberOrDim) = +(promote(x, y)...)
-(x::NumberOrDim, y::NumberOrDim) = -(promote(x, y)...)
*(x::NumberOrDim, y::NumberOrDim) = *(promote(x, y)...)
/(x::NumberOrDim, y::NumberOrDim) = /(promote(x, y)...)


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
    print(io, "$(q.unit.name)$(pretty_order(q.ord))")
end

function showcompact(io::IO, q::Quantity)
    print(io, "$(q.unit.abbrev)$(pretty_order(q.ord))")
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
