# Modelo de trocador de calor, dada a carga termica
type Trocador
	Trocador()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Potencia(),
			Dif_Pres(),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in}"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{out}"
			)),
			[
				:(Fout.F = Fin.F),
				:(Fout.P = Fin.P - DP),
				:(Fout.F * (Fout.H - Fin.H) = Q),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
			],
			[
				"","","","",
			],
			[:PP2,],
			[:Q,:DP,:Fin,:Fout,]
		)
	end
	PP2::DanaPlugin
	Q::Potencia
	DP::Dif_Pres
	Fin::Corrente 
	Fout::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
end
export Trocador
function setEquationFlow(in::Trocador)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
end
