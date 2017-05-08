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
type reboiler
	reboiler()=begin
		PP=outers.PP
		NComp=outers.NComp
		[
			:(LI = Levelpercent_Initial),
			:(OutletLiquid.T = Initial_Temperature),
			:(OutletLiquid.z(1:NComp-1) = Initial_Composition(1:NComp-1)/sum(Initial_Composition)),
		],
		[
			"Initial level Percent","Initial Temperature","Initial Composition",
		],
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of Components"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Initial liquid height in Percent",
				:Default=>0.70
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Initial Temperature of Reboiler"
			)),
			fill(positive(Dict{Symbol,Any}(
				:Brief=>"Initial Liquid Composition",
				:Lower=>1E-6
			)),(NComp)),
			VesselVolume(Dict{Symbol,Any}(
				:Brief=>"Vessel Geometry",
				:Symbol=>" "
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Liquid inlet stream",
				:PosX=>0.17,
				:PosY=>1,
				:Symbol=>"_{in}^{Liquid}"
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.53,
				:PosY=>1,
				:Symbol=>"_{out}^{Liquid}"
			)),
			vapour_stream(Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0.17,
				:PosY=>0,
				:Symbol=>"_{out}^{Vapour}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Heat supplied",
				:Protected=>true,
				:PosX=>1,
				:PosY=>0.08,
				:Symbol=>"Q_{in}"
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Temperature  Indicator of Reboiler",
				:Protected=>true,
				:PosX=>0.44,
				:PosY=>0
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Level Indicator of Reboiler",
				:Protected=>true,
				:PosX=>0.53,
				:PosY=>0
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Pressure Indicator of Reboiler",
				:Protected=>true,
				:PosX=>0.35,
				:PosY=>0
			)),
			fill(mol(Dict{Symbol,Any}(
				:Brief=>"Molar Holdup in the tray",
				:Protected=>true
			)),(NComp)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar liquid holdup",
				:Protected=>true
			)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar vapour holdup",
				:Protected=>true
			)),
			energy(Dict{Symbol,Any}(
				:Brief=>"Total Energy Holdup on tray",
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
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Vapour Density",
				:Protected=>true,
				:Symbol=>"\\rho"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P",
				:Protected=>true
			)),
			[
				:(diff(M)= InletLiquid.F*InletLiquid.z - OutletLiquid.F*OutletLiquid.z - OutletVapour.F*OutletVapour.z),
				:(diff(E) = InletLiquid.F*InletLiquid.h - OutletLiquid.F*OutletLiquid.h - OutletVapour.F*OutletVapour.h + InletQ),
				:(M = ML*OutletLiquid.z + MV*OutletVapour.z),
				:(E = ML*OutletLiquid.h + MV*OutletVapour.h - OutletLiquid.P*Geometry.Vtotal),
				:(sum(OutletLiquid.z)=1.0),
				:(sum(OutletLiquid.z)=sum(OutletVapour.z)),
				:(rhoV = PP.VapourDensity(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(vL = PP.LiquidVolume(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, OutletVapour.P, OutletVapour.z)*OutletVapour.z),
				:(OutletLiquid.P = OutletVapour.P),
				:(OutletLiquid.T = OutletVapour.T),
				:(OutletLiquid.P = InletLiquid.P - Pdrop),
				:(Geometry.Vtotal = ML*vL + MV*vV),
				:(ML * vL = Geometry.Vfilled),
				:(TI * "K" = OutletLiquid.T),
				:(PI * "atm" = OutletLiquid.P),
				:(LI*Geometry.Vtotal= Geometry.Vfilled),
			],
			[
				"Component Molar Balance","Energy Balance","Molar Holdup","Energy Holdup","Mol Fraction Normalisation","Mol fraction Constraint","Vapour Density","Liquid Volume","Vapour Volume","Chemical Equilibrium","Mechanical Equilibrium","Thermal Equilibrium","Pressure Drop","Geometry Constraint","Liquid Level","Temperature Indicator","Pressure Indicator","Level indicator",
			],
			[:PP,:NComp,:Levelpercent_Initial,:Initial_Temperature,:Initial_Composition,],
			[:Geometry,:InletLiquid,:OutletLiquid,:OutletVapour,:InletQ,:TI,:LI,:PI,:M,:ML,:MV,:E,:vL,:vV,:rhoV,:Pdrop,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	Levelpercent_Initial::positive 
	Initial_Temperature::temperature 
	Initial_Composition::Array{positive }
	Geometry::VesselVolume 
	InletLiquid::stream 
	OutletLiquid::liquid_stream 
	OutletVapour::vapour_stream 
	InletQ::power 
	TI::control_signal 
	LI::control_signal 
	PI::control_signal 
	M::Array{mol }
	ML::mol 
	MV::mol 
	E::energy 
	vL::volume_mol 
	vV::volume_mol 
	rhoV::dens_mass 
	Pdrop::press_delta 
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export reboiler
function initial(in::reboiler)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function setEquationFlow(in::reboiler)
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
end
function atributes(in::reboiler,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Reboiler"
	fields[:Brief]="Model of a dynamic reboiler - kettle with control."
	fields[:Info]="== ASSUMPTIONS ==
* perfect mixing of both phases;
* thermodynamics equilibrium;
* no liquid entrainment in the vapour stream.

== SET ==
*Orientation: vessel position - vertical or horizontal;
*Heads (bottom and top heads are identical)
**elliptical: 2:1 elliptical heads (25% of vessel diameter);
**hemispherical: hemispherical heads (50% of vessel diameter);
*Diameter: Vessel diameter;
*Lenght: Side length of the cylinder shell;

== SPECIFY ==
* the InletLiquid stream;
* the outlet flows: OutletVapour.F and OutletLiquid.F;
* the InletQ (the model requires an energy stream, also you can use a controller for setting the heat duty using the heat_flow model).

== OPTIONAL ==
* the reboiler model has three control ports
** TI OutletLiquid Temperature Indicator;
** PI OutletLiquid Pressure Indicator;
** LI Level Indicator of Reboiler;

== INITIAL CONDITIONS ==
* Initial_Temperature :  the reboiler temperature (OutletLiquid.T);
* Levelpercent_Initial : the reboiler liquid level in percent (LI);
* Initial_Composition : (NoComps) OutletLiquid compositions.
"
	drive!(fields,_)
	return fields
end
reboiler(_::Dict{Symbol,Any})=begin
	newModel=reboiler()
	newModel.attributes=atributes(newModel,_)
	newModel
end
