# Modelo de separador de corrente de 4 saidas
type Splitter4
	Splitter4()=begin
		new(
			fill(Fracao(Dict{Symbol,Any}(
				:Brief=>"Fracao de massa"
			)),(3)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in}",
				:PosX=>1,
				:PosY=>0.5
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out1}",
				:PosX=>0,
				:PosY=>0.19
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out2}",
				:PosX=>0,
				:PosY=>0.4
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out3}",
				:PosX=>0,
				:PosY=>0.62
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out4}",
				:PosX=>0,
				:PosY=>0.85
			)),
			[
				:(Fout1.P = Fin.P),
				:(Fout1.T = Fin.T),
				:(Fout1.S = Fin.S),
				:(Fout1.H = Fin.H),
				:(Fout2.P = Fin.P),
				:(Fout2.T = Fin.T),
				:(Fout2.S = Fin.S),
				:(Fout2.H = Fin.H),
				:(Fout3.P = Fin.P),
				:(Fout3.T = Fin.T),
				:(Fout3.S = Fin.S),
				:(Fout3.H = Fin.H),
				:(Fout4.P = Fin.P),
				:(Fout4.T = Fin.T),
				:(Fout4.S = Fin.S),
				:(Fout4.H = Fin.H),
				:(Fout1.F = Fin.F * y(1)),
				:(Fout2.F = Fin.F * y(2)),
				:(Fout3.F = Fin.F * y(3)),
				:(Fout4.F = Fin.F - Fout1.F - Fout2.F - Fout3.F),
			],
			[
				"","","","","","","","","","","","","","","","","","","","",
			],
			[:y,:Fin,:Fout1,:Fout2,:Fout3,:Fout4,]
		)
	end
	y::Array{Fracao}
	Fin::Corrente 
	Fout1::Corrente 
	Fout2::Corrente
	Fout3::Corrente 
	Fout4::Corrente
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Splitter4
function setEquationFlow(in::Splitter4)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
	addEquation(8)
	addEquation(9)
	addEquation(10)
	addEquation(11)
	addEquation(12)
	addEquation(13)
	addEquation(14)
	addEquation(15)
	addEquation(16)
	addEquation(17)
	addEquation(18)
	addEquation(19)
	#Fout4.F = Fin.F * y(4);
	addEquation(20)
end
function atributes(in::Splitter4,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/splitter4"
	drive!(fields,_)
	return fields
end
Splitter4(_::Dict{Symbol,Any})=begin
	newModel=Splitter4()
	newModel.attributes=atributes(newModel,_)
	newModel
end
