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
#*---------------------------------------------------------------------
#* Author: Gerson B. Bicca
#*$Id:$									
#*-------------------------------------------------------------------
type heat_flow
	heat_flow()=begin
		new(
			power(Dict{Symbol,Any}(
				:Brief=>"Minimum of Heat Flow",
				:Default=>-1000
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Maximum of Heat Flow",
				:Default=>1000
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Heat Flow",
				:PosX=>0,
				:PosY=>0.60,
				:Protected=>true
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Flow Signal",
				:PosX=>0.50,
				:PosY=>0,
				:Protected=>true
			)),
			[
				:(HeatFlow = MinHeatFlow + HeatFlowFraction*(MaxHeatFlow-MinHeatFlow)),
			],
			[
				"Heat Flow",
			],
			[:MinHeatFlow,:MaxHeatFlow,],
			[:HeatFlow,:HeatFlowFraction,]
		)
	end
	MinHeatFlow::power 
	MaxHeatFlow::power 
	HeatFlow::power 
	HeatFlowFraction::fraction 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export heat_flow
function setEquationFlow(in::heat_flow)
	addEquation(1)
end
function atributes(in::heat_flow,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/heat_flow"
	fields[:Brief]="Model of a very simple valve for setting the energy flow with a controller."
	fields[:Info]="== ASSUMPTIONS ==
* nothing happens in this valve

== SET ==
* MinHeatFlow: the Minimum Heat Flow Allowable in the valve;
* MaxHeatFlow: the Maximum Heat Flow Allowable in the valve;

== SPECIFY ==
* the HeatFlowFraction (the model requires an inlet signal, also you can use a controller for setting the HeatFlowFraction)
"
	drive!(fields,_)
	return fields
end
heat_flow(_::Dict{Symbol,Any})=begin
	newModel=heat_flow()
	newModel.attributes=atributes(newModel,_)
	newModel
end
