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
type Packed_Section_ColumnBasic
	Packed_Section_ColumnBasic()=begin
		PP=outers.PP
		NComp=outers.NComp
		[
			
		],
		[
			
		],
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of components",
				:Protected=>true
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of Feed Stages",
				:Default=>3,
				:Protected=>true
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of Stages",
				:Default=>3
			)),
			fill(DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Feed Stage Location",
				:Default=>2
			)),(NumberOfFeeds)),
			length(Dict{Symbol,Any}(
				:Brief=>"Height of packing"
			)),
			heat_rate(Dict{Symbol,Any}(
				:Brief=>"Rate of heat supply"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Column diameter"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Void fraction of packing, (m^3 void space/m^3 packed bed)"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Resistance coefficient on the liquid load",
				:Default=>1
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"surface area per packing volume",
				:Unit=>"m^2/m^3"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"The Height Equivalent to a Theoretical Plate",
				:Protected=>true
			)),
			[
				:(LiquidConnector.F= LiquidInlet.F),
				:(LiquidConnector.T = LiquidInlet.T),
				:(LiquidConnector.P = LiquidInlet.P),
				:(LiquidConnector.z = LiquidInlet.z),
				:(LiquidConnector.v = LiquidInlet.v),
				:(LiquidConnector.h = LiquidInlet.h),
				:(VapourConnector.F= VapourInlet.F),
				:(VapourConnector.T = VapourInlet.T),
				:(VapourConnector.P = VapourInlet.P),
				:(VapourConnector.z = VapourInlet.z),
				:(VapourConnector.v = VapourInlet.v),
				:(VapourConnector.h = VapourInlet.h),
				:(LiquidOutlet.F= STAGES(NumberOfStages).OutletLiquid.F),
				:(LiquidOutlet.T = STAGES(NumberOfStages).OutletLiquid.T),
				:(LiquidOutlet.P = STAGES(NumberOfStages).OutletLiquid.P),
				:(LiquidOutlet.z = STAGES(NumberOfStages).OutletLiquid.z),
				:(VapourOutlet.F= STAGES(1).OutletVapour.F),
				:(VapourOutlet.T = STAGES(1).OutletVapour.T),
				:(VapourOutlet.P = STAGES(1).OutletVapour.P),
				:(VapourOutlet.z = STAGES(1).OutletVapour.z),
				:(TCI*"K" = STAGES(CONTROL.Tindicator_TrayNumber).OutletVapour.T),
				:(PCI*"atm" = STAGES(CONTROL.Pindicator_TrayNumber).OutletVapour.P),
				:(zCI * 1e-6 = STAGES(CONTROL.zindicator_TrayNumber).OutletLiquid.z(CONTROL.zindicator_Component) * STAGES(CONTROL.zindicator_TrayNumber).Mw(CONTROL.zindicator_Component) / sum(STAGES(CONTROL.zindicator_TrayNumber).Mw*STAGES(CONTROL.zindicator_TrayNumber).OutletLiquid.z)),
				:(PressureDrop = STAGES(NumberOfStages).OutletLiquid.P - STAGES(1).OutletLiquid.P),
			],
			[
				"","","","","","","","","","","","","","","","","","","","","Tray Temperature Indicator","Tray Pressure Indicator","Tray Composition Indicator","PressureDrop",
			],
			[:PP,:NComp,:NumberOfFeeds,:NumberOfStages,:FeedStageLocation,:PackingHeight,:HeatSupply,:ColumnDiameter,:VoidFraction,:ResistanceCoeff,:AreaPerPackingVol,:HETP,],
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	NumberOfFeeds::DanaInteger 
	NumberOfStages::DanaInteger 
	FeedStageLocation::Array{DanaInteger }
	PackingHeight::length 
	HeatSupply::heat_rate 
	ColumnDiameter::length 
	VoidFraction::DanaReal 
	ResistanceCoeff::positive 
	AreaPerPackingVol::DanaReal 
	HETP::length 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	parameters::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Packed_Section_ColumnBasic
function set(in::Packed_Section_ColumnBasic)
	STAGES.Number_Stages = NumberOfStages
	 STAGES.HeightOfPacking = PackingHeight
	 STAGES.HeatOnStage = HeatSupply
	 STAGES.ColumnInternalDiameter = ColumnDiameter
	 STAGES.PackingVoidFraction = VoidFraction
	 STAGES.LiquidResistanceCoeff = ResistanceCoeff
	 STAGES.AreaPerPackingVolume = AreaPerPackingVol
	 HETP = PackingHeight/NumberOfStages
	 
end
function setEquationFlow(in::Packed_Section_ColumnBasic)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
	addEquation(9)
	addEquation(10)
	addEquation(11)
	addEquation(12)
	addEquation(13)
	addEquation(14)
	addEquation(15)
	addEquation(16)
	addEquation(17)
	addEquation(18)
	addEquation(19)
	addEquation(20)
	#TCI*'K' = TRAYS(min([NumberOfTrays, CONTROL.Tindicator_TrayNumber])).OutletVapour.T;
	addEquation(21)
	#PCI*'atm' = TRAYS(min([NumberOfTrays, CONTROL.Pindicator_TrayNumber])).OutletVapour.P;
	addEquation(22)
	#zCI * .000001 = STAGES(CONTROL.zindicator_TrayNumber).OutletVapour.z(CONTROL.zindicator_Component) * STAGES(CONTROL.zindicator_TrayNumber).Mw(CONTROL.zindicator_Component) ; #/sum(STAGES(CONTROL.zindicator_TrayNumber).Mw*STAGES(CONTROL.zindicator_TrayNumber).OutletLiquid.z);
	addEquation(23)
	addEquation(24)
end
function initial(in::Packed_Section_ColumnBasic)
	
end
function atributes(in::Packed_Section_ColumnBasic,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
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
Packed_Section_ColumnBasic(_::Dict{Symbol,Any})=begin
	newModel=Packed_Section_ColumnBasic()
	newModel.attributes=atributes(newModel,_)
	newModel
end
