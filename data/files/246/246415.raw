# Modelo de bomba
type Bomba
	Bomba()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Entalpia(),
			Pot_sinal(Dict{Symbol,Any}(
				:Brief=>"Potencia do motor da bomba",
				:PosX=>0.5,
				:PosY=>1 
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia injetada pela bomba"
			)),
			Eficiencia(Dict{Symbol,Any}(
				:Brief=>"Eficiencia da bomba"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{in}"
			)),
			Corrente(Dict{Symbol,Any}(
				:Symbol=>"_{out}",
				:PosX=>0,
				:PosY=>0.2
			)),
			VolumeEspecifico(),
			[
				:(v_esp = PP2.Vesp(Fin.P,Fin.T)),
				:(H_IS = PP2.propPS(Fout.P,Fin.S)),
				:((Fout.H - Fin.H) * EF_B = H_IS - Fin.H),
				:([Fout.S,Fout.T] = PP2.propPH(Fout.P,Fout.H)),
				:(POT_EF = POT_BMB * EF_B),
				:(POT_EF = Fin.F * v_esp * (Fout.P - Fin.P)),
				:(Fout.F = Fin.F),
			],
			[
				"","","","","","","",
			],
			[:PP2,],
			[:H_IS,:POT_BMB,:POT_EF,:EF_B,:Fin,:Fout,:v_esp,]
		)
	end
	PP2::DanaPlugin
	H_IS::Entalpia
	POT_BMB::Pot_sinal
	POT_EF::Potencia
	EF_B::Eficiencia
	Fin::Corrente
	Fout::Corrente
	v_esp::VolumeEspecifico
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Bomba
function setEquationFlow(in::Bomba)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	#	(Fout.H - Fin.H) * Fin.F = POT_EF; # Forma alternativa
	addEquation(4)
	addEquation(5)
	addEquation(6)
	addEquation(7)
end
function atributes(in::Bomba,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/bomba1"
	drive!(fields,_)
	return fields
end
Bomba(_::Dict{Symbol,Any})=begin
	newModel=Bomba()
	newModel.attributes=atributes(newModel,_)
	newModel
end
