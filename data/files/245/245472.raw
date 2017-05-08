#---------------------------------------------------------------------
#*	only vapour phase
#*--------------------------------------------------------------------
type tank_vap
	tank_vap()=begin
		new(
			tank_basic(),
			[
				:(_base_1.Outletm.v = 1),
				:(_base_1.Outletm.h = _base_1.PP.VapourEnthalpy(_base_1.Outletm.T,_base_1.Outletm.P,_base_1.Outletm.z)),
				:(_base_1.Tank.V = _base_1.Mt*_base_1.PP.VapourVolume(_base_1.Outletm.T,_base_1.Outletm.P,_base_1.Outletm.z)),
				:(E = _base_1.Mt*_base_1.Outletm.h),
			],
			[
				"Vapourisation fraction","Vapour Enthalpy","Volume constraint","Total internal energy",
			],
		)
	end
	_base_1::tank_basic
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	attributes::Dict{Symbol,Any}
end
export tank_vap
function setEquationFlow(in::tank_vap)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
end
function atributes(in::tank_vap,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Brief]="Model of a generic vapour-phase tank"
	drive!(fields,_)
	return fields
end
tank_vap(_::Dict{Symbol,Any})=begin
	newModel=tank_vap()
	newModel.attributes=atributes(newModel,_)
	newModel
end
