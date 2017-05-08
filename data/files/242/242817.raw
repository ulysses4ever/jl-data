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
type VesselVolume
	VesselVolume()=begin
		new(
			positive(Dict{Symbol,Any}(
				:Brief=>"Pi value",
				:Default=>3.141593,
				:Hidden=>true,
				:Symbol=>"\\pi"
			)),
			acceleration(Dict{Symbol,Any}(
				:Brief=>"Gravity Acceleration",
				:Default=>9.81,
				:Hidden=>true
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Valid=>["vertical","horizontal"],
				:Default=>"vertical"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Valid=>["elliptical","hemispherical","flat"],
				:Default=>"flat"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Vessel diameter",
				:Default=>2,
				:Symbol=>"D_{i}"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Side length of the cylinder shell",
				:Default=>6,
				:Symbol=>"L_{vessel}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Elliptical Head Total Volume",
				:Hidden=>true,
				:Symbol=>"V_{head}^{elliptical}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Hemispherical Head Total Volume",
				:Hidden=>true,
				:Symbol=>"V_{head}^{hemispherical}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Cylinder Total Volume",
				:Hidden=>true,
				:Symbol=>"V_{cylinder}"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"Vessel radius",
				:Hidden=>true,
				:Symbol=>"R_{cylinder}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Vessel total volume",
				:Protected=>true,
				:Symbol=>"V_{total}"
			)),
			volume(Dict{Symbol,Any}(
				:Brief=>"Vessel volume content",
				:Protected=>true,
				:Symbol=>"V_{filled}"
			)),
			length(Dict{Symbol,Any}(
				:Brief=>"liquid height",
				:Protected=>true
			)),
			area(Dict{Symbol,Any}(
				:Brief=>"Vessel cylinder shell Cross section area",
				:Hidden=>true,
				:Symbol=>"A_{cross}"
			)),
			[
				:(Across = 0.25*(Pi*Diameter^2)),
				:(Vtotal = Vhead_elliptical + Vcylinder),
				:(Vfilled = 0.25*Pi*(((Diameter*Level)/(0.25*Diameter))^2)*(0.25*Diameter-Level/3)),
				:(Vfilled = 0.25*Pi*(Diameter^2)*(Level - 0.25*Diameter/3)),
				:(Vtotal = Vhead_hemispherical + Vcylinder),
				:(Vfilled = 0.25*Pi*(Level^2)*(2*Diameter-4*Level/3)),
				:(Vfilled = 0.25*Pi*((2/3)*((0.5*Diameter)^3) - (0.25*(Diameter)^3) + Level*Diameter^2)),
				:(Vtotal = Vcylinder),
				:(Vfilled = Across*Level),
				:(Across = (radius^2)*acos((radius-Level)/radius)/"rad"-(radius-Level)*sqrt((2*radius*Level-Level^2))),
				:(Vtotal = Vhead_elliptical + Vcylinder),
				:(Vfilled = 0.5236*Level^2*(1.5*Diameter-Level) + Across*Lenght),
				:(Vtotal = Vhead_hemispherical + Vcylinder),
				:(Vfilled = 1.0472*Level^2*(1.5*Diameter-Level) + Across*Lenght),
				:(Vtotal = Vcylinder),
				:(Vfilled = Across*Lenght),
			],
			[
				"Vessel Cross Section Area","Vessel Total Volume","Vessel Filled Volume","Vessel Filled Volume","Vessel Total Volume","Vessel Filled Volume","Vessel Filled Volume","Vessel Total Volume","Vessel Filled Volume","Vessel Cross Section Area","Vessel Total Volume","Vessel Filled Volume","Vessel Total Volume","Vessel Filled Volume","Vessel Total Volume","Vessel Filled Volume",
			],
			[:Pi,:Gconst,:Orientation,:Heads,:Diameter,:Lenght,:Vhead_elliptical,:Vhead_hemispherical,:Vcylinder,:radius,],
			[:Vtotal,:Vfilled,:Level,:Across,]
		)
	end
	Pi::positive
	Gconst::acceleration
	Orientation::DanaSwitcher
	Heads::DanaSwitcher
	Diameter::length
	Lenght::length
	Vhead_elliptical::volume
	Vhead_hemispherical::volume
	Vcylinder::volume
	radius::length
	Vtotal::volume
	Vfilled::volume
	Level::length
	Across::area
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export VesselVolume
function set(in::VesselVolume)
	Gconst = 9.81 * "m/(s^2)"
	 Vhead_elliptical = (Pi*Diameter^3)/12
	 Vhead_hemispherical = (Pi*Diameter^3)/6
	 Vcylinder = 0.25*(Pi*Diameter^2)*Lenght
	 radius = 0.5*Diameter
	 
end
function setEquationFlow(in::VesselVolume)
	let switch=Orientation
		if switch=="vertical"
			addEquation(1)
			let switch=Heads
				if switch=="elliptical"
					addEquation(2)
					if Level < 0.25*Diameter 
						addEquation(3)
					else
						addEquation(4)
					end
				elseif switch=="hemispherical"
					addEquation(5)
					if Level < 0.5*Diameter 
						addEquation(6)
					else
						addEquation(7)
					end
				elseif switch=="flat"
					addEquation(8)
					addEquation(9)
				end
			end
		elseif switch=="horizontal"
			addEquation(10)
			let switch=Heads
				if switch=="elliptical"
					addEquation(11)
					addEquation(12)
				elseif switch=="hemispherical"
					addEquation(13)
					addEquation(14)
				elseif switch=="flat"
					addEquation(15)
					addEquation(16)
				end
			end
		end
	end
end
function atributes(in::VesselVolume,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Brief]="Model to calculate vessel total volume and vessel filled volume from 
different geometries and orientations."
	fields[:Info]="== SET ==
*Orientation: vessel position - vertical or horizontal;
*Heads (bottom and top heads are identical)
**elliptical: 2:1 elliptical heads (25% of vessel diameter);
**hemispherical: hemispherical heads (50% of vessel diameter);
**flat: flat heads (0% of vessel diameter);
*Diameter: Vessel diameter;
*Lenght: Side length of the cylinder shell;
"
	drive!(fields,_)
	return fields
end
VesselVolume(_::Dict{Symbol,Any})=begin
	newModel=VesselVolume()
	newModel.attributes=atributes(newModel,_)
	newModel
end
