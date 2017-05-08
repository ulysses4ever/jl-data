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
type Packed_Section_Column
	Packed_Section_Column()=begin
		new(
			Packed_Section_ColumnBasic(),
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:PosX=>0,
				:PosY=>0.55
			)),
			[
				:(FeedStage.F= STAGES([1:_base_1.NumberOfStages]).Inlet.F),
				:(FeedStage.T = STAGES([1:_base_1.NumberOfStages]).Inlet.T),
				:(FeedStage.P = STAGES([1:_base_1.NumberOfStages]).Inlet.P),
				:(FeedStage.z = STAGES([1:_base_1.NumberOfStages]).Inlet.z),
				:(FeedStage.v = STAGES([1:_base_1.NumberOfStages]).Inlet.v),
				:(FeedStage.h = STAGES([1:_base_1.NumberOfStages]).Inlet.h),
				:(0*"mol/h"= STAGES([1:_base_1.NumberOfStages]).Inlet.F),
				:(300*"K" = STAGES([1:_base_1.NumberOfStages]).Inlet.T),
				:(1*"atm" = STAGES([1:_base_1.NumberOfStages]).Inlet.P),
				:(0.1 = STAGES([1:_base_1.NumberOfStages]).Inlet.z),
				:(0 = STAGES([1:_base_1.NumberOfStages]).Inlet.v),
				:(0*"J/mol" = STAGES([1:_base_1.NumberOfStages]).Inlet.h),
			],
			[
				"FeedTrayTop Inlet Flow","FeedTrayTop Inlet Temperature","FeedTrayTop Inlet Pressure","FeedTrayTop Inlet Composition","FeedTrayTop Inlet Vapour Fraction","FeedTrayTop Inlet Enthalpy","Inlet Tray - Flow Sealed","Inlet Tray -  Temperature","Inlet Tray -  Pressure","Inlet Tray -  Composition","Inlet Tray -  Vapour Fraction","Inlet Tray -  Enthalpy",
			],
			[:FeedStage,]
		)
	end
	_base_1::Packed_Section_ColumnBasic
	FeedStage::stream 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Packed_Section_Column
function set(in::Packed_Section_Column)
	_base_1.NumberOfFeeds = 1
	 
end
function setEquationFlow(in::Packed_Section_Column)
	#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	# Equating Feed Tray Variables to Trays Variables
	#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if i == FeedStageLocation(1) 
		addEquation(1)
		addEquation(2)
		addEquation(3)
		addEquation(4)
		addEquation(5)
		addEquation(6)
	else
		addEquation(7)
		addEquation(8)
		addEquation(9)
		addEquation(10)
		addEquation(11)
		addEquation(12)
	end
end
function atributes(in::Packed_Section_Column,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/PackedSectionColumn"
	fields[:Brief]="Model of a packed column section."
	fields[:Info]="== Model of a packed column section containing ==
* NStages theoretical stages.

== Specify ==
* the feed stream of each tray (Inlet);
* the InletLiquid stream of the top tray;
* the InletVapour stream of the bottom tray;
* the total pressure drop (dP) of the section.

== Initial Conditions ==
* the stages temperature (OutletLiquid.T);
* the stages liquid holdup;
* (NoComps - 1) OutletLiquid (OR OutletVapour) compositions for each tray.
"
	drive!(fields,_)
	return fields
end
Packed_Section_Column(_::Dict{Symbol,Any})=begin
	newModel=Packed_Section_Column()
	newModel.attributes=atributes(newModel,_)
	newModel
end
