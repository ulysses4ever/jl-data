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
#* File containg models of columns: distillation, stripping, absorbers
#* rectifier, ....
#*
#* The default nomenclature is:
#*		Type_Column_reboilertype_condensertyper
#*
#* where:
#*	Type = refluxed or reboiled or section
#*	Column = Stripping, Absorption, Rectifier, Distillation
#*	Reboiler type (if exists) = kettle or thermosyphon
#*	Condenser type (if exists) = with subccoling or without subcooling
#*
#*-----------------------------------------------------------------------
#* Author: Paula B. Staudt
#* $Id: column.mso 511 2008-05-12 17:25:33Z paula $
#*---------------------------------------------------------------------
type ControlSection
	ControlSection()=begin
		NComp=outers.NComp
		new(
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of components"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Temperature Indicator in the tray"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Pressure Indicator in the tray"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Composition Indicator in the tray"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Component to indicate"
			)),
			[:NComp,:Tindicator_TrayNumber,:Pindicator_TrayNumber,:zindicator_TrayNumber,:zindicator_Component,],
		)
	end
	NComp::DanaInteger 
	Tindicator_TrayNumber::DanaInteger 
	Pindicator_TrayNumber::DanaInteger 
	zindicator_TrayNumber::DanaInteger 
	zindicator_Component::DanaInteger 
	parameters::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export ControlSection
function atributes(in::ControlSection,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Control variables for column section."
	drive!(fields,_)
	return fields
end
ControlSection(_::Dict{Symbol,Any})=begin
	newModel=ControlSection()
	newModel.attributes=atributes(newModel,_)
	newModel
end
