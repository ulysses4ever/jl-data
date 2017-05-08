#-------------------------------------------------------------------
#* Model of a pump (simplified, used in distillation column model)
#*----------------------------------------------------------------------
#* Author: Paula B. Staudt
#*--------------------------------------------------------------------
type pump2
	pump2()=begin
		PP=outers.PP
		NComp=outers.NComp
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties",
				:Type=>"PP"
			)),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of chemical components"
			)),
			stream(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>1,
				:PosY=>0.4727,
				:Protected=>true,
				:Symbol=>"_{in}"
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>0,
				:PosY=>0.1859,
				:Protected=>true,
				:Symbol=>"_{out}"
			)),
			press_delta(Dict{Symbol,Any}(
				:Brief=>"Pressure Increase",
				:Lower=>0,
				:DisplayUnit=>"kPa",
				:Symbol=>"P_{incr}"
			)),
			[
				:(Inlet.F = Outlet.F),
				:(Inlet.z = Outlet.z),
				:(Outlet.P = Inlet.P + Pincrease),
				:(Outlet.T = Inlet.T),
			],
			[
				"Molar Balance","Composittion","Pump head","Pump potency",
			],
			[:PP,:NComp,],
			[:Inlet,:Outlet,:Pincrease,]
		)
	end
	PP::DanaPlugin 
	NComp::DanaInteger 
	Inlet::stream 
	Outlet::liquid_stream 
	Pincrease::press_delta 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export pump2
function setEquationFlow(in::pump2)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	# FIXME: add a consistent equation for this pump using the work added
	# and a flashPH call
	#	Outlet.h = Inlet.h;
	addEquation(4)
end
function atributes(in::pump2,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/Pump2"
	fields[:Brief]="Model of a simplified pump, used in distillation column model."
	fields[:Info]="== ASSUMPTIONS ==
* Steady State;
* Only Liquid;
* Adiabatic;
* Isentropic.

== SPECIFY == 
* the inlet stream;
* the pump Pincrease.
"
	drive!(fields,_)
	return fields
end
pump2(_::Dict{Symbol,Any})=begin
	newModel=pump2()
	newModel.attributes=atributes(newModel,_)
	newModel
end
