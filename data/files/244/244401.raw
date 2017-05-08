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
#*--------------------------------------------------------------------
#* Author: Gerson Balbueno Bicca 
#* $Id: HairpinIncr.mso								$
#*------------------------------------------------------------------
type Hairpin_HeatTransfer
	Hairpin_HeatTransfer()=begin
		N=outers.N
		Npoints=outers.Npoints
		new(
			area (Dict{Symbol,Any}(
				:Brief=>"Cross Sectional Area for Flow",
				:Default=>0.05,
				:Lower=>1e-8
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Hydraulic Diameter of Pipe for Heat Transfer",
				:Lower=>1e-8
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of zones",
				:Default=>2
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of incremental points",
				:Default=>3
			)),
			fill(temperature (Dict{Symbol,Any}(
				:Brief=>"Incremental Local  Temperature",
				:Lower=>50
			)),(Npoints)),
			fill(positive (Dict{Symbol,Any}(
				:Brief=>"Incremental Reynolds Number",
				:Default=>100,
				:Lower=>1
			)),(N)),
			fill(heat_trans_coeff (Dict{Symbol,Any}(
				:Brief=>"Incremental Film Coefficient",
				:Default=>1,
				:Lower=>1e-12,
				:Upper=>1e6,
				:DisplayUnit=>"W/m^2/K"
			)),(N)),
			fill(fricfactor (Dict{Symbol,Any}(
				:Brief=>"Incremental Friction Factor",
				:Default=>0.05,
				:Lower=>1e-10,
				:Upper=>2000
			)),(N)),
			fill(positive (Dict{Symbol,Any}(
				:Brief=>"Incremental Nusselt Number",
				:Default=>0.5,
				:Lower=>1e-8
			)),(N)),
			fill(positive (Dict{Symbol,Any}(
				:Brief=>"Incremental Prandtl Number",
				:Default=>0.5,
				:Lower=>1e-8
			)),(N)),
			fill(positive (Dict{Symbol,Any}(
				:Brief=>"Incremental Phi Correction",
				:Default=>1,
				:Lower=>1e-3
			)),(N)),
			fill(velocity (Dict{Symbol,Any}(
				:Brief=>"Incremental Tube Velocity",
				:Lower=>1e-8
			)),(N)),
			fill(enth_mol (Dict{Symbol,Any}(
				:Brief=>"Incremental Stream Enthalpy"
			)),(Npoints)),
			[:As,:Dh,:N,:Npoints,],
			[:Tlocal,:Re,:hcoeff,:fi,:Nu,:PR,:Phi,:Vmean,:Enth,]
		)
	end
	As::area 
	Dh::length 
	N::DanaInteger 
	Npoints::DanaInteger 
	Tlocal::Array{temperature }
	Re::Array{positive }
	hcoeff::Array{heat_trans_coeff }
	fi::Array{fricfactor }
	Nu::Array{positive }
	PR::Array{positive }
	Phi::Array{positive }
	Vmean::Array{velocity }
	Enth::Array{enth_mol }
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Hairpin_HeatTransfer
function atributes(in::Hairpin_HeatTransfer,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="to be documented"
	fields[:Info]="to be documented"
	drive!(fields,_)
	return fields
end
Hairpin_HeatTransfer(_::Dict{Symbol,Any})=begin
	newModel=Hairpin_HeatTransfer()
	newModel.attributes=atributes(newModel,_)
	newModel
end
