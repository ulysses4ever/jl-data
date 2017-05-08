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
#*--------------------------------------------------------------------
#* Author: Gerson Balbueno Bicca 
#* $Id$
#*--------------------------------------------------------------------
type LMTD_Basic
	LMTD_Basic()=begin
		new(
			temp_delta (Dict{Symbol,Any}(
				:Brief=>"Temperature Difference at Inlet",
				:Lower=>1e-6,
				:Symbol=>"\\Delta T_0",
				:Protected=>true
			)),
			temp_delta (Dict{Symbol,Any}(
				:Brief=>"Temperature Difference at Outlet",
				:Lower=>1e-6,
				:Symbol=>"\\Delta T_L",
				:Protected=>true
			)),
			temp_delta (Dict{Symbol,Any}(
				:Brief=>"Logarithmic Mean Temperature Difference",
				:Lower=>1e-6,
				:Protected=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"LMTD Correction Factor",
				:Lower=>0.1,
				:Protected=>true
			)),
			[
				:(LMTD = 0.5*(DT0+DTL)),
				:(LMTD= (DT0-DTL)/ln(DT0/DTL)),
				:(LMTD = 0.5*(DT0+DTL)*(1-(DT0-DTL)^2/(DT0*DTL)*(1+(DT0-DTL)^2/(DT0*DTL)/2)/12)),
			],
			[
				"Log Mean Temperature Difference","Log Mean Temperature Difference","Log Mean Temperature Difference",
			],
			[:DT0,:DTL,:LMTD,:Fc,]
		)
	end
	DT0::temp_delta 
	DTL::temp_delta 
	LMTD::temp_delta 
	Fc::positive 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export LMTD_Basic
function setEquationFlow(in::LMTD_Basic)
	if DT0*DTL <= 0 * "K^2" 
		addEquation(1)
	else
		if abs(DT0 - DTL) > 0.05*max(abs([DT0,DTL])) 
			addEquation(2)
		else
			addEquation(3)
		end
	end
end
function atributes(in::LMTD_Basic,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Log Mean Temperature Difference Method."
	fields[:Info]="This model should be used as submodel when the LMTD needs to be calculating"
	drive!(fields,_)
	return fields
end
LMTD_Basic(_::Dict{Symbol,Any})=begin
	newModel=LMTD_Basic()
	newModel.attributes=atributes(newModel,_)
	newModel
end
