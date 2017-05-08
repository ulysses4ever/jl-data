#---------------------------------------------------------------------
#*	only vapour phase
#*--------------------------------------------------------------------
type Equil_vap
	Equil_vap()=begin
		PP=outers.PP
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"External Physical Properties"
			)),
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
			fill(Pressao(Dict{Symbol,Any}(
				:Brief=>"Fugacity in standard state",
				:Default=>1,
				:DisplayUnit=>"atm"
			)),(NComp)),
			Temperatura(Dict{Symbol,Any}(
				:Brief=>"Reference temperature",
				:Default=>298.15
			)),
			Volume(),
			fill(molweight()),
			CorrenteZ(Dict{Symbol,Any}(
				:Brief=>"Inlet stream",
				:PosX=>0,
				:PosY=>0,
				:Symbol=>"_{in}"
			)),
			CorrenteVap(Dict{Symbol,Any}(
				:Brief=>"Outlet stream",
				:PosX=>1,
				:PosY=>1,
				:Symbol=>"_{out}"
			)),
			fill(EntalpiaMol(Dict{Symbol,Any}(
				:Brief=>"Gibbs free-energy of formation"
			)),(NComp)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Equillibrium constant",
				:Lower=>0,
				:Default=>1.5
			)),(NReac)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Activity",
				:Symbol=>"\\hat{a}",
				:Lower=>0,
				:Default=>0.2
			)),(NComp)),
			fill(Reacao_mol(Dict{Symbol,Any}(
				:Brief=>"Overall component rate of reaction"
			)),(NComp)),
			fill(VazaoMolar(Dict{Symbol,Any}(
				:Brief=>"Extent of reaction",
				:Symbol=>"\\xi"
			)),(NReac)),
			fill(DanaReal(Dict{Symbol,Any}(
				:Brief=>"Fractional conversion of component",
				:Symbol=>"X",
				:Default=>0
			)),(NComp)),
			[
				:(Outlet.F*Outlet.z = Inlet.F*Inlet.z + rate*V*Mw),
				:(Outlet.P = Inlet.P),
				:(Outlet.F*Outlet.H = Inlet.F*Inlet.H),
				:(Outlet.F = Inlet.F + sum(sumt(stoic*extent)*Mw)),
				:(G = PP.IdealGasGibbsOfFormation(Outlet.T)),
				:(sumt(G*stoic(:,[1:NReac])) = -Rg*Outlet.T*ln(K([1:NReac]))),
				:(K([1:NReac]) = prod(activ^stoic(:,[1:NReac]))),
				:(Outlet.F*Outlet.z([1:NComp]) = (Inlet.F*Inlet.z([1:NComp]) + sumt(stoic([1:NComp],:)*extent)*Mw)),
				:(Outlet.F*Outlet.z([1:NComp]) = Inlet.F*Inlet.z([1:NComp])*(1 - conv([1:NComp]))),
				:(conv([1:NComp]) = 1),
				:(conv([1:NComp]) = 0),
				:(activ = PP.VapourFugacityCoefficient(Outlet.T,Outlet.P,Outlet.z)*Outlet.P*Outlet.z/fs),
			],
			[
				"Outlet stream","Mechanical equilibrium","Energy balance","Steady-state","Gibbs free-energy of formation","Gibbs free energy of reaction","Equilibrium constant","Outlet molar fraction","Molar conversion","Molar conversion","Molar conversion","Activity",
			],
			[:PP,:NReac,:stoic,:Rg,:fs,:To,:V,:Mw,],
			[:Inlet,:Outlet,:G,:K,:activ,:rate,:extent,:conv,]
		)
	end
	PP::DanaPlugin
	NReac::DanaInteger
	stoic::Array{DanaReal}
	Rg::DanaReal
	fs::Array{Pressao}
	To::Temperatura
	V::Volume
	Mw::Array{molweight}
	Inlet::CorrenteZ
	Outlet::CorrenteVap
	G::Array{EntalpiaMol}
	K::Array{DanaReal}
	activ::Array{DanaReal}
	rate::Array{Reacao_mol}
	extent::Array{VazaoMolar}
	conv::Array{DanaReal}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Equil_vap
function set(in::Equil_vap)
	Mw = PP.MolecularWeight()
	 
end
function setEquationFlow(in::Equil_vap)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	#	"Gibbs free-energy of formation without Cp correction"
	#	G = PP.IdealGasGibbsOfFormationAt25C()*Outlet.T/To
	#		+ PP.IdealGasEnthalpyOfFormationAt25C()*(1 - Outlet.T/To);
	addEquation(6)
	#		K(j) = exp(-sumt(G*stoic(:,j))/(Rg*Outlet.T));
	addEquation(7)
	addEquation(8)
	if (Inlet.z(i) > 1e-16) 
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
function atributes(in::Equil_vap,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/cstr"
	fields[:Brief]="Model of a generic vapour-phase equilibrium CSTR"
	fields[:Info]="
== Assumptions ==
* only vapour-phase
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
Equil_vap(_::Dict{Symbol,Any})=begin
	newModel=Equil_vap()
	newModel.attributes=atributes(newModel,_)
	newModel
end
