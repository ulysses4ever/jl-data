#-------------------------------------------------------------------
#* EMSO Model Library (EML) Copyright (C) 2004 - 2007 ALSOC.
#*
#* This LIBRARY is free software; you can distribute it and/or modify
#* it under the therms of the ALSOC FREE LICENSE as available at
#* http://www.enq.ufrgs.br/alsoc.
#*
#* EMSO Copyright (C) 2004 - 2007 ALSOC, original code
#* from http://www.rps.eng.br Copyright (C) 2002-2004.
#* All rights reserved.
#*
#* EMSO is distributed under the therms of the ALSOC LICENSE as
#* available at http://www.enq.ufrgs.br/alsoc.
#*
#*----------------------------------------------------------------------
#* Author: Paula B. Staudt
#* $Id: condenser.mso 555 2008-07-18 19:01:13Z rafael $
#*--------------------------------------------------------------------
type condenserReact
	condenserReact()=begin
		PP=outers.PP
		NComp=outers.NComp
		[
			:(Level = Initial_Level),
			:(OutletLiquid.T = Initial_Temperature),
			:(OutletLiquid.z(1:NComp-1) = Initial_Composition(1:NComp-1)/sum(Initial_Composition)),
		],
		[
			"","","",
		],
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Type=>"PP"
			)),
			DanaInteger(),
			volume(Dict{Symbol,Any}(
				:Brief=>"Condenser total volume"
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Cross Section Area of reboiler"
			)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Stoichiometric matrix"
			)),(NComp)),
			energy_mol(),
			length(Dict{Symbol,Any}(
				:Brief=>"Initial Level of liquid phase"
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Initial Temperature of Condenser"
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Initial Liquid Composition"
			)),(NComp)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Vapour inlet stream",
				:PosX=>0.1164,
				:PosY=>0,
				:Symbol=>"_{inV}"
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.4513,
				:PosY=>1,
				:Symbol=>"_{outL}"
			)),
			vapour_stream(Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0.4723,
				:PosY=>0,
				:Symbol=>"_{outV}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Cold supplied",
				:PosX=>1,
				:PosY=>0.6311,
				:Symbol=>"_{in}"
			)),
			fill(mol(Dict{Symbol,Any}(
				:Brief=>"Molar Holdup in the tray"
			)),(NComp)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar liquid holdup"
			)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar vapour holdup"
			)),
			energy(Dict{Symbol,Any}(
				:Brief=>"Total Energy Holdup on tray"
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Volume"
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Vapour Molar volume"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Level of liquid phase"
			)),
			volume(),
			reaction_mol(Dict{Symbol,Any}(
				:Brief=>"Reaction Rates",
				:DisplayUnit=>"mol/l/s"
			)),
			fill(conc_mol(Dict{Symbol,Any}(
				:Brief=>"Molar concentration",
				:Lower=>-1
			)),(NComp)),
			[
				:(OutletLiquid.z = vL * C),
				:(r3 = exp(-7150*"K"/OutletLiquid.T)*(4.85e4*C(1)*C(2) - 1.23e4*C(3)*C(4)) * "l/mol/s"),
				:(diff(M) = InletVapour.F*InletVapour.z - OutletLiquid.F*OutletLiquid.z - OutletVapour.F*OutletVapour.z + stoic*r3*ML*vL),
				:(diff(E) = InletVapour.F*InletVapour.h - OutletLiquid.F*OutletLiquid.h- OutletVapour.F*OutletVapour.h + InletQ + Hr * r3 * ML*vL),
				:(M = ML*OutletLiquid.z + MV*OutletVapour.z),
				:(E = ML*OutletLiquid.h + MV*OutletVapour.h - OutletVapour.P*V),
				:(sum(OutletLiquid.z)=1.0),
				:(vL = PP.LiquidVolume(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(OutletLiquid.T = OutletVapour.T),
				:(OutletVapour.P = OutletLiquid.P),
				:(V = ML*vL + MV*vV),
				:(Vol = ML*vL),
				:(Level = ML*vL/Across),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, OutletVapour.P, OutletVapour.z)*OutletVapour.z),
				:(sum(OutletLiquid.z)=sum(OutletVapour.z)),
			],
			[
				"Molar Concentration","Reaction","Component Molar Balance","Energy Balance","Molar Holdup","Energy Holdup","Mol fraction normalisation","Liquid Volume","Vapour Volume","Thermal Equilibrium","Mechanical Equilibrium","Geometry Constraint","","Level of liquid phase","Chemical Equilibrium","",
			],
			[:PP,:NComp,:V,:Across,:stoic,:Hr,:Initial_Level,:Initial_Temperature,:Initial_Composition,],
			[:InletVapour,:OutletLiquid,:OutletVapour,:InletQ,:M,:ML,:MV,:E,:vL,:vV,:Level,:Vol,:r3,:C,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	V::volume
	Across::area
	stoic::Array{DanaReal}
	Hr::energy_mol
	Initial_Level::length
	Initial_Temperature::temperature
	Initial_Composition::Array{fraction}
	InletVapour::stream
	OutletLiquid::liquid_stream
	OutletVapour::vapour_stream
	InletQ::power
	M::Array{mol}
	ML::mol
	MV::mol
	E::energy
	vL::volume_mol
	vV::volume_mol
	Level::length
	Vol::volume
	r3::reaction_mol
	C::Array{conc_mol}
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export condenserReact
function initial(in::condenserReact)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function setEquationFlow(in::condenserReact)
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
end
function atributes(in::condenserReact,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Icon]="icon/Condenser"
	fields[:Brief]="Model of a Condenser with reaction in liquid phase."
	fields[:Info]="== Assumptions ==
* perfect mixing of both phases;
* thermodynamics equilibrium;
* the reaction only takes place in liquid phase.
	
== Specify ==
* the reaction related variables;
* the inlet stream;
* the outlet flows: OutletVapour.F and OutletLiquid.F;
* the heat supply.

== Initial Conditions ==
* the condenser temperature (OutletLiquid.T);
* the condenser liquid level (Level);
* (NoComps - 1) OutletLiquid (OR OutletVapour) compositions.
"
	drive!(fields,_)
	return fields
end
condenserReact(_::Dict{Symbol,Any})=begin
	newModel=condenserReact()
	newModel.attributes=atributes(newModel,_)
	newModel
end
