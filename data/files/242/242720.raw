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
type Section_Column3
	Section_Column3()=begin
		new(
			SectionColumnBasic(),
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
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:PosX=>0,
				:PosY=>0.85
			)),
			[
				:(FeedTrayOne.F= TRAYS([1:_base_1.NumberOfTrays]).Inlet.F),
				:(FeedTrayOne.T = TRAYS([1:_base_1.NumberOfTrays]).Inlet.T),
				:(FeedTrayOne.P = TRAYS([1:_base_1.NumberOfTrays]).Inlet.P),
				:(FeedTrayOne.z = TRAYS([1:_base_1.NumberOfTrays]).Inlet.z),
				:(FeedTrayOne.v = TRAYS([1:_base_1.NumberOfTrays]).Inlet.v),
				:(FeedTrayOne.h = TRAYS([1:_base_1.NumberOfTrays]).Inlet.h),
				:(FeedTrayTwo.F= TRAYS([1:_base_1.NumberOfTrays]).Inlet.F),
				:(FeedTrayTwo.T = TRAYS([1:_base_1.NumberOfTrays]).Inlet.T),
				:(FeedTrayTwo.P = TRAYS([1:_base_1.NumberOfTrays]).Inlet.P),
				:(FeedTrayTwo.z = TRAYS([1:_base_1.NumberOfTrays]).Inlet.z),
				:(FeedTrayTwo.v = TRAYS([1:_base_1.NumberOfTrays]).Inlet.v),
				:(FeedTrayTwo.h = TRAYS([1:_base_1.NumberOfTrays]).Inlet.h),
				:(FeedTrayThree.F= TRAYS([1:_base_1.NumberOfTrays]).Inlet.F),
				:(FeedTrayThree.T = TRAYS([1:_base_1.NumberOfTrays]).Inlet.T),
				:(FeedTrayThree.P = TRAYS([1:_base_1.NumberOfTrays]).Inlet.P),
				:(FeedTrayThree.z = TRAYS([1:_base_1.NumberOfTrays]).Inlet.z),
				:(FeedTrayThree.v = TRAYS([1:_base_1.NumberOfTrays]).Inlet.v),
				:(FeedTrayThree.h = TRAYS([1:_base_1.NumberOfTrays]).Inlet.h),
				:(0*"mol/h"= TRAYS([1:_base_1.NumberOfTrays]).Inlet.F),
				:(300*"K" = TRAYS([1:_base_1.NumberOfTrays]).Inlet.T),
				:(1*"atm" = TRAYS([1:_base_1.NumberOfTrays]).Inlet.P),
				:(0.1 = TRAYS([1:_base_1.NumberOfTrays]).Inlet.z),
				:(0 = TRAYS([1:_base_1.NumberOfTrays]).Inlet.v),
				:(0*"J/mol" = TRAYS([1:_base_1.NumberOfTrays]).Inlet.h),
			],
			[
				"FeedTrayTop Inlet Flow","FeedTrayTop Inlet Temperature","FeedTrayTop Inlet Pressure","FeedTrayTop Inlet Composition","FeedTrayTop Inlet Vapour Fraction","FeedTrayTop Inlet Enthalpy","FeedTrayBottom Inlet Flow","FeedTrayBottom Inlet Temperature","FeedTrayBottom Inlet Pressure","FeedTrayBottom Inlet Composition","FeedTrayBottom Inlet Vapour Fraction","FeedTrayBottom Inlet Enthalpy","FeedTrayBottom Inlet Flow","FeedTrayBottom Inlet Temperature","FeedTrayBottom Inlet Pressure","FeedTrayBottom Inlet Composition","FeedTrayBottom Inlet Vapour Fraction","FeedTrayBottom Inlet Enthalpy","Inlet Tray - Flow Sealed","Inlet Tray -  Temperature","Inlet Tray -  Pressure","Inlet Tray -  Composition","Inlet Tray -  Vapour Fraction","Inlet Tray -  Enthalpy",
			],
			[:FeedTrayOne,:FeedTrayTwo,:FeedTrayThree,]
		)
	end
	_base_1::SectionColumnBasic
	FeedTrayOne::stream 
	FeedTrayTwo::stream 
	FeedTrayThree::stream 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Section_Column3
function set(in::Section_Column3)
	_base_1.NumberOfFeeds = 3
	 
end
function setEquationFlow(in::Section_Column3)
	if i == FeedTrayLocation(1) 
		addEquation(1)
		addEquation(2)
		addEquation(3)
		addEquation(4)
		addEquation(5)
		addEquation(6)
	else
		if i == FeedTrayLocation(2) 
			addEquation(7)
			addEquation(8)
			addEquation(9)
			addEquation(10)
			addEquation(11)
			addEquation(12)
		else
			if i == FeedTrayLocation(3) 
				addEquation(13)
				addEquation(14)
				addEquation(15)
				addEquation(16)
				addEquation(17)
				addEquation(18)
			else
				addEquation(19)
				addEquation(20)
				addEquation(21)
				addEquation(22)
				addEquation(23)
				addEquation(24)
			end
		end
	end
end
function atributes(in::Section_Column3,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/SectionColumn"
	fields[:Brief]="Model of a column section."
	fields[:Info]="== Model of a column section containing ==
* NumberOfTrays TRAYS.
* Three Feed Inlets.

== Specify ==
* the feed stream of each tray (Inlet);
* the Murphree eficiency for each tray Emv;
* the InletLiquid stream of the top tray;
* the InletVapour stream of the bottom tray.

== Initial Conditions ==
* the TRAYS temperature (OutletLiquid.T);
* the TRAYS liquid level (Level) OR the TRAYS liquid flow (OutletLiquid.F);
* (NoComps - 1) OutletLiquid (OR OutletVapour) compositions for each tray.
"
	drive!(fields,_)
	return fields
end
Section_Column3(_::Dict{Symbol,Any})=begin
	newModel=Section_Column3()
	newModel.attributes=atributes(newModel,_)
	newModel
end
