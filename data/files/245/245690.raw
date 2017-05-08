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
#*----------------------------------------------------------------------
#* Author: Paula B. Staudt
#* $Id$
#*--------------------------------------------------------------------
type flash
	flash()=begin
		PP=outers.PP
		NComp=outers.NComp
		[
			:(LI = Levelpercent_Initial),
			:(OutletLiquid.T = Temperature_Initial),
			:(OutletLiquid.z(1:NComp - 1) = Composition_Initial(1:NComp - 1)/sum(Composition_Initial)),
		],
		[
			"Initial level Percent","Initial Outlet Liquid Temperature","Initial Outlet Liquid Composition Normalized",
		],
		new(
			VesselVolume(),
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of components",
				:Lower=>1
			)),
			fill(molweight(Dict{Symbol,Any}(
				:Brief=>"Mol Weight",
				:Hidden=>true
			)),(NComp)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Initial liquid height in Percent",
				:Default=>0.70
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Initial Liquid Temperature",
				:Default=>330
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Initial Composition",
				:Default=>0.10
			)),(NComp)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed Stream",
				:PosX=>0,
				:PosY=>0.48,
				:Symbol=>"_{in}"
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.43,
				:PosY=>1,
				:Symbol=>"_{out}^{Liquid}"
			)),
			vapour_stream(Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0.43,
				:PosY=>0,
				:Symbol=>"_{out}^{Vapour}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Heat Duty",
				:PosX=>1,
				:PosY=>0.81,
				:Protected=>true,
				:Symbol=>"Q_{in}"
			)),
			fill(mol(Dict{Symbol,Any}(
				:Brief=>"Molar Holdup in the Vessel",
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
				:Brief=>"Total Energy Holdup in the Vessel",
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
			positive(Dict{Symbol,Any}(
				:Brief=>"Vapourization fraction",
				:Symbol=>"\\phi",
				:Protected=>true
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Pressure Ratio",
				:Symbol=>"P_{ratio}",
				:Protected=>true
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P",
				:Protected=>true
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Equilibrium pressure on the liquid surface",
				:Protected=>true,
				:Symbol=>"\\Delta P_{eq}"
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Static head at the bottom of the tank",
				:Protected=>true,
				:Symbol=>"P_{static}^{Liquid}"
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Temperature Indicator",
				:PosX=>1,
				:PosY=>0.39,
				:Protected=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Pressure Indicator",
				:PosX=>1,
				:PosY=>0.21,
				:Protected=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Level Indicator",
				:PosX=>1,
				:PosY=>0.59,
				:Protected=>true
			)),
			[
				:(diff(TotalHoldup)=Inlet.F*Inlet.z - OutletLiquid.F*OutletLiquid.z - OutletVapour.F*OutletVapour.z),
				:(diff(E) = Inlet.F*Inlet.h - OutletLiquid.F*OutletLiquid.h - OutletVapour.F*OutletVapour.h + InletQ),
				:(TotalHoldup = LiquidHoldup*OutletLiquid.z + VapourHoldup*OutletVapour.z),
				:(E = LiquidHoldup*OutletLiquid.h + VapourHoldup*OutletVapour.h - OutletLiquid.P*Vtotal),
				:(sum(OutletLiquid.z)=1.0),
				:(sum(OutletLiquid.z)=sum(OutletVapour.z)),
				:(OutletVapour.F = Inlet.F * vfrac),
				:(vL = PP.LiquidVolume(OutletLiquid.T, Peq, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, Peq, OutletVapour.z)),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, Peq, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, Peq, OutletVapour.z)*OutletVapour.z),
				:(OutletVapour.T = OutletLiquid.T),
				:(OutletVapour.P = Peq),
				:(Pstatic = PP.LiquidDensity(OutletLiquid.T, Peq, OutletLiquid.z) * _base_1.Gconst * Level),
				:(OutletLiquid.P = Peq + Pstatic),
				:(OutletLiquid.P = Inlet.P - Pdrop),
				:(OutletLiquid.P = Inlet.P * Pratio),
				:(Vtotal = LiquidHoldup * vL + VapourHoldup * vV),
				:(TI * "K" = OutletLiquid.T),
				:(PI * "atm" = OutletLiquid.P),
				:(LI*Vtotal= Vfilled),
				:(LiquidHoldup * vL = Vfilled),
			],
			[
				"Component Molar Balance","Energy Balance","Molar Holdup","Energy Holdup","Mol fraction normalisation","Mol fraction normalisation","Vaporization Fraction","Liquid Volume","Vapour Volume","Chemical Equilibrium","Thermal Equilibrium","Mechanical Equilibrium for the Vapour Phase","Static Head","Mechanical Equilibrium for the Liquid Phase","Pressure Drop","Pressure Ratio","Geometry Constraint","Temperature indicator","Pressure indicator","Level indicator","Liquid Level",
			],
			[:PP,:NComp,:Mw,:Levelpercent_Initial,:Temperature_Initial,:Composition_Initial,],
			[:Inlet,:OutletLiquid,:OutletVapour,:InletQ,:TotalHoldup,:LiquidHoldup,:VapourHoldup,:E,:vL,:vV,:vfrac,:Pratio,:Pdrop,:Peq,:Pstatic,:TI,:PI,:LI,]
		)
	end
	_base_1::VesselVolume
	PP::DanaPlugin
	NComp::DanaInteger
	Mw::Array{molweight}
	Levelpercent_Initial::positive
	Temperature_Initial::temperature
	Composition_Initial::Array{fraction}
	Inlet::stream
	OutletLiquid::liquid_stream
	OutletVapour::vapour_stream
	InletQ::power
	TotalHoldup::Array{mol}
	LiquidHoldup::mol
	VapourHoldup::mol
	E::energy
	vL::volume_mol
	vV::volume_mol
	vfrac::positive
	Pratio::positive
	Pdrop::press_delta
	Peq::pressure
	Pstatic::pressure
	TI::control_signal
	PI::control_signal
	LI::control_signal
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export flash
function set(in::flash)
	Mw=PP.MolecularWeight()
	 
end
function initial(in::flash)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function setEquationFlow(in::flash)
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
	addEquation(20)
	addEquation(21)
end
function atributes(in::flash,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Flash"
	fields[:Brief]="Model of a Dynamic Flash Vessel."
	fields[:Info]="== ASSUMPTIONS ==
* perfect mixing of both phases;
* thermodynamics equilibrium.

== SET ==
*Orientation: vessel position - vertical or horizontal;
*Heads (bottom and top heads are identical)
**elliptical: 2:1 elliptical heads (25% of vessel diameter);
**hemispherical: hemispherical heads (50% of vessel diameter);
**flat: flat heads (0% of vessel diameter);
*Diameter: Vessel diameter;
*Lenght: Side length of the cylinder shell;
	
== SPECIFY ==
* the Inlet stream;
* the outlet flows: OutletVapour.F and OutletLiquid.F;
* the InletQ (the model requires an energy stream, also you can use a controller for setting the heat duty using the heat_flow model).

== OPTIONAL ==
* the Flash model has three control ports
** TI OutletLiquid Temperature Indicator;
** PI OutletLiquid Pressure Indicator;
** LI Level Indicator;

== INITIAL CONDITIONS ==
* Initial_Temperature :  the Flash temperature (OutletLiquid.T);
* Initial_Level : the Flash liquid level (Level);
* Initial_Composition : (NoComps) OutletLiquid compositions.
"
	drive!(fields,_)
	return fields
end
flash(_::Dict{Symbol,Any})=begin
	newModel=flash()
	newModel.attributes=atributes(newModel,_)
	newModel
end
