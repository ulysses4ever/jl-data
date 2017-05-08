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
#*----------------------------------------------------------------------
#* Author: Paula B. Staudt
#* $Id$
#*--------------------------------------------------------------------
type flash_steady
	flash_steady()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(),
			stream (Dict{Symbol,Any}(
				:Brief=>"Feed Stream",
				:PosX=>0,
				:PosY=>0.48,
				:Symbol=>"_{in}"
			)),
			liquid_stream (Dict{Symbol,Any}(
				:Brief=>"Liquid outlet stream",
				:PosX=>0.43,
				:PosY=>1,
				:Symbol=>"_{out}^{Liquid}"
			)),
			vapour_stream (Dict{Symbol,Any}(
				:Brief=>"Vapour outlet stream",
				:PosX=>0.43,
				:PosY=>0,
				:Symbol=>"_{out}^{Vapour}"
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Heat Duty",
				:PosX=>1,
				:PosY=>0.81,
				:Protected=>true,
				:Symbol=>"Q_{in}"
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Vaporization fraction",
				:Symbol=>"\\phi",
				:Protected=>true
			)),
			enth_mol (Dict{Symbol,Any}(
				:Brief=>"Mixture enthalpy",
				:Hidden=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Pressure Ratio",
				:Symbol=>"P_{ratio}",
				:Protected=>true
			)),
			press_delta (Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P",
				:Protected=>true
			)),
			[
				:([vfrac, OutletLiquid.z, OutletVapour.z] = PP.Flash(OutletVapour.T, OutletVapour.P, Inlet.z)),
				:([vfrac,OutletLiquid.z,OutletVapour.z]=PP.FlashPH(OutletLiquid.P,h,Inlet.z)),
				:(Inlet.F = OutletVapour.F + OutletLiquid.F),
				:(OutletVapour.F = Inlet.F * vfrac),
				:(Inlet.F*(h - Inlet.h) = InletQ),
				:(Inlet.F*h = Inlet.F*(1-vfrac)*OutletLiquid.h + Inlet.F*vfrac*OutletVapour.h),
				:(OutletVapour.T = OutletLiquid.T),
				:(OutletVapour.P = OutletLiquid.P),
				:(OutletLiquid.P = Inlet.P - Pdrop),
				:(OutletLiquid.P = Inlet.P * Pratio),
			],
			[
				"The flash calculation","Chemical equilibrium","Global Molar Balance","Vapour Fraction","Energy Balance","","Thermal Equilibrium","Mechanical Equilibrium","Pressure Drop","Pressure Ratio",
			],
			[:PP,:NComp,],
			[:Inlet,:OutletLiquid,:OutletVapour,:InletQ,:vfrac,:h,:Pratio,:Pdrop,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Inlet::stream 
	OutletLiquid::liquid_stream 
	OutletVapour::vapour_stream 
	InletQ::power 
	vfrac::fraction 
	h::enth_mol 
	Pratio::positive 
	Pdrop::press_delta 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export flash_steady
function setEquationFlow(in::flash_steady)
	if vfrac > 0 && vfrac <1 
		addEquation(1)
	else
		addEquation(2)
	end
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
	addEquation(9)
	addEquation(10)
end
function atributes(in::flash_steady,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Flash"
	fields[:Brief]="Model of a static PH flash."
	fields[:Info]="This model is for using the flashPH routine available on VRTherm.

== ASSUMPTIONS ==
* perfect mixing of both phases;
* thermodynamics equilibrium.
* static model.

== SPECIFY ==
* The Inlet stream;
* The heat duty;
* The outlet pressure.
"
	drive!(fields,_)
	return fields
end
flash_steady(_::Dict{Symbol,Any})=begin
	newModel=flash_steady()
	newModel.attributes=atributes(newModel,_)
	newModel
end
