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
#* $Id: PHE.mso 250 2007-04-27 16:32:02Z bicca $
#*------------------------------------------------------------------
type PHE_PressureDrop
	PHE_PressureDrop()=begin
		new(
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Channel Pressure Drop",
				:Default=>0.01,
				:Lower=>1E-10,
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P^{channel}"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Ports Pressure Drop",
				:Default=>0.01,
				:Lower=>1E-10,
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P^{ports}"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Total Pressure Drop",
				:Default=>0.01,
				:Lower=>1E-10,
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P"
			)),
			fricfactor(Dict{Symbol,Any}(
				:Brief=>"Friction Factor",
				:Default=>0.05,
				:Lower=>1E-10,
				:Upper=>2000
			)),
			velocity(Dict{Symbol,Any}(
				:Brief=>"Stream Velocity in Channel",
				:Lower=>1E-8,
				:Symbol=>"V^{channel}"
			)),
			velocity(Dict{Symbol,Any}(
				:Brief=>"Stream Velocity in Ports",
				:Lower=>1E-8,
				:Symbol=>"V^{ports}"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Number of  Channels per Pass",
				:Symbol=>"N^{passage}"
			)),
			[:DPchannel,:DPports,:Pdrop,:fi,:Vchannel,:Vports,:Npassage,]
		)
	end
	DPchannel::press_delta
	DPports::press_delta
	Pdrop::press_delta
	fi::fricfactor
	Vchannel::velocity
	Vports::velocity
	Npassage::positive
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export PHE_PressureDrop
function atributes(in::PHE_PressureDrop,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="to be documented"
	fields[:Info]="to be documented"
	drive!(fields,_)
	return fields
end
PHE_PressureDrop(_::Dict{Symbol,Any})=begin
	newModel=PHE_PressureDrop()
	newModel.attributes=atributes(newModel,_)
	newModel
end
