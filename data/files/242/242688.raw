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
type SectionColumnBasic
	SectionColumnBasic()=begin
		PP=outers.PP
		NComp=outers.NComp
		[
			
		],
		[
			
		],
		new(
			DanaPlugin (Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of components"
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of Feed Trays",
				:Default=>3,
				:Protected=>true
			)),
			fill(DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Feed tray Location",
				:Default=>2
			)),(NumberOfFeeds)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of trays",
				:Default=>8
			)),
			fill(DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Liquid Side Tray Index",
				:Default=>0,
				:Hidden=>true
			)),(NumberOfTrays)),
			fill(DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Vapour Side Tray Index",
				:Default=>0,
				:Hidden=>true
			)),(NumberOfTrays)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Liquid Side Stream Location",
				:Default=>2
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Vapour Side Stream Location",
				:Default=>2
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Valid=>["Reepmeyer", "Feehery_Fv", "Roffel_Fv", "Klingberg", "Wang_Fv", "Elgue"],
				:Default=>"Reepmeyer"
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Valid=>["Francis", "Wang_Fl", "Olsen", "Feehery_Fl", "Roffel_Fl"],
				:Default=>"Francis"
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Tray Diameter",
				:Default=>1.600
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Tray Spacing",
				:Default=>0.600
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Fraction of the active area that is occupied by the holes with respect to the total tray area",
				:Default=>0.10
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Fraction of the downcomer area with respect to the total tray area",
				:Default=>0.20
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Weir length",
				:Default=>1
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Weir height",
				:Default=>0.05
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Number of liquid passes in the tray",
				:Lower=>1,
				:Default=>1
			)),
			heat_rate (Dict{Symbol,Any}(
				:Brief=>"Rate of heat supply",
				:Default=>0
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Aeration fraction",
				:Default=>1
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Dry pressure drop coefficient",
				:Default=>0.60
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Murphree efficiency for All Trays",
				:Default=>1
			)),
			[
				:(TCI*"K" = TRAYS(CONTROL.Tindicator_TrayNumber).OutletVapour.T),
				:(PCI*"atm" = TRAYS(CONTROL.Pindicator_TrayNumber).OutletVapour.P),
				:(TRAYS.LFlowModel = 1),
				:(TRAYS.LFlowModel = 2),
				:(TRAYS.LFlowModel = 3),
				:(TRAYS.LFlowModel = 4),
				:(TRAYS.LFlowModel = 5),
				:(TRAYS.VFlowModel = 1),
				:(TRAYS.VFlowModel = 2),
				:(TRAYS.VFlowModel = 3),
				:(TRAYS.VFlowModel = 4),
				:(TRAYS.VFlowModel = 5),
				:(TRAYS.VFlowModel = 6),
				:(LiquidConnector.F = LiquidInlet.F),
				:(LiquidConnector.T = LiquidInlet.T),
				:(LiquidConnector.P = LiquidInlet.P),
				:(LiquidConnector.z = LiquidInlet.z),
				:(LiquidConnector.v = LiquidInlet.v),
				:(LiquidConnector.h = LiquidInlet.h),
				:(VapourConnector.F = VapourInlet.F),
				:(VapourConnector.T = VapourInlet.T),
				:(VapourConnector.P = VapourInlet.P),
				:(VapourConnector.z = VapourInlet.z),
				:(VapourConnector.v = VapourInlet.v),
				:(VapourConnector.h = VapourInlet.h),
				:(LiquidOutlet.F = TRAYS(NumberOfTrays).OutletLiquid.F),
				:(LiquidOutlet.T = TRAYS(NumberOfTrays).OutletLiquid.T),
				:(LiquidOutlet.P = TRAYS(NumberOfTrays).OutletLiquid.P),
				:(LiquidOutlet.z = TRAYS(NumberOfTrays).OutletLiquid.z),
				:(VapourOutlet.F = TRAYS(1).OutletVapour.F),
				:(VapourOutlet.T = TRAYS(1).OutletVapour.T),
				:(VapourOutlet.P = TRAYS(1).OutletVapour.P),
				:(VapourOutlet.z = TRAYS(1).OutletVapour.z),
				:(VapourDrawOff.F*VapSideTrayIndex= TRAYS.VapourSideStream.F),
				:(VapourDrawOff.T = TRAYS(VapourSideStreamLocation).VapourSideStream.T),
				:(VapourDrawOff.P = TRAYS(VapourSideStreamLocation).VapourSideStream.P),
				:(VapourDrawOff.z = TRAYS(VapourSideStreamLocation).VapourSideStream.z),
				:(VapourDrawOffFlow = VapourDrawOff.F),
				:(LiquidDrawOff.F*LiqSideTrayIndex= TRAYS.LiquidSideStream.F),
				:(LiquidDrawOff.T = TRAYS(LiquidSideStreamLocation).LiquidSideStream.T),
				:(LiquidDrawOff.P = TRAYS(LiquidSideStreamLocation).LiquidSideStream.P),
				:(LiquidDrawOff.z = TRAYS(LiquidSideStreamLocation).LiquidSideStream.z),
				:(LiquidDrawOffFlow = LiquidDrawOff.F),
			],
			[
				"Tray Temperature Indicator","Tray Pressure Indicator","","","","","","","","","","","","Liquid Inlet Flow","Liquid Inlet Temperature","Liquid Inlet Pressure","Liquid Inlet Composition","Liquid Inlet Vapour Fraction","Liquid Inlet Enthalpy","Vapour Inlet Flow","Vapour Inlet Temperature","Vapour Inlet Pressure","Vapour Inlet Composition","Vapour Inlet Vapour Fraction","Vapour Inlet Enthalpy","Liquid Outlet Flow","Liquid Outlet Temperature","Liquid Outlet Pressure","Liquid Outlet Composition","Vapour Outlet Flow","Vapour Outlet Temperature","Vapour Outlet Pressure","Vapour Outlet Composition","Vapour Draw Off Stream - Flow","Vapour Draw Off Stream - Temperature","Vapour Draw Off Stream - Pressure","Vapour Draw Off Stream - Composition","Vapour Draw Off Stream","Liquid Draw Off Stream - Flow","Liquid Draw Off Stream - Temperature","Liquid Draw Off Stream - Pressure","Liquid Draw Off Stream - Composition","Liquid Draw Off Stream",
			],
			[:PP,:NComp,:NumberOfFeeds,:FeedTrayLocation,:NumberOfTrays,:LiqSideTrayIndex,:VapSideTrayIndex,:LiquidSideStreamLocation,:VapourSideStreamLocation,:VapourFlowModel,:LiquidFlowModel,:TrayDiameter,:TraySpacing,:Fraction_HoleArea,:Fraction_DowncomerArea,:WeirLength,:WeirHeight,:TrayLiquidPasses,:HeatSupply,:AerationFraction,:DryPdropCoeff,:MurphreeEff,],
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	NumberOfFeeds::DanaInteger 
	FeedTrayLocation::Array{DanaInteger }
	NumberOfTrays::DanaInteger 
	LiqSideTrayIndex::Array{DanaInteger }
	VapSideTrayIndex::Array{DanaInteger }
	LiquidSideStreamLocation::DanaInteger 
	VapourSideStreamLocation::DanaInteger 
	VapourFlowModel::DanaSwitcher 
	LiquidFlowModel::DanaSwitcher 
	TrayDiameter::length 
	TraySpacing::length 
	Fraction_HoleArea::fraction 
	Fraction_DowncomerArea::fraction 
	WeirLength::length 
	WeirHeight::length 
	TrayLiquidPasses::positive 
	HeatSupply::heat_rate 
	AerationFraction::DanaReal 
	DryPdropCoeff::DanaReal 
	MurphreeEff::DanaReal 
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export SectionColumnBasic
function set(in::SectionColumnBasic)
	VapSideTrayIndex(VapourSideStreamLocation) =1
	 LiqSideTrayIndex(LiquidSideStreamLocation) =1
	 TRAYS.TrayDiameter_ = TrayDiameter
	 TRAYS.TraySpacing_ = TraySpacing
	 TRAYS.Fraction_HoleArea_ = Fraction_HoleArea
	 TRAYS.Fraction_DowncomerArea_ = Fraction_DowncomerArea
	 TRAYS.WeirLength_ = WeirLength
	 TRAYS.WeirHeight_ = WeirHeight
	 TRAYS.TrayLiquidPasses_ = TrayLiquidPasses
	 TRAYS.HeatSupply_ = HeatSupply
	 TRAYS.AerationFraction_ = AerationFraction
	 TRAYS.DryPdropCoeff_ = DryPdropCoeff
	 TRAYS.MurphreeEff_ = MurphreeEff
	 
end
function initial(in::SectionColumnBasic)
	
end
function setEquationFlow(in::SectionColumnBasic)
	#TCI*'K' = TRAYS(min([NumberOfTrays, CONTROL.Tindicator_TrayNumber])).OutletVapour.T;
	addEquation(1)
	#PCI*'atm' = TRAYS(min([NumberOfTrays, CONTROL.Pindicator_TrayNumber])).OutletVapour.P;
	addEquation(2)
	let switch=LiquidFlowModel
		if switch=="Francis"
			addEquation(3)
		elseif switch=="Wang_Fl"
			addEquation(4)
		elseif switch=="Olsen"
			addEquation(5)
		elseif switch=="Feehery_Fl"
			addEquation(6)
		elseif switch=="Roffel_Fl"
			addEquation(7)
		end
	end
	let switch=VapourFlowModel
		if switch=="Reepmeyer"
			addEquation(8)
		elseif switch=="Feehery_Fv"
			addEquation(9)
		elseif switch=="Roffel_Fv"
			addEquation(10)
		elseif switch=="Klingberg"
			addEquation(11)
		elseif switch=="Wang_Fv"
			addEquation(12)
		elseif switch=="Elgue"
			addEquation(13)
		end
	end
	addEquation(14)
	addEquation(15)
	addEquation(16)
	addEquation(17)
	addEquation(18)
	addEquation(19)
	addEquation(20)
	addEquation(21)
	addEquation(22)
	addEquation(23)
	addEquation(24)
	addEquation(25)
	addEquation(26)
	addEquation(27)
	addEquation(28)
	addEquation(29)
	addEquation(30)
	addEquation(31)
	addEquation(32)
	addEquation(33)
	addEquation(34)
	addEquation(35)
	addEquation(36)
	addEquation(37)
	addEquation(38)
	addEquation(39)
	addEquation(40)
	addEquation(41)
	addEquation(42)
	addEquation(43)
end
function atributes(in::SectionColumnBasic,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Model of a basic column section."
	fields[:Info]="Model of a basic column section containing a vetor of TRAYS numbered from the top-down."
	drive!(fields,_)
	return fields
end
SectionColumnBasic(_::Dict{Symbol,Any})=begin
	newModel=SectionColumnBasic()
	newModel.attributes=atributes(newModel,_)
	newModel
end
