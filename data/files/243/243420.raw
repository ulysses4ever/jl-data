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
#* Author: Tiago Os��io
#* $Id$
#*-------------------------------------------------------------------
type PID
	PID()=begin
		[
			:(PID_intTerm = 0),
			:(diff(PID_dFilt) = 0/"s"),
			:(diff(PID_inputFilt) = 0/"s"),
			:(diff(PID_setPointFilt) = 0/"s"),
		],
		[
			"","","","",
		],
		new(
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Type of PID Incremental",
				:Valid=>["Ideal","Parallel","Series","Ideal_AWBT","Parallel_AWBT","Series_AWBT","Ideal_AW","Parallel_AW","Series_AW"],
				:Default=>"Ideal"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Controller action",
				:Valid=>["Direct","Reverse"],
				:Default=>"Reverse"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Controller mode",
				:Valid=>["Automatic","Manual"],
				:Default=>"Automatic"
			)),
			DanaSwitcher(Dict{Symbol,Any}(
				:Brief=>"Controller mode",
				:Valid=>["Clipped","Unclipped"],
				:Default=>"Clipped"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Derivative term filter constant",
				:Default=>1
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Proportional term setPoint change filter"
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Previous scaled bias",
				:Default=>0.5
			)),
			time_sec(Dict{Symbol,Any}(
				:Brief=>"Derivative time constant"
			)),
			time_sec(Dict{Symbol,Any}(
				:Brief=>"Integral time constant"
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Controller gain",
				:Default=>0.5
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Derivative term SP change filter"
			)),
			time_sec(Dict{Symbol,Any}(
				:Brief=>"Input filter time constant"
			)),
			time_sec(Dict{Symbol,Any}(
				:Brief=>"Input filter time constant"
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>0
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>1000
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>0
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>1
			)),
			control_signal(Dict{Symbol,Any}(
				:Protected=>true,
				:PosX=>0,
				:PosY=>0.5
			)),
			control_signal(Dict{Symbol,Any}(
				:Protected=>true,
				:PosX=>0.54,
				:PosY=>1
			)),
			control_signal(),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Derivative term",
				:Hidden=>true ,
				:Default=>0
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Derivative term filtered",
				:Hidden=>true ,
				:Default=>0.5
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Error definition for proportional term",
				:Hidden=>true 
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Error definition for derivative term",
				:Hidden=>true 
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Error definition for integral term",
				:Hidden=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Filtered input",
				:Hidden=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Integral term",
				:Hidden=>true ,
				:Default=>0
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Sum of proportional, integral and derivative terms",
				:Hidden=>true 
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Variable outp scaled between -1 and 1",
				:Hidden=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Proportional term",
				:Default=>0 ,
				:Hidden=>true 
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Filtered setPoint",
				:Default=>0,
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Integral term multiplier used in anti-reset windup",
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Protected=>true,
				:Hidden=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Previous scaled input signal",
				:Default=>0.5,
				:Hidden=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Scaled output signal",
				:Default=>0.5,
				:Hidden=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Scaled setPoint",
				:Default=>0.5,
				:Hidden=>true
			)),
			[
				:(PID_input*(MaxInput - MinInput) = Input - MinInput),
				:(Output = PID_output*(MaxOutput - MinOutput) + MinOutput),
				:(PID_setPoint*(MaxInput - MinInput) = SetPoint - MinInput),
				:((tau + 1e-3*"s")*diff(PID_inputFilt)= PID_input - PID_inputFilt),
				:(tau*diff(PID_inputFilt)= PID_input - PID_inputFilt),
				:((tauSet + 1e-3*"s")*diff(PID_setPointFilt)= PID_setPoint - PID_setPointFilt),
				:(tauSet*diff(PID_setPointFilt)= PID_setPoint - PID_setPointFilt),
				:(PID_error = PID_inputFilt*(beta-1.0)),
				:(PID_errorD= PID_inputFilt*(gamma-1.0)),
				:(PID_errorI= 0),
				:(PID_error = beta*PID_setPointFilt - PID_inputFilt),
				:(PID_errorD = gamma*PID_setPointFilt - PID_inputFilt),
				:(PID_errorI = PID_setPointFilt-PID_inputFilt),
				:(PID_propTerm=PID_error),
				:(alpha*(derivTime + 1e-3*"s")*diff(PID_dFilt) = PID_errorD - PID_dFilt),
				:(alpha*(derivTime)*diff(PID_dFilt) = PID_errorD - PID_dFilt),
				:(PID_derivTerm = derivTime*diff(PID_dFilt)),
				:(PID_outps=2*PID_outp-1),
				:(PID_output=(sign(PID_outps)+1)/2),
				:(PID_output=PID_outp),
				:(PID_output=PID_outp),
				:(PID_action = -1.0),
				:(PID_action = 1.0),
				:(intTime*diff(PID_intTerm) = PID_AWFactor*PID_errorI),
				:(PID_outp = bias + PID_action*gain*(PID_propTerm + PID_intTerm + PID_derivTerm)),
				:(PID_AWFactor=-tanh(sign(PID_outps)*PID_outps*100-102)),
				:(PID_AWFactor=1),
				:(intTime*diff(PID_intTerm) = PID_AWFactor*PID_errorI),
				:(PID_outp = bias + PID_action*(gain*PID_propTerm + PID_intTerm + PID_derivTerm)),
				:(PID_AWFactor=-tanh(sign(PID_outps)*PID_outps*100-102)),
				:(PID_AWFactor=1),
				:(intTime*diff(PID_intTerm) = PID_AWFactor*PID_errorI),
				:(PID_outp = bias + PID_action*(gain*(PID_propTerm + PID_intTerm)*(1 + PID_derivTerm))),
				:(PID_AWFactor=-tanh(sign(PID_outps)*PID_outps*100-102)),
				:(PID_AWFactor=1),
				:(intTime*diff(PID_intTerm) = PID_errorI),
				:(PID_outp = bias + PID_action*gain*(PID_propTerm + PID_intTerm + PID_derivTerm)),
				:(PID_AWFactor=1),
				:(intTime*diff(PID_intTerm) = PID_errorI),
				:(PID_outp = bias + PID_action*(gain*PID_propTerm + PID_intTerm + PID_derivTerm)),
				:(PID_AWFactor=1),
				:(intTime*diff(PID_intTerm) = PID_errorI),
				:(PID_outp = bias + PID_action*(gain*(PID_propTerm + PID_intTerm)*(1 + PID_derivTerm))),
				:(PID_AWFactor=1),
				:(PID_action*gain*(intTime*diff(PID_intTerm)-PID_errorI) = PID_output-PID_outp),
				:(PID_outp = bias + PID_action*gain*(PID_propTerm + PID_intTerm + PID_derivTerm)),
				:(PID_AWFactor=1),
				:(PID_action*gain*(intTime*diff(PID_intTerm)-PID_errorI) = PID_output-PID_outp),
				:(PID_outp = bias + PID_action*(gain*PID_propTerm + PID_intTerm + PID_derivTerm)),
				:(PID_AWFactor=1),
				:(PID_action*gain*(intTime*diff(PID_intTerm)-PID_errorI) = PID_output-PID_outp),
				:(PID_outp = bias + PID_action*(gain*(PID_propTerm + PID_intTerm)*(1 + PID_derivTerm))),
				:(PID_AWFactor=1),
			],
			[
				"Input ","Output ","Set Point ","Input first order filter","Input first order filter","setPoint first order filter","setPoint first order filter","Error definition for proportional term","Error definition for derivative term","Error definition for integral term","Error definition for proportional term","Error definition for derivative term","Error definition for integral term","Calculate proportional term","Derivative term filter","Derivative term filter","Calculate derivative term","Scale outp","Calculate clipped output when saturated","Calculate clipped output when not saturated","Calculate unclipped output","","","Calculate integral term with anti-windup","Sum of proportional, integral and derivative terms","Calculate AWFactor","Calculate AWFactor","Calculate integral term with anti-windup","Sum of proportional, integral and derivative terms","Calculate AWFactor","Calculate AWFactor","Calculate integral term with anti-windup","Sum of proportional, integral and derivative terms","Calculate AWFactor","Calculate AWFactor","Calculate integral term","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term with anti-windup and bumpless transfer","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term with anti-windup and bumpless transfer","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term with anti-windup and bumpless transfer","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode",
			],
			[:PID_Select,:Action,:Mode,:Clip,:alpha,:beta,:bias,:derivTime,:intTime,:gain,:gamma,:tau,:tauSet,:MinInput,:MaxInput,:MinOutput,:MaxOutput,],
			[:Input,:Output,:SetPoint,:PID_derivTerm,:PID_dFilt,:PID_error,:PID_errorD,:PID_errorI,:PID_inputFilt,:PID_intTerm,:PID_outp,:PID_outps,:PID_propTerm,:PID_setPointFilt,:PID_AWFactor,:PID_action,:PID_input,:PID_output,:PID_setPoint,]
		)
	end
	PID_Select::DanaSwitcher
	Action::DanaSwitcher
	Mode::DanaSwitcher
	Clip::DanaSwitcher
	alpha::positive
	beta::positive
	bias::control_signal
	derivTime::time_sec
	intTime::time_sec
	gain::positive
	gamma::positive
	tau::time_sec
	tauSet::time_sec
	MinInput::control_signal
	MaxInput::control_signal
	MinOutput::control_signal
	MaxOutput::control_signal
	Input::control_signal
	Output::control_signal
	SetPoint::control_signal
	PID_derivTerm::control_signal
	PID_dFilt::control_signal
	PID_error::control_signal
	PID_errorD::control_signal
	PID_errorI::control_signal
	PID_inputFilt::control_signal
	PID_intTerm::control_signal
	PID_outp::control_signal
	PID_outps::control_signal
	PID_propTerm::control_signal
	PID_setPointFilt::control_signal
	PID_AWFactor::DanaReal
	PID_action::DanaReal
	PID_input::control_signal
	PID_output::control_signal
	PID_setPoint::control_signal
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export PID
function initial(in::PID)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
end
function setEquationFlow(in::PID)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	if (tau < 1e-3*"s") 
		addEquation(4)
	else
		addEquation(5)
	end
	if (tauSet < 1e-3*"s") 
		addEquation(6)
	else
		addEquation(7)
	end
	let switch=Mode
		if switch=="Manual"
			addEquation(8)
			addEquation(9)
			addEquation(10)
		elseif switch=="Automatic"
			addEquation(11)
			addEquation(12)
			addEquation(13)
		end
	end
	addEquation(14)
	if (derivTime < 1e-3*"s") 
		addEquation(15)
	else
		addEquation(16)
	end
	addEquation(17)
	addEquation(18)
	let switch=Clip
		if switch=="Clipped"
			if abs(PID_outps)>1 
				addEquation(19)
			else
				addEquation(20)
			end
		elseif switch=="Unclipped"
			addEquation(21)
		end
	end
	let switch=Action
		if switch=="Direct"
			addEquation(22)
		elseif switch=="Reverse"
			addEquation(23)
		end
	end
	let switch=PID_Select
		if switch=="Ideal_AW"
			addEquation(24)
			addEquation(25)
			if abs(PID_outps)>1 && (PID_action*sign(PID_outps)*PID_errorI)>0 
				addEquation(26)
			else
				addEquation(27)
			end
		elseif switch=="Parallel_AW"
			addEquation(28)
			addEquation(29)
			if abs(PID_outps)>1 && (PID_action*sign(PID_outps)*PID_errorI)>0 
				addEquation(30)
			else
				addEquation(31)
			end
		elseif switch=="Series_AW"
			addEquation(32)
			addEquation(33)
			if abs(PID_outps)>1 && (PID_action*sign(PID_outps)*PID_errorI)>0 
				addEquation(34)
			else
				addEquation(35)
			end
		elseif switch=="Ideal"
			addEquation(36)
			addEquation(37)
			addEquation(38)
		elseif switch=="Parallel"
			addEquation(39)
			addEquation(40)
			addEquation(41)
		elseif switch=="Series"
			addEquation(42)
			addEquation(43)
			addEquation(44)
		elseif switch=="Ideal_AWBT"
			addEquation(45)
			addEquation(46)
			addEquation(47)
		elseif switch=="Parallel_AWBT"
			addEquation(48)
			addEquation(49)
			addEquation(50)
		elseif switch=="Series_AWBT"
			addEquation(51)
			addEquation(52)
			addEquation(53)
		end
	end
end
function atributes(in::PID,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/PID"
	drive!(fields,_)
	return fields
end
PID(_::Dict{Symbol,Any})=begin
	newModel=PID()
	newModel.attributes=atributes(newModel,_)
	newModel
end
