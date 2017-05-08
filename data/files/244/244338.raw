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
type Shell_Side_Main
	Shell_Side_Main()=begin
		new(
			length(Dict{Symbol,Any}(
				:Brief=>"Inside Shell Diameter",
				:Lower=>1E-6
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Shellside Fouling Resistance",
				:Unit=>"m^2*K/kW",
				:Symbol=>"Rf_{shell}",
				:Default=>1E-6 ,
				:Lower=>0
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Inlet Nozzle Inside Diameter",
				:Lower=>1E-6
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Outlet Nozzle Inside Diameter",
				:Lower=>1E-6
			)),
			Shell_Pdrop(Dict{Symbol,Any}(
				:Brief=>"Shell Side Pressure Drop",
				:Symbol=>" "
			)),
			Shell_Heat_Transfer(Dict{Symbol,Any}(
				:Brief=>"Shell Side Heat Transfer",
				:Symbol=>" "
			)),
			Physical_Properties(Dict{Symbol,Any}(
				:Brief=>"ShellSide Properties",
				:Symbol=>" "
			)),
			[:ShellID,:Fouling,:InletNozzleID,:OutletNozzleID,],
			[:PressureDrop,:HeatTransfer,:Properties,]
		)
	end
	ShellID::length 
	Fouling::positive 
	InletNozzleID::length 
	OutletNozzleID::length 
	PressureDrop::Shell_Pdrop 
	HeatTransfer::Shell_Heat_Transfer 
	Properties::Physical_Properties 
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Shell_Side_Main
function atributes(in::Shell_Side_Main,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Main variables in the Shell Side section of a shell and tube heat exchanger."
	drive!(fields,_)
	return fields
end
Shell_Side_Main(_::Dict{Symbol,Any})=begin
	newModel=Shell_Side_Main()
	newModel.attributes=atributes(newModel,_)
	newModel
end
