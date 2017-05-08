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
#* $Id$
#*--------------------------------------------------------------------
type centrifugal_compressor
	centrifugal_compressor()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin (Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of chemical components",
				:Lower=>1
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Constant of Gases",
				:Unit=>"kJ/kmol/K",
				:Default=>8.31451,
				:Hidden=>true
			)),
			fill(molweight (Dict{Symbol,Any}(
				:Brief=>"Molar Weight",
				:Hidden=>true
			)),(NComp)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Compressor Operation Model",
				:Valid=>["Polytropic","Isentropic"],
				:Default=>"Isentropic"
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Method of Calculation",
				:Valid=>["GPSA Method","ASME Method"],
				:Default=>"GPSA Method"
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Pressure Ratio",
				:Lower=>1E-6,
				:Symbol=>"P_{ratio}"
			)),
			press_delta (Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P"
			)),
			press_delta (Dict{Symbol,Any}(
				:Brief=>"Pressure Increase",
				:Lower=>0,
				:DisplayUnit=>"kPa",
				:Symbol=>"P_{incr}"
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Compressor efficiency - Polytropic or Isentropic (See Compressor Type)",
				:Lower=>1E-3,
				:Upper=>1
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Mechanical efficiency",
				:Lower=>1E-3,
				:Upper=>1
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Power Losses"
			)),
			energy_mass (Dict{Symbol,Any}(
				:Brief=>"Actual Head",
				:Protected=>true
			)),
			energy_mass (Dict{Symbol,Any}(
				:Brief=>"Isentropic Head",
				:Protected=>true
			)),
			energy_mass (Dict{Symbol,Any}(
				:Brief=>"Polytropic Head",
				:Protected=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Schultz Polytropic Head Correction",
				:Protected=>true
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Fluid Power",
				:Protected=>true
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Brake Power",
				:Protected=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Polytropic Coefficient",
				:Lower=>0.2,
				:Protected=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Isentropic Coefficient",
				:Lower=>0.2,
				:Protected=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Polytropic efficiency",
				:Lower=>1E-3,
				:Upper=>1,
				:Protected=>true
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Isentropic efficiency",
				:Lower=>1E-3,
				:Upper=>1,
				:Protected=>true
			)),
			temperature (Dict{Symbol,Any}(
				:Brief=>"Isentropic Temperature",
				:Protected=>true
			)),
			enth_mol (Dict{Symbol,Any}(
				:Brief=>"Enthalpy at constant entropy",
				:Hidden=>true
			)),
			molweight (Dict{Symbol,Any}(
				:Brief=>"Mixture Molar Weight",
				:Hidden=>true
			)),
			dens_mass (Dict{Symbol,Any}(
				:Brief=>"Mass Density at inlet conditions",
				:Lower=>1E-6,
				:Protected=>true
			)),
			dens_mass (Dict{Symbol,Any}(
				:Brief=>"Mass Density at outlet conditions",
				:Lower=>1E-6,
				:Protected=>true
			)),
			dens_mass (Dict{Symbol,Any}(
				:Brief=>"Mass Density at isentropic conditions",
				:Lower=>1E-6,
				:Hidden=>true
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Compressibility factor at inlet",
				:Lower=>1E-3,
				:Protected=>true
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Compressibility factor at outlet",
				:Lower=>1E-3,
				:Protected=>true
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0.16,
				:PosY=>1,
				:Symbol=>"_{in}"
			)),
			streamPH (Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>0.87,
				:PosY=>0.0,
				:Symbol=>"_{out}"
			)),
			power (Dict{Symbol,Any}(
				:Brief=>"Work Inlet",
				:PosX=>0,
				:PosY=>0.45,
				:Protected=>true
			)),
			[
				:(Outlet.F = Inlet.F),
				:(Outlet.z = Inlet.z),
				:(Mwm = sum(Mw*Inlet.z)),
				:(Outlet.P = Inlet.P * Pratio),
				:(Outlet.P = Inlet.P - Pdrop),
				:(Outlet.P = Inlet.P + Pincrease),
				:(rho_in = PP.VapourDensity(Inlet.T, Inlet.P, Inlet.z)),
				:(rho_out= PP.VapourDensity(Outlet.T, Outlet.P, Outlet.z)),
				:(rho_ise= PP.VapourDensity(Tisentropic, Outlet.P, Outlet.z)),
				:(hise = PP.VapourEnthalpy(Tisentropic, Outlet.P, Outlet.z)),
				:(Zfac_in = PP.VapourCompressibilityFactor(Inlet.T,Inlet.P,Inlet.z)),
				:(Zfac_out = PP.VapourCompressibilityFactor(Outlet.T,Outlet.P,Outlet.z)),
				:(IsentropicEff*(Outlet.h-Inlet.h) = (hise-Inlet.h)),
				:(Head*Mwm = (Outlet.h-Inlet.h)),
				:(PP.VapourEntropy(Tisentropic, Outlet.P, Outlet.z) = PP.VapourEntropy(Inlet.T, Inlet.P, Inlet.z)),
				:(BrakePower = -WorkIn),
				:(BrakePower*MechanicalEff = FluidPower),
				:(PowerLoss = BrakePower - FluidPower),
				:(PolytropicEff*HeadIsentropic = HeadPolytropic*IsentropicEff),
				:(FluidPower = Head*Mwm*Inlet.F),
				:(EfficiencyOperation = IsentropicEff),
				:(IseCoeff*ln(rho_ise/rho_in) = ln(Outlet.P/Inlet.P)),
				:(PolyCoeff*ln(rho_out/rho_in) = ln(Outlet.P/Inlet.P)),
				:(HeadIsentropic*rho_in = (IseCoeff/(IseCoeff-1.001))*Inlet.P*HeadCorrection*((Pratio)^((IseCoeff-1.001)/IseCoeff) - 1)),
				:(HeadPolytropic*rho_in = (PolyCoeff/(PolyCoeff-1.001))*Inlet.P*HeadCorrection*((Pratio)^((PolyCoeff-1.001)/PolyCoeff) - 1)),
				:(HeadCorrection*Mwm*(IseCoeff/(IseCoeff-1.001))*(Outlet.P/rho_ise -Inlet.P/rho_in) = (hise-Inlet.h)),
				:(EfficiencyOperation = IsentropicEff),
				:(PolytropicEff*IseCoeff*(PolyCoeff-1) = PolyCoeff*(IseCoeff-1)),
				:(HeadIsentropic*Mwm*((IseCoeff-1.001)/IseCoeff) = (0.5*Zfac_in+0.5*Zfac_out)*Rgas*Inlet.T*((Pratio)^((IseCoeff-1.001)/IseCoeff) - 1)),
				:(HeadPolytropic*Mwm*((PolyCoeff-1.001)/PolyCoeff) = (0.5*Zfac_in+0.5*Zfac_out)*Rgas*Inlet.T*((Pratio)^((PolyCoeff-1.001)/PolyCoeff) - 1)),
				:(HeadCorrection =1),
				:(HeadIsentropic = Head*IsentropicEff),
				:(EfficiencyOperation = PolytropicEff),
				:(PolytropicEff*IseCoeff*(PolyCoeff-1) = PolyCoeff*(IseCoeff-1)),
				:(HeadIsentropic*Mwm*((IseCoeff-1.001)/IseCoeff) = (0.5*Zfac_in+0.5*Zfac_out)*Rgas*Inlet.T*((Pratio)^((IseCoeff-1.001)/IseCoeff) - 1)),
				:(HeadPolytropic*Mwm*((PolyCoeff-1.001)/PolyCoeff) = (0.5*Zfac_in+0.5*Zfac_out)*Rgas*Inlet.T*((Pratio)^((PolyCoeff-1.001)/PolyCoeff) - 1)),
				:(HeadCorrection =1),
				:(HeadIsentropic = Head*IsentropicEff),
				:(EfficiencyOperation = PolytropicEff),
				:(IseCoeff*ln(rho_ise/rho_in) = ln(Outlet.P/Inlet.P)),
				:(PolyCoeff*ln(rho_out/rho_in) = ln(Outlet.P/Inlet.P)),
				:(HeadIsentropic*rho_in = (IseCoeff/(IseCoeff-1.001))*Inlet.P*HeadCorrection*((Pratio)^((IseCoeff-1.001)/IseCoeff) - 1)),
				:(HeadPolytropic*rho_in = (PolyCoeff/(PolyCoeff-1.001))*Inlet.P*HeadCorrection*((Pratio)^((PolyCoeff-1.001)/PolyCoeff) - 1)),
				:(HeadCorrection*Mwm*(IseCoeff/(IseCoeff-1.001))*(Outlet.P/rho_ise -Inlet.P/rho_in) = (hise-Inlet.h)),
			],
			[
				"Overall Molar Balance","Component Molar Balance","Average Molecular Weight","Pressure Ratio","Pressure Drop","Pressure Increase","Mass Density at inlet conditions","Mass Density at outlet conditions","Mass Density at isentropic conditions","Enthalpy at isentropic conditions","Compressibility factor at Inlet Conditions","Compressibility factor at Outlet Conditions","Isentropic Efficiency","Actual Head","Isentropic Outlet Temperature","Brake Power","Brake Power","Power Loss","Polytropic-Isentropic Relation","Fluid Power","Efficiency","Isentropic Coefficient","Polytropic Coefficient","Isentropic Head","Polytropic Head","Schultz Polytropic Head Correction","Efficiency","Polytropic Efficiency","Isentropic Coefficient","Polytropic Coefficient","Head Correction","Isentropic Head","Efficiency","Polytropic Efficiency","Isentropic Coefficient","Polytropic Coefficient","Head Correction","Isentropic Head","Efficiency","Isentropic Coefficient","Polytropic Coefficient","Isentropic Head","Polytropic Head","Schultz Polytropic Head Correction",
			],
			[:PP,:NComp,:Rgas,:Mw,:CompressorOperation,:Method,],
			[:Pratio,:Pdrop,:Pincrease,:EfficiencyOperation,:MechanicalEff,:PowerLoss,:Head,:HeadIsentropic,:HeadPolytropic,:HeadCorrection,:FluidPower,:BrakePower,:PolyCoeff,:IseCoeff,:PolytropicEff,:IsentropicEff,:Tisentropic,:hise,:Mwm,:rho_in,:rho_out,:rho_ise,:Zfac_in,:Zfac_out,:Inlet,:Outlet,:WorkIn,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	Rgas::positive 
	Mw::Array{molweight }
	CompressorOperation::DanaSwitcher 
	Method::DanaSwitcher 
	Pratio::positive 
	Pdrop::press_delta 
	Pincrease::press_delta 
	EfficiencyOperation::positive 
	MechanicalEff::positive 
	PowerLoss::power 
	Head::energy_mass 
	HeadIsentropic::energy_mass 
	HeadPolytropic::energy_mass 
	HeadCorrection::positive 
	FluidPower::power 
	BrakePower::power 
	PolyCoeff::positive 
	IseCoeff::positive 
	PolytropicEff::positive 
	IsentropicEff::positive 
	Tisentropic::temperature 
	hise::enth_mol 
	Mwm::molweight 
	rho_in::dens_mass 
	rho_out::dens_mass 
	rho_ise::dens_mass 
	Zfac_in::fraction 
	Zfac_out::fraction 
	Inlet::stream 
	Outlet::streamPH 
	WorkIn::power 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export centrifugal_compressor
function set(in::centrifugal_compressor)
	Mw = PP.MolecularWeight()
	 Rgas = 8.31451*"kJ/kmol/K"
	 
end
function setEquationFlow(in::centrifugal_compressor)
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
	let switch=CompressorOperation
		if switch=="Isentropic"
			let switch=Method
				if switch=="ASME Method"
					addEquation(21)
					addEquation(22)
					addEquation(23)
					addEquation(24)
					addEquation(25)
					addEquation(26)
				elseif switch=="GPSA Method"
					addEquation(27)
					addEquation(28)
					addEquation(29)
					addEquation(30)
					addEquation(31)
					addEquation(32)
				end
			end
		elseif switch=="Polytropic"
			let switch=Method
				if switch=="GPSA Method"
					addEquation(33)
					addEquation(34)
					addEquation(35)
					addEquation(36)
					addEquation(37)
					addEquation(38)
				elseif switch=="ASME Method"
					addEquation(39)
					addEquation(40)
					addEquation(41)
					addEquation(42)
					addEquation(43)
					addEquation(44)
				end
			end
		end
	end
end
function atributes(in::centrifugal_compressor,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/CentrifugalCompressor"
	fields[:Brief]="Model of a centrifugal compressor."
	fields[:Info]="To be documented

== References ==

[1] GPSA, 1979, Engineering Data Book, Chapter 4, 5-9 - 5-10.

[2] Bloch, Heinz P., A Practical Guide to Compressor Technology, John Wiley & Sons, Incorporate, 2006. 

[3] Mark R. Sandberg, Equation Of State Influences On Compressor Performance Determination,PROCEEDINGS OF THE THIRTY-FOURTH TURBOMACHINERY SYMPOSIUM, 2005."
	drive!(fields,_)
	return fields
end
centrifugal_compressor(_::Dict{Symbol,Any})=begin
	newModel=centrifugal_compressor()
	newModel.attributes=atributes(newModel,_)
	newModel
end
