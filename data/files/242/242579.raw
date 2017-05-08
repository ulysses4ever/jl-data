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
type splitter3
	splitter3()=begin
		new(
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0,
				:PosY=>0.5001,
				:Symbol=>"_{in}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream 1",
				:PosX=>1,
				:PosY=>0.25,
				:Symbol=>"_{Out1}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream 2",
				:PosX=>1,
				:PosY=>0.5059,
				:Symbol=>"_{Out2}"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream 3",
				:PosX=>1,
				:PosY=>0.75,
				:Symbol=>"_{Out3}"
			)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Distribution of Outlets",
				:Default=>0.33,
				:Symbol=>"\\phi"
			)),(3)),
			[
				:(sum(FlowRatios) = 1),
				:(Outlet1.F = Inlet.F*FlowRatios(1)),
				:(Outlet2.F = Inlet.F*FlowRatios(2)),
				:(Outlet3.F = Inlet.F*FlowRatios(3)),
				:(Outlet1.z = Inlet.z),
				:(Outlet2.z = Inlet.z),
				:(Outlet3.z = Inlet.z),
				:(Outlet1.P = Inlet.P),
				:(Outlet2.P = Inlet.P),
				:(Outlet3.P = Inlet.P),
				:(Outlet1.h = Inlet.h),
				:(Outlet2.h = Inlet.h),
				:(Outlet3.h = Inlet.h),
				:(Outlet1.T = Inlet.T),
				:(Outlet2.T = Inlet.T),
				:(Outlet3.T = Inlet.T),
				:(Outlet1.v = Inlet.v),
				:(Outlet2.v = Inlet.v),
				:(Outlet3.v = Inlet.v),
			],
			[
				"Normalize Flow Ratios","Outlet1 Flow","Outlet2 Flow","Outlet3 Flow","Outlet1 Composition","Outlet2 Composition","Outlet3 Composition","Outlet1 Pressure","Outlet2 Pressure","Outlet3 Pressure","Outlet1 Enthalpy","Outlet2 Enthalpy","Outlet3 Enthalpy","Outlet1 Temperature","Outlet2 Temperature","Outlet3 Temperature","Outlet1 Vapourisation Fraction","Outlet2 Vapourisation Fraction","Outlet3 Vapourisation Fraction",
			],
			[:Inlet,:Outlet1,:Outlet2,:Outlet3,:FlowRatios,]
		)
	end
	Inlet::stream
	Outlet1::stream
	Outlet2::stream
	Outlet3::stream
	FlowRatios::Array{fraction}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export splitter3
function setEquationFlow(in::splitter3)
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
end
function atributes(in::splitter3,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/splitter"
	fields[:Brief]="Model of a splitter with 3 outlet streams"
	fields[:Info]="== Assumptions ==
* Thermodynamics equilibrium
* Adiabatic
			
== Specify ==
*The inlet stream
*Two FlowRatios of split of the outlet streams:

	FlowRatios(i) = (Mole Flow of the outlet stream i / 
				Mole Flow of the inlet stream)
				where i = 1, 2, 3
"
	drive!(fields,_)
	return fields
end
splitter3(_::Dict{Symbol,Any})=begin
	newModel=splitter3()
	newModel.attributes=atributes(newModel,_)
	newModel
end
