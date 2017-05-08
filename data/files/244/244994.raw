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
#*---------------------------------------------------------------------
#* Author: Estefane Horn, N�bia do Carmo Ferreira
#*$Id$									
#*-------------------------------------------------------------------
#-------------------------------------------------------------------
#* Model of a valve (simplified)
#*-------------------------------------------------------------------- 
#*
#* Author: Paula B. Staudt
#*--------------------------------------------------------------------
type valve
	valve()=begin
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
			DanaSwitcher(Dict{Symbol,Any}(
				:Valid=>["linear", "parabolic", "equal", "quick", "hyperbolic"],
				:Default=>"linear"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Valid Phases for Flash Calculation",
				:Valid=>["Vapour-Only", "Liquid-Only"],
				:Default=>"Liquid-Only"
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Water Mass Density at 60 F",
				:Hidden=>true
			)),
			flow_mass(Dict{Symbol,Any}(
				:DisplayUnit=>"kg/s"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Drop",
				:DisplayUnit=>"kPa",
				:Symbol=>"\\Delta P"
			)),
			flow_vol(Dict{Symbol,Any}(
				:Brief=>"Volumetric Flow"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Opening Function",
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Valve Flow Coefficient",
				:Unit=>"gal/min/psi^0.5"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Valve Flow Coefficient",
				:Unit=>"m^2"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Valve Gas Flow Coefficient",
				:Unit=>"ft^3/h/psi"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Liquid-gas Coefficient Ratio",
				:Unit=>"(ft^3/gal)*(min/h)/(psi^.5)"
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Actual valve stem position"
			)),
			DanaReal(),
			vol_mol(Dict{Symbol,Any}(
				:Brief=>"Mixture Molar Volume"
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Mixture Mass Density"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0,
				:PosY=>0.7365,
				:Symbol=>"_{in}"
			)),
			streamPH(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>0.7365,
				:Symbol=>"_{out}"
			)),
			[
				:(Outlet.P = Inlet.P - Pdrop),
				:(Outlet.h = Inlet.h),
				:(Outlet.F = Inlet.F),
				:(Outlet.z = Inlet.z),
				:(Cv1=Cv*"1/(gal/min/psi^0.5)"*2.3837e-5*"m^2"),
				:(Fvol = fc*(Cv/sqrt(1/rho60F))*sqrt(Pdrop/rho)),
				:(C*Cv=Cg),
				:(a=1/(1.6764e-2*C*"1/((ft^3/gal)*(min/h)/(psi^.5))")*sqrt(Pdrop/Inlet.P)),
				:(Fvol = fc*(Cv/sqrt(1/rho60F))*sqrt(Pdrop/rho)),
				:(C*Cv=Cg),
				:(a=1/(1.6764e-2*C*"1/((ft^3/gal)*(min/h)/(psi^.5))")*sqrt(Pdrop/Inlet.P)),
				:(rho = PP.LiquidDensity(Inlet.T,Inlet.P,Inlet.z)),
				:(vm = PP.LiquidVolume(Inlet.T,Inlet.P,Inlet.z)),
				:(C*Cv=Cg),
				:(a=1/(1.6764e-2*C*"1/((ft^3/gal)*(min/h)/(psi^.5))")*sqrt(Pdrop/Inlet.P)),
				:(Fvol = fc*0.13446*"psi^.5"*Cg*sqrt(Inlet.P/1000*rho60F/rho)*sin(a*"rad")),
				:(Fvol = fc*0.13446*Cv*sqrt(Inlet.P*rho60F/rho)),
				:(Fvol = fc*(Cv/sqrt(1/rho60F))*sqrt(Pdrop/rho)),
				:(C*Cv=Cg),
				:(a=1/(1.6764e-2*C*"1/((ft^3/gal)*(min/h)/(psi^.5))")*sqrt(Pdrop/Inlet.P)),
				:(rho = PP.VapourDensity(Inlet.T,Inlet.P,Inlet.z)),
				:(vm = PP.VapourVolume(Inlet.T,Inlet.P,Inlet.z)),
				:(Fvol = Inlet.F*vm),
				:(W=Fvol*rho),
				:(fc = StemPosition),
				:(fc = StemPosition^2),
				:(fc = StemPosition^2/(2-StemPosition^4)^(1/2)),
				:(fc = 10*StemPosition/sqrt(1+99*StemPosition^2)),
				:(fc = 0.1*StemPosition/sqrt(1-0.99*StemPosition^2)),
			],
			[
				"Pressure Drop","Enthalpy Balance","Molar Balance","Outlet Composition","","Valve Equation - Liquid Flow","Liquid-gas Coefficient Ratio","","Valve Equation - Liquid Flow","Liquid-gas Coefficient Ratio","","Liquid Mass Density","Liquid Molar Volume","Liquid-gas Coefficient Ratio","","Valve Equation - Vapour Flow","Valve Equation - Vapour Flow","Valve Equation - Vapour Flow","Liquid-gas Coefficient Ratio","","Vapour Mass Density","Vapour Molar Volume","Calculate Mass Flow","","Opening Equation","Opening Equation","Opening Equation","Opening Equation","Opening Equation",
			],
			[:PP,:NComp,:ValveType,:ValidPhases,:rho60F,],
			[:W,:Pdrop,:Fvol,:fc,:Cv,:Cv1,:Cg,:C,:StemPosition,:a,:vm,:rho,:Inlet,:Outlet,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	ValveType::DanaSwitcher 
	ValidPhases::DanaSwitcher 
	rho60F::dens_mass 
	W::flow_mass
	Pdrop::press_delta 
	Fvol::flow_vol 
	fc::positive 
	Cv::DanaReal 
	Cv1::DanaReal 
	Cg::DanaReal 
	C::DanaReal 
	StemPosition::fraction 
	a::DanaReal
	vm::vol_mol 
	rho::dens_mass 
	Inlet::stream 
	Outlet::streamPH 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export valve
function set(in::valve)
	rho60F = 984.252 * "kg/m^3"
	 
end
function setEquationFlow(in::valve)
	#"First order valve dynamics"
	#	Tau*diff(StemPosition) = vsp-StemPosition;
	#"Flow Signal"
	#	vsp = vsignal;
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	let switch=ValidPhases
		#############################################################
		if switch=="Liquid-Only"
			if Pdrop > 0 * "atm" 
				addEquation(6)
				addEquation(7)
				addEquation(8)
			else
				addEquation(9)
				addEquation(10)
				addEquation(11)
			end
			addEquation(12)
			addEquation(13)
			############################################################
			
		elseif switch=="Vapour-Only"
			if Pdrop > 0 * "atm" 
				#Update for gas flow !!!!
				addEquation(14)
				addEquation(15)
				if 1.5708 > a 
					#Fvol = fc*Cg*sqrt(Inlet.P/1000*rho60F/rho);####rho60f/rho ok!!!!
					#Fvol = fc*Cv*sqrt(Pdrop/1000*rho60F/rho);
					#W = fc*Cv1*sqrt(Pdrop/1000*rho);
					addEquation(16)
				else
					addEquation(17)
				end
			else
				addEquation(18)
				addEquation(19)
				addEquation(20)
			end
			addEquation(21)
			#rho=3.708741*'kg/m^3';
			addEquation(22)
		end
	end
	######################################################
	addEquation(23)
	addEquation(24)
	let switch=ValveType
		#Update the valve Type
		if switch=="linear"
			addEquation(25)
		elseif switch=="parabolic"
			addEquation(26)
		elseif switch=="equal"
			addEquation(27)
		elseif switch=="quick"
			addEquation(28)
		elseif switch=="hyperbolic"
			addEquation(29)
		end
	end
end
function atributes(in::valve,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Valve"
	fields[:Brief]="Model of a valve."
	fields[:Info]="== Model of valves ==
* Linear;
* Parabolic;
* Equal;
* Quick;
* Hyperbolic.
	
== Assumptions ==
* First Order Dynamic;
* Only Liquid or Only Vapour;
* Isentalpic.
	
== Specify ==
* the valve type;
* the Valve Coefficient (Cv);
* the valve time constant (Tau).
"
	drive!(fields,_)
	return fields
end
valve(_::Dict{Symbol,Any})=begin
	newModel=valve()
	newModel.attributes=atributes(newModel,_)
	newModel
end
