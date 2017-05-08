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
type SumpTank
	SumpTank()=begin
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
				:Brief=>"Pi value",
				:Default=>3.141593,
				:Hidden=>true,
				:Symbol=>"\\pi"
			)),
			acceleration(Dict{Symbol,Any}(
				:Brief=>"Gravity Acceleration",
				:Default=>9.81,
				:Hidden=>true
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Valid=>["elliptical","hemispherical","flat"],
				:Default=>"flat"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Vessel diameter",
				:Symbol=>"D_{i}"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Side length of the cylinder shell",
				:Symbol=>"L_{vessel}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Elliptical Head Total Volume",
				:Hidden=>true,
				:Symbol=>"V_{head}^{elliptical}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Hemispherical Head Total Volume",
				:Hidden=>true,
				:Symbol=>"V_{head}^{hemispherical}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Cylinder Total Volume",
				:Hidden=>true,
				:Symbol=>"V_{cylinder}"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Vessel radius",
				:Hidden=>true,
				:Symbol=>"R_{cylinder}"
			)),
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
				:PosX=>0.22,
				:PosY=>0,
				:Symbol=>"_{in}"
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.50,
				:PosY=>1,
				:Symbol=>"_{out}^{Liquid}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>1,
				:PosY=>0.20,
				:Symbol=>"_{out}^{Vapour}"
			)),
			vapour_stream(Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0.68,
				:PosY=>0,
				:Symbol=>"_{out}^{Vapour}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Heat Duty",
				:Protected=>false,
				:Symbol=>"Q_{in}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Vessel total volume",
				:Protected=>true,
				:Symbol=>"V_{total}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Vessel volume content",
				:Protected=>true,
				:Symbol=>"V_{filled}"
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
			length(Dict{Symbol,Any}(
				:Brief=>"liquid height",
				:Protected=>true
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Vessel cylinder shell Cross section area",
				:Hidden=>true,
				:Symbol=>"A_{cross}"
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Equilibrium pressure on the liquid surface",
				:Protected=>true,
				:Symbol=>"P_{eq}"
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Static head at the bottom of the tank",
				:Protected=>true,
				:Symbol=>"P_{static}^{Liquid}"
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Level Indicator",
				:PosX=>1,
				:PosY=>0.73,
				:Protected=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Temperature Indicator",
				:PosX=>1,
				:PosY=>0.40,
				:Protected=>true
			)),
			[
				:(Across = 0.25*(pi*Diameter^2)),
				:(Vtotal = Vhead_elliptical + Vcylinder),
				:(Vfilled = 0.25*pi*(((Diameter*Level)/(0.25*Diameter))^2)*(0.25*Diameter-Level/3)),
				:(Vfilled = 0.25*pi*(Diameter^2)*(Level - 0.25*Diameter/3)),
				:(Vtotal = Vhead_hemispherical + Vcylinder),
				:(Vfilled = 0.25*pi*(Level^2)*(2*Diameter-4*Level/3)),
				:(Vfilled = 0.25*pi*((2/3)*((0.5*Diameter)^3) - (0.25*(Diameter)^3) + Level*Diameter^2)),
				:(Vtotal = Vcylinder),
				:(Vfilled = Across*Level),
				:(diff(TotalHoldup) = InletLiquid.F*InletLiquid.z + InletVapour.F*InletVapour.z- OutletLiquid.F*OutletLiquid.z - OutletVapour.F*OutletVapour.z),
				:(diff(E) = InletLiquid.F*InletLiquid.h + InletVapour.F*InletVapour.h - OutletLiquid.F*OutletLiquid.h - OutletVapour.F*OutletVapour.h + InletQ),
				:(TotalHoldup = LiquidHoldup*OutletLiquid.z + VapourHoldup*OutletVapour.z),
				:(E = LiquidHoldup*OutletLiquid.h + VapourHoldup*OutletVapour.h - OutletLiquid.P*Vtotal),
				:(sum(OutletLiquid.z)=1.0),
				:(sum(OutletLiquid.z)=sum(OutletVapour.z)),
				:(vL = PP.LiquidVolume(OutletLiquid.T, Peq, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, Peq, OutletVapour.z)),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, Peq, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, Peq, OutletVapour.z)*OutletVapour.z),
				:(OutletVapour.T = OutletLiquid.T),
				:(OutletVapour.P = Peq),
				:(Pstatic = PP.LiquidDensity(OutletLiquid.T, Peq, OutletLiquid.z) * g * Level),
				:(OutletLiquid.P = Peq + Pstatic),
				:(Vtotal = LiquidHoldup * vL + VapourHoldup * vV),
				:(LI*Vtotal= Vfilled),
				:(TI * "K" = OutletVapour.T),
				:(LiquidHoldup * vL = Vfilled),
			],
			[
				"Vessel Cross Section Area","Vessel Total Volume","Vessel Filled Volume","Vessel Filled Volume","Vessel Total Volume","Vessel Filled Volume","Vessel Filled Volume","Vessel Total Volume","Vessel Filled Volume","Component Molar Balance","Energy Balance","Molar Holdup","Energy Holdup","Mol fraction normalisation","Mol fraction normalisation","Liquid Volume","Vapour Volume","Chemical Equilibrium","Thermal Equilibrium","Mechanical Equilibrium for the Vapour Phase","Static Head","Mechanical Equilibrium for the Liquid Phase","Geometry Constraint","Level indicator","Temperature indicator","Liquid Level",
			],
			[:PP,:NComp,:Mw,:pi,:g,:Heads,:Diameter,:Lenght,:Vhead_elliptical,:Vhead_hemispherical,:Vcylinder,:radius,:Levelpercent_Initial,:Temperature_Initial,:Composition_Initial,],
			[:InletLiquid,:OutletLiquid,:InletVapour,:OutletVapour,:InletQ,:Vtotal,:Vfilled,:TotalHoldup,:LiquidHoldup,:VapourHoldup,:E,:vL,:vV,:Level,:Across,:Peq,:Pstatic,:LI,:TI,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Mw::Array{molweight}
	pi::positive
	g::acceleration
	Heads::DanaSwitcher
	Diameter::length
	Lenght::length
	Vhead_elliptical::volume
	Vhead_hemispherical::volume
	Vcylinder::volume
	radius::length
	Levelpercent_Initial::positive
	Temperature_Initial::temperature
	Composition_Initial::Array{fraction}
	InletLiquid::stream
	OutletLiquid::liquid_stream
	InletVapour::stream
	OutletVapour::vapour_stream
	InletQ::power
	Vtotal::volume
	Vfilled::volume
	TotalHoldup::Array{mol}
	LiquidHoldup::mol
	VapourHoldup::mol
	E::energy
	vL::volume_mol
	vV::volume_mol
	Level::length
	Across::area
	Peq::pressure
	Pstatic::pressure
	LI::control_signal
	TI::control_signal
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export SumpTank
function set(in::SumpTank)
	Mw=PP.MolecularWeight()
	 g = 9.81 * "m/(s^2)"
	 Vhead_elliptical = (pi*Diameter^3)/12
	 Vhead_hemispherical = (pi*Diameter^3)/6
	 Vcylinder = 0.25*(pi*Diameter^2)*Lenght
	 radius = 0.5*Diameter
	 
end
function initial(in::SumpTank)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function setEquationFlow(in::SumpTank)
	addEquation(1)
	let switch=Heads
		if switch=="elliptical"
			addEquation(2)
			if Level < 0.25*Diameter 
				addEquation(3)
			else
				addEquation(4)
			end
		elseif switch=="hemispherical"
			addEquation(5)
			if Level < 0.5*Diameter 
				addEquation(6)
			else
				addEquation(7)
			end
		elseif switch=="flat"
			addEquation(8)
			addEquation(9)
		end
	end
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
	#"Pressure Drop"
#	Pdrop = min([InletLiquid.P,InletVapour.P]) - OutletLiquid.P;
#	#OutletLiquid.P  = InletLiquid.P - Pdrop;
#
addEquation(23)
	addEquation(24)
	addEquation(25)
	addEquation(26)
end
function atributes(in::SumpTank,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/SumpTank"
	fields[:Brief]="Model of a tank with 2 material inlet streams and with thermodynamic equilibrium."
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
* the SumpTank model has three control ports
** TI OutletLiquid Temperature Indicator;
** PI OutletLiquid Pressure Indicator;
** LI Level Indicator;

== INITIAL CONDITIONS ==
* Initial_Temperature :  the Tank temperature (OutletLiquid.T);
* Levelpercent_Initial : the Tank liquid level in percent (LI);
* Initial_Composition : (NoComps) OutletLiquid compositions.
"
	drive!(fields,_)
	return fields
end
SumpTank(_::Dict{Symbol,Any})=begin
	newModel=SumpTank()
	newModel.attributes=atributes(newModel,_)
	newModel
end
