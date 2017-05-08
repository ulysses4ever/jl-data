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
#* Author: Maur좩cio Carvalho Maciel, Paula B. Staudt, Rafael P. Soares
#* $Id$
#*--------------------------------------------------------------------
type splitter_column
	splitter_column()=begin
		new(
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0.5,
				:PosY=>0,
				:Symbol=>"_{in}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Reflux stream",
				:PosX=>0.25,
				:PosY=>1,
				:Symbol=>"_{reflux}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Distillate stream",
				:PosX=>0.75,
				:PosY=>1,
				:Symbol=>"_{distillate}"
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"split of the outlet Reflux stream",
				:Default=>0.33
			)),
			fraction(Dict{Symbol,Any}(
				:Brief=>"split of the outlet Distillate stream",
				:Default=>0.33
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Reflux Ratio",
				:Default=>10,
				:Lower=>0.05
			)),
			[
				:(SplitFlow_RefluxStream*(1 + RefluxRatio) = RefluxRatio),
				:(SplitFlow_RefluxStream + SplitFlow_DistillateStream = 1),
				:(Reflux.F = Inlet.F * SplitFlow_RefluxStream),
				:(Inlet.F = Reflux.F + Distillate.F),
				:(Reflux.z = Inlet.z),
				:(Distillate.z = Inlet.z),
				:(Reflux.P = Inlet.P),
				:(Distillate.P = Inlet.P),
				:(Reflux.h = Inlet.h),
				:(Distillate.h = Inlet.h),
				:(Reflux.T = Inlet.T),
				:(Distillate.T = Inlet.T),
				:(Reflux.v = Inlet.v),
				:(Distillate.v = Inlet.v),
			],
			[
				"Reflux Ratio","Normalize Flow Ratios","Flow","","Composition","","Pressure","","Enthalpy","","Temperature","","Vapourisation Fraction","",
			],
			[:Inlet,:Reflux,:Distillate,:SplitFlow_RefluxStream,:SplitFlow_DistillateStream,:RefluxRatio,]
		)
	end
	Inlet::stream
	Reflux::stream
	Distillate::stream
	SplitFlow_RefluxStream::fraction
	SplitFlow_DistillateStream::fraction
	RefluxRatio::positive
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export splitter_column
function setEquationFlow(in::splitter_column)
	#Reflux.F*RefluxRatio = SplitFlow_RefluxStream*(Reflux.F*RefluxRatio + Reflux.F);
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
end
function atributes(in::splitter_column,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/splitter_column"
	fields[:Brief]="Splitter with 2 outlet streams to be used with column section model"
	fields[:Info]="== Assumptions ==
*Thermodynamics equilibrium
*Adiabatic

== Specify ==
* The inlet stream
* One Split Flow of the outlet stream:
**SplitFlow_RefluxStream: split of the outlet Reflux stream
**SplitFlow_DistillateStream: split of the outlet Distillate stream

OR

* The inlet stream and the RefluxRatio
"
	drive!(fields,_)
	return fields
end
splitter_column(_::Dict{Symbol,Any})=begin
	newModel=splitter_column()
	newModel.attributes=atributes(newModel,_)
	newModel
end
