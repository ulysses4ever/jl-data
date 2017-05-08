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
#* Author: Paula B. Staudt
#* $Id: tray.mso 522 2008-05-21 23:21:12Z arge $
#*--------------------------------------------------------------------
type tray
	tray()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of components"
			)),
			fill(molweight(Dict{Symbol,Any}(
				:Brief=>"Component Mol Weight",
				:Hidden=>true
			)),(NComp)),
			acceleration(Dict{Symbol,Any}(
				:Brief=>"Gravity Acceleration",
				:Default=>9.81,
				:Hidden=>true
			)),
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"Stream Flow closed",
				:Default=>0,
				:Hidden=>true
			)),
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"Low stream Flow",
				:Default=>1E-6,
				:Hidden=>true
			)),
			constant(Dict{Symbol,Any}(
				:Brief=>"Pi Number",
				:Default=>3.14159265,
				:Symbol=>"\\pi",
				:Hidden=>true
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Tray Diameter",
				:Default=>1.600
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Tray Spacing",
				:Default=>0.600
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Fraction of the active area that is occupied by the holes with respect to the total tray area",
				:Default=>0.10
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Fraction of the downcomer area with respect to the total tray area",
				:Default=>0.20
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Weir length",
				:Default=>1
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Weir height",
				:Default=>0.05
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Number of liquid passes in the tray",
				:Lower=>1,
				:Default=>1
			)),
			heat_rate(Dict{Symbol,Any}(
				:Brief=>"Rate of heat supply",
				:Default=>0
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Aeration fraction",
				:Default=>1
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Dry pressure drop coefficient",
				:Default=>0.60
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Murphree efficiency for All Trays",
				:Lower=>0.01,
				:Upper=>1
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Plate area = Atray - Adowncomer",
				:Protected=>true
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Total Volume of the tray",
				:Protected=>true
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Total holes area",
				:Protected=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Feeherys correlation coefficient",
				:Unit=>"1/m^4",
				:Default=>1,
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Elgues correlation coefficient",
				:Unit=>"kg/m/mol^2",
				:Default=>1,
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Olsens correlation coefficient",
				:Default=>1,
				:Hidden=>true
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Flag for Vapour Flow condition",
				:Valid=>["on", "off"],
				:Default=>"off",
				:Hidden=>true
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Flag for Liquid Flow condition",
				:Valid=>["on", "off"],
				:Default=>"off",
				:Hidden=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Feed stream",
				:Hidden=>true,
				:PosX=>0,
				:PosY=>0.4932,
				:Symbol=>"_{in}"
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"liquid Sidestream",
				:Hidden=>true,
				:Symbol=>"_{outL}"
			)),
			vapour_stream(Dict{Symbol,Any}(
				:Brief=>"vapour Sidestream",
				:Hidden=>true,
				:Symbol=>"_{outV}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet liquid stream",
				:PosX=>0.5195,
				:PosY=>0,
				:Symbol=>"_{inL}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet vapour stream",
				:PosX=>0.4994,
				:PosY=>1,
				:Symbol=>"_{inV}"
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Outlet liquid stream",
				:PosX=>0.8277,
				:PosY=>1,
				:Symbol=>"_{outL}"
			)),
			vapour_stream(Dict{Symbol,Any}(
				:Brief=>"Outlet vapour stream",
				:PosX=>0.8043,
				:PosY=>0,
				:Symbol=>"_{outV}"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Flag for Liquid Flow Model",
				:Lower=>0,
				:Default=>1 ,
				:Hidden=>true
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Flag for Vapour Flow Model",
				:Lower=>0,
				:Default=>1 ,
				:Hidden=>true
			)),
			fill(mol(Dict{Symbol,Any}(
				:Brief=>"Molar Holdup in the tray"
			)),(NComp)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar liquid holdup"
			)),
			mol(Dict{Symbol,Any}(
				:Brief=>"Molar vapour holdup"
			)),
			energy(Dict{Symbol,Any}(
				:Brief=>"Total Energy Holdup on tray"
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Volume"
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Vapour Molar volume"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Height of clear liquid on plate"
			)),
			fill(fraction()),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Mass Density of liquid phase"
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Mass Density of vapour phase"
			)),
			[
				:(OutletLiquid.F*vL = 1.84*"1/s"*WeirLength_*((Level-(AerationFraction_*WeirHeight_))/(AerationFraction_))^2),
				:(OutletLiquid.F*vL = 1.84*"m^0.5/s"*WeirLength_*((Level-(AerationFraction_*WeirHeight_))/(AerationFraction_))^1.5),
				:(OutletLiquid.F / "mol/s"= WeirLength_*TrayLiquidPasses_*rhoL/sum(Mw*OutletVapour.z)/(0.665*OlsenCoeff)^1.5 * ((ML*sum(Mw*OutletLiquid.z)/rhoL/PlateArea_)-WeirHeight_)^1.5 * "m^0.5/mol"),
				:(OutletLiquid.F = WeirLength_*rhoL/sum(Mw*OutletLiquid.z) * ((Level-WeirHeight_)/750/"mm")^1.5 * "m^2/s"),
				:(OutletLiquid.F = 2/3*rhoL/sum(Mw*OutletLiquid.z)*WeirLength_*(ML*sum(Mw*OutletLiquid.z)/(PlateArea_*1.3)/rhoL)^1.5*sqrt(2*Gconst/ (2*(1 - 0.3593/"Pa^0.0888545"*abs(OutletVapour.F*sum(Mw*OutletVapour.z)/(PlateArea_*1.3)/sqrt(rhoV))^0.177709)-1))),
				:(OutletLiquid.F = zero_flow),
				:(InletVapour.F*vV = sqrt((InletVapour.P - OutletVapour.P)/(rhoV*DryPdropCoeff_))*HolesArea_),
				:(InletVapour.F = rhoV/PlateArea_/FeeheryCoeff/sum(Mw*OutletVapour.z) * sqrt(((InletVapour.P - OutletVapour.P)-(rhoV*Gconst*ML*vL/PlateArea_))/rhoV)),
				:(InletVapour.F^1.08 * 0.0013 * "kg/m/mol^1.08/s^0.92*1e5" = (InletVapour.P - OutletVapour.P)*1e5 - (AerationFraction_*sum(M*Mw)/(PlateArea_*1.3)*Gconst*1e5) * (rhoV*HolesArea_/sum(Mw*OutletVapour.z))^1.08 * "m^1.08/mol^1.08"),
				:(InletVapour.F * vV = PlateArea_ * sqrt(((InletVapour.P - OutletVapour.P)-rhoL*Gconst*Level)/rhoV)),
				:(InletVapour.F * vV = PlateArea_ * sqrt(((InletVapour.P - OutletVapour.P)-rhoL*Gconst*Level)/rhoV*DryPdropCoeff_)),
				:(InletVapour.F = sqrt((InletVapour.P - OutletVapour.P)/ElgueCoeff)),
				:(InletVapour.F = zero_flow),
				:(OutletVapour.z = MurphreeEff_ * (yideal - InletVapour.z) + InletVapour.z),
				:(diff(E) = ( Inlet.F*Inlet.h + InletLiquid.F*InletLiquid.h + InletVapour.F*InletVapour.h- OutletLiquid.F*OutletLiquid.h - OutletVapour.F*OutletVapour.h - VapourSideStream.F*VapourSideStream.h - LiquidSideStream.F*LiquidSideStream.h + HeatSupply_ )),
				:(E = ML*OutletLiquid.h + MV*OutletVapour.h - OutletLiquid.P*TrayVolume_),
				:(TrayVolume_ = ML* vL + MV*vV),
				:(Level = ML*vL/PlateArea_),
				:(diff(M)=Inlet.F*Inlet.z + InletLiquid.F*InletLiquid.z + InletVapour.F*InletVapour.z- OutletLiquid.F*OutletLiquid.z - OutletVapour.F*OutletVapour.z- LiquidSideStream.F*LiquidSideStream.z-VapourSideStream.F*VapourSideStream.z),
				:(M = ML*OutletLiquid.z + MV*OutletVapour.z),
				:(sum(OutletLiquid.z)= 1.0),
				:(sum(OutletLiquid.z)= sum(OutletVapour.z)),
				:(vL = PP.LiquidVolume(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(vV = PP.VapourVolume(OutletVapour.T, OutletVapour.P, OutletVapour.z)),
				:(rhoL = PP.LiquidDensity(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(rhoV = PP.VapourDensity(InletVapour.T, InletVapour.P, InletVapour.z)),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(OutletVapour.T, OutletVapour.P, yideal)*yideal),
				:(OutletVapour.T = OutletLiquid.T),
				:(OutletVapour.P = OutletLiquid.P),
				:(OutletVapour.T = VapourSideStream.T),
				:(OutletLiquid.T = LiquidSideStream.T),
				:(OutletVapour.P= VapourSideStream.P),
				:(OutletLiquid.P = LiquidSideStream.P),
				:(OutletLiquid.z= LiquidSideStream.z),
				:(OutletVapour.z= VapourSideStream.z),
			],
			[
				"Francis Equation","Wang_Fl","Olsen","Feehery_Fl","Roffel_Fl","Low level","Reepmeyer","Feehery_Fv","Roffel_Fv","Klingberg","Wang_Fv","Elgue","","Murphree Efficiency","Energy Balance","Energy Holdup","Geometry Constraint","Level of clear liquid over the weir","Component Molar Balance","Molar Holdup","Mol fraction normalisation","Mol fraction constraint","Liquid Volume","Vapour Volume","Liquid Density","Vapour Density","Chemical Equilibrium","Thermal Equilibrium","Mechanical Equilibrium","Thermal Equilibrium Vapour Side Stream","Thermal Equilibrium Liquid Side Stream","Mechanical Equilibrium Vapour Side Stream","Mechanical Equilibrium Liquid Side Stream","Composition Liquid Side Stream","Composition Vapour Side Stream",
			],
			[:PP,:NComp,:Mw,:Gconst,:zero_flow,:low_flow,:Pi,:TrayDiameter_,:TraySpacing_,:Fraction_HoleArea_,:Fraction_DowncomerArea_,:WeirLength_,:WeirHeight_,:TrayLiquidPasses_,:HeatSupply_,:AerationFraction_,:DryPdropCoeff_,:MurphreeEff_,:PlateArea_,:TrayVolume_,:HolesArea_,:FeeheryCoeff,:ElgueCoeff,:OlsenCoeff,:VapourFlow,:LiquidFlow,],
			[:Inlet,:LiquidSideStream,:VapourSideStream,:InletLiquid,:InletVapour,:OutletLiquid,:OutletVapour,:LFlowModel,:VFlowModel,:M,:ML,:MV,:E,:vL,:vV,:Level,:yideal,:rhoL,:rhoV,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Mw::Array{molweight}
	Gconst::acceleration
	zero_flow::flow_mol
	low_flow::flow_mol
	Pi::constant
	TrayDiameter_::length
	TraySpacing_::length
	Fraction_HoleArea_::fraction
	Fraction_DowncomerArea_::fraction
	WeirLength_::length
	WeirHeight_::length
	TrayLiquidPasses_::positive
	HeatSupply_::heat_rate
	AerationFraction_::DanaReal
	DryPdropCoeff_::DanaReal
	MurphreeEff_::DanaReal
	PlateArea_::area
	TrayVolume_::volume
	HolesArea_::area
	FeeheryCoeff::DanaReal
	ElgueCoeff::DanaReal
	OlsenCoeff::DanaReal
	VapourFlow::DanaSwitcher
	LiquidFlow::DanaSwitcher
	Inlet::stream
	LiquidSideStream::liquid_stream
	VapourSideStream::vapour_stream
	InletLiquid::stream
	InletVapour::stream
	OutletLiquid::liquid_stream
	OutletVapour::vapour_stream
	LFlowModel::positive
	VFlowModel::positive
	M::Array{mol}
	ML::mol
	MV::mol
	E::energy
	vL::volume_mol
	vV::volume_mol
	Level::length
	yideal::Array{fraction}
	rhoL::dens_mass
	rhoV::dens_mass
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export tray
function set(in::tray)
	Mw = PP.MolecularWeight()
	 zero_flow = 0 * "kmol/h"
	 low_flow = 1E-6 * "kmol/h"
	 PlateArea_ = 0.25*Pi*(TrayDiameter_^2)*(1-Fraction_DowncomerArea_)
	 TrayVolume_ = 0.25*Pi*(TrayDiameter_^2)*TraySpacing_
	 HolesArea_ = 0.25*Pi*(TrayDiameter_^2)*Fraction_HoleArea_
	 
end
function setEquationFlow(in::tray)
	# LiquidFlow and VapourFlow equations need to be linerized to avoid indetermination !
	let switch=LiquidFlow
		if LiquidFlow==Level < (AerationFraction_ *WeirHeight_)
			set(switch,"off")
		end
		if LiquidFlow==Level > (AerationFraction_ * WeirHeight_)
			set(switch,"on")
		end
		if switch=="on"
			if LFlowModel == 1 
				addEquation(1)
			else
				if LFlowModel == 2 
					addEquation(2)
				else
					if LFlowModel == 3 
						addEquation(3)
					else
						if LFlowModel == 4 
							addEquation(4)
						else
							addEquation(5)
							#/'(kg/m)^0.0888545/s^0.177709';
							
						end
					end
				end
			end
		elseif switch=="off"
			addEquation(6)
		end
	end
	let switch=VapourFlow
		if VapourFlow==InletVapour.F < low_flow
			set(switch,"off")
		end
		if VapourFlow==InletVapour.P > OutletVapour.P
			set(switch,"on")
		end
		if switch=="on"
			if VFlowModel == 1 
				addEquation(7)
			else
				if VFlowModel == 2 
					addEquation(8)
				else
					if VFlowModel == 3 
						addEquation(9)
					else
						if VFlowModel == 4 
							addEquation(10)
						else
							if VFlowModel == 5 
								addEquation(11)
							else
								addEquation(12)
							end
						end
					end
				end
			end
		elseif switch=="off"
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
end
function atributes(in::tray,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Icon]="icon/Tray"
	fields[:Brief]="Complete model of a column tray."
	fields[:Info]="== Assumptions ==
* both phases (liquid and vapour) exists all the time;
* thermodymanic equilibrium with Murphree plate efficiency;
* no entrainment of liquid or vapour phase;
* no weeping;
* the dymanics in the downcomer are neglected.

== Options ==
You can choose the equation for the liquid outlet flow and the vapour
inlet flow calculation through the VapourFlowModel and LiquidFlowModel
switchers.

== References ==
* ELGUE, S.; PRAT, L.; CABASSUD, M.; LANN, J. L.; C虅ZERAC, J. Dynamic models for start-up operations of batch distillation columns with experimental validation. Computers and Chemical Engineering, v. 28, p. 2735-2747, 2004.
* FEEHERY, W. F. Dynamic Optimization with Path Constraints. Tese (Doutorado) - Massachusetts Institute of Technology, June 1998.
* KLINGBERG, A. Modeling and Optimization of Batch Distillation. Disserta袯⭠o (Mestrado) - Department of Automatic Control, Lund Institute of Technology, Lund, Sweden, fev. 2000.
* OLSEN, I.; ENDRESTOL, G. O.; SIRA, T. A rigorous and efficient distillation column model for engineering and training simulators. Computers and Chemical Engineering,v. 21, n. Suppl, p. S193-S198, 1997.
* REEPMEYER, F.; REPKE, J.-U.; WOZNY, G. Analysis of the start-up process for reactive distillation. Chemical Engineering Technology, v. 26, p. 81-86, 2003.
* ROFFEL, B.; BETLEM, B.; RUIJTER, J. de. First principles dynamic modeling and multivariable control of a cryogenic distillation column process. Computers and Chemical Engineering, v. 24, p. 111-123, 2000.
* WANG, L.; LI, P.; WOZNY, G.; WANG, S. A start-up model for simulation of batch distillation starting from a cold state. Computers and Chemical Engineering, v. 27, p.1485-1497, 2003.
"
	drive!(fields,_)
	return fields
end
tray(_::Dict{Symbol,Any})=begin
	newModel=tray()
	newModel.attributes=atributes(newModel,_)
	newModel
end
