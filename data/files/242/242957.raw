# Modelo de tanque de armazenamento com dois alimentacoes
type Tanque2
	Tanque2()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in1}",
				:PosX=>0.1,
				:PosY=>0.20
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in2}",
				:PosX=>0.1,
				:PosY=>0.79
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out}",
				:PosX=>0.9,
				:PosY=>0.5
			)),
			[
				:(Fout.F = Fin1.F + Fin2.F),
				:(Fout.F * Fout.H = Fin1.F * Fin1.H + Fin2.F * Fin2.H),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
			],
			[
				"","","",
			],
			[:PP2,],
			[:Fin1,:Fin2,:Fout,]
		)
	end
	PP2::DanaPlugin
	Fin1::Corrente 
	Fin2::Corrente 
	Fout::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Tanque2
function setEquationFlow(in::Tanque2)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
function atributes(in::Tanque2,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/tanque2"
	drive!(fields,_)
	return fields
end
Tanque2(_::Dict{Symbol,Any})=begin
	newModel=Tanque2()
	newModel.attributes=atributes(newModel,_)
	newModel
end
