# Modelo de flash provis򱨯rio, pois o PP tem cૣlculo de flash mas
# esta fun袯⭠o n⭠o est� disponibilizada no plugin (esta fun袯⭠o seria mais
# eficiente nos cૣlculos, n⭠o teria cૣlculos repetitivos)
type ETA_CICLO
	ETA_CICLO()=begin
		new(
			Eficiencia(),
			Pot_sinal(Dict{Symbol,Any}(
				:Symbol=>"_{inB1}",
				:PosX=>0.2,
				:PosY=>0
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Symbol=>"_{inB2}",
				:PosX=>0.4,
				:PosY=>0
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Symbol=>"_{inB3}",
				:PosX=>0.6,
				:PosY=>0
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Symbol=>"_{inB4}",
				:PosX=>0.8,
				:PosY=>0
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Symbol=>"_{inB5}",
				:PosX=>0.25,
				:PosY=>1
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Symbol=>"_{inGE}",
				:PosX=>0.5,
				:PosY=>1
			)),
			Pot_sinal(Dict{Symbol,Any}(
				:Symbol=>"_{inGV}",
				:PosX=>0.75,
				:PosY=>1
			)),
			[
				:(EF_CIC * POT_GV = POT_GE - POT_BMB1 - POT_BMB2 - POT_BMB3 - POT_BMB4 - POT_BMB5),
			],
			[
				"Eficiencia do Ciclo",
			],
			[:EF_CIC,:POT_BMB1,:POT_BMB2,:POT_BMB3,:POT_BMB4,:POT_BMB5,:POT_GE,:POT_GV,]
		)
	end
	EF_CIC::Eficiencia
	POT_BMB1::Pot_sinal
	POT_BMB2::Pot_sinal
	POT_BMB3::Pot_sinal
	POT_BMB4::Pot_sinal
	POT_BMB5::Pot_sinal
	POT_GE::Pot_sinal
	POT_GV::Pot_sinal
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export ETA_CICLO
function setEquationFlow(in::ETA_CICLO)
	addEquation(1)
end
function atributes(in::ETA_CICLO,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/eficiencia"
	drive!(fields,_)
	return fields
end
ETA_CICLO(_::Dict{Symbol,Any})=begin
	newModel=ETA_CICLO()
	newModel.attributes=atributes(newModel,_)
	newModel
end
