#---------------------------------------------------------------------
#*	only liquid-phase
#*--------------------------------------------------------------------
type equil_liq
	equil_liq()=begin
		new(
			tank_liq(),
			DanaInteger(Dict{Symbol,Any}(
				:Brief=>"Number of reactions",
				:Default=>1
			)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Stoichiometric matrix",
				:Symbol=>"\\nu"
			)),(NComp,NReac)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Universal gas constant",
				:Unit=>"J/mol/K",
				:Default=>8.314
			)),
			pressure(Dict{Symbol,Any}(
				:Brief=>"Standard pressure",
				:Default=>1,
				:DisplayUnit=>"bar"
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
			fill(enth_mol(Dict{Symbol,Any}(
				:Brief=>"Gibbs free-energy of formation"
			)),(NReac)),
			fill(fraction(Dict{Symbol,Any}(
				:Brief=>"Equillibrium constant"
			)),(NReac)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Activity",
				:Symbol=>"\\hat{a}"
			)),(NComp)),
			fill(reaction_mol(Dict{Symbol,Any}(
				:Brief=>"Overall component rate of reaction"
			)),(NComp)),
			fill(flow_mol(Dict{Symbol,Any}(
				:Brief=>"Extent of reaction",
				:Symbol=>"\\xi"
			)),(NReac)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Fractional conversion of component",
				:Symbol=>"X",
				:Default=>0
			)),(NComp)),
			[
				:(Outlet.F*Outlet.z = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.z + rate*_base_1._base_1.Tank.V),
				:(Outlet.P = _base_1._base_1.Outletm.P),
				:(Outlet.F*Outlet.h = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.h),
				:(Outlet.F = _base_1._base_1.Inlet.F + sum(sumt(stoic*extent))),
				:(G = _base_1._base_1.PP.IdealGasGibbsOfFormation(Outlet.T)),
				:(sumt(G*stoic) = -Rg*Outlet.T*ln(K)),
				:(K([1:NReac]) = prod(activ^stoic(:,[1:NReac]))),
				:(Outlet.F*Outlet.z([1:_base_1._base_1.NComp]) = (_base_1._base_1.Inlet.F*_base_1._base_1.Inlet.z([1:_base_1._base_1.NComp]) + sumt(stoic([1:_base_1._base_1.NComp],:)*extent))),
				:(Outlet.F*Outlet.z([1:_base_1._base_1.NComp]) = _base_1._base_1.Outletm.F*_base_1._base_1.Outletm.z([1:_base_1._base_1.NComp])*(1 - conv([1:_base_1._base_1.NComp]))),
				:(conv([1:_base_1._base_1.NComp]) = 1),
				:(conv([1:_base_1._base_1.NComp]) = 0),
				:(activ = _base_1._base_1.PP.LiquidFugacityCoefficient(Outlet.T,Outlet.P,Outlet.z)*Outlet.z *exp(_base_1._base_1.PP.LiquidVolume(Outlet.T,Outlet.P,Outlet.z)*(Outlet.P - Ps)/Rg/Outlet.T)),
			],
			[
				"Outlet stream","Mechanical equilibrium","Energy balance","Steady-state","Gibbs free-energy of formation","Gibbs free energy of reaction","Equilibrium constant","Outlet molar fraction","Molar conversion","Molar conversion","Molar conversion","Activity",
			],
			[:NReac,:stoic,:Rg,:Ps,:To,],
			[:Outlet,:G,:K,:activ,:rate,:extent,:conv,]
		)
	end
	_base_1::tank_liq
	NReac::DanaInteger 
	stoic::Array{DanaReal }
	Rg::DanaReal 
	Ps::pressure 
	To::temperature 
	Outlet::liquid_stream
	G::Array{enth_mol }
	K::Array{fraction }
	activ::Array{DanaReal }
	rate::Array{reaction_mol }
	extent::Array{flow_mol }
	conv::Array{DanaReal }
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export equil_liq
function setEquationFlow(in::equil_liq)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	#	"Gibbs free-energy of formation without Cp correction"
	#	G = PP.IdealGasGibbsOfFormationAt25C()*Outlet.T/To
	#		+ PP.IdealGasEnthalpyOfFormationAt25C()*(1 - Outlet.T/To);
	addEquation(6)
	#	K = exp(-sumt(G*stoic)/(Rg*Outlet.T));
	addEquation(7)
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
function atributes(in::equil_liq,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/cstr"
	fields[:Brief]="Model of a generic liquid-phase equilibrium CSTR"
	fields[:Info]="
== Assumptions ==
* only liquid-phase
* thermodynamic equilibrium
* steady-state

== Specify ==
* inlet stream
* stoichiometric matrix
* equilibrium temperature
"
	drive!(fields,_)
	return fields
end
equil_liq(_::Dict{Symbol,Any})=begin
	newModel=equil_liq()
	newModel.attributes=atributes(newModel,_)
	newModel
end
