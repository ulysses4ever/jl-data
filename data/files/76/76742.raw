module Units
### Sections
# * Container Types
# * Exceptions
# * Unit Definitions
# * Prefixes
# * Unit Systems
# * Conversion
# * Operators
# * Printing
### TODO
# * Compose units to a set of preferred unit forms with `compose` function
# * Array operators
# * Support all mathematical functions in Base on `Composite`
# * Add all prefixes
# * Parse CODATA for physical constants
# * Unit system based `to` method
# * Complete treatment of CGS electromagnetic systems, emu/esu/gauss
# * Add full test coverage
# * Add full documentation
###

import Base: +, -, *, /, \, ^, ==, !=, >, <, <=, >=
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

    function UnitDef(utype::Type, abbrev::String, ref::Number, dim::Dimension)
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
# Unit Definitions
##############################################################################

# Speed of light (in a vacuum) factor, m / s
const _c = 299792458.0

abstract Unit
abstract DerivedUnit <: Unit

# Canonical units
# Length
abstract Length <: Unit
abstract Meter <: Length
abstract AstronomicalUnit <: Length
abstract Parsec <: Length
abstract Angstrom <: Length
const l_dim = Dimension(1,0,0,0,0,0,0)
const meter = UnitDef(Meter, "m", 1, l_dim)
const astronomicalunit = UnitDef(AstronomicalUnit, "AU", 1.495978707e11, l_dim)
const parsec = UnitDef(Parsec, "pc", 3.0856776e16, l_dim)
const angstrom = UnitDef(Angstrom, "Å", 1e-10, l_dim)

# Mass
abstract Mass <: Unit
abstract Gram <: Mass
abstract Tonne <: Mass
const m_dim = Dimension(0,1,0,0,0,0,0)
const gram = UnitDef(Gram, "g", 1e-3, m_dim)
const tonne = UnitDef(Tonne, "t", 1e3, m_dim)

# Time
abstract Time <: Unit
abstract Second <: Time
abstract Minute <: Time
abstract Hour <: Time
abstract Day <: Time
abstract Year <: Time
const t_dim = Dimension(0,0,1,0,0,0,0)
const second = UnitDef(Second, "s", 1, t_dim)
const minute = UnitDef(Minute, "min", 60, t_dim)
const hour = UnitDef(Hour, "h", 3600, t_dim)
const day = UnitDef(Day, "d", 86400, t_dim)
const year = UnitDef(Year, "yr", 3.15576e7, t_dim)

# ElectricCurrent
abstract ElectricCurrent <: Unit
abstract Ampere <: ElectricCurrent
abstract AbAmpere <: ElectricCurrent
abstract StatAmpere <: ElectricCurrent
const i_dim = Dimension(0,0,0,1,0,0,0)
const ampere = UnitDef(Ampere, "A", 1, i_dim)
const abampere = UnitDef(AbAmpere, "abA", 10, i_dim)
const statampere = UnitDef(StatAmpere, "statA", 3.335641e-10, i_dim)
typealias Biot AbAmpere

# Temperature
abstract Temperature <: Unit
abstract Kelvin <: Temperature
const θ_dim = Dimension(0,0,0,0,1,0,0)
const kelvin = UnitDef(Kelvin, "K", 1, θ_dim)
typealias Centigrade Kelvin

# AmountOfSubstance
abstract AmountOfSubstance <: Unit
abstract Mole <: AmountOfSubstance
const n_dim = Dimension(0,0,0,0,0,1,0)
const mole = UnitDef(Mole, "mol", 1, n_dim)

# LuminousIntensity
abstract LuminousIntensity <: Unit
abstract Candela <: LuminousIntensity
const j_dim = Dimension(0,0,0,0,0,0,1)
const candela = UnitDef(Candela, "cd", 1, j_dim)

# Derived Units
# Plane angle
abstract Angle <: DerivedUnit
abstract Radian <: Angle
abstract Degree <: Angle
abstract ArcHour <: Angle
abstract ArcMinute <: Angle
abstract ArcSecond <: Angle
const radian = UnitDef(Radian, "rad", 1, dimensionless)
const degree = UnitDef(Degree, "°", 2π / 360, dimensionless)
const archour = UnitDef(ArcHour, "archr", 24 * 2π / 360, dimensionless)
const arcminute = UnitDef(ArcMinute, "arcmin", 2π / (360 * 60), dimensionless)
const arcsecond = UnitDef(ArcSecond, "arcsec", 2π / (360 * 60 * 60), dimensionless)

# Solid Angle
abstract SolidAngle <: DerivedUnit
abstract Steradian <: SolidAngle
const steradian = UnitDef(Steradian, "sr", 1, dimensionless)

# Area
abstract Area <: DerivedUnit
abstract Hectare <: Area
abstract Are <: Area
abstract Acre <: Area
abstract Barn <: Area
const area_dim = Dimension(2,0,0,0,0,0,0)
const hectare = UnitDef(Hectare, "ha", 1e5, area_dim)
const are = UnitDef(Are, "are", 1e2, area_dim)
const acre = UnitDef(Acre, "ac", 4046.8564224, area_dim)
const barn = UnitDef(Barn, "b", 1e-28, area_dim)

# Volume
abstract Volume <: DerivedUnit
abstract Litre <: Volume
const volume_dim = Dimension(3,0,0,0,0,0,0)
const litre = UnitDef(Litre, "l", 0.001, volume_dim)

# Frequency
abstract Frequency <: DerivedUnit
abstract Hertz <: Frequency
const frequency_dim = Dimension(0,0,-1,0,0,0,0)
const hertz = UnitDef(Hertz, "Hz", 1, frequency_dim)

# Acceleration
abstract Acceleration <: DerivedUnit
abstract Gal <: Acceleration
const acceleration_dim = Dimension(1,0,2,0,0,0,0)
const gal = UnitDef(Gal, "gal", 1e-2, acceleration_dim)

# Force
abstract Force <: DerivedUnit
abstract Newton <: Force
abstract Dyne <: Force
abstract Sthene <: Force
const force_dim = Dimension(1,1,-2,0,0,0,0)
const newton = UnitDef(Newton, "N", 1, force_dim)
const dyne = UnitDef(Dyne, "dyn", 1e-5, force_dim)
const sthene = UnitDef(Sthene, "sn", 1e3, force_dim)

# Pressure
abstract Pressure <: DerivedUnit
abstract Pascal <: Pressure
abstract Bar <: Pressure
abstract Barye <: Pressure
abstract Pieze <: Pressure
abstract TechnicalAtmosphere <: Pressure
abstract Atmosphere <: Pressure
abstract Torr <: Pressure
abstract Psi <: Pressure
const pressure_dim = Dimension(-1,1,-2,0,0,0,0)
const pascal = UnitDef(Pascal, "Pa", 1, pressure_dim)
const bar = UnitDef(Bar, "bar", 1e5, pressure_dim)
const barye = UnitDef(Barye, "Ba", 1e-1, pressure_dim)
const pieze = UnitDef(Pieze, "pz", 1e3, pressure_dim)
const technicalatmosphere = UnitDef(TechnicalAtmosphere, "at", 0.980665e5, pressure_dim)
const atmosphere = UnitDef(Atmosphere, "atm", 1.01325e5, pressure_dim)
const torr = UnitDef(Torr, "torr", 133.3224, pressure_dim)
const psi = UnitDef(Psi, "psi", 6.8948e3, pressure_dim)

# Energy
abstract Energy <: DerivedUnit
abstract Joule <: Energy
abstract Erg <: Energy
abstract ElectronVolt <: Energy
abstract Calorie <: Energy
abstract Btu <: Energy
const energy_dim = Dimension(2,1,-2,0,0,0,0)
const joule = UnitDef(Joule, "J", 1, energy_dim)
const erg = UnitDef(Erg, "erg", 1e-7, energy_dim)
const electronvolt = UnitDef(ElectronVolt, "eV", 1.602176565e-19, energy_dim)
const calorie = UnitDef(Calorie, "cal", 4.184, energy_dim)
const btu = UnitDef(Btu, "btu", 1055.056, energy_dim)  # ISO 31-4

# Power
abstract Power <: DerivedUnit
abstract Watt <: Power
abstract SolarLuminosity <: Power
abstract HorsePower <: Power
const power_dim = Dimension(2,1,-3,0,0,0,0)
const watt = UnitDef(Watt, "W", 1, power_dim)
const solarluminosity = UnitDef(SolarLuminosity, "Lsol", 3.846e26, power_dim)
const horsepower = UnitDef(HorsePower, "HP", 745.7, power_dim)

# Electric charge
abstract Charge <: DerivedUnit
abstract Coulomb <: Charge
abstract AbCoulomb <: Charge
abstract StatCoulomb <: Charge
const charge_dim = Dimension(0,0,1,1,0,0,0)
const coulomb = UnitDef(Coulomb, "C", 1, charge_dim)
const abcoulomb = UnitDef(AbCoulomb, "abC", 10, charge_dim)
const statcoulomb = UnitDef(StatCoulomb, "statC", 0.1 / _c, charge_dim)
const franklin = statcoulomb
typealias Franklin StatCoulomb

# Voltage
abstract Voltage <: DerivedUnit
abstract Volt <: Voltage
abstract AbVolt <: Voltage
abstract StatVolt <: Voltage
const voltage_dim = Dimension(2,1,-3,-1,0,0,0)
const volt = UnitDef(Volt, "V", 1, voltage_dim)
const abvolt = UnitDef(AbVolt, "abV", 1e-8, voltage_dim)
const statvolt = UnitDef(StatVolt, "statV", 1e-6 * _c, voltage_dim)

# Electric capacitance
abstract Capacitance <: DerivedUnit
abstract Farad <: Capacitance
abstract AbFarad <: Capacitance
abstract StatFarad <: Capacitance
const capacitance_dim = Dimension(-2,-1,4,2,0,0,0)
const farad = UnitDef(Farad, "F", 1, capacitance_dim)
const abfarad = UnitDef(AbFarad, "abF", 1e9, capacitance_dim)
const statfarad = UnitDef(StatFarad, "statF", 1e5 * _c^-2, capacitance_dim)

# Electric resistance
abstract Resistance <: DerivedUnit
abstract Ohm <: Resistance
abstract AbOhm <: Resistance
abstract StatOhm <: Resistance
const resistance_dim = Dimension(2,1,-3,-2,0,0,0)
const ohm = UnitDef(Ohm, "Ω", 1, resistance_dim)
const abohm = UnitDef(AbOhm, "abΩ", 1e-9, resistance_dim)
const statohm = UnitDef(StatOhm, "statΩ", 1e-5 * _c^2, resistance_dim)

# Electric conductance
abstract Conductance <: DerivedUnit
abstract Siemens <: Conductance
abstract Mho <: Conductance
abstract AbMho <: Conductance
abstract StatMho <: Conductance
const conductance_dim = Dimension(-2,-1,3,2,0,0,0)
const siemens = UnitDef(Siemens, "S", 1, conductance_dim)
const mho = UnitDef(Mho, "℧", 0.99951, conductance_dim)
const abmho = UnitDef(AbMho, "ab℧", 1e9, conductance_dim)
const statmho = UnitDef(StatMho, "stat℧", 1e5 / _c^2, conductance_dim)

# Electric dipole moment
abstract ElectricDipoleMoment <: DerivedUnit
abstract Debye <: ElectricDipoleMoment
const electricdipolemoment_dim = Dimension(1,0,1,1,0,0,0)
const debye = UnitDef(Debye, "D", 1e-21 / _c, electricdipolemoment_dim)

# Magnetic flux
abstract MagneticFlux <: DerivedUnit
abstract Weber <: MagneticFlux
abstract Maxwell <: MagneticFlux
const magneticflux_dim = Dimension(2,1,-2,-1,0,0,0)
const weber = UnitDef(Weber, "Wb", 1, magneticflux_dim)
const maxwell = UnitDef(Maxwell, "Mx", 1e-8, magneticflux_dim)

# Magnetic flux density
abstract MagneticFluxDensity <: DerivedUnit
abstract Tesla <: MagneticFluxDensity
abstract Gauss <: MagneticFluxDensity
const magneticfluxdensity_dim = Dimension(0,1,-2,-1,0,0,0)
const tesla = UnitDef(Tesla, "T", 1, magneticfluxdensity_dim)
const gauss = UnitDef(Gauss, "G", 1e-4, magneticfluxdensity_dim)

# Inductance
abstract Inductance <: DerivedUnit
abstract Henry <: Inductance
abstract AbHenry <: Inductance
abstract StatHenry <: Inductance
const inductance_dim = Dimension(2,1,-2,-2,0,0,0)
const henry = UnitDef(Henry, "H", 1, inductance_dim)
const abhenry = UnitDef(AbHenry, "abH", 1e-9, inductance_dim)
const stathenry = UnitDef(StatHenry, "statH", 1e-5 * _c^2, inductance_dim)

# Luminous flux
abstract LuminousFlux <: DerivedUnit
abstract Lumen <: LuminousFlux
const luminousflux_dim = Dimension(0,0,0,0,0,0,1)
const lumen = UnitDef(Lumen, "lm", 1, luminousflux_dim)

# Illuminance
abstract Illuminance <: DerivedUnit
abstract Lux <: Illuminance
const illuminance_dim = Dimension(-2,0,0,0,0,0,1)
const lux = UnitDef(Lux, "lx", 1, illuminance_dim)

# Radioactivity
abstract Radioactivity <: DerivedUnit
abstract Becquerel <: Radioactivity
abstract Curie <: Radioactivity
const radioactivity_dim = Dimension(0,0,-1,0,0,0,0)
const becquerel = UnitDef(Becquerel, "Bq", 1, radioactivity_dim)
const curie = UnitDef(Curie, "Ci", 3.70e10, radioactivity_dim)

# Absorbed dose
abstract AbsorbedDose <: DerivedUnit
abstract Gray <: AbsorbedDose
abstract Rad <: AbsorbedDose
const absorbeddose_dim = Dimension(2,0,-2,0,0,0,0)
const gray = UnitDef(Gray, "Gy", 1, absorbeddose_dim)
const rad = UnitDef(Rad, "rad", 0.01, absorbeddose_dim)

# Equivalent dose
abstract EquivalentDose <: DerivedUnit
abstract Sievert <: EquivalentDose
abstract Rem <: EquivalentDose
const equivalentdose_dim = Dimension(2,0,-2,0,0,0,0)
const sievert = UnitDef(Sievert, "Sv", 1, equivalentdose_dim)
const rem = UnitDef(Rem, "rem", 0.01, equivalentdose_dim)

# Catalytic activity
abstract CatalyticActivity <: DerivedUnit
abstract Katal <: CatalyticActivity
const catalyticactivity_dim = Dimension(0,0,-1,0,0,1,0)
const katal = UnitDef(Katal, "kat", 1, catalyticactivity_dim)

# Dynamic viscosity
abstract DynamicViscosity <: DerivedUnit
abstract Poise <: DynamicViscosity
const dynamicviscosity_dim = Dimension(-1,1,-1,0,0,0,0)
const poise = UnitDef(Poise, "P", 0.1, dynamicviscosity_dim)

# Kinematic viscosity
abstract KinematicViscosity <: DerivedUnit
abstract Stokes <: KinematicViscosity
const kinematicviscosity_dim = Dimension(2,0,-1,0,0,0,0)
const stokes = UnitDef(Stokes, "St", 1e-4, kinematicviscosity_dim)

# Wavenumber
abstract Wavenumber <: DerivedUnit
abstract Kayser <: Wavenumber
const wavenumber_dim = Dimension(-1,0,0,0,0,0,0)
const kayser = UnitDef(Kayser, "K", 0.01, wavenumber_dim)

# Spectral irradiance
abstract SpectralIrradiance <: DerivedUnit
abstract Jansky <: SpectralIrradiance
const spectralirradiance_dim = Dimension(0,1,-2,0,0,0,0)
const jansky = UnitDef(Jansky, "Jy", 1e-26, spectralirradiance_dim)

# Aliases for unit quantities
typealias Weight Force
typealias Stress Pressure
typealias Work Energy
typealias Heat Energy
typealias RadiateFlux Power
typealias EMF Voltage
typealias Impedance Resistance
typealias Reactance Resistance
typealias MagneticFieldStrength MagneticFluxDensity


# FIXME
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

prefix_short_forms = Dict(
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
)


macro add_prefix(prefix, base)
    pbase = symbol(string(prefix, base))
    pinst = symbol(lowercase(string(prefix, base)))
    binst = symbol(lowercase(string(base)))
    pcons = symbol(lowercase(string(prefix)))
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
# Unit Systems
##############################################################################

SiUnit = [Meter, KiloGram, Second] |>
    x -> [Type{T} for T in x] |>
    x -> Union(x...)
si = Dict(
    # Base units
    Length => meter,
    Mass => kilogram,
    Time => second,
    Temperature => kelvin,
    ElectricCurrent => ampere,
    AmountOfSubstance => mole,
    LuminousIntensity => candela,
    # Derived units
    Angle => radian,
    SolidAngle => steradian,
    Area => hectare,
    Volume => litre,
    Frequency => hertz,
    Force => newton,
    Pressure => pascal,
    Energy => joule,
    Power => watt,
    Charge => coulomb,
    Voltage => volt,
    Capacitance => farad,
    Resistance => ohm,
    Conductance => siemens,
    MagneticFlux => weber,
    MagneticFluxDensity => tesla,
    Inductance => henry,
    LuminousFlux => lumen,
    Illuminance => lux,
    Radioactivity => becquerel,
    AbsorbedDose => gray,
    EquivalentDose => sievert,
    CatalyticActivity => katal,
)

CgsUnit = [CentiMeter, Gram, Second] |>
    x -> [Type{T} for T in x] |>
    x -> Union(x...)
cgs = Dict(
    # Base units
    Length => centimeter,
    Mass => gram,
    Time => second,
    Temperature => kelvin,
    ElectricCurrent => statampere,
    AmountOfSubstance => mole,
    LuminousIntensity => candela,
    # Derived Units
    Angle => radian,
    SolidAngle => steradian,
    Frequency => hertz,
    Acceleration => gal,
    Force => dyne,
    Pressure => barye,
    Energy => erg,
    Charge => statcoulomb,
    Voltage => statvolt,
    Capacitance => statfarad,
    Resistance => statohm,
    Conductance => statmho,
    MagneticFlux => maxwell,
    MagneticFluxDensity => gauss,
    Inductance => stathenry,
    LuminousFlux => lumen,
    Radioactivity => becquerel,
    CatalyticActivity => katal,
    DynamicViscosity => poise,
    KinematicViscosity => stokes,
    Wavenumber => kayser,
)


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
function to(x::Composite, s::String)
    y = Composite(s)
    to(x, y)
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
    dim = get_dim(c)
    # FIXME
    # Treat as an eigenvalue problem using the dimensions,
    # with the basis vectors being first the derived units.
    # Then, look at the "left-over" dimensional values,
    # and fill those in with the concrete base units.
end


##############################################################################
# Operators
##############################################################################

# Unary addition operator
+(x::UnitDef) = x
+(x::Composite) = x

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
    y = Composite(inv(y.mag), [Quantity(q.unit, -q.ord) for q in y.quants])
    x * y
end

# Binary inverse division operator
\(x::UnitDef, y::Number) = y / x
\(x::Number, y::UnitDef) = y / x
\(x::Composite, y::Number) = y / x
\(x::Number, y::Composite) =  y / x
\(x::Composite, y::Composite) =  y / x

# Binary exponentiation operator.
# Add `Integer` method to avoid method ambiguity with ^(::Any, ::Integer)
^(x::UnitDef, y::Integer) = x^Rational(y)
^(x::UnitDef, y::Number) = Composite(1, [Quantity(x, y)])
^(x::Quantity, y::Integer) = x^Rational(y)
^(x::Quantity, y::Number) = Quantity(x.unit, x.ord * y)
^(x::Composite, y::Integer) = x^Rational(y)
function ^(x::Composite, y::Number)
    x = copy(x)
    mag = x.mag^y
    new_quants = [Quantity(q.unit, q.ord * y) for q in x.quants]
    Composite(mag, new_quants)
end

# Comparison operators
for op=(:(==), :!=, :<, :<=, :>, :>=)
    @eval begin
        function ($op)(x::Composite, y::Composite)
            check_dim(x, y)
            x = sys_decompose(x)  # defaults to SI
            y = sys_decompose(y)
            ($op)(x.mag, y.mag)
        end
    end
end


# Catch-all operators to force conversion to Composite
for op=(:+, :-, :*, :/, :\, :<, :<=, :>, :>=)
    @eval begin
        function ($op)(x::UnitContainer, y::UnitContainer)
            x, y, _ = promote(x, y, Composite(meter))
            ($op)(promote(x, y)...)
        end
    end
end


# Dimension
convert{T<:Number}(::Type{Dimension}, x::T) = Dimension((dimensionless.data .+ x)...)
promote_rule{T<:Number}(::Type{Dimension}, ::Type{T}) = Dimension

-(x::Dimension) = Dimension((-x.data)...)
^(x::Dimension, y::Integer) = Dimension(x.data .^ y)
^(x::Dimension, y::Number) = Dimension(x.data .^ y)

+(x::Dimension, y::Dimension) = Dimension((x.data .+ y.data)...)
-(x::Dimension, y::Dimension) = Dimension((x.data .- y.data)...)
*(x::Dimension, y::Dimension) = Dimension((x.data .* y.data)...)
/(x::Dimension, y::Dimension) = Dimension((x.data ./ y.data)...)

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

const sup_vals = Dict(
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
)

const sub_vals = Dict(
    1 => "₁",
    2 => "₂",
    3 => "₃",
    4 => "₄",
    5 => "₅",
    6 => "₆",
    7 => "₇",
    8 => "₈",
    9 => "₉",
)

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
