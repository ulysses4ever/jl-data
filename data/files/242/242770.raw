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
type thermosyphon
	thermosyphon()=begin
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
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Drop in the reboiler",
				:Symbol=>"\\Delta P"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Flow Constant"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Flow Constant",
				:Hidden=>true,
				:Unit=>"mol^3/(kg*m^2)"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Liquid inlet stream",
				:PosX=>0.44,
				:PosY=>1,
				:Symbol=>"_{inL}"
			)),
			streamPH(Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0,
				:PosY=>0.09,
				:Symbol=>"_{outV}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Heat supplied",
				:PosX=>1,
				:PosY=>0.77,
				:Symbol=>"Q_{in}",
				:Protected=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Temperature  Indicator of Reboiler",
				:Protected=>true,
				:PosX=>1,
				:PosY=>0.57
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Pressure Indicator of Reboiler",
				:Protected=>true,
				:PosX=>1,
				:PosY=>0.35
			)),
			[
				:(InletLiquid.F = OutletVapour.F),
				:(InletLiquid.z = OutletVapour.z),
				:(InletLiquid.F*InletLiquid.h + InletQ = OutletVapour.F*OutletVapour.h),
				:(OutletVapour.P = InletLiquid.P - Pdrop),
				:(TI * "K" = OutletVapour.T),
				:(PI * "atm" = OutletVapour.P),
				:(OutletVapour.F^3 = FlowConstant*k*InletQ),
			],
			[
				"Molar Flow Balance","Molar Composition Balance","Energy Balance","Pressure Drop","Temperature indicator","Pressure indicator","Flow through the thermosyphon reboiler",
			],
			[:PP,:NComp,:Pdrop,:FlowConstant,:k,],
			[:InletLiquid,:OutletVapour,:InletQ,:TI,:PI,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Pdrop::press_delta
	FlowConstant::DanaReal
	k::DanaReal
	InletLiquid::stream
	OutletVapour::streamPH
	InletQ::power
	TI::control_signal
	PI::control_signal
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export thermosyphon
function set(in::thermosyphon)
	k = 1*"mol^3/(kg*m^2)"
	 
end
function setEquationFlow(in::thermosyphon)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
end
function atributes(in::thermosyphon,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Thermosyphon"
	fields[:Brief]="Model of a  Steady State reboiler thermosyphon."
	fields[:Info]="== ASSUMPTIONS ==
* perfect mixing of both phases;
* no thermodynamics equilibrium;

== SET ==
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
thermosyphon(_::Dict{Symbol,Any})=begin
	newModel=thermosyphon()
	newModel.attributes=atributes(newModel,_)
	newModel
end
