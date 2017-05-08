# Modelo de tanque de armazenamento com tres alimentacoes
type Tanque
	Tanque()=begin
		propterm=outers.propterm
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables",
				:Type=>"water"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in1}"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in2}"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in3}"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{out}"
			)),
			[
				:(Fout.F = Fin1.F + Fin2.F + Fin3.F),
				:(Fout.F * Fout.H = Fin1.F * Fin1.H + Fin2.F * Fin2.H + Fin3.F * Fin3.H),
				:([Fout.S,Fout.T] = propterm.propPH(Fout.P,Fout.H)),
			],
			[
				"","","",
			],
			[:propterm,],
			[:Fin1,:Fin2,:Fin3,:Fout,]
		)
	end
	propterm::DanaPlugin
	Fin1::Corrente 
	Fin2::Corrente 
	Fin3::Corrente 
	Fout::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Tanque
function setEquationFlow(in::Tanque)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function atributes(in::Tanque,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/tanque2"
	drive!(fields,_)
	return fields
end
Tanque(_::Dict{Symbol,Any})=begin
	newModel=Tanque()
	newModel.attributes=atributes(newModel,_)
	newModel
end
