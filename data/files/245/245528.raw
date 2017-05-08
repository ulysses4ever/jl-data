#---------------------------------------------------------------------
#*	only liquid phase
#*--------------------------------------------------------------------
type yield_liq
	yield_liq()=begin
		new(
			tank_liq(),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Number of reactions",
				:Default=>1
			)),
			DanaInteger (Dict{Symbol,Any}(
				:Brief=>"Key component",
				:Lower=>1,
				:Default=>1
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>1,
				:Symbol=>"_{out}"
			)),
			fill(reaction_mol (Dict{Symbol,Any}(
				:Brief=>"Overall component rate of reaction"
			)),(NComp)),
			fill(DanaReal (Dict{Symbol,Any}(
				:Brief=>"Fractional conversion of component",
				:Symbol=>"X",
				:Default=>0
			)),(NComp)),
			fill(DanaReal (Dict{Symbol,Any}(
				:Brief=>"Molar component yield (global)",
				:Symbol=>"Y_G"
			)),(NComp)),
			fill(DanaReal (Dict{Symbol,Any}(
				:Brief=>"Molar reaction yield (instantaneous)",
				:Symbol=>"Y_I"
			)),(NComp)),
			[
				:(Outlet.F*Outlet.z = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.z + rate*_base_1._base_1.Tank.V),
				:(rate*_base_1._base_1.Tank.V = _base_1._base_1.Outletm.F*(yield/(1 + yield(KComp))*_base_1._base_1.Outletm.z(KComp) - _base_1._base_1.Outletm.z)),
				:(rate = yield_*rate(KComp)),
				:(Outlet.P = _base_1._base_1.Outletm.P),
				:(Outlet.F*Outlet.h = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.h),
				:(Outlet.F*Outlet.z([1:_base_1._base_1.NComp]) = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.z([1:_base_1._base_1.NComp])*(1 - conv([1:_base_1._base_1.NComp]))),
				:(conv([1:_base_1._base_1.NComp]) = 1),
				:(conv([1:_base_1._base_1.NComp]) = 0),
			],
			[
				"Outlet stream","Rate of reaction","Molar reaction yield","Mechanical equilibrium","Energy balance","Molar conversion","Molar conversion","Molar conversion",
			],
			[:NReac,:KComp,],
			[:Outlet,:rate,:conv,:yield,:yield_,]
		)
	end
	_base_1::tank_liq
	NReac::DanaInteger 
	KComp::DanaInteger 
	Outlet::liquid_stream
	rate::Array{reaction_mol }
	conv::Array{DanaReal }
	yield::Array{DanaReal }
	yield_::Array{DanaReal }
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export yield_liq
function setEquationFlow(in::yield_liq)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	if (Outletm.z(i) > 0) 
		addEquation(6)
	else
		if (Outlet.z(i) > 0) 
			addEquation(7)
			# ?
			
		else
			addEquation(8)
			# ?
			
		end
	end
end
function atributes(in::yield_liq,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/cstr"
	fields[:Brief]="Model of a generic liquid-phase yield CSTR"
	fields[:Info]="
== Assumptions ==
* only liquid-phase
* steady-state

== Specify ==
* inlet stream
* component yield or
* reaction yield
"
	drive!(fields,_)
	return fields
end
yield_liq(_::Dict{Symbol,Any})=begin
	newModel=yield_liq()
	newModel.attributes=atributes(newModel,_)
	newModel
end
