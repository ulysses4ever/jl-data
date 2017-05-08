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
#* $Id: Hairpin.mso  Z bicca $
#*------------------------------------------------------------------
type Hairpin_NTU
	Hairpin_NTU()=begin
		new(
			Hairpin_Basic(),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Flow Direction",
				:Valid=>["counter","cocurrent"],
				:Default=>"cocurrent"
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Effectiveness estimate",
				:Default=>0.5
			)),
			NTU_Basic (Dict{Symbol,Any}(
				:Brief=>"NTU Method of Calculation",
				:Symbol=>" "
			)),
			[
				:(Method.Eft1 = 1),
				:(Method.NTU*Method.Cmin = _base_1.Details.Ud*_base_1.Pi*_base_1.DoInner*(2*_base_1.Lpipe)),
				:(Method.Cmin = min([Method.Ch,Method.Cc])),
				:(Method.Cmax = max([Method.Ch,Method.Cc])),
				:(Method.Cr = Method.Cmin/Method.Cmax),
				:(Method.Eft = 1-exp(-Method.NTU)),
				:(Method.Eft = (1-exp(-Method.NTU*(1+Method.Cr)))/(1+Method.Cr)),
				:(Method.Eft = 1),
				:(Method.NTU*(Method.Cr-1.00001) = ln(abs((Method.Eft-1.00001))) - ln(abs((Method.Cr*Method.Eft-1.00001)))),
				:(Method.NTU = 1),
				:(Method.Cmin = min([Method.Ch,Method.Cc])),
				:(Method.Cmax = max([Method.Ch,Method.Cc])),
				:(Method.Cr = 1),
				:(Method.Eft = Eftestimated),
				:(_base_1.Details.Q = Method.Eft*Method.Cmin*(_base_1.InletOuter.T-_base_1.InletInner.T)),
				:(_base_1.Details.Q = _base_1.Qestimated),
				:(Method.Ch = _base_1.InletOuter.F*_base_1.Outer.Properties.Average.Cp),
				:(Method.Cc = _base_1.InletInner.F*_base_1.Inner.Properties.Average.Cp),
				:(_base_1.Details.Q = Method.Eft*Method.Cmin*(_base_1.InletInner.T-_base_1.InletOuter.T)),
				:(_base_1.Details.Q = _base_1.Qestimated),
				:(Method.Cc = _base_1.InletOuter.F*_base_1.Outer.Properties.Average.Cp),
				:(Method.Ch = _base_1.InletInner.F*_base_1.Inner.Properties.Average.Cp),
			],
			[
				"Effectiveness Correction","Number of Units Transference","Minimum Heat Capacity","Maximum Heat Capacity","Thermal Capacity Ratio","Effectiveness","Effectiveness in Cocurrent Flow","Effectiveness in Counter Flow","Effectiveness in Counter Flow","Number of Units Transference","Minimum Heat Capacity","Maximum Heat Capacity","Thermal Capacity Ratio","Effectiveness","Duty","Duty","Hot Stream Heat Capacity","Cold Stream Heat Capacity","Duty","Duty","Cold Stream Heat Capacity","Hot Stream Heat Capacity",
			],
			[:FlowDirection,:Eftestimated,],
			[:Method,]
		)
	end
	_base_1::Hairpin_Basic
	FlowDirection::DanaSwitcher 
	Eftestimated::positive 
	Method::NTU_Basic 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export Hairpin_NTU
function setEquationFlow(in::Hairpin_NTU)
	addEquation(1)
	let switch=CalculationApproach
		if switch=="Full"
			addEquation(2)
			addEquation(3)
			addEquation(4)
			addEquation(5)
			if Method.Cr == 0 
				addEquation(6)
			else
				let switch=FlowDirection
					if switch=="cocurrent"
						addEquation(7)
					elseif switch=="counter"
						if Method.Eft >= 1 
							addEquation(8)
						else
							addEquation(9)
						end
					end
				end
			end
		elseif switch=="Simplified"
			addEquation(10)
			addEquation(11)
			addEquation(12)
			addEquation(13)
			addEquation(14)
		end
	end
	let switch=HotSide
		if HotSide==InletInner.T > InletOuter.T
			set(switch,"inner")
		end
		if HotSide==InletInner.T < InletOuter.T
			set(switch,"outer")
		end
		if switch=="outer"
			let switch=CalculationApproach
				if switch=="Full"
					addEquation(15)
				elseif switch=="Simplified"
					addEquation(16)
				end
			end
			addEquation(17)
			addEquation(18)
		elseif switch=="inner"
			let switch=CalculationApproach
				if switch=="Full"
					addEquation(19)
				elseif switch=="Simplified"
					addEquation(20)
				end
			end
			addEquation(21)
			addEquation(22)
		end
	end
end
function atributes(in::Hairpin_NTU,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Icon]="icon/hairpin"
	fields[:Pallete]=true
	fields[:Brief]="Hairpin Heat Exchanger - NTU Method"
	fields[:Info]="to be documented."
	drive!(fields,_)
	return fields
end
Hairpin_NTU(_::Dict{Symbol,Any})=begin
	newModel=Hairpin_NTU()
	newModel.attributes=atributes(newModel,_)
	newModel
end
