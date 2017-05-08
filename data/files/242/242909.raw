# Modelo de flash provis򱨯rio, pois o PP tem cૣlculo de flash mas
# esta fun袯⭠o n⭠o est� disponibilizada no plugin (esta fun袯⭠o seria mais
# eficiente nos cૣlculos, n⭠o teria cૣlculos repetitivos)
type Flash
	Flash()=begin
		PP2=outers.PP2
		new(
			DanaPlugin(Dict{Symbol,Any}(
				:Brief=>"Steam tables"
			)),
			Fracao (Dict{Symbol,Any}(
				:Upper=>2
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{in}",
				:PosX=>1,
				:PosY=>0.5
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{outL}",
				:PosX=>0.4,
				:PosY=>1
			)),
			Corrente (Dict{Symbol,Any}(
				:Symbol=>"_{outV}",
				:PosX=>0.4,
				:PosY=>0
			)),
			[
				:(Fin.F = FoutL.F + FoutV.F),
				:(FoutV.F = TIT * Fin.F),
				:(FoutL.T = FoutV.T),
				:(FoutL.P = FoutV.P),
				:([FoutL.S,FoutL.H,FoutV.S,FoutV.H,FoutL.T,TIT] = PP2.FlashPH(FoutL.P,Fin.H)),
			],
			[
				"","","","","",
			],
			[:PP2,],
			[:TIT,:Fin,:FoutL,:FoutV,]
		)
	end
	PP2::DanaPlugin
	TIT::Fracao 
	Fin::Corrente 
	FoutL::Corrente 
	FoutV::Corrente 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Flash
function setEquationFlow(in::Flash)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	#	[S_ad,FoutL.T] = PP2.propPH(FoutL.P,Fin.H);
	#	[FoutV.S,FoutV.H] = PP2.propPTv(FoutV.P,FoutV.T+0.1*'K'); # perturbado para evitar ir para liq.
	#	[FoutL.S,FoutL.H] = PP2.propPTl(FoutL.P,FoutL.T-0.1*'K'); # perturbado para evitar ir para vap.
	addEquation(5)
	#	TIT * (FoutV.H - FoutL.H) = Fin.H - FoutL.H;
	
end
function atributes(in::Flash,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/flash"
	drive!(fields,_)
	return fields
end
Flash(_::Dict{Symbol,Any})=begin
	newModel=Flash()
	newModel.attributes=atributes(newModel,_)
	newModel
end
