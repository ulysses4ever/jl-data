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
#* $Id: condenser.mso 555 2008-07-18 19:01:13Z rafael $
#*--------------------------------------------------------------------
type condenser2
	condenser2()=begin
		PP=outers.PP
		NComp=outers.NComp
		[
			:(LI = Levelpercent_Initial),
			:(OutletLiquid.T = Initial_Temperature),
			:(OutletLiquid.z(1:NComp-1) = Initial_Composition(1:NComp-1)/sum(Initial_Composition)),
		],
		[
			"Initial level Percent","Initial Temperature","Initial Composition",
		],
		new(
			DanaPlugin (Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of Components"
			)),
			fill(molweight (Dict{Symbol,Any}(
				:Brief=>"Component Mol Weight",
				:Hidden=>true
			)),(NComp)),
			flow_mol (Dict{Symbol,Any}(
				:Brief=>"Low Flow",
				:Default=>1E-6,
				:Hidden=>true
			)),
			flow_mol (Dict{Symbol,Any}(
				:Brief=>"No Flow",
				:Default=>0,
				:Hidden=>true
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Condenser type",
				:Valid=>["partial", "total"],
				:Default=>"partial"
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Vapour Flow",
				:Valid=>["on", "off"],
				:Default=>"on",
				:Hidden=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"K factor for pressure drop",
				:Lower=>1E-8,
				:Default=>1E-3
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Initial liquid height in Percent",
				:Default=>0.70
			)),
			temperature (Dict{Symbol,Any}(
				:Brief=>"Initial Temperature of Condenser"
			)),
			fill(positive (Dict{Symbol,Any}(
				:Brief=>"Initial Liquid Composition",
				:Lower=>1E-6
			)),(NComp)),
			VesselVolume (Dict{Symbol,Any}(
				:Brief=>"Vessel Geometry",
				:Symbol=>" "
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Vapour inlet stream",
				:PosX=>0.13,
				:PosY=>0,
				:Symbol=>"_{in}^{Vapour}"
			)),
			liquid_stream (Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.35,
				:PosY=>1,
				:Symbol=>"_{out}^{Liquid}"
			)),
			vapour_stream (Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:Hidden=>true,
				:Symbol=>"_{out}^{Vapour}"
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Vapour or Liquid product stream",
				:PosX=>0.54,
				:PosY=>0,
				:Symbol=>"_{out}^{Vapour}"
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Heat supplied",
				:Protected=>true,
				:PosX=>1,
				:PosY=>0.08,
				:Symbol=>"Q_{in}"
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Reflux Ratio",
				:Default=>10,
				:Lower=>0.05
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Temperature  Indicator of Condenser",
				:Protected=>true,
				:PosX=>0.33,
				:PosY=>0
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Level  Indicator of Condenser",
				:Protected=>true,
				:PosX=>0.43,
				:PosY=>0
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Pressure  Indicator of Condenser",
				:Protected=>true,
				:PosX=>0.25,
				:PosY=>0
			)),
			fill(mol (Dict{Symbol,Any}(
				:Brief=>"Molar Holdup in the tray",
				:Protected=>true
			)),(NComp)),
			mol (Dict{Symbol,Any}(
				:Brief=>"Molar liquid holdup",
				:Protected=>true
			)),
			mol (Dict{Symbol,Any}(
				:Brief=>"Molar vapour holdup",
				:Protected=>true
			)),
			energy (Dict{Symbol,Any}(
				:Brief=>"Total Energy Holdup on tray",
				:Protected=>true
			)),
			volume_mol (Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Volume",
				:Protected=>true
			)),
			volume_mol (Dict{Symbol,Any}(
				:Brief=>"Vapour Molar volume",
				:Protected=>true
			)),
			dens_mass (Dict{Symbol,Any}(
				:Brief=>"Inlet Vapour Mass Density",
				:Hidden=>true,
				:Symbol=>"\\rho"
			)),
			press_delta (Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P",
				:Protected=>true
			)),
			[
				:(Vapour.F = zero_flow),
				:(RefluxRatio*Product.F = OutletLiquid.F),
				:(Product.v = Vapour.v),
				:(Product.h = Vapour.h),
				:(Product.z = Vapour.z),
				:(Product.v = OutletLiquid.v),
				:(Product.h = OutletLiquid.h),
				:(Product.z = OutletLiquid.z),
				:(InletVapour.F*vV = Kfactor *sqrt(Pdrop/rho)*"m^2"),
				:(InletVapour.F = zero_flow),
				:(diff(M) = InletVapour.F*InletVapour.z - OutletLiquid.F*OutletLiquid.z- Product.F*Product.z),
				:(diff(E) = InletVapour.F*InletVapour.h - OutletLiquid.F*OutletLiquid.h- Product.F*Product.h + InletQ),
				:(M = ML*OutletLiquid.z + MV*Vapour.z),
				:(E = ML*OutletLiquid.h + MV*Vapour.h - Vapour.P*Geometry.Vtotal),
				:(sum(OutletLiquid.z)=1.0),
				:(sum(OutletLiquid.z)=sum(Vapour.z)),
				:(vL = PP.LiquidVolume(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)),
				:(vV = PP.VapourVolume(Vapour.T, Vapour.P, Vapour.z)),
				:(rho = PP.VapourDensity(InletVapour.T, InletVapour.P, InletVapour.z)),
				:(PP.LiquidFugacityCoefficient(OutletLiquid.T, OutletLiquid.P, OutletLiquid.z)*OutletLiquid.z = PP.VapourFugacityCoefficient(Vapour.T, Vapour.P, Vapour.z)*Vapour.z),
				:(OutletLiquid.T = Vapour.T),
				:(OutletLiquid.T = Product.T),
				:(Vapour.P = OutletLiquid.P),
				:(Vapour.P = Product.P),
				:(OutletLiquid.P = InletVapour.P - Pdrop),
				:(Geometry.Vtotal = ML*vL + MV*vV),
				:(ML * vL = Geometry.Vfilled),
				:(TI * "K" = OutletLiquid.T),
				:(PI * "atm" = OutletLiquid.P),
				:(LI*Geometry.Vtotal= Geometry.Vfilled),
			],
			[
				"","Reflux ratio","","","","","","","","","Component Molar Balance","Energy Balance","Molar Holdup","Energy Holdup","Mol fraction normalisation","Mol fraction Constraint","Liquid Volume","Vapour Volume","Inlet Vapour Density","Chemical Equilibrium","Thermal Equilibrium","","Mechanical Equilibrium","","Pressure Drop","Geometry Constraint","Liquid Level","Temperature indicator","Pressure indicator","Level indicator",
			],
			[:PP,:NComp,:Mw,:low_flow,:zero_flow,:CondenserType,:VapourFlow,:Kfactor,:Levelpercent_Initial,:Initial_Temperature,:Initial_Composition,],
			[:Geometry,:InletVapour,:OutletLiquid,:Vapour,:Product,:InletQ,:RefluxRatio,:TI,:LI,:PI,:M,:ML,:MV,:E,:vL,:vV,:rho,:Pdrop,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	Mw::Array{molweight }
	low_flow::flow_mol 
	zero_flow::flow_mol 
	CondenserType::DanaSwitcher 
	VapourFlow::DanaSwitcher 
	Kfactor::positive 
	Levelpercent_Initial::positive 
	Initial_Temperature::temperature 
	Initial_Composition::Array{positive }
	Geometry::VesselVolume 
	InletVapour::stream 
	OutletLiquid::liquid_stream 
	Vapour::vapour_stream 
	Product::stream 
	InletQ::power 
	RefluxRatio::positive 
	TI::control_signal 
	LI::control_signal 
	PI::control_signal 
	M::Array{mol }
	ML::mol 
	MV::mol 
	E::energy 
	vL::volume_mol 
	vV::volume_mol 
	rho::dens_mass 
	Pdrop::press_delta 
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export condenser2
function set(in::condenser2)
	Mw = PP.MolecularWeight()
	 low_flow = 1E-6 * "kmol/h"
	 zero_flow = 0 * "kmol/h"
	 
end
function initial(in::condenser2)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function setEquationFlow(in::condenser2)
	addEquation(1)
	addEquation(2)
	let switch=CondenserType
		if switch=="partial"
			addEquation(3)
			addEquation(4)
			addEquation(5)
		elseif switch=="total"
			addEquation(6)
			addEquation(7)
			addEquation(8)
		end
	end
	let switch=VapourFlow
		if VapourFlow==InletVapour.F < low_flow
			set(switch,"off")
		end
		if VapourFlow==InletVapour.P > OutletLiquid.P
			set(switch,"on")
		end
		if switch=="on"
			addEquation(9)
		elseif switch=="off"
			addEquation(10)
		end
	end
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
end
function atributes(in::condenser2,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Condenser"
	fields[:Brief]="Model of a  dynamic condenser with control."
	fields[:Info]="== ASSUMPTIONS ==
* perfect mixing of both phases;
* thermodynamics equilibrium.
	
== SPECIFY ==
* the InletVapour stream;
* the outlet flows: Product.F and Reflux.F;
* the InletQ (the model requires an energy stream, also you can use a controller for setting the heat duty using the heat_flow model).

== OPTIONAL ==
* the condenser model has three control ports
** TI OutletLiquid Temperature Indicator;
** PI OutletLiquid Pressure Indicator;
** LI Level Indicator of Condenser;

== INITIAL CONDITIONS ==
* Initial_Temperature :  the condenser temperature (OutletLiquid.T);
* Levelpercent_Initial : the condenser liquid level in percent (LI);
* Initial_Composition : (NoComps) OutletLiquid compositions.
"
	drive!(fields,_)
	return fields
end
condenser2(_::Dict{Symbol,Any})=begin
	newModel=condenser2()
	newModel.attributes=atributes(newModel,_)
	newModel
end
