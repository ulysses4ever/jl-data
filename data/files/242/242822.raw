#-------------------------------------------------------------------
#* Model of a tray with reaction
#*-------------------------------------------------------------------
type trayReac
	trayReac()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Type=>"PP"
			)),
			DanaInteger(),
			stream (Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:PosX=>0,
				:PosY=>0.4932,
				:Symbol=>"_{in}"
			)),
			liquid_stream (Dict{Symbol,Any}(
				:Brief=>"liquid Sidestream",
				:Hidden=>true,
				:Symbol=>"_{outL}"
			)),
			vapour_stream (Dict{Symbol,Any}(
				:Brief=>"vapour Sidestream",
				:Hidden=>true,
				:Symbol=>"_{outV}"
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Inlet liquid stream",
				:PosX=>0.5195,
				:PosY=>0,
				:Symbol=>"_{inL}"
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Inlet vapour stream",
				:PosX=>0.4994,
				:PosY=>1,
				:Symbol=>"_{inV}"
			)),
			liquid_stream (Dict{Symbol,Any}(
				:Brief=>"Outlet liquid stream",
				:PosX=>0.8277,
				:PosY=>1,
				:Symbol=>"_{outL}"
			)),
			vapour_stream (Dict{Symbol,Any}(
				:Brief=>"Outlet vapour stream",
				:PosX=>0.8043,
				:PosY=>0,
				:Symbol=>"_{outV}"
			)),
			fill(fraction()),
			fill(mol (Dict{Symbol,Any}(
				:Brief=>"Molar Holdup in the tray"
			)),(NComp)),
			mol (Dict{Symbol,Any}(
				:Brief=>"Molar liquid holdup"
			)),
			mol (Dict{Symbol,Any}(
				:Brief=>"Molar vapour holdup"
			)),
			energy (Dict{Symbol,Any}(
				:Brief=>"Total Energy Holdup on tray"
			)),
			volume_mol (Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Volume"
			)),
			volume_mol (Dict{Symbol,Any}(
				:Brief=>"Vapour Molar volume"
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Height of clear liquid on plate"
			)),
			volume(),
			dens_mass(),
			dens_mass(),
			reaction_mol (Dict{Symbol,Any}(
				:Brief=>"Reaction resulting ethyl acetate",
				:DisplayUnit=>"mol/l/s"
			)),
			fill(conc_mol (Dict{Symbol,Any}(
				:Brief=>"Molar concentration",
				:Lower=>-1
			)),(NComp)),
			[
				:(OutletLiquid.z = vL * C),
				:(r3 = exp(-7150*"K"/OutletLiquid.T)*(4.85e4*C(1)*C(2) - 1.23e4*C(3)*C(4))*"l/mol/s"),
				:(M = ML*OutletLiquid.z + MV*OutletVapour.z),
				:(OutletVapour.T = VapourSideStream.T),
				:(OutletLiquid.T = LiquidSideStream.T),
				:(OutletVapour.P= VapourSideStream.P),
				:(OutletLiquid.P = LiquidSideStream.P),
				:(OutletLiquid.z= LiquidSideStream.z),
				:(OutletVapour.z= VapourSideStream.z),
				:(sum(OutletLiquid.z)= 1.0),
				:(vL = PP.LiquidVolume(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(OutletVapour.T = OutletLiquid.T),
				:(OutletVapour.P = OutletLiquid.P),
				:(Vol = ML*vL),
				:(rhoL = PP.LiquidDensity(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(rhoV = PP.VapourDensity(InletVapour.T, InletVapour.P, InletVapour.z)),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, OutletVapour.P, yideal)*yideal),
				:(sum(OutletLiquid.z)= sum(OutletVapour.z)),
			],
			[
				"Molar Concentration","Reaction","Molar Holdup","Thermal Equilibrium Vapour Side Stream","Thermal Equilibrium Liquid Side Stream","Mechanical Equilibrium Vapour Side Stream","Mechanical Equilibrium Liquid Side Stream","Composition Liquid Side Stream","Composition Vapour Side Stream","Mol fraction normalisation","Liquid Volume","Vapour Volume","Thermal Equilibrium","Mechanical Equilibrium","","Liquid Density","Vapour Density","Chemical Equilibrium","",
			],
			[:PP,:NComp,],
			[:Inlet,:LiquidSideStream,:VapourSideStream,:InletLiquid,:InletVapour,:OutletLiquid,:OutletVapour,:yideal,:M,:ML,:MV,:E,:vL,:vV,:Level,:Vol,:rhoL,:rhoV,:r3,:C,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Inlet::stream 
	LiquidSideStream::liquid_stream 
	VapourSideStream::vapour_stream 
	InletLiquid::stream 
	InletVapour::stream 
	OutletLiquid::liquid_stream 
	OutletVapour::vapour_stream 
	yideal::Array{fraction}
	M::Array{mol }
	ML::mol 
	MV::mol 
	E::energy 
	vL::volume_mol 
	vV::volume_mol 
	Level::length 
	Vol::volume
	rhoL::dens_mass
	rhoV::dens_mass
	r3::reaction_mol 
	C::Array{conc_mol }
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export trayReac
function setEquationFlow(in::trayReac)
	addEquation(1)
	addEquation(2)
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
end
function atributes(in::trayReac,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Icon]="icon/Tray"
	fields[:Brief]="Model of a tray with reaction."
	fields[:Info]="== Assumptions ==
* both phases (liquid and vapour) exists all the time;
* thermodymanic equilibrium with Murphree plate efficiency;
* no entrainment of liquid or vapour phase;
* no weeping;
* the dymanics in the downcomer are neglected.
	
== Specify ==
* the Feed stream;
* the Liquid inlet stream;
* the Vapour inlet stream;
* the Vapour outlet flow (OutletVapour.F);
* the reaction related variables.
	
== Initial ==
* the plate temperature (OutletLiquid.T)
* the liquid height (Level) OR the liquid flow OutletLiquid.F
* (NoComps - 1) OutletLiquid compositions
"
	drive!(fields,_)
	return fields
end
trayReac(_::Dict{Symbol,Any})=begin
	newModel=trayReac()
	newModel.attributes=atributes(newModel,_)
	newModel
end
