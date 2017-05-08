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
#* Author: Estefane Horn, N�bia do Carmo Ferreira
#*$Id$									
#*-------------------------------------------------------------------
#-------------------------------------------------------------------
#* Model of a valve (simplified)
#*-------------------------------------------------------------------- 
#*
#* Author: Paula B. Staudt
#*--------------------------------------------------------------------
type valve_flow
	valve_flow()=begin
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
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"Minimum Flow Allowable in the valve",
				:Default=>0
			)),
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"Maximum Flow Allowable in the valve",
				:Default=>1000
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0,
				:PosY=>0.7365,
				:Symbol=>"_{in}",
				:Protected=>true
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>0.7365,
				:Symbol=>"_{out}",
				:Protected=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Flow Signal",
				:PosX=>0.5,
				:PosY=>0,
				:Protected=>true
			)),
			[
				:(Outlet.F = Inlet.F),
				:(Outlet.T = Inlet.T),
				:(Outlet.P = Inlet.P),
				:(Outlet.h = Inlet.h),
				:(Outlet.v = Inlet.v),
				:(Outlet.z = Inlet.z),
				:(Outlet.F = MinFlow + FlowFraction*(MaxFlow-MinFlow)),
			],
			[
				"Overall Molar Balance","Temperature","Pressure","Energy Balance","Vapour fraction","Componente Molar Balance","Flow computation",
			],
			[:PP,:NComp,:MinFlow,:MaxFlow,],
			[:Inlet,:Outlet,:FlowFraction,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	MinFlow::flow_mol
	MaxFlow::flow_mol
	Inlet::stream 
	Outlet::stream 
	FlowFraction::control_signal 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export valve_flow
function setEquationFlow(in::valve_flow)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
end
function atributes(in::valve_flow,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Valve"
	fields[:Brief]="Model of a very simple valve for setting the flow with a controller."
	fields[:Info]="== ASSUMPTIONS ==
* nothing happens in this valve

== SET ==
* MinFlow: the Minimum Flow Allowable in the valve;
* MaxFlow: the Maximum Flow Allowable in the valve;

== SPECIFY ==
* the Inlet stream
* the FlowFraction (the model requires an inlet signal, also you can use a controller for setting the FlowFraction)
"
	drive!(fields,_)
	return fields
end
valve_flow(_::Dict{Symbol,Any})=begin
	newModel=valve_flow()
	newModel.attributes=atributes(newModel,_)
	newModel
end
