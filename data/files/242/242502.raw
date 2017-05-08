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
#* Author: Gerson Bicca
#*$Id$									
#*-------------------------------------------------------------------
type flow_measurement
	flow_measurement()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Type=>"PP"
			)),
			DanaInteger(),
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"Flow Constant",
				:Hidden=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0,
				:PosY=>0.78,
				:Protected=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>0.78,
				:Protected=>true
			)),
			control_signal(Dict{Symbol,Any}(
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
				:(FlowSignal*FlowConst = Inlet.F),
			],
			[
				"Overall Molar Balance","Temperature","Pressure","Energy Balance","Vapour fraction","Componente Molar Balance","Flow Measurement in kmol/h",
			],
			[:PP,:NComp,:FlowConst,],
			[:Inlet,:Outlet,:FlowSignal,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	FlowConst::flow_mol
	Inlet::stream
	Outlet::stream
	FlowSignal::control_signal
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export flow_measurement
function set(in::flow_measurement)
	FlowConst = 1*"kmol/h"
	 
end
function setEquationFlow(in::flow_measurement)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
end
function atributes(in::flow_measurement,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/flow_measurement"
	fields[:Brief]="Model to measure the flow rate in a pipe line. "
	drive!(fields,_)
	return fields
end
flow_measurement(_::Dict{Symbol,Any})=begin
	newModel=flow_measurement()
	newModel.attributes=atributes(newModel,_)
	newModel
end
