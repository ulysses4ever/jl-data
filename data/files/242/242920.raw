# Modelo de gerador eletrico
type Gerador_Eletrico_Simples
	Gerador_Eletrico_Simples()=begin
		new(
			Eficiencia(Dict{Symbol,Any}(
				:Brief=>"Eficiencia do gerador eletrico"
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Brief=>"Potencia do gerador eletrico",
				:PosX=>1,
				:PosY=>0.5
			)),
			[:EF_GE,],
			[:POT_GE,]
		)
	end
	EF_GE::Eficiencia
	POT_GE::Pot_sinal
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Gerador_Eletrico_Simples
function atributes(in::Gerador_Eletrico_Simples,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/gerador"
	drive!(fields,_)
	return fields
end
Gerador_Eletrico_Simples(_::Dict{Symbol,Any})=begin
	newModel=Gerador_Eletrico_Simples()
	newModel.attributes=atributes(newModel,_)
	newModel
end
