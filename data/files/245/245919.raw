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
type sink
	sink()=begin
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
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet Stream",
				:PosX=>0,
				:PosY=>0.5308,
				:Protected=>true,
				:Symbol=>"_{in}"
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"Vapourization fraction",
				:Hidden=>true
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Liquid Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Vapour Molar Fraction",
				:Hidden=>true
			)),(NComp)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Mass Fraction"
			)),(NComp)),
			molweight(Dict{Symbol,Any}(
				:Brief=>"Average Mol Weight"
			)),
			volume_mol(Dict{Symbol,Any}(
				:Brief=>"Molar Volume"
			)),
			dens_mass(Dict{Symbol,Any}(
				:Brief=>"Stream Mass Density"
			)),
			dens_mol(Dict{Symbol,Any}(
				:Brief=>"Stream Molar Density"
			)),
			flow_mass(Dict{Symbol,Any}(
				:Brief=>"Stream Mass Flow"
			)),
			flow_vol(Dict{Symbol,Any}(
				:Brief=>"Volumetric Flow"
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Temperature in  C",
				:Lower=>-250,
				:Upper=>5000
			)),
			[
				:([v, x, y] = PP.FlashPH(Inlet.P, Inlet.h, Inlet.z)),
				:(Mw = sum(M*Inlet.z)),
				:(rhom * vm = 1),
				:(rhom * Mw = rho),
				:(Fw = Mw*Inlet.F),
				:(vm = (1-v)*PP.LiquidVolume(Inlet.T, Inlet.P, x) + v*PP.VapourVolume(Inlet.T,Inlet.P,y)),
				:(Fvol = Inlet.F*vm),
				:(zmass = M*Inlet.z / Mw),
				:(T_Cdeg = Inlet.T/"K" - 273.15),
			],
			[
				"Flash Calculation","Average Molecular Weight","Molar Density","Mass or Molar Density","Flow Mass","Molar Volume","Volumetric Flow","Mass Fraction","Temperature in  C",
			],
			[:PP,:NComp,:M,],
			[:Inlet,:v,:x,:y,:zmass,:Mw,:vm,:rho,:rhom,:Fw,:Fvol,:T_Cdeg,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	M::Array{molweight }
	Inlet::stream 
	v::fraction 
	x::Array{fraction }
	y::Array{fraction }
	zmass::Array{fraction }
	Mw::molweight 
	vm::volume_mol 
	rho::dens_mass 
	rhom::dens_mol 
	Fw::flow_mass 
	Fvol::flow_vol 
	T_Cdeg::DanaReal
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export sink
function set(in::sink)
	M = PP.MolecularWeight()
	 
end
function setEquationFlow(in::sink)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
	addEquation(9)
end
function atributes(in::sink,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Sink"
	fields[:Brief]="Material stream sink"
	fields[:Info]="
	This model should be used for boundary streams when additional
	information about the stream is desired.

	Some of the additional informations calculated by this models are:
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
sink(_::Dict{Symbol,Any})=begin
	newModel=sink()
	newModel.attributes=atributes(newModel,_)
	newModel
end
