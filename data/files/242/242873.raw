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
#*--------------------------------------------------------------------
#* Models to simulate a power plant.
#*--------------------------------------------------------------------
#* Author: Argimiro R. Secchi
#* $Id: power_plant.mso 195 2007-03-07 20:30:12Z arge $
#*-------------------------------------------------------------------
# Declaracao de tipos
type CorrenteVap
	CorrenteVap()=begin
		PP=outers.PP
		new(
			CorrenteZ(),
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties"
			)),
			[
				:(H = PP.VapourEnthalpy(T, P, z)),
				:(S = PP.VapourEntropy(T, P, z)),
			],
			[
				"Vapour Enthalpy","Vapour Entropy",
			],
			[:PP,],
		)
	end
	_base_1::CorrenteZ
	PP::DanaPlugin
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export CorrenteVap
function setEquationFlow(in::CorrenteVap)
	addEquation(1)
	addEquation(2)
end
function atributes(in::CorrenteVap,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Vapour Material Stream"
	fields[:Info]="Model for vapour material streams.
	This model should be used only when the phase of the stream
	is known ''a priori''."
	drive!(fields,_)
	return fields
end
CorrenteVap(_::Dict{Symbol,Any})=begin
	newModel=CorrenteVap()
	newModel.attributes=atributes(newModel,_)
	newModel
end
