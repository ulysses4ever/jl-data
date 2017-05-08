#-------------------------------------------------------------------
#* EMSO Model Library (EML) Copyright (C) 2004 - 2007 ALSOC.
#*
#* This LIBRARY is free software; you can distribute it and/or modify
#* it under the therms of the ALSOC FREE LICENSE as available at
#* http://www.enq.ufrgs.br/alsoc.
#*
#* EMSO Copyright (C) 2004 - 2007 ALSOC, original code
#* from http://www.rps.eng.br Copyright (C) 2002-2004.
#* All rights reserved.
#*
#* EMSO is distributed under the therms of the ALSOC LICENSE as
#* available at http://www.enq.ufrgs.br/alsoc.
#*--------------------------------------------------------------------
#* Author: Gerson Balbueno Bicca 
#* $Id: HeatExchangerDetailed.mso 197 2007-03-08 14:31:57Z bicca $
#*------------------------------------------------------------------
type ShellandTubes_LMTD
	ShellandTubes_LMTD()=begin
		new(
			ShellandTubesBasic(),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"LMTD Correction Factor Model",
				:Valid=>["Bowmann","Fakeri" , "User Specified"],
				:Default=>"Bowmann"
			)),
			fraction(Dict{Symbol,Any}(
				:Default=>0.8
			)),
			LMTD_Basic(),
			positive(Dict{Symbol,Any}(
				:Brief=>" Capacity Ratio for LMTD Correction Fator",
				:Lower=>1e-6
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Non - Dimensional Variable for LMTD Correction Fator ",
				:Lower=>1e-6
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Non - Dimensional Variable for LMTD Correction Fator when 2 Pass Shell Side",
				:Lower=>1e-6
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Non - Dimensional Variable for LMTD Correction Fator in Fakeri Equation",
				:Lower=>1e-6
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Non - Dimensional Variable for LMTD Correction Fator in Fakeri Equation",
				:Lower=>1e-6
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Non - Dimensional Variable for LMTD Correction Fator in Fakeri Equation when 2 Pass Shell Side",
				:Lower=>1e-6
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Non - Dimensional Variable for LMTD Correction Fator in Fakeri Equationwhen 2 Pass Shell Side",
				:Lower=>1e-6
			)),
			[
				:(_base_1.Details.Q = _base_1.Details.Ud*_base_1.Pi*_base_1.Tubes.TubeOD*_base_1.Tubes.NumberOfTubes*_base_1.Tubes.TubeLength*Method.LMTD*Method.Fc),
				:(Phi*(2*((_base_1.InletShell.T+ _base_1.OutletShell.T)-(_base_1.InletTube.T+ _base_1.OutletTube.T))) = (sqrt(((_base_1.InletShell.T- _base_1.OutletShell.T)*(_base_1.InletShell.T- _base_1.OutletShell.T))+((_base_1.OutletTube.T - _base_1.InletTube.T)*(_base_1.OutletTube.T - _base_1.InletTube.T))))),
				:(R*(_base_1.OutletTube.T - _base_1.InletTube.T ) = (_base_1.InletShell.T-_base_1.OutletShell.T)),
				:(P*(_base_1.InletShell.T- _base_1.InletTube.T)= (_base_1.OutletTube.T-_base_1.InletTube.T)),
				:(Method.DT0 = _base_1.InletShell.T - _base_1.OutletTube.T),
				:(Method.DTL = _base_1.OutletShell.T - _base_1.InletTube.T),
				:(Phi*(2*((_base_1.InletShell.T+ _base_1.OutletShell.T)-(_base_1.InletTube.T+ _base_1.OutletTube.T))) = (sqrt(((_base_1.InletShell.T- _base_1.OutletShell.T)*(_base_1.InletShell.T- _base_1.OutletShell.T))+((_base_1.OutletTube.T - _base_1.InletTube.T)*(_base_1.OutletTube.T - _base_1.InletTube.T))))),
				:(R*(_base_1.OutletShell.T - _base_1.InletShell.T ) = (_base_1.InletTube.T-_base_1.OutletTube.T)),
				:(P*(_base_1.InletTube.T- _base_1.InletShell.T)= (_base_1.OutletShell.T-_base_1.InletShell.T)),
				:(Method.DT0 = _base_1.InletTube.T - _base_1.OutletShell.T),
				:(Method.DTL = _base_1.OutletTube.T - _base_1.InletShell.T),
				:(Method.Fc = FLMTDcorrection),
				:(lambdaN =1),
				:(lambda1 =1),
				:(Rho =1),
				:(Pc = P),
				:(lambdaN =1),
				:(lambda1 =1),
				:(Rho =1),
				:(Pc*(2-P)= P),
				:(Method.Fc= (sqrt(2)*Pc)/((1-Pc)*ln( abs( ( 2-Pc*0.585786)/( 2-Pc*3.414214))))),
				:(Pc = (sqrt(abs(( 1-P*R)/(1-P)))-1)/(sqrt(abs(( 1-P*R)/(1-P)))-R)),
				:(Method.Fc = sqrt(R*R+1)*ln(abs((1-Pc*R)/(1-Pc)))/((1-R)*ln( abs( ( 2-Pc*(R+1-sqrt(R*R+1)))/ ( 2-Pc*(R + 1 + sqrt(R*R+1))))))),
				:(Pc = P),
				:(Rho*(1-P*R) = (1-P)),
				:(lambdaN = 1),
				:(lambda1 = 1),
				:(Method.Fc = (2*Phi )/(ln(abs((1+Phi )/(1-Phi ))))),
				:(lambdaN = (1/ln(sqrt(abs(Rho))))*((2*sqrt(abs(Rho))-2)/(sqrt(abs(Rho))+1))),
				:(lambda1 = (1/ln(abs(Rho)))*((2*Rho-2)/(Rho+1))),
				:(Method.Fc = ((2*Phi *(lambdaN/lambda1))/(ln(abs((1+Phi *(lambdaN/lambda1))/(1-Phi *(lambdaN/lambda1))))))*(1/lambdaN)),
				:(lambdaN =1),
				:(lambda1 =1),
				:(Pc = P),
				:(Method.Fc = FLMTDcorrection),
				:(Rho =1),
				:(Rho = 1),
				:(Method.Fc = (sqrt(2)*P)/((1-P)*ln( abs( ( 2-P*0.585786)/( 2-P*3.414214))))),
				:(Method.Fc = sqrt(R*R+1)*ln(abs((1-P*R)/(1-P)))/((1-R)*ln( abs( ( 2-P*(R+1-sqrt(R*R+1)))/ ( 2-P*(R + 1 + sqrt(R*R+1))))))),
				:(Rho*(1-P*R) = (1-P)),
				:(Method.Fc = (4*Phi)/(ln(abs((1+2*Phi)/(1-2*Phi))))),
				:(Method.Fc = (2*Phi*(Rho+1)*ln(abs(Rho)))/( ln(abs((1+2*Phi)/(1-2*Phi)))*(Rho-1))),
			],
			[
				"Exchange Surface Area","Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation ","R: Capacity Ratio for LMTD Correction Fator","P: Non - Dimensional Variable for LMTD Correction Fator","Temperature Difference at Inlet","Temperature Difference at Outlet","Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation ","R: Capacity Ratio for LMTD Correction Fator","P: Non - Dimensional Variable for LMTD Correction Fator","Temperature Difference at Inlet","Temperature Difference at Outlet",""," Variable not in use with this equation"," Variable not in use with this equation"," Variable not in use with this equation"," Variable not in use with this equation"," Variable not in use with Bowmann equation"," Variable not in use with Bowmann equation"," Variable not in use with Bowmann equation","Non Dimensional Variable for LMTD Correction Fator when 2 Pass Shell Side","LMTD Correction Fator when 2 Pass Shell Side","Non Dimensional Variable for LMTD Correction Fator when 2 Pass Shell Side","LMTD Correction Fator when 2 Pass Shell Side"," Variable not in use with Fakeri equation","Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation"," Variable not in use when Rho = 1"," Variable not in use when Rho = 1","LMTD Correction Fator when 2 Pass Shell Side","Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation","Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation","LMTD Correction Fator when 2 Pass Shell Side"," Variable not in use when 1 Pass Shell Side"," Variable not in use when 1 Pass Shell Side"," Variable not in use when 1 Pass Shell Side",""," Variable not in use with this equation"," Variable not in use with Bowmann equation","LMTD Correction Fator when 1 Pass Shell Side","LMTD Correction Fator when 1 Pass Shell Side","Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation","LMTD Correction Fator when 1 Pass Shell Side","LMTD Correction Fator when 1 Pass Shell Side",
			],
			[:LMTDcorrection,:FLMTDcorrection,],
			[:Method,:R,:P,:Pc,:Rho,:Phi,:lambdaN,:lambda1,]
		)
	end
	_base_1::ShellandTubesBasic
	LMTDcorrection::DanaSwitcher
	FLMTDcorrection::fraction
	Method::LMTD_Basic
	R::positive
	P::positive
	Pc::positive
	Rho::positive
	Phi::positive
	lambdaN::positive
	lambda1::positive
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export ShellandTubes_LMTD
function setEquationFlow(in::ShellandTubes_LMTD)
	addEquation(1)
	let switch=HotSide
		if HotSide==InletTube.T > InletShell.T
			set(switch,"tubes")
		end
		if HotSide==InletTube.T < InletShell.T
			set(switch,"shell")
		end
		if switch=="shell"
			addEquation(2)
			addEquation(3)
			addEquation(4)
			addEquation(5)
			addEquation(6)
		elseif switch=="tubes"
			addEquation(7)
			addEquation(8)
			addEquation(9)
			addEquation(10)
			addEquation(11)
		end
	end
	let switch=ShellType
		if switch=="Fshell"
			let switch=LMTDcorrection
				if switch=="User Specified"
					#Just For Initialization
					addEquation(12)
					addEquation(13)
					addEquation(14)
					#" Variable not in use with this equation"
					#	Phi = 1;
					addEquation(15)
					addEquation(16)
				elseif switch=="Bowmann"
					addEquation(17)
					addEquation(18)
					#" Variable not in use with Bowmann equation"
					#	Phi = 1;
					addEquation(19)
					if R == 1 
						addEquation(20)
						addEquation(21)
					else
						addEquation(22)
						addEquation(23)
					end
				elseif switch=="Fakeri"
					addEquation(24)
					addEquation(25)
					#"Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation "
					#	Phi = (sqrt(((Inlet.Hot.T - Outlet.Hot.T)*(Inlet.Hot.T- Outlet.Hot.T))+((Outlet.Cold.T -  Inlet.Cold.T)*(Outlet.Cold.T -  Inlet.Cold.T))))/(2*((Inlet.Hot.T + Outlet.Hot.T)-( Inlet.Cold.T + Outlet.Cold.T)));
					if Rho == 1 
						addEquation(26)
						addEquation(27)
						addEquation(28)
					else
						addEquation(29)
						addEquation(30)
						addEquation(31)
					end
				end
			end
		elseif switch=="Eshell"
			addEquation(32)
			addEquation(33)
			addEquation(34)
			let switch=LMTDcorrection
				if switch=="User Specified"
					#Just For Initialization
					addEquation(35)
					#" Variable not in use with this equation"
					#	lambdaN =1;
					#" Variable not in use with this equation"
					#	lambda1 =1;
					#" Variable not in use with this equation"
					#	Phi = 1;
					addEquation(36)
				elseif switch=="Bowmann"
					#" Variable not in use with Bowmann equation"
					#	Phi  = 1;
					addEquation(37)
					if R == 1 
						addEquation(38)
					else
						addEquation(39)
					end
				elseif switch=="Fakeri"
					#"Non Dimensional Variable for LMTD Correction Fator in Fakeri Equation "
					#	Phi  = (sqrt(((Inlet.Hot.T- Outlet.Hot.T)*(Inlet.Hot.T- Outlet.Hot.T))+((Outlet.Cold.T - Inlet.Cold.T)*(Outlet.Cold.T - Inlet.Cold.T))))/(2*((Inlet.Hot.T+ Outlet.Hot.T)-(Inlet.Cold.T+ Outlet.Cold.T)));
					addEquation(40)
					if Rho == 1 
						addEquation(41)
					else
						addEquation(42)
					end
				end
			end
		end
	end
end
function atributes(in::ShellandTubes_LMTD,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/STHE"
	fields[:Brief]="Shell and Tubes Heat Exchangers"
	fields[:Info]="to be documented."
	drive!(fields,_)
	return fields
end
ShellandTubes_LMTD(_::Dict{Symbol,Any})=begin
	newModel=ShellandTubes_LMTD()
	newModel.attributes=atributes(newModel,_)
	newModel
end
