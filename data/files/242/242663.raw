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
type Packed_Section_Column2
	Packed_Section_Column2()=begin
		new(
			Packed_Section_ColumnBasic(),
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:PosX=>0,
				:PosY=>0.45
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:PosX=>0,
				:PosY=>0.65
			)),
			[
				:(FeedStageOne.F= STAGES([1:_base_1.NumberOfStages]).Inlet.F),
				:(FeedStageOne.T = STAGES([1:_base_1.NumberOfStages]).Inlet.T),
				:(FeedStageOne.P = STAGES([1:_base_1.NumberOfStages]).Inlet.P),
				:(FeedStageOne.z = STAGES([1:_base_1.NumberOfStages]).Inlet.z),
				:(FeedStageOne.v = STAGES([1:_base_1.NumberOfStages]).Inlet.v),
				:(FeedStageOne.h = STAGES([1:_base_1.NumberOfStages]).Inlet.h),
				:(FeedStageTwo.F= STAGES([1:_base_1.NumberOfStages]).Inlet.F),
				:(FeedStageTwo.T = STAGES([1:_base_1.NumberOfStages]).Inlet.T),
				:(FeedStageTwo.P = STAGES([1:_base_1.NumberOfStages]).Inlet.P),
				:(FeedStageTwo.z = STAGES([1:_base_1.NumberOfStages]).Inlet.z),
				:(FeedStageTwo.v = STAGES([1:_base_1.NumberOfStages]).Inlet.v),
				:(FeedStageTwo.h = STAGES([1:_base_1.NumberOfStages]).Inlet.h),
				:(0*"mol/h"= STAGES([1:_base_1.NumberOfStages]).Inlet.F),
				:(300*"K" = STAGES([1:_base_1.NumberOfStages]).Inlet.T),
				:(1*"atm" = STAGES([1:_base_1.NumberOfStages]).Inlet.P),
				:(0.1 = STAGES([1:_base_1.NumberOfStages]).Inlet.z),
				:(0 = STAGES([1:_base_1.NumberOfStages]).Inlet.v),
				:(0*"J/mol" = STAGES([1:_base_1.NumberOfStages]).Inlet.h),
			],
			[
				"FeedTrayTop Inlet Flow","FeedTrayTop Inlet Temperature","FeedTrayTop Inlet Pressure","FeedTrayTop Inlet Composition","FeedTrayTop Inlet Vapour Fraction","FeedTrayTop Inlet Enthalpy","FeedTrayBottom Inlet Flow","FeedTrayBottom Inlet Temperature","FeedTrayBottom Inlet Pressure","FeedTrayBottom Inlet Composition","FeedTrayBottom Inlet Vapour Fraction","FeedTrayBottom Inlet Enthalpy","Inlet Tray - Flow Sealed","Inlet Tray -  Temperature","Inlet Tray -  Pressure","Inlet Tray -  Composition","Inlet Tray -  Vapour Fraction","Inlet Tray -  Enthalpy",
			],
			[:FeedStageOne,:FeedStageTwo,]
		)
	end
	_base_1::Packed_Section_ColumnBasic
	FeedStageOne::stream 
	FeedStageTwo::stream 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Packed_Section_Column2
function set(in::Packed_Section_Column2)
	_base_1.NumberOfFeeds = 2
	 
end
function setEquationFlow(in::Packed_Section_Column2)
	#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	# Equating Feed Stage Variables to Stages Variables
	#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if i == FeedStageLocation(1) 
		addEquation(1)
		addEquation(2)
		addEquation(3)
		addEquation(4)
		addEquation(5)
		addEquation(6)
	else
		if i == FeedStageLocation(2) 
			addEquation(7)
			addEquation(8)
			addEquation(9)
			addEquation(10)
			addEquation(11)
			addEquation(12)
		else
			addEquation(13)
			addEquation(14)
			addEquation(15)
			addEquation(16)
			addEquation(17)
			addEquation(18)
		end
	end
end
function atributes(in::Packed_Section_Column2,_::Dict{Symbol,Any})
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
Packed_Section_Column2(_::Dict{Symbol,Any})=begin
	newModel=Packed_Section_Column2()
	newModel.attributes=atributes(newModel,_)
	newModel
end
