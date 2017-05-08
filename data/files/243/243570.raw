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
#*-----------------------------------------------------------------------
#* Author: Tiago Os򱨯rio
#* $Id$
#*---------------------------------------------------------------------
type Multiply
	Multiply()=begin
		new(
			control_signal (Dict{Symbol,Any}(
				:Brief=>"input signal 1",
				:PosX=>0,
				:PosY=>0.75
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"input signal 2",
				:PosX=>0,
				:PosY=>0.25
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"output signal",
				:PosX=>1,
				:PosY=>0.5
			)),
			[
				:(output=input1*input2),
			],
			[
				"Calculate output",
			],
			[:input1,:input2,:output,]
		)
	end
	input1::control_signal 
	input2::control_signal 
	output::control_signal 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Multiply
function setEquationFlow(in::Multiply)
	addEquation(1)
end
function atributes(in::Multiply,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Icon]="icon/Multiply"
	fields[:Brief]="Model Multiply."
	fields[:Info]="== Inputs ==
* Two input signals.
	
== Outputs ==
* One output signal.
"
	drive!(fields,_)
	return fields
end
Multiply(_::Dict{Symbol,Any})=begin
	newModel=Multiply()
	newModel.attributes=atributes(newModel,_)
	newModel
end
