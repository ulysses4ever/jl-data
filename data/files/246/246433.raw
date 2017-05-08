# Modelo de condensador com duas alimentacoes
type Condensador_2alim
	Condensador_2alim()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Potencia (Dict{Symbol,Any}(
				:Brief=>"Taxa de calor removido"
			)),
			Dif_Temp (Dict{Symbol,Any}(
				:Brief=>"Grau de sub-resfriamento"
			)),
			Corrente (Dict{Symbol,Any}(
				:Brief=>"Corrente com pressao igual a saida",
				:Symbol=>"_{in1}"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in2}"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{out}"
			)),
			[
				:(Fout.P = Fin1.P),
				:(Fout.T = PP2.Tsat(Fout.P) - G_S),
				:([Fout.S,Fout.H] = PP2.propPTl(Fout.P,Fout.T)),
				:(Fout.F = Fin1.F + Fin2.F),
				:(Q_COND = Fin1.F * Fin1.H + Fin2.F * Fin2.H - Fout.F * Fout.H),
			],
			[
				"","","","","",
			],
			[:PP2,],
			[:Q_COND,:G_S,:Fin1,:Fin2,:Fout,]
		)
	end
	PP2::DanaPlugin
	Q_COND::Potencia 
	G_S::Dif_Temp 
	Fin1::Corrente 
	Fin2::Corrente 
	Fout::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
end
export Condensador_2alim
function setEquationFlow(in::Condensador_2alim)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
end
