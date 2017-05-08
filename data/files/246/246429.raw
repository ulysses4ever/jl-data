# Modelo de condensador com uma alimentacao
type Condensador
	Condensador()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Taxa de calor removido",
				:PosX=>1,
				:PosY=>0.5
			)),
			Dif_Temp(Dict{Symbol,Any}(
				:Brief=>"Grau de sub-resfriamento"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in}",
				:PosX=>0.5,
				:PosY=>0
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out}",
				:PosX=>0.5,
				:PosY=>1
			)),
			[
				:(Fout.P = Fin.P),
				:(Fout.T = PP2.Tsat(Fout.P) - G_S),
				:([Fout.S,Fout.H] = PP2.propPTl(Fout.P,Fout.T)),
				:(Q_COND = Fin.F * (Fin.H - Fout.H)),
				:(Fout.F = Fin.F),
			],
			[
				"","","","","",
			],
			[:PP2,],
			[:Q_COND,:G_S,:Fin,:Fout,]
		)
	end
	PP2::DanaPlugin
	Q_COND::Potencia 
	G_S::Dif_Temp 
	Fin::Corrente 
	Fout::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Condensador
function setEquationFlow(in::Condensador)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
end
function atributes(in::Condensador,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/condensador"
	drive!(fields,_)
	return fields
end
Condensador(_::Dict{Symbol,Any})=begin
	newModel=Condensador()
	newModel.attributes=atributes(newModel,_)
	newModel
end
