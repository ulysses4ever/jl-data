# Modelo de tanque de armazenamento com tres alimentacoes e perdas
type Tanque3
	Tanque3()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
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
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{perda}"
			)),
			[
				:(Fout.F = Fin1.F + Fin2.F + Fin3.F - Fperda.F),
				:(Fout.F * Fout.H = Fin1.F * Fin1.H + Fin2.F * Fin2.H + Fin3.F * Fin3.H - Fperda.F*Fperda.H),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
				:(Fperda.S = Fout.S),
				:(Fperda.T = Fout.T),
				:(Fperda.P = Fout.P),
				:(Fperda.H = Fout.H),
			],
			[
				"","","","","","","",
			],
			[:PP2,],
			[:Fin1,:Fin2,:Fin3,:Fout,:Fperda,]
		)
	end
	PP2::DanaPlugin
	Fin1::Corrente 
	Fin2::Corrente 
	Fin3::Corrente 
	Fout::Corrente 
	Fperda::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
end
export Tanque3
function setEquationFlow(in::Tanque3)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
end
