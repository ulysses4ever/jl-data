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
#* $Id$
#*--------------------------------------------------------------------
type reboilerReact
	reboilerReact()=begin
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
			area (Dict{Symbol,Any}(
				:Brief=>"Cross Section Area of reboiler"
			)),
			volume (Dict{Symbol,Any}(
				:Brief=>"Total volume of reboiler"
			)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Stoichiometric matrix"
			)),(NComp)),
			energy_mol(),
			length (Dict{Symbol,Any}(
				:Brief=>"Initial Level of liquid phase"
			)),
			temperature (Dict{Symbol,Any}(
				:Brief=>"Initial Temperature of Reboiler"
			)),
			fill(fraction (Dict{Symbol,Any}(
				:Brief=>"Initial Liquid Composition"
			)),(NComp)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Liquid inlet stream",
				:PosX=>0,
				:PosY=>0.5254,
				:Symbol=>"_{inL}"
			)),
			liquid_stream (Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.2413,
				:PosY=>1,
				:Symbol=>"_{outL}"
			)),
			vapour_stream (Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0.5079,
				:PosY=>0,
				:Symbol=>"_{outV}"
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Heat supplied",
				:PosX=>1,
				:PosY=>0.6123,
				:Symbol=>"_{in}"
			)),
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
				:Brief=>"Level of liquid phase"
			)),
			volume(),
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
				:(r3 = exp(-7150*"K"/OutletLiquid.T)*(4.85e4*C(1)*C(2) - 1.23e4*C(3)*C(4)) * "l/mol/s"),
				:(diff(M)= InletLiquid.F*InletLiquid.z- OutletLiquid.F*OutletLiquid.z - OutletVapour.F*OutletVapour.z + stoic*r3*ML*vL),
				:(diff(E) = InletLiquid.F*InletLiquid.h- OutletLiquid.F*OutletLiquid.h - OutletVapour.F*OutletVapour.h + InletQ + Hr * r3 * vL*ML),
				:(M = ML*OutletLiquid.z + MV*OutletVapour.z),
				:(E = ML*OutletLiquid.h + MV*OutletVapour.h - OutletLiquid.P*V),
				:(sum(OutletLiquid.z)=1.0),
				:(vL = PP.LiquidVolume(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(rhoV = PP.VapourDensity(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(Level = ML*vL/Across),
				:(Vol = ML*vL),
				:(OutletLiquid.P = OutletVapour.P),
				:(OutletLiquid.T = OutletVapour.T),
				:(V = ML*vL + MV*vV),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, OutletVapour.P, OutletVapour.z)*OutletVapour.z),
				:(sum(OutletLiquid.z)=sum(OutletVapour.z)),
			],
			[
				"Molar Concentration","Reaction","Component Molar Balance","Energy Balance","Molar Holdup","Energy Holdup","Mol fraction normalisation","Liquid Volume","Vapour Volume","Vapour Density","Level of liquid phase","","Mechanical Equilibrium","Thermal Equilibrium","Geometry Constraint","Chemical Equilibrium","",
			],
			[:PP,:NComp,:Across,:V,:stoic,:Hr,:Initial_Level,:Initial_Temperature,:Initial_Composition,],
			[:InletLiquid,:OutletLiquid,:OutletVapour,:InletQ,:M,:ML,:MV,:E,:vL,:vV,:Level,:Vol,:rhoV,:r3,:C,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Across::area 
	V::volume 
	stoic::Array{DanaReal}
	Hr::energy_mol
	Initial_Level::length 
	Initial_Temperature::temperature 
	Initial_Composition::Array{fraction }
	InletLiquid::stream 
	OutletLiquid::liquid_stream 
	OutletVapour::vapour_stream 
	InletQ::power 
	M::Array{mol }
	ML::mol 
	MV::mol 
	E::energy 
	vL::volume_mol 
	vV::volume_mol 
	Level::length 
	Vol::volume
	rhoV::dens_mass
	r3::reaction_mol 
	C::Array{conc_mol }
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export reboilerReact
function initial(in::reboilerReact)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function setEquationFlow(in::reboilerReact)
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
end
function atributes(in::reboilerReact,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Icon]="icon/Reboiler"
	fields[:Brief]="Model of a dynamic reboiler with reaction."
	fields[:Info]="== Assumptions ==
* perfect mixing of both phases;
* thermodynamics equilibrium;
* no liquid entrainment in the vapour stream;
* the reaction takes place only in the liquid phase.
	
== Specify ==
* the kinetics variables;
* the inlet stream;
* the liquid inlet stream;
* the outlet flows: OutletVapour.F and OutletLiquid.F;
* the heat supply.

== Initial Conditions ==
* the reboiler temperature (OutletLiquid.T);
* the reboiler liquid level (Level);
* (NoComps - 1) OutletLiquid (OR OutletVapour) compositions.
"
	drive!(fields,_)
	return fields
end
reboilerReact(_::Dict{Symbol,Any})=begin
	newModel=reboilerReact()
	newModel.attributes=atributes(newModel,_)
	newModel
end
