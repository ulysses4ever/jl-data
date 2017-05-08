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
type condenserSteady
	condenserSteady()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin (Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of Components"
			)),
			press_delta (Dict{Symbol,Any}(
				:Brief=>"Pressure Drop in the condenser",
				:Default=>0,
				:Symbol=>"\\Delta _P"
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Vapour inlet stream",
				:PosX=>0.16,
				:PosY=>0,
				:Symbol=>"_{in}^{Vapour}"
			)),
			liquid_stream (Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.53,
				:PosY=>1,
				:Symbol=>"_{out}^{Liquid}"
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Heat Duty",
				:PosX=>1,
				:PosY=>0.08,
				:Symbol=>"Q_{in}",
				:Protected=>true
			)),
			temperature (Dict{Symbol,Any}(
				:Brief=>"Bubble Temperature",
				:Protected=>true,
				:Symbol=>"T_{bubble}"
			)),
			temp_delta (Dict{Symbol,Any}(
				:Brief=>"Degrees subcooled",
				:Symbol=>"\\Delta T_{subcooled}"
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Temperature  Indicator of Condenser",
				:Protected=>true,
				:PosX=>0.50,
				:PosY=>0
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Pressure  Indicator of Condenser",
				:Protected=>true,
				:PosX=>0.32,
				:PosY=>0
			)),
			[
				:(InletVapour.F = OutletLiquid.F),
				:(InletVapour.z = OutletLiquid.z),
				:(InletVapour.F*InletVapour.h + InletQ = OutletLiquid.F*OutletLiquid.h),
				:(OutletLiquid.P = InletVapour.P - Pdrop),
				:(Tbubble = PP.BubbleT(OutletLiquid.P,OutletLiquid.z)),
				:(OutletLiquid.T = Tbubble-Deg_Subcooled),
				:(TI * "K" = OutletLiquid.T),
				:(PI * "atm" = OutletLiquid.P),
			],
			[
				"Molar Flow Balance","Molar Composition Balance","Energy Balance","Pressure Drop","Bubble Temperature","Temperature","Temperature indicator","Pressure indicator",
			],
			[:PP,:NComp,:Pdrop,],
			[:InletVapour,:OutletLiquid,:InletQ,:Tbubble,:Deg_Subcooled,:TI,:PI,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	Pdrop::press_delta 
	InletVapour::stream 
	OutletLiquid::liquid_stream 
	InletQ::power 
	Tbubble::temperature 
	Deg_Subcooled::temp_delta 
	TI::control_signal 
	PI::control_signal 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export condenserSteady
function setEquationFlow(in::condenserSteady)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
end
function atributes(in::condenserSteady,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/CondenserSteady"
	fields[:Brief]="Model of a  Steady State condenser with no thermodynamics equilibrium."
	fields[:Info]="== ASSUMPTIONS ==
* perfect mixing of both phases;
* no thermodynamics equilibrium.

== SET ==
* the pressure drop in the condenser;

== SPECIFY ==
* the InletVapour stream;
* the InletQ (the model requires an energy stream, also you can use a controller for setting the heat duty using the heat_flow model).

== OPTIONAL ==
* the condenser model has two control ports
** TI OutletLiquid Temperature Indicator;
** PI OutletLiquid Pressure Indicator;
"
	drive!(fields,_)
	return fields
end
condenserSteady(_::Dict{Symbol,Any})=begin
	newModel=condenserSteady()
	newModel.attributes=atributes(newModel,_)
	newModel
end
