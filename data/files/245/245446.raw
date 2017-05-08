#---------------------------------------------------------------------
#*	only liquid phase
#*--------------------------------------------------------------------
type tank_liq
	tank_liq()=begin
		new(
			tank_basic(),
			[
				:(_base_1.Outletm.v = 0),
				:(_base_1.Outletm.h = _base_1.PP.LiquidEnthalpy(_base_1.Outletm.T,_base_1.Outletm.P,_base_1.Outletm.z)),
				:(_base_1.Tank.V = _base_1.Mt*_base_1.PP.LiquidVolume(_base_1.Outletm.T,_base_1.Outletm.P,_base_1.Outletm.z)),
				:(E = _base_1.Mt*_base_1.Outletm.h - _base_1.Outletm.P*_base_1.Tank.V),
			],
			[
				"Vapourisation fraction","Liquid Enthalpy","Volume constraint","Total internal energy",
			],
		)
	end
	_base_1::tank_basic
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	attributes::Dict{Symbol,Any}
end
export tank_liq
function setEquationFlow(in::tank_liq)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
end
function atributes(in::tank_liq,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Brief]="Model of a generic liquid-phase tank"
	drive!(fields,_)
	return fields
end
tank_liq(_::Dict{Symbol,Any})=begin
	newModel=tank_liq()
	newModel.attributes=atributes(newModel,_)
	newModel
end
