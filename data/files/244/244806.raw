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
#* Author: Maur좩cio Carvalho Maciel
#* $Id$
#*--------------------------------------------------------------------
type sepComp
	sepComp()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of chemical components"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0,
				:PosY=>0.5001,
				:Symbol=>"_{Inlet}"
			)),
			streamPH(Dict{Symbol,Any}(
				:Brief=>"Overhead_Outlet stream",
				:PosX=>0.5,
				:PosY=>0,
				:Symbol=>"_{Overhead}"
			)),
			streamPH(Dict{Symbol,Any}(
				:Brief=>"Bottom_Outlet stream",
				:PosX=>0.5,
				:PosY=>1,
				:Symbol=>"_{Bottom}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Rate of heat supply",
				:PosX=>1,
				:PosY=>0.7559,
				:Symbol=>"_{in}"
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Fraction to Overhead_Outlet",
				:Symbol=>"\\phi_{overhead}"
			)),(NComp)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Fraction to Bottom_Outlet",
				:Symbol=>"\\phi_{bottom}"
			)),(NComp)),
			[
				:(Overhead_Outlet.F*Overhead_Outlet.z = Inlet.F * Inlet.z*Overhead_Splits),
				:(sum(Bottom_Outlet.z) = 1),
				:(Overhead_Splits+Bottom_Splits = 1),
				:(sum(Overhead_Outlet.z) = 1),
				:(Overhead_Outlet.F*Overhead_Outlet.z + Bottom_Outlet.F*Bottom_Outlet.z = Inlet.F*Inlet.z),
				:(Inlet.F*Inlet.h = Overhead_Outlet.F*Overhead_Outlet.h + Bottom_Outlet.F*Bottom_Outlet.h - InletQ),
			],
			[
				"Composition Overhead","Bottom Composition Constraints","Sum Of Splits","Overhead Composition Constraints","Global Composition","Energy Balance",
			],
			[:PP,:NComp,],
			[:Inlet,:Overhead_Outlet,:Bottom_Outlet,:InletQ,:Overhead_Splits,:Bottom_Splits,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Inlet::stream
	Overhead_Outlet::streamPH
	Bottom_Outlet::streamPH
	InletQ::power
	Overhead_Splits::Array{fraction}
	Bottom_Splits::Array{fraction}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export sepComp
function setEquationFlow(in::sepComp)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	#"Overhead Pressure"
	#	Overhead_Outlet.P = Inlet.P;
	#"Bottom Pressure"
	#	Bottom_Outlet.P = Inlet.P;
	#"Overhead Temperature"
	#	Overhead_Outlet.T = Inlet.T;
	#"Bottom Temperature"
	#	Bottom_Outlet.T = Inlet.T;
	
end
function atributes(in::sepComp,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/SepComp"
	fields[:Brief]="Model of a separator of components"
	fields[:Info]="== Assumptions ==
* thermodynamics equilibrium
	
== Specify ==
* the inlet stream
* (NComp) Overhead_Splits or (NComp) Bottom_Splits 
* the Pressure and Temperature of the outlet streams
"
	drive!(fields,_)
	return fields
end
sepComp(_::Dict{Symbol,Any})=begin
	newModel=sepComp()
	newModel.attributes=atributes(newModel,_)
	newModel
end
