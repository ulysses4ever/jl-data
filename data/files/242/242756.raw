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
type condenserSubcooled
	condenserSubcooled()=begin
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
			stream(Dict{Symbol,Any}(
				:Brief=>"Vapour inlet stream",
				:PosX=>0.16,
				:PosY=>0,
				:Symbol=>"_{in}^{Vapour}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.53,
				:PosY=>1,
				:Symbol=>"_{out}^{Liquid}"
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Condensate temperature (subcooled)",
				:Symbol=>"T_{sub}"
			)),
			temp_delta(Dict{Symbol,Any}(
				:Brief=>"Subcooling Degree",
				:Symbol=>"\\Delta T_{sub}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Calculated condenser duty for desired subcooling",
				:Protected=>true,
				:Symbol=>"Q_{cond}"
			)),
			[
				:(InletVapour.F = OutletLiquid.F),
				:(InletVapour.z = OutletLiquid.z),
				:(OutletLiquid.P = InletVapour.P),
				:(OutletLiquid.T = T_sub),
				:(SubcoolingDegree = InletVapour.T - T_sub),
				:(OutletLiquid.h = PP.LiquidEnthalpy(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(CondenserDuty = OutletLiquid.F*OutletLiquid.h - InletVapour.F*InletVapour.h),
				:(OutletLiquid.v = 0),
			],
			[
				"Molar Flow Balance","Molar Composition Balance","Pressure Drop","Subcooled Temperature","Degree of subcooling","Liquid enthalpy","Condenser Duty","Vapourisation Fraction",
			],
			[:PP,:NComp,],
			[:InletVapour,:OutletLiquid,:T_sub,:SubcoolingDegree,:CondenserDuty,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	InletVapour::stream 
	OutletLiquid::stream 
	T_sub::temperature 
	SubcoolingDegree::temp_delta 
	CondenserDuty::power 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export condenserSubcooled
function setEquationFlow(in::condenserSubcooled)
	addEquation(1)
	addEquation(2)
	#"Energy Balance"
	#InletVapour.F*InletVapour.h  + InletQ = OutletLiquid.F*OutletLiquid.h;
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
end
function atributes(in::condenserSubcooled,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/CondenserSteady"
	fields[:Brief]="Model of a  Steady State total condenser with specified outlet temperature conditions."
	fields[:Info]="A simple model of a Steady State total condenser with specified temperature (or subcooling degree), with a real 
calculation of the output stream enthalpy. The subcooling degree is considered to be the difference between the 
inlet vapour and the outlet liquid temperatures.

== ASSUMPTIONS ==
* perfect mixing of both phases;
* saturated vapour at the Inlet;
* no thermodynamics equilibrium;
* no pressure drop in the condenser.

== SPECIFY ==
* the InletVapour stream;
* the subcooled temperature OR the the degree of subcooling.

"
	drive!(fields,_)
	return fields
end
condenserSubcooled(_::Dict{Symbol,Any})=begin
	newModel=condenserSubcooled()
	newModel.attributes=atributes(newModel,_)
	newModel
end
