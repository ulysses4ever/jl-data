#-------------------------------------
#* Nonequilibrium Model
#-------------------------------------
type trayRate
	trayRate()=begin
		new(
			trayRateBasic(),
			area (Dict{Symbol,Any}(
				:Brief=>"Total holes area"
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Weir length"
			)),
			acceleration (Dict{Symbol,Any}(
				:Default=>9.81
			)),
			length (Dict{Symbol,Any}(
				:Brief=>"Weir height"
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Aeration fraction"
			)),
			fraction (Dict{Symbol,Any}(
				:Brief=>"Dry pressure drop coefficient"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Valid=>["on", "off"],
				:Default=>"on"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Valid=>["on", "off"],
				:Default=>"on"
			)),
			dens_mass(),
			dens_mass(),
			[
				:(rhoL = _base_1.PP.LiquidDensity(_base_1.OutletL.T, _base_1.OutletL.P, _base_1.OutletL.z)),
				:(rhoV = _base_1.PP.VapourDensity(_base_1.InletV.T, _base_1.InletV.P, _base_1.InletV.z)),
				:(_base_1.OutletL.F*_base_1.vL = 1.84*"1/s"*lw*((_base_1.Level-(beta*hw))/(beta))^2),
				:(_base_1.OutletL.F = 0 * "mol/h"),
				:(_base_1.InletV.F*_base_1.vV = sqrt((_base_1.InletV.P - _base_1.OutletV.P)/(rhoV*alfa))*Ah),
				:(_base_1.InletV.F = 0 * "mol/s"),
			],
			[
				"Liquid Density","Vapour Density","Francis Equation","Low level","","",
			],
			[:Ah,:lw,:g,:hw,:beta,:alfa,:VapourFlow,:LiquidFlow,],
			[:rhoL,:rhoV,]
		)
	end
	_base_1::trayRateBasic
	Ah::area 
	lw::length 
	g::acceleration 
	hw::length 
	beta::fraction 
	alfa::fraction 
	VapourFlow::DanaSwitcher
	LiquidFlow::DanaSwitcher
	rhoL::dens_mass
	rhoV::dens_mass
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export trayRate
function setEquationFlow(in::trayRate)
	addEquation(1)
	addEquation(2)
	let switch=LiquidFlow
		if LiquidFlow==Level < (beta * hw)
			set(switch,"off")
		end
		if LiquidFlow==Level > (beta * hw) + 1e-6*"m"
			set(switch,"on")
		end
		if switch=="on"
			#		OutletL.F*vL = 1.84*'m^0.5/s'*lw*((Level-(beta*hw))/(beta))^1.5;
			addEquation(3)
		elseif switch=="off"
			addEquation(4)
		end
	end
	let switch=VapourFlow
		if VapourFlow==InletV.F < 1e-6 * "kmol/h"
			set(switch,"off")
		end
		if VapourFlow==InletV.P > OutletV.P + Level*g*rhoL + 1e-1 * "atm"
			set(switch,"on")
		end
		if switch=="on"
			addEquation(5)
		elseif switch=="off"
			addEquation(6)
		end
	end
end
function atributes(in::trayRate,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=false
	fields[:Icon]="icon/Tray"
	fields[:Brief]="Complete rate model of a column tray."
	fields[:Info]="== Specify ==
* the Feed stream
* the Liquid inlet stream
* the Vapour inlet stream
* the Vapour outlet flow (OutletV.F)
	
== Initial ==
* the plate temperature of both phases (OutletL.T and OutletV.T)
* the liquid height (Level) OR the liquid flow holdup (ML)
* the vapor holdup (MV)
* (NoComps - 1) OutletL compositions
"
	drive!(fields,_)
	return fields
end
trayRate(_::Dict{Symbol,Any})=begin
	newModel=trayRate()
	newModel.attributes=atributes(newModel,_)
	newModel
end
