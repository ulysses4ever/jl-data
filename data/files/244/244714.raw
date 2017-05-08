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
#*----------------------------------------------------------------------
#* Author: Gerson Balbueno Bicca 
#* $Id$
#*--------------------------------------------------------------------
type cooler
	cooler()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin (Dict{Symbol,Any}(
				:Brief=>"Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of Components"
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Option for Display Phase Equilibrium K-values",
				:Valid=>["yes","no"],
				:Default=>"yes"
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Actual Duty",
				:Symbol=>"Q_{Duty}"
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Vapor fraction Outlet Stream",
				:Symbol=>"V_{frac}"
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Liquid fraction Outlet Stream",
				:Symbol=>"L_{frac}"
			)),
			fill(DanaReal (Dict{Symbol,Any}(
				:Brief=>"Phase Equilibrium K-values",
				:Lower=>1E-30,
				:Upper=>1E30,
				:Symbol=>"K_{value}"
			)),(NComp)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Pressure Ratio",
				:Symbol=>"P_{ratio}"
			)),
			press_delta (Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P"
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Inlet Stream",
				:PosX=>0,
				:PosY=>0.615,
				:Symbol=>"^{in}"
			)),
			streamPH (Dict{Symbol,Any}(
				:Brief=>"Outlet Stream",
				:PosX=>1,
				:PosY=>0.615,
				:Symbol=>"^{out}"
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Inlet Heat Stream",
				:PosX=>0.5,
				:PosY=>0,
				:Symbol=>"_{out}"
			)),
			[
				:(Outlet.F = Inlet.F),
				:(Outlet.F*Outlet.z([1 : NComp]) = Inlet.F*Inlet.z([1 : NComp])),
				:(Vfrac = Outlet.v),
				:(Lfrac = 1-Vfrac),
				:(Duty = Outlet.F*Outlet.h - Inlet.F*Inlet.h),
				:(Outlet.P = Inlet.P - Pdrop),
				:(Outlet.P = Inlet.P * Pratio),
				:(Kvalue*Outlet.x = Outlet.y),
				:(Kvalue = 1),
				:(Heat = -Duty),
			],
			[
				"Flow","Composition","Vapor fraction Outlet Stream","Liquid fraction Outlet Stream","Heat Duty","Pressure Drop","Pressure Ratio","K-values Phase Equilibrium","K-values Phase Equilibrium","Duty Specification",
			],
			[:PP,:NComp,:Kvalues,],
			[:Duty,:Vfrac,:Lfrac,:Kvalue,:Pratio,:Pdrop,:Inlet,:Outlet,:Heat,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	Kvalues::DanaSwitcher 
	Duty::power 
	Vfrac::fraction 
	Lfrac::fraction 
	Kvalue::Array{DanaReal }
	Pratio::positive 
	Pdrop::press_delta 
	Inlet::stream 
	Outlet::streamPH 
	Heat::power 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export cooler
function setEquationFlow(in::cooler)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	let switch=Kvalues
		# Fix for better convergence !!!
		if switch=="yes"
			addEquation(8)
		elseif switch=="no"
			addEquation(9)
		end
	end
	addEquation(10)
end
function atributes(in::cooler,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/cooler"
	fields[:Brief]="Cooler"
	fields[:Info]="Determines thermal and phase conditions of an outlet stream.

== Specify ==
* The Inlet stream
* Specify: 
**The outlet temperature and the outlet pressure or
** The outlet temperature and the inlet energy stream or
** The outlet pressure and the inlet energy stream
"
	drive!(fields,_)
	return fields
end
cooler(_::Dict{Symbol,Any})=begin
	newModel=cooler()
	newModel.attributes=atributes(newModel,_)
	newModel
end
