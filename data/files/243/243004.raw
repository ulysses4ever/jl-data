# Modelo de tanque de armazenamento com quatro alimentacoes e perdas
type Tanque4perdas
	Tanque4perdas()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Fracao(Dict{Symbol,Any}(
				:Brief=>"Fracao massica de perdas"
			)),
			VazaoMassica(),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in1}",
				:PosX=>0.1,
				:PosY=>0.16
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in2}",
				:PosX=>0.1,
				:PosY=>0.35
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in3}",
				:PosX=>0.1,
				:PosY=>0.55
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in4}",
				:PosX=>0.1,
				:PosY=>0.75
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{out}",
				:PosX=>1,
				:PosY=>0.45
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{perdas}",
				:PosX=>0.5,
				:PosY=>1
			)),
			[
				:(Fout.F = Fin1.F + Fin2.F + Fin3.F + Fin4.F - Fperda.F),
				:(Fsalida= Fin1.F + Fin2.F + Fin3.F + Fin4.F),
				:(Fperda.F=y*Fsalida),
				:(Fout.F * Fout.H = Fin1.F * Fin1.H + Fin2.F * Fin2.H + Fin3.F * Fin3.H + Fin4.F * Fin4.H - Fperda.F*Fperda.H),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
				:(Fperda.S = Fout.S),
				:(Fperda.T = Fout.T),
				:(Fperda.P = Fout.P),
				:(Fperda.H = Fout.H),
			],
			[
				"","","","","","","","","",
			],
			[:PP2,],
			[:y,:Fsalida,:Fin1,:Fin2,:Fin3,:Fin4,:Fout,:Fperda,]
		)
	end
	PP2::DanaPlugin
	y::Fracao
	Fsalida::VazaoMassica
	Fin1::Corrente 
	Fin2::Corrente 
	Fin3::Corrente 
	Fin4::Corrente 
	Fout::Corrente 
	Fperda::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Tanque4perdas
function setEquationFlow(in::Tanque4perdas)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
	addEquation(9)
end
function atributes(in::Tanque4perdas,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/tanque4perdas"
	drive!(fields,_)
	return fields
end
Tanque4perdas(_::Dict{Symbol,Any})=begin
	newModel=Tanque4perdas()
	newModel.attributes=atributes(newModel,_)
	newModel
end
