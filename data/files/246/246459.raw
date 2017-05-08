# Modelo de gerador eletrico
type Gerador_Eletrico
	Gerador_Eletrico()=begin
		new(
			Eficiencia(Dict{Symbol,Any}(
				:Brief=>"Eficiencia do gerador eletrico"
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Brief=>"Potencia do gerador eletrico",
				:PosX=>1,
				:PosY=>0.5
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia total das turbinas"
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia total da turbina",
				:PosX=>0,
				:PosY=>0.5
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia total da turbina",
				:PosX=>0.02,
				:PosY=>0.25
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia total da turbina",
				:PosX=>0.02,
				:PosY=>0.75
			)),
			Potencia(Dict{Symbol,Any}(
				:Brief=>"Potencia total da turbina",
				:PosX=>0.5,
				:PosY=>1
			)),
			[
				:(POT_TURB = POT_TURB1 + POT_TURB2 + POT_TURB3 + POT_TURB4),
				:(POT_GE = EF_GE * POT_TURB),
			],
			[
				"Potencia total das turbinas","Potencia do Gerador Eletrico",
			],
			[:EF_GE,],
			[:POT_GE,:POT_TURB,:POT_TURB1,:POT_TURB2,:POT_TURB3,:POT_TURB4,]
		)
	end
	EF_GE::Eficiencia
	POT_GE::Pot_sinal
	POT_TURB::Potencia
	POT_TURB1::Potencia
	POT_TURB2::Potencia
	POT_TURB3::Potencia
	POT_TURB4::Potencia
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Gerador_Eletrico
function setEquationFlow(in::Gerador_Eletrico)
	addEquation(1)
	addEquation(2)
end
function atributes(in::Gerador_Eletrico,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/gerador"
	drive!(fields,_)
	return fields
end
Gerador_Eletrico(_::Dict{Symbol,Any})=begin
	newModel=Gerador_Eletrico()
	newModel.attributes=atributes(newModel,_)
	newModel
end
