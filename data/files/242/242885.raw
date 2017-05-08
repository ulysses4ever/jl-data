# Modelo de desaerador (tanque) com 5 entradas e sa죡da l찵quido saturado (x=0)
type Desaerador5
	Desaerador5()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in1}",
				:PosX=>1,
				:PosY=>0.2
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in2}",
				:PosX=>1,
				:PosY=>0.45
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in3}",
				:PosX=>1,
				:PosY=>0.7
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in4}",
				:PosX=>1,
				:PosY=>0.9
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in5}",
				:PosX=>0.5,
				:PosY=>0
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out}",
				:PosX=>0,
				:PosY=>0.85
			)),
			[
				:(Fout.F = Fin1.F + Fin2.F + Fin3.F + Fin4.F + Fin5.F),
				:(Fout.F * Fout.H = Fin1.F * Fin1.H + Fin2.F * Fin2.H + Fin3.F * Fin3.H + Fin4.F * Fin4.H + Fin5.F * Fin5.H),
				:([Fout.S,Fout.H] = PP2.propPTl(Fout.P,Fout.T)),
			],
			[
				"","","",
			],
			[:PP2,],
			[:Fin1,:Fin2,:Fin3,:Fin4,:Fin5,:Fout,]
		)
	end
	PP2::DanaPlugin
	Fin1::Corrente 
	Fin2::Corrente 
	Fin3::Corrente 
	Fin4::Corrente 
	Fin5::Corrente 
	Fout::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Desaerador5
function setEquationFlow(in::Desaerador5)
	addEquation(1)
	addEquation(2)
	#Fout.T = PP2.Tsat(Fout.P);
	addEquation(3)
end
function atributes(in::Desaerador5,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/desaerador"
	drive!(fields,_)
	return fields
end
Desaerador5(_::Dict{Symbol,Any})=begin
	newModel=Desaerador5()
	newModel.attributes=atributes(newModel,_)
	newModel
end
