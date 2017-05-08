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
#* Author: Marcos L. Alencastro,  Estefane S. Horn (Revised Gerson B. Bicca)
#* $Id: expander.mso 687 2008-11-20 19:42:33Z bicca $
#*--------------------------------------------------------------------
type expander
	expander()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of chemical components",
				:Lower=>1
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Constant of Gases",
				:Unit=>"kJ/kmol/K",
				:Default=>8.31451,
				:Hidden=>true
			)),
			fill(molweight(Dict{Symbol,Any}(
				:Brief=>"Molar Weight",
				:Hidden=>true
			)),(NComp)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Mechanical efficiency",
				:Lower=>1E-3
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Isentropic efficiency",
				:Lower=>1E-3
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Pressure Ratio",
				:Lower=>1E-6,
				:Symbol=>"P_{ratio}"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Decrease",
				:DisplayUnit=>"kPa",
				:Symbol=>"P_{incr}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Power Losses",
				:Lower=>0
			)),
			energy_mass(Dict{Symbol,Any}(
				:Brief=>"Actual Head",
				:Protected=>true
			)),
			energy_mass(Dict{Symbol,Any}(
				:Brief=>"Isentropic Head",
				:Protected=>true
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Fluid Power",
				:Protected=>true
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Brake Power",
				:Protected=>true
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Isentropic Coefficient",
				:Lower=>0.2,
				:Protected=>true
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Isentropic Temperature",
				:Protected=>true
			)),
			enth_mol(Dict{Symbol,Any}(
				:Brief=>"Enthalpy at constant entropy",
				:Hidden=>true
			)),
			molweight(Dict{Symbol,Any}(
				:Brief=>"Mixture Molar Weight",
				:Hidden=>true
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Mass Density at inlet conditions",
				:Lower=>1E-6,
				:Protected=>true
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Mass Density at outlet conditions",
				:Lower=>1E-6,
				:Protected=>true
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Compressibility factor at inlet",
				:Lower=>1E-3,
				:Protected=>true
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Compressibility factor at outlet",
				:Lower=>1E-3,
				:Protected=>true
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0.14,
				:PosY=>0.0,
				:Symbol=>"_{in}"
			)),
			streamPH(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>0.83,
				:PosY=>1,
				:Symbol=>"_{out}"
			)),
			power(Dict{Symbol,Any}(
				:Brief=>"Work Outlet",
				:PosX=>1,
				:PosY=>0.45,
				:Protected=>true
			)),
			[
				:(Outlet.F = Inlet.F),
				:(Outlet.z = Inlet.z),
				:(Mwm = sum(Mw*Inlet.z)),
				:(Outlet.P = Inlet.P * Pratio),
				:(Outlet.P = Inlet.P - Pdrop),
				:(Outlet.P = Inlet.P - Pdecrease),
				:(rho_in = PP.VapourDensity(Inlet.T, Inlet.P, Inlet.z)),
				:(rho_out= PP.VapourDensity(Outlet.T, Outlet.P, Outlet.z)),
				:(hise = PP.VapourEnthalpy(Tisentropic, Outlet.P, Outlet.z)),
				:(Zfac_in = PP.VapourCompressibilityFactor(Inlet.T,Inlet.P,Inlet.z)),
				:(Zfac_out = PP.VapourCompressibilityFactor(Outlet.T,Outlet.P,Outlet.z)),
				:(Head*Mwm = (Outlet.h-Inlet.h)),
				:(Outlet.T = Tisentropic),
				:((Outlet.h-Inlet.h)= (hise-Inlet.h)*IsentropicEff),
				:(PP.VapourEntropy(Tisentropic, Outlet.P, Outlet.z) = PP.VapourEntropy(Inlet.T, Inlet.P, Inlet.z)),
				:(BrakePower = WorkOut),
				:(BrakePower = FluidPower*MechanicalEff),
				:(PowerLoss = BrakePower - FluidPower),
				:(FluidPower = HeadIsentropic*Mwm*Inlet.F*IsentropicEff),
				:(HeadIsentropic*Mwm*((IseCoeff-1.001)/IseCoeff) = (0.5*Zfac_in+0.5*Zfac_out)*Rgas*Inlet.T*((Pratio)^((IseCoeff-1.001)/IseCoeff) - 1)),
				:(HeadIsentropic*Mwm = (hise -Inlet.h)),
			],
			[
				"Overall Molar Balance","Component Molar Balance","Average Molecular Weight","Pressure Ratio","Pressure Drop","Pressure Decrease","Mass Density at inlet conditions","Mass Density at outlet conditions","Enthalpy at isentropic conditions","Compressibility factor at Inlet Conditions","Compressibility factor at Outlet Conditions","Actual Head","Discharge Temperature","Discharge Temperature","Isentropic Outlet Temperature","Brake Power","Brake Power","Power Loss","Fluid Power","Isentropic Coefficient","Isentropic Head",
			],
			[:PP,:NComp,:Rgas,:Mw,:MechanicalEff,:IsentropicEff,],
			[:Pratio,:Pdrop,:Pdecrease,:PowerLoss,:Head,:HeadIsentropic,:FluidPower,:BrakePower,:IseCoeff,:Tisentropic,:hise,:Mwm,:rho_in,:rho_out,:Zfac_in,:Zfac_out,:Inlet,:Outlet,:WorkOut,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	Rgas::positive
	Mw::Array{molweight}
	MechanicalEff::positive
	IsentropicEff::positive
	Pratio::positive
	Pdrop::press_delta
	Pdecrease::press_delta
	PowerLoss::power
	Head::energy_mass
	HeadIsentropic::energy_mass
	FluidPower::power
	BrakePower::power
	IseCoeff::positive
	Tisentropic::temperature
	hise::enth_mol
	Mwm::molweight
	rho_in::dens_mass
	rho_out::dens_mass
	Zfac_in::fraction
	Zfac_out::fraction
	Inlet::stream
	Outlet::streamPH
	WorkOut::power
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export expander
function set(in::expander)
	Mw = PP.MolecularWeight()
	 Rgas = 8.31451*"kJ/kmol/K"
	 
end
function setEquationFlow(in::expander)
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
	if IsentropicEff >= 1 
		addEquation(13)
	else
		addEquation(14)
	end
	addEquation(15)
	addEquation(16)
	addEquation(17)
	addEquation(18)
	addEquation(19)
	addEquation(20)
	addEquation(21)
end
function atributes(in::expander,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/expander"
	fields[:Brief]="Model of an expander."
	fields[:Info]="To be documented

== References ==

[1] GPSA, 1979, Engineering Data Book, Chapter 4, 5-9 - 5-10.

[2] Bloch, Heinz P., A Practical Guide to Compressor Technology, John Wiley & Sons, Incorporate, 2006."
	drive!(fields,_)
	return fields
end
expander(_::Dict{Symbol,Any})=begin
	newModel=expander()
	newModel.attributes=atributes(newModel,_)
	newModel
end
