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
#* Model of cstr reactor
#*--------------------------------------------------------------------
#* Author: Paula B. Staudt
#* $Id$
#*--------------------------------------------------------------------
type cstr_yield
	cstr_yield()=begin
		new(
			cstr_basic(),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Yield"
			)),(NReac)),
			[
				:(_base_1.Outlet.z*_base_1.Outlet.F = _base_1.Inlet.z*_base_1.Inlet.F * sumt(_base_1.stoic*(1-yield))),
				:(diff(M*_base_1.Outlet.h) = _base_1.Inlet.F*_base_1.Inlet.h - _base_1.Outlet.F*_base_1.Outlet.h - q),
			],
			[
				"","Reactor Energy Balance",
			],
			[:yield,],
		)
	end
	_base_1::cstr_basic
	yield::Array{fraction}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export cstr_yield
function setEquationFlow(in::cstr_yield)
	addEquation(1)
	addEquation(2)
end
function atributes(in::cstr_yield,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/cstr"
	fields[:Brief]="Model of a CSTR with given yield"
	drive!(fields,_)
	return fields
end
cstr_yield(_::Dict{Symbol,Any})=begin
	newModel=cstr_yield()
	newModel.attributes=atributes(newModel,_)
	newModel
end
