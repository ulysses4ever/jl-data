#---------------------------------------------------------------------
#*	only liquid phase
#*--------------------------------------------------------------------
type gibbs_liq
	gibbs_liq()=begin
		NElem=outers.NElem
		new(
			tank_liq(),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of elements",
				:Default=>1
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Universal gas constant",
				:Unit=>"J/mol/K",
				:Default=>8.314
			)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Number of elements per component"
			)),(NElem,NComp)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Pressure of standard state",
				:Default=>1,
				:DisplayUnit=>"atm"
			)),
			temperature(Dict{Symbol,Any}(
				:Brief=>"Reference temperature",
				:Default=>298.15
			)),
			liquid_stream(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>1,
				:Symbol=>"_{out}"
			)),
			fill(energy_mol(Dict{Symbol,Any}(
				:Brief=>"Gibbs free-energy change of formation"
			)),(NComp)),
			fill(energy_mol(Dict{Symbol,Any}(
				:Brief=>"Lagrangian multiplier",
				:Symbol=>"\\lambda"
			)),(NElem)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Activity",
				:Symbol=>"\\hat{a}",
				:Lower=>0
			)),(NComp)),
			fill(reaction_mol(Dict{Symbol,Any}(
				:Brief=>"Overall component rate of reaction"
			)),(NComp)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Fractional conversion of component",
				:Symbol=>"X",
				:Default=>0
			)),(NComp)),
			fill(flow_mol(Dict{Symbol,Any}(
				:Brief=>"Component molar flow rate"
			)),(NComp)),
			[
				:(Outlet.F*Outlet.z = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.z + rate*_base_1._base_1.Tank.V),
				:(Outlet.P = _base_1._base_1.Outletm.P),
				:(Outlet.F = sum(Fi)),
				:(Fi = Outlet.F*Outlet.z),
				:(Outlet.F*Outlet.h = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.h),
				:(sumt(Fi*na) = sumt(_base_1._base_1.Outletm.F*_base_1._base_1.Outletm.z*na)),
				:(G = _base_1._base_1.PP.IdealGasGibbsOfFormation(Outlet.T)),
				:(G([1:_base_1._base_1.NComp]) + sumt(lambda*na(:,[1:_base_1._base_1.NComp])) = -Rg*Outlet.T*ln(activ([1:_base_1._base_1.NComp]))),
				:(Fi([1:_base_1._base_1.NComp]) = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.z([1:_base_1._base_1.NComp])*(1 - conv([1:_base_1._base_1.NComp]))),
				:(conv([1:_base_1._base_1.NComp]) = 1),
				:(conv([1:_base_1._base_1.NComp]) = 0),
				:(activ = _base_1._base_1.PP.LiquidFugacityCoefficient(Outlet.T,Outlet.P,Outlet.z)*Outlet.z *exp(_base_1._base_1.PP.LiquidVolume(Outlet.T,Outlet.P,Outlet.z)*(Outlet.P - Ps)/Rg/Outlet.T)),
			],
			[
				"Outlet stream","Mechanical equilibrium","Steady-state","Component molar flow rate","Energy balance","Element balance","Gibbs free-energy of formation","Lagrangian multiplier","Molar conversion","Molar conversion","Molar conversion","Activity",
			],
			[:NElem,:Rg,:na,:Ps,:To,],
			[:Outlet,:G,:lambda,:activ,:rate,:conv,:Fi,]
		)
	end
	_base_1::tank_liq
	NElem::DanaInteger 
	Rg::DanaReal 
	na::Array{DanaReal }
	Ps::pressure 
	To::temperature 
	Outlet::liquid_stream
	G::Array{energy_mol }
	lambda::Array{energy_mol }
	activ::Array{DanaReal }
	rate::Array{reaction_mol }
	conv::Array{DanaReal }
	Fi::Array{flow_mol }
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export gibbs_liq
function setEquationFlow(in::gibbs_liq)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	#	"Gibbs free-energy of formation without Cp correction"
	#	G = PP.IdealGasGibbsOfFormationAt25C()*Outlet.T/To
	#		+ PP.IdealGasEnthalpyOfFormationAt25C()*(1 - Outlet.T/To);
	addEquation(8)
	if (Outletm.z(i) > 1e-16) 
		addEquation(9)
	else
		if (Outlet.z(i) > 0) 
			addEquation(10)
			# ?
			
		else
			addEquation(11)
			# ?
			
		end
	end
	addEquation(12)
end
function atributes(in::gibbs_liq,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/cstr"
	fields[:Brief]="Model of a generic liquid-phase Gibbs CSTR"
	fields[:Info]="
== Assumptions ==
* thermodynamic equilibrium
* steady-state

== Specify ==
* inlet stream
* number of elements related to components
* matrix of elements by components
* equilibrium temperature
"
	drive!(fields,_)
	return fields
end
gibbs_liq(_::Dict{Symbol,Any})=begin
	newModel=gibbs_liq()
	newModel.attributes=atributes(newModel,_)
	newModel
end
