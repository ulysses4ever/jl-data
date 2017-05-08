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
type InitializeStage
	InitializeStage()=begin
		NComp=outers.NComp
		new(
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of components"
			)),
			temperature (Dict{Symbol,Any}(
				:Brief=>"Tray Temperature at Column Top",
				:Default=>300
			)),
			temperature (Dict{Symbol,Any}(
				:Brief=>"Tray Temperature at Column Bottom",
				:Default=>300
			)),
			fill(fraction (Dict{Symbol,Any}(
				:Brief=>"Component Molar Fraction at Top"
			)),(NComp)),
			fill(fraction (Dict{Symbol,Any}(
				:Brief=>"Component Molar Fraction at Bottom"
			)),(NComp)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Column holdup",
				:Default=>0.1
			)),
			[:NComp,:TopStageTemperature,:BottomStageTemperature,:TopStageComposition,:BottomStageComposition,:ColumnHoldup,],
		)
	end
	NComp::DanaInteger 
	TopStageTemperature::temperature 
	BottomStageTemperature::temperature 
	TopStageComposition::Array{fraction }
	BottomStageComposition::Array{fraction }
	ColumnHoldup::positive 
	parameters::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export InitializeStage
function atributes(in::InitializeStage,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Initial conditions for Packed column section."
	drive!(fields,_)
	return fields
end
InitializeStage(_::Dict{Symbol,Any})=begin
	newModel=InitializeStage()
	newModel.attributes=atributes(newModel,_)
	newModel
end
