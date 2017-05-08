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
type simple_source2
	simple_source2()=begin
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
			fill(molweight (Dict{Symbol,Any}(
				:Brief=>"Component Mol Weight",
				:Protected=>true
			)),(NComp)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Valid Phases for Flash Calculation",
				:Valid=>["Vapour-Only", "Liquid-Only","Vapour-Liquid"],
				:Default=>"Vapour-Liquid"
			)),
			stream (Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>0.5256,
				:Symbol=>"_{out}",
				:Protected=>true
			)),
			fill(positive (Dict{Symbol,Any}(
				:Brief=>"Stream Molar Composition"
			)),(NComp)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Sum of Stream Composition",
				:Protected=>true
			)),
			flow_mol (Dict{Symbol,Any}(
				:Brief=>"Stream Molar Flow Rate"
			)),
			temperature (Dict{Symbol,Any}(
				:Brief=>"Stream Temperature"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Temperature in  C",
				:Lower=>-250,
				:Upper=>5000
			)),
			pressure (Dict{Symbol,Any}(
				:Brief=>"Stream Pressure"
			)),
			fill(fraction (Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			fill(fraction (Dict{Symbol,Any}(
				:Brief=>"Vapour Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			[
				:(SumOfComposition = sum(MolarComposition)),
				:(Outlet.z = MolarComposition/sum(MolarComposition)),
				:(Outlet.v = 0),
				:(x = Outlet.z),
				:(y = Outlet.z),
				:(Outlet.h = PP.LiquidEnthalpy(Outlet.T, Outlet.P, x)),
				:(Outlet.v = 1),
				:(x = Outlet.z),
				:(y = Outlet.z),
				:(Outlet.h = PP.VapourEnthalpy(Outlet.T, Outlet.P, y)),
				:([Outlet.v, x, y] = PP.Flash(Outlet.T, Outlet.P, Outlet.z)),
				:(Outlet.h = (1-Outlet.v)*PP.LiquidEnthalpy(Outlet.T, Outlet.P, x) + Outlet.v*PP.VapourEnthalpy(Outlet.T, Outlet.P, y)),
				:(T_Cdeg = Outlet.T/"K" - 273.15),
				:(Outlet.F = F),
				:(Outlet.P = P),
				:(Outlet.T = T),
			],
			[
				"Sum of Composition","Stream Molar Composition","Vapour Fraction","Liquid Composition","Vapour Composition","Overall Enthalpy","Vapor Fraction","Liquid Composition","Vapour Composition","Overall Enthalpy","Flash Calculation","Overall Enthalpy","Temperature in  C","Equate Flow","Equate Pressures","Equate Temperatures",
			],
			[:PP,:NComp,:M,:ValidPhases,],
			[:Outlet,:MolarComposition,:SumOfComposition,:F,:T,:T_Cdeg,:P,:x,:y,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	M::Array{molweight }
	ValidPhases::DanaSwitcher 
	Outlet::stream 
	MolarComposition::Array{positive }
	SumOfComposition::positive 
	F::flow_mol 
	T::temperature 
	T_Cdeg::DanaReal
	P::pressure 
	x::Array{fraction }
	y::Array{fraction }
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export simple_source2
function set(in::simple_source2)
	M = PP.MolecularWeight()
	 
end
function setEquationFlow(in::simple_source2)
	addEquation(1)
	addEquation(2)
	let switch=ValidPhases
		if switch=="Liquid-Only"
			addEquation(3)
			addEquation(4)
			addEquation(5)
			addEquation(6)
		elseif switch=="Vapour-Only"
			addEquation(7)
			addEquation(8)
			addEquation(9)
			addEquation(10)
		elseif switch=="Vapour-Liquid"
			addEquation(11)
			addEquation(12)
		end
	end
	addEquation(13)
	addEquation(14)
	addEquation(15)
	addEquation(16)
end
function atributes(in::simple_source2,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Source2"
	fields[:Brief]="Simple Material stream source"
	fields[:Info]="
	This model should be used for boundary streams.
	Usually these streams are known and come from another process
	units.

	The user should specify:
	 * Total molar flow
	 * Temperature
	 * Pressure
	 * Molar composition
"
	drive!(fields,_)
	return fields
end
simple_source2(_::Dict{Symbol,Any})=begin
	newModel=simple_source2()
	newModel.attributes=atributes(newModel,_)
	newModel
end
