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
#* Author: Paula B. Staudt
#* $Id$
#*--------------------------------------------------------------------
type tank_simplified
	tank_simplified()=begin
		new(
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Valve Constant",
				:Unit=>"m^2.5/h",
				:Default=>4
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Tank area",
				:Default=>2
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Tank level"
			)),
			flow_vol(Dict{Symbol,Any}(
				:Brief=>"Input flow",
				:PosX=>0.3037,
				:PosY=>0
			)),
			flow_vol(Dict{Symbol,Any}(
				:Brief=>"Output flow",
				:PosX=>1,
				:PosY=>1
			)),
			[
				:(diff(A*Level) = Fin - Fout),
				:(Fout = k*sqrt(Level)),
			],
			[
				"Mass balance","Valve equation",
			],
			[:k,:A,],
			[:Level,:Fin,:Fout,]
		)
	end
	k::DanaReal 
	A::area 
	Level::length
	Fin::flow_vol
	Fout::flow_vol
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export tank_simplified
function setEquationFlow(in::tank_simplified)
	addEquation(1)
	addEquation(2)
end
function atributes(in::tank_simplified,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Tank"
	fields[:Brief]="Model of a simplified tank."
	fields[:Info]="== Specify ==
* the Inlet flow rate;

== Initial Conditions ==
* the tank initial level (Level);
"
	drive!(fields,_)
	return fields
end
tank_simplified(_::Dict{Symbol,Any})=begin
	newModel=tank_simplified()
	newModel.attributes=atributes(newModel,_)
	newModel
end
