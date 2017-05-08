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
#* Authors: Rafael de Pelegrini Soares
#*          Andrey Copat, Estefane S. Horn, Marcos L. Alencastro
#* $Id$
#*--------------------------------------------------------------------
#Needs to be reformulated
type HidraulicTurbineGenerator
	HidraulicTurbineGenerator()=begin
		new(
			HidraulicTurbine(),
			power(Dict{Symbol,Any}(
				:Brief=>"Eletrical Potency"
			)),
			[
				:(EPower = _base_1.BPower * _base_1.Meff),
			],
			[
				"Calculate Eletric Power",
			],
			[:EPower,]
		)
	end
	_base_1::HidraulicTurbine
	EPower::power
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export HidraulicTurbineGenerator
function setEquationFlow(in::HidraulicTurbineGenerator)
	addEquation(1)
end
function atributes(in::HidraulicTurbineGenerator,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/HidraulicTurbine"
	fields[:Brief]="Model of a Hidraulic Turbine."
	fields[:Info]="== Assumptions ==
* Steady State;
* Only Liquid;
* Adiabatic;
* Isentropic.
	
== Specify ==
* the inlet stream;
* the Pressure Increase (Pdiff) OR the outlet pressure (Outlet.P);
* the Turbine efficiency (Eff);
* the Brake efficiency (Meff);
* the Volumetric expansivity (Beta).
"
	drive!(fields,_)
	return fields
end
HidraulicTurbineGenerator(_::Dict{Symbol,Any})=begin
	newModel=HidraulicTurbineGenerator()
	newModel.attributes=atributes(newModel,_)
	newModel
end
