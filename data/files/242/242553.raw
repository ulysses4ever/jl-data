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
#*-------------------------------------------------------------------
#* Author: Rafael de Pelegrini Soares
#*         Maur좩cio Carvalho Maciel
#* $Id$
#*--------------------------------------------------------------------
type mixer2
	mixer2()=begin
		new(
			stream (Dict{Symbol,Any}(
				:Brief=>"Inlet stream 1",
				:PosX=>0,
				:PosY=>0.25,
				:Symbol=>"_{in1}"
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Inlet stream 2",
				:PosX=>0,
				:PosY=>0.75,
				:Symbol=>"_{in2}"
			)),
			streamPH (Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>0.5059,
				:Symbol=>"_{out}"
			)),
			[
				:(Outlet.F = Inlet1.F + Inlet2.F),
				:(Outlet.F*Outlet.z = Inlet1.F*Inlet1.z + Inlet2.F*Inlet2.z),
				:(Outlet.F*Outlet.h = Inlet1.F*Inlet1.h + Inlet2.F*Inlet2.h),
				:(Outlet.P = min([Inlet1.P, Inlet2.P])),
			],
			[
				"Flow","Composition","Energy Balance","Pressure",
			],
			[:Inlet1,:Inlet2,:Outlet,]
		)
	end
	Inlet1::stream 
	Inlet2::stream 
	Outlet::streamPH 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export mixer2
function setEquationFlow(in::mixer2)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
end
function atributes(in::mixer2,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/mixer"
	fields[:Brief]="Model of a mixer with 2 inputs"
	fields[:Info]="== Assumptions ==
* static
* adiabatic

== Specify ==
* the inlet streams"
	drive!(fields,_)
	return fields
end
mixer2(_::Dict{Symbol,Any})=begin
	newModel=mixer2()
	newModel.attributes=atributes(newModel,_)
	newModel
end
