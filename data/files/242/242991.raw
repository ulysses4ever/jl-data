# Modelo de tanque de armazenamento com quatro alimentacoes
type Tanque4
	Tanque4()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in1}"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in2}"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in3}"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in4}"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out}"
			)),
			[
				:(Fout.F = Fin1.F + Fin2.F + Fin3.F + Fin4.F),
				:(Fout.F * Fout.H = Fin1.F * Fin1.H + Fin2.F * Fin2.H + Fin3.F * Fin3.H + Fin4.F * Fin4.H),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
			],
			[
				"","","",
			],
			[:PP2,],
			[:Fin1,:Fin2,:Fin3,:Fin4,:Fout,]
		)
	end
	PP2::DanaPlugin
	Fin1::Corrente 
	Fin2::Corrente 
	Fin3::Corrente 
	Fin4::Corrente 
	Fout::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
end
export Tanque4
function setEquationFlow(in::Tanque4)
	addEquation(1)
	addEquation(2)
	addEquation(3)
end
