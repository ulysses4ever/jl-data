#-------------------------------------
#* Model of a packed column stage
#-------------------------------------
type packedStage
	packedStage()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number Of Components"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Resistance coefficient on the liquid load",
				:Default=>1,
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"surface area per packing volume",
				:Unit=>"m^2/m^3",
				:Hidden=>true
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Column diameter",
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Void fraction of packing, (m^3 void space/m^3 packed bed)",
				:Hidden=>true
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Height of packing",
				:Hidden=>true
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of Stages",
				:Default=>3,
				:Hidden=>true
			)),
			heat_rate(Dict{Symbol,Any}(
				:Brief=>"Rate of heat supply",
				:Hidden=>true
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"The Height Equivalent to a Theoretical Plate",
				:Hidden=>true
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Column Sectional Cross Area",
				:Hidden=>true
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Total Volume of the tray",
				:Hidden=>true
			)),
			constant(Dict{Symbol,Any}(
				:Brief=>"Pi Number",
				:Default=>3.14159265,
				:Symbol=>"\\pi",
				:Hidden=>true
			)),
			acceleration(Dict{Symbol,Any}(
				:Brief=>"Gravity Acceleration",
				:Default=>9.81,
				:Hidden=>true
			)),
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"Low Flow",
				:Default=>1E-6,
				:Hidden=>true
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Low Pressure",
				:Default=>1E-6,
				:Hidden=>true
			)),
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"No Flow",
				:Default=>0,
				:Hidden=>true
			)),
			fill(molweight(Dict{Symbol,Any}(
				:Brief=>"Component Mol Weight",
				:Hidden=>true
			)),(NComp)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Vapour Flow",
				:Valid=>["on", "off"],
				:Default=>"on",
				:Hidden=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:Symbol=>"_{in}",
				:Protected=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet liquid stream",
				:Symbol=>"_{inL}",
				:Protected=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet vapour stream",
				:Symbol=>"_{inV}",
				:Protected=>true
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Outlet liquid stream",
				:Symbol=>"_{outL}",
				:Protected=>true
			)),
			vapour_stream(Dict{Symbol,Any}(
				:Brief=>"Outlet vapour stream",
				:Symbol=>"_{outV}",
				:Protected=>true
			)),
			fill(mol(Dict{Symbol,Any}(
				:Brief=>"Molar Holdup in the tray",
				:Default=>0.01,
				:Lower=>-0.000001,
				:Upper=>100,
				:Protected=>true
			)),(NComp)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar liquid holdup",
				:Default=>0.01,
				:Lower=>0,
				:Upper=>100,
				:Protected=>true
			)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar vapour holdup",
				:Default=>0.01,
				:Lower=>0,
				:Upper=>100,
				:Protected=>true
			)),
			energy(Dict{Symbol,Any}(
				:Brief=>"Total Energy Holdup on tray",
				:Default=>-500,
				:Protected=>true
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Volume",
				:Protected=>true
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Vapour Molar volume",
				:Protected=>true
			)),
			viscosity(Dict{Symbol,Any}(
				:Brief=>"Liquid dynamic viscosity",
				:DisplayUnit=>"kg/m/s",
				:Protected=>true
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Liquid mass density",
				:Protected=>true
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Vapour mass density",
				:Protected=>true
			)),
			velocity(Dict{Symbol,Any}(
				:Brief=>"volume flow rate of liquid, m^3/m^2/s",
				:Lower=>-10,
				:Upper=>1000,
				:Protected=>true
			)),
			velocity(Dict{Symbol,Any}(
				:Brief=>"volume flow rate of vapor, m^3/m^2/s",
				:Lower=>-10,
				:Upper=>1000,
				:Protected=>true
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Area occupied by the liquid",
				:Default=>0.001,
				:Upper=>10,
				:Protected=>true
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Column holdup",
				:Unit=>"m^3/m^3",
				:Default=>0.01,
				:Upper=>10,
				:Protected=>true
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Stage Pressure drop",
				:Protected=>true
			)),
			[
				:(deltaP/HETP = LiquidResistanceCoeff *( 0.5*AreaPerPackingVolume + 2/ColumnInternalDiameter) * 1/((PackingVoidFraction-hl)^3) * (uV^2) *rhoV),
				:(InletVapour.F = zero_flow),
				:(diff(E) = (Inlet.F*Inlet.h + InletLiquid.F*InletLiquid.h + InletVapour.F*InletVapour.h- OutletLiquid.F*OutletLiquid.h - OutletVapour.F*OutletVapour.h + HeatOnStage )),
				:(E = ML*OutletLiquid.h + MV*OutletVapour.h - OutletLiquid.P*V),
				:(V*PackingVoidFraction= ML*vL + MV*vV),
				:(uV * (V*PackingVoidFraction/HETP - Al) = InletVapour.F * vV),
				:(hl*V*PackingVoidFraction = ML*vL),
				:(hl^3 = (12/Gconst) * AreaPerPackingVolume^2 * (miL/rhoL) * uL),
				:(Al = ML*vL/HETP),
				:(diff(M)=Inlet.F*Inlet.z + InletLiquid.F*InletLiquid.z + InletVapour.F*InletVapour.z- OutletLiquid.F*OutletLiquid.z - OutletVapour.F*OutletVapour.z),
				:(M = ML*OutletLiquid.z + MV*OutletVapour.z),
				:(sum(OutletLiquid.z)= 1.0),
				:(sum(OutletLiquid.z)= sum(OutletVapour.z)),
				:(vL = PP.LiquidVolume(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, OutletVapour.P, OutletVapour.z)*OutletVapour.z),
				:(OutletVapour.T = OutletLiquid.T),
				:(OutletLiquid.P = OutletVapour.P),
				:(rhoL = PP.LiquidDensity(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(rhoV = PP.VapourDensity(InletVapour.T, InletVapour.P, InletVapour.z)),
				:(miL = PP.LiquidViscosity(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(uL * Al = OutletLiquid.F * vL),
				:(deltaP = InletVapour.P - OutletVapour.P),
			],
			[
				"Pressure drop and Vapor flow, Billet (4-58)","Vapour Flow","Energy Balance","Energy Holdup","Geometry Constraint","Volume flow rate of vapor, m^3/m^2/s","Liquid holdup","Liquid velocity as a function of liquid holdup, Billet (4-27)","Area occupied by the liquid","Component Molar Balance","Molar Holdup","Mol Fraction Normalisation","Mol Fraction Constraint","Liquid Volume","Vapour Volume","Chemical Equilibrium","Thermal Equilibrium","Mechanical Equilibrium","Liquid Density","Vapour Density","Liquid viscosity","Volume flow rate of liquid, m^3/m^2/s","Pressure Drop",
			],
			[:PP,:NComp,:LiquidResistanceCoeff,:AreaPerPackingVolume,:ColumnInternalDiameter,:PackingVoidFraction,:HeightOfPacking,:Number_Stages,:HeatOnStage,:HETP,:ColumnArea,:V,:Pi,:Gconst,:low_flow,:low_pressure,:zero_flow,:Mw,:VapourFlow,],
			[:Inlet,:InletLiquid,:InletVapour,:OutletLiquid,:OutletVapour,:M,:ML,:MV,:E,:vL,:vV,:miL,:rhoL,:rhoV,:uL,:uV,:Al,:hl,:deltaP,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	LiquidResistanceCoeff::positive
	AreaPerPackingVolume::DanaReal
	ColumnInternalDiameter::length
	PackingVoidFraction::DanaReal
	HeightOfPacking::length
	Number_Stages::DanaInteger
	HeatOnStage::heat_rate
	HETP::length
	ColumnArea::area
	V::volume
	Pi::constant
	Gconst::acceleration
	low_flow::flow_mol
	low_pressure::pressure
	zero_flow::flow_mol
	Mw::Array{molweight}
	VapourFlow::DanaSwitcher
	Inlet::stream
	InletLiquid::stream
	InletVapour::stream
	OutletLiquid::liquid_stream
	OutletVapour::vapour_stream
	M::Array{mol}
	ML::mol
	MV::mol
	E::energy
	vL::volume_mol
	vV::volume_mol
	miL::viscosity
	rhoL::dens_mass
	rhoV::dens_mass
	uL::velocity
	uV::velocity
	Al::area
	hl::positive
	deltaP::pressure
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export packedStage
function set(in::packedStage)
	Mw = PP.MolecularWeight()
	 ColumnArea = 0.25*Pi*ColumnInternalDiameter^2
	 HETP = HeightOfPacking/Number_Stages
	 V = HETP * ColumnArea
	 low_pressure = 1E-4 * "atm"
	 low_flow = 1E-6 * "kmol/h"
	 zero_flow = 0 * "kmol/h"
	 
end
function setEquationFlow(in::packedStage)
	let switch=VapourFlow
		if VapourFlow==InletVapour.F < low_flow
			set(switch,"off")
		end
		if VapourFlow==deltaP > low_pressure
			set(switch,"on")
		end
		if switch=="on"
			addEquation(1)
		elseif switch=="off"
			addEquation(2)
		end
	end
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
	addEquation(9)
	addEquation(10)
	addEquation(11)
	addEquation(12)
	addEquation(13)
	addEquation(14)
	addEquation(15)
	addEquation(16)
	addEquation(17)
	addEquation(18)
	addEquation(19)
	addEquation(20)
	addEquation(21)
	addEquation(22)
	addEquation(23)
end
function atributes(in::packedStage,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Complete model of a packed column stage."
	fields[:Info]="== Specify ==
* the Feed stream
* the Liquid inlet stream
* the Vapour inlet stream
* the stage pressure drop (deltaP)
	
== Initial ==
* the plate temperature (OutletLiquid.T)
* the liquid molar holdup ML
* (NoComps - 1) OutletLiquid compositions
"
	drive!(fields,_)
	return fields
end
packedStage(_::Dict{Symbol,Any})=begin
	newModel=packedStage()
	newModel.attributes=atributes(newModel,_)
	newModel
end
