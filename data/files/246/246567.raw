# Modelo de turbina sem sangria
type Turbina
	Turbina()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Entalpia(),
			Eficiencia(Dict{Symbol,Any}(
				:Brief=>"Eficiencia da turbina"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in}",
				:PosX=>0,
				:PosY=>0.25
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia da turbina",
				:PosX=>1,
				:PosY=>0.5
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out}",
				:PosX=>1,
				:PosY=>1
			)),
			[
				:(H_IS = PP2.propPS(Fout.P,Fin.S)),
				:(Fout.H = (H_IS - Fin.H) * EF_T + Fin.H),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
				:(Fin.F * (Fin.H - Fout.H) = POT_TURB),
				:(Fout.F = Fin.F),
			],
			[
				"","","","","",
			],
			[:PP2,],
			[:H_IS,:EF_T,:Fin,:POT_TURB,:Fout,]
		)
	end
	PP2::DanaPlugin
	H_IS::Entalpia
	EF_T::Eficiencia
	Fin::Corrente
	POT_TURB::Potencia
	Fout::Corrente
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Turbina
function setEquationFlow(in::Turbina)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	addEquation(5)
end
function atributes(in::Turbina,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/turbina"
	drive!(fields,_)
	return fields
end
Turbina(_::Dict{Symbol,Any})=begin
	newModel=Turbina()
	newModel.attributes=atributes(newModel,_)
	newModel
end
