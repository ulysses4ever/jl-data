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
#*--------------------------------------------------------------------
#* Model of basic streams
#*----------------------------------------------------------------------
#* Author: Paula B. Staudt and Rafael de P. Soares
#* $Id$
#*---------------------------------------------------------------------
type source2
	source2()=begin
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
			fill(molweight(Dict{Symbol,Any}(
				:Brief=>"Component Mol Weight",
				:Protected=>true
			)),(NComp)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Valid Phases for Flash Calculation",
				:Valid=>["Vapour-Only", "Liquid-Only","Vapour-Liquid"],
				:Default=>"Vapour-Liquid"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Molar or Mass Composition",
				:Valid=>["Molar", "Mass"],
				:Default=>"Molar"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>0,
				:PosY=>0.5256,
				:Symbol=>"_{out}",
				:Protected=>true
			)),
			fill(positive(Dict{Symbol,Any}(
				:Brief=>"Stream Composition"
			)),(NComp)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Sum of Stream Composition",
				:Protected=>true
			)),
			flow_mol(Dict{Symbol,Any}(
				:Brief=>"Stream Molar Flow Rate"
			)),
			flow_mass(Dict{Symbol,Any}(
				:Brief=>"Stream Mass Flow"
			)),
			flow_vol(Dict{Symbol,Any}(
				:Brief=>"Volumetric Flow"
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Stream Temperature"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Temperature in  C",
				:Lower=>-250,
				:Upper=>5000
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Stream Pressure"
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Vapour Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			molweight(Dict{Symbol,Any}(
				:Brief=>"Average Mol Weight",
				:Protected=>true
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Molar Volume",
				:Protected=>true
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Stream Mass Density",
				:Protected=>true
			)),
			dens_mol(Dict{Symbol,Any}(
				:Brief=>"Stream Molar Density",
				:Protected=>true
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Mass Fraction",
				:Protected=>true
			)),(NComp)),
			[
				:(Outlet.z = Composition/sum(Composition)),
				:(zmass = M*Outlet.z / Mw),
				:(zmass = Composition/sum(Composition)),
				:(Outlet.z*sum(zmass/M) = zmass/M),
				:(Outlet.v = 0),
				:(x = Outlet.z),
				:(y = Outlet.z),
				:(Outlet.h = PP.LiquidEnthalpy(Outlet.T, Outlet.P, x)),
				:(vm = PP.LiquidVolume(Outlet.T, Outlet.P, x)),
				:(Outlet.v = 1),
				:(x = Outlet.z),
				:(y = Outlet.z),
				:(Outlet.h = PP.VapourEnthalpy(Outlet.T, Outlet.P, y)),
				:(vm = PP.VapourVolume(Outlet.T, Outlet.P, y)),
				:([Outlet.v, x, y] = PP.Flash(Outlet.T, Outlet.P, Outlet.z)),
				:(Outlet.h = (1-Outlet.v)*PP.LiquidEnthalpy(Outlet.T, Outlet.P, x) + Outlet.v*PP.VapourEnthalpy(Outlet.T, Outlet.P, y)),
				:(vm = (1-Outlet.v)*PP.LiquidVolume(Outlet.T, Outlet.P, x) + Outlet.v*PP.VapourVolume(Outlet.T,Outlet.P,y)),
				:(SumOfComposition = sum(Composition)),
				:(rhom * vm = 1),
				:(Mw = sum(M*Outlet.z)),
				:(rhom * Mw = rho),
				:(Fw = Mw*Outlet.F),
				:(Fvol = Outlet.F*vm),
				:(T_Cdeg = Outlet.T/"K" - 273.15),
				:(Outlet.F = F),
				:(Outlet.P = P),
				:(Outlet.T = T),
			],
			[
				"Stream Molar Composition","Stream Mass Composition","Stream Mass Composition","Stream Molar Composition","Vapour Fraction","Liquid Composition","Vapour Composition","Overall Enthalpy","Molar Volume","Vapor Fraction","Liquid Composition","Vapour Composition","Overall Enthalpy","Molar Volume","Flash Calculation","Overall Enthalpy","Molar Volume","Sum of Composition","Molar Density","Average Molecular Weight","Mass or Molar Density","Flow Mass","Volumetric Flow","Temperature in  C","Equate Flow","Equate Pressures","Equate Temperatures",
			],
			[:PP,:NComp,:M,:ValidPhases,:CompositionBasis,],
			[:Outlet,:Composition,:SumOfComposition,:F,:Fw,:Fvol,:T,:T_Cdeg,:P,:x,:y,:Mw,:vm,:rho,:rhom,:zmass,]
		)
	end
	PP::DanaPlugin
	NComp::DanaInteger
	M::Array{molweight}
	ValidPhases::DanaSwitcher
	CompositionBasis::DanaSwitcher
	Outlet::stream
	Composition::Array{positive}
	SumOfComposition::positive
	F::flow_mol
	Fw::flow_mass
	Fvol::flow_vol
	T::temperature
	T_Cdeg::DanaReal
	P::pressure
	x::Array{fraction}
	y::Array{fraction}
	Mw::molweight
	vm::volume_mol
	rho::dens_mass
	rhom::dens_mol
	zmass::Array{fraction}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export source2
function set(in::source2)
	M = PP.MolecularWeight()
	 
end
function setEquationFlow(in::source2)
	let switch=CompositionBasis
		if switch=="Molar"
			addEquation(1)
			addEquation(2)
		elseif switch=="Mass"
			addEquation(3)
			addEquation(4)
		end
	end
	let switch=ValidPhases
		if switch=="Liquid-Only"
			addEquation(5)
			addEquation(6)
			addEquation(7)
			addEquation(8)
			addEquation(9)
		elseif switch=="Vapour-Only"
			addEquation(10)
			addEquation(11)
			addEquation(12)
			addEquation(13)
			addEquation(14)
		elseif switch=="Vapour-Liquid"
			addEquation(15)
			addEquation(16)
			addEquation(17)
		end
	end
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
end
function atributes(in::source2,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Source2"
	fields[:Brief]="Material stream source"
	fields[:Info]="
	This model should be used for boundary streams.
	Usually these streams are known and come from another process
	units.

	The user should specify:
	 * Total molar (mass or volumetric) flow
	 * Temperature
	 * Pressure
	 * Molar or mass composition
	
	No matter the specification set, the model will calculate some
	additional properties:
	 * Mass density
	 * Mass flow
	 * Mass compostions
	 * Specific volume
	 * Vapour fraction
	 * Volumetric flow
	 * Liquid and Vapour compositions
	"
	drive!(fields,_)
	return fields
end
source2(_::Dict{Symbol,Any})=begin
	newModel=source2()
	newModel.attributes=atributes(newModel,_)
	newModel
end
