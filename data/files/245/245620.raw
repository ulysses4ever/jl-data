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
type Section_Column
	Section_Column()=begin
		new(
			SectionColumnBasic(),
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:PosX=>0,
				:PosY=>0.55
			)),
			[
				:(FeedTray.F= TRAYS([1:_base_1.NumberOfTrays]).Inlet.F),
				:(FeedTray.T = TRAYS([1:_base_1.NumberOfTrays]).Inlet.T),
				:(FeedTray.P = TRAYS([1:_base_1.NumberOfTrays]).Inlet.P),
				:(FeedTray.z = TRAYS([1:_base_1.NumberOfTrays]).Inlet.z),
				:(FeedTray.v = TRAYS([1:_base_1.NumberOfTrays]).Inlet.v),
				:(FeedTray.h = TRAYS([1:_base_1.NumberOfTrays]).Inlet.h),
				:(0*"mol/h"= TRAYS([1:_base_1.NumberOfTrays]).Inlet.F),
				:(300*"K" = TRAYS([1:_base_1.NumberOfTrays]).Inlet.T),
				:(1*"atm" = TRAYS([1:_base_1.NumberOfTrays]).Inlet.P),
				:(0.1 = TRAYS([1:_base_1.NumberOfTrays]).Inlet.z),
				:(0 = TRAYS([1:_base_1.NumberOfTrays]).Inlet.v),
				:(0*"J/mol" = TRAYS([1:_base_1.NumberOfTrays]).Inlet.h),
			],
			[
				"FeedTrayTop Inlet Flow","FeedTrayTop Inlet Temperature","FeedTrayTop Inlet Pressure","FeedTrayTop Inlet Composition","FeedTrayTop Inlet Vapour Fraction","FeedTrayTop Inlet Enthalpy","Inlet Tray - Flow Sealed","Inlet Tray -  Temperature","Inlet Tray -  Pressure","Inlet Tray -  Composition","Inlet Tray -  Vapour Fraction","Inlet Tray -  Enthalpy",
			],
			[:FeedTray,]
		)
	end
	_base_1::SectionColumnBasic
	FeedTray::stream
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Section_Column
function set(in::Section_Column)
	_base_1.NumberOfFeeds = 1
	 
end
function setEquationFlow(in::Section_Column)
	#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	# Equating Feed Tray Variables to Trays Variables
	#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if i == FeedTrayLocation(1) 
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
function atributes(in::Section_Column,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/SectionColumn"
	fields[:Brief]="Model of a column section."
	fields[:Info]="== Model of a column section containing ==
* NumberOfTrays TRAYS.
* One Feed Inlet.

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
Section_Column(_::Dict{Symbol,Any})=begin
	newModel=Section_Column()
	newModel.attributes=atributes(newModel,_)
	newModel
end
