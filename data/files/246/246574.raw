# Modelo de turbina com sangria
type Turbina_sangra
	Turbina_sangra()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Entalpia(),
			Eficiencia(Dict{Symbol,Any}(
				:Brief=>"Eficiencia da turbina"
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia da turbina",
				:PosX=>0.9,
				:PosY=>0.45
			)),
			Fracao(Dict{Symbol,Any}(
				:Brief=>"Fracao massica da sangria"
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in}",
				:PosX=>0,
				:PosY=>0.25
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{out}",
				:PosX=>1,
				:PosY=>0.85
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{outx}",
				:PosX=>0.85,
				:PosY=>1
			)),
			[
				:(H_IS = PP2.propPS(Fout.P,Fin.S)),
				:(Fout.H = (H_IS - Fin.H) * EF_T + Fin.H),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
				:(Fin.F * (Fin.H - Fout.H) = POT_TURB),
				:(Fouts.F = Fin.F * y),
				:(Fout.F = Fin.F - Fouts.F),
				:(Fouts.P = Fout.P),
				:(Fouts.T = Fout.T),
				:(Fouts.S = Fout.S),
				:(Fouts.H = Fout.H),
			],
			[
				"","","","","","","","","","",
			],
			[:PP2,],
			[:H_IS,:EF_T,:POT_TURB,:y,:Fin,:Fout,:Fouts,]
		)
	end
	PP2::DanaPlugin
	H_IS::Entalpia
	EF_T::Eficiencia
	POT_TURB::Potencia
	y::Fracao
	Fin::Corrente 
	Fout::Corrente 
	Fouts::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Turbina_sangra
function setEquationFlow(in::Turbina_sangra)
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
end
function atributes(in::Turbina_sangra,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/turbina_sa"
	drive!(fields,_)
	return fields
end
Turbina_sangra(_::Dict{Symbol,Any})=begin
	newModel=Turbina_sangra()
	newModel.attributes=atributes(newModel,_)
	newModel
end
