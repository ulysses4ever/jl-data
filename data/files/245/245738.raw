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
type reboilerSteady
	reboilerSteady()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of Components"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Flash Calculation",
				:Valid=>["Flash_PH","Fake_Conditions"],
				:Default=>"Fake_Conditions"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Drop in the reboiler",
				:Symbol=>"\\Delta P"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Flow Constant"
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Fake temperature",
				:Symbol=>"T_{fake}"
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Fake vapour fraction",
				:Symbol=>"v_{fake}"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Flow Constant",
				:Hidden=>true,
				:Unit=>"mol^3/(kg*m^2)"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Liquid inlet stream",
				:PosX=>0.345,
				:PosY=>1,
				:Symbol=>"_{inL}",
				:Protected=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0.17,
				:PosY=>0,
				:Symbol=>"_{outV}",
				:Protected=>true
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Heat supplied",
				:PosX=>1,
				:PosY=>0.08,
				:Symbol=>"Q_{in}",
				:Protected=>true
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Vapour Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Temperature  Indicator of Reboiler",
				:Protected=>true,
				:PosX=>0.44,
				:PosY=>0
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Pressure Indicator of Reboiler",
				:Protected=>true,
				:PosX=>0.35,
				:PosY=>0
			)),
			[
				:(InletLiquid.F = OutletVapour.F),
				:(InletLiquid.z = OutletVapour.z),
				:(InletLiquid.F*InletLiquid.h + InletQ = OutletVapour.F*OutletVapour.h),
				:(OutletVapour.P = InletLiquid.P - Pdrop),
				:(TI * "K" = OutletVapour.T),
				:(PI * "atm" = OutletVapour.P),
				:(OutletVapour.F^3 = FlowConstant*k*InletQ),
				:(OutletVapour.v = Fake_Vfrac),
				:(OutletVapour.T = Fake_Temperature),
				:(x = 1),
				:(y = 1),
				:(OutletVapour.v = Fake_Vfrac),
				:(OutletVapour.T = Fake_Temperature),
				:(x = 1),
				:(y = 1),
			],
			[
				"Molar Flow Balance","Molar Composition Balance","Energy Balance","Pressure Drop","Temperature indicator","Pressure indicator","Flow through the reboiler","Fake Vapourisation Fraction","Fake output temperature","Fake Liquid Molar Fraction","Fake Vapour Molar Fraction","Fake Vapourisation Fraction","Fake output temperature","Fake Liquid Molar Fraction","Fake Vapour Molar Fraction",
			],
			[:PP,:NComp,:Flash_Calculation,:Pdrop,:FlowConstant,:Fake_Temperature,:Fake_Vfrac,:k,],
			[:InletLiquid,:OutletVapour,:InletQ,:x,:y,:TI,:PI,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Flash_Calculation::DanaSwitcher
	Pdrop::press_delta
	FlowConstant::DanaReal
	Fake_Temperature::temperature
	Fake_Vfrac::fraction
	k::DanaReal
	InletLiquid::stream
	OutletVapour::stream
	InletQ::power
	x::Array{fraction}
	y::Array{fraction}
	TI::control_signal
	PI::control_signal
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export reboilerSteady
function set(in::reboilerSteady)
	k = 1*"mol^3/(kg*m^2)"
	 
end
function setEquationFlow(in::reboilerSteady)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	let switch=Flash_Calculation
		if switch=="Flash_PH"
			#"Flash Calculation"
#	[OutletVapour.v, x, y] = PP.FlashPH(OutletVapour.P, OutletVapour.h, OutletVapour.z);
#	
#"Enthalpy"
#	OutletVapour.h = (1-OutletVapour.v)*PP.LiquidEnthalpy(OutletVapour.T, OutletVapour.P, x) + 
#	OutletVapour.v*PP.VapourEnthalpy(OutletVapour.T, OutletVapour.P, y);
#
addEquation(8)
			addEquation(9)
			addEquation(10)
			addEquation(11)
		elseif switch=="Fake_Conditions"
			addEquation(12)
			addEquation(13)
			addEquation(14)
			addEquation(15)
		end
	end
end
function atributes(in::reboilerSteady,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/ReboilerSteady"
	fields[:Brief]="Model of a  Steady State reboiler with no thermodynamics equilibrium - thermosyphon."
	fields[:Info]="Model of a  Steady State reboiler with two approaches:
**Fake Conditions: fake calculation of vaporisation fraction and output temperature, but with a real 
calculation of the output stream enthalpy.

**Flash PH: in the outlet stream a PH Flash is performed to obtain the outlet conditions. 

== ASSUMPTIONS ==
* perfect mixing of both phases;
* no thermodynamics equilibrium;

== SET ==
* the option Flash_Calculation
* the fake Outlet temperature;
* the fake outlet vapour fraction;
* the pressure drop in the reboiler;
* the FlowConstant that relates the Flow through the reboiler and the heat duty
**	Flow^3 = FlowConstant*InletQ

== SPECIFY ==
* the InletLiquid stream;
* the InletQ (the model requires an energy stream, also you can use a controller for setting the heat duty using the heat_flow model)
OR the outlet temperature (OutletVapour.T);

== OPTIONAL ==
* the reboiler model has two control ports
** TI OutletVapour Temperature Indicator;
** PI OutletVapour Pressure Indicator;
"
	drive!(fields,_)
	return fields
end
reboilerSteady(_::Dict{Symbol,Any})=begin
	newModel=reboilerSteady()
	newModel.attributes=atributes(newModel,_)
	newModel
end
