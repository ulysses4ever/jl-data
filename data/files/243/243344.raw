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
#* Author: Tiago Os򱨯rio
#* $Id$
#*-------------------------------------------------------------------
type PIDIncr
	PIDIncr()=begin
		[
			:(PID_output = bias),
			:(diff(PID_dFilt) = 0/"s^2"),
			:(diff(PID_inputFilt)=0/"s"),
			:(diff(PID_setPointFilt)=0/"s"),
		],
		[
			"","","","",
		],
		new(
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Type of PID Incremental",
				:Valid=>["Ideal","Parallel","Series","Ideal_AWBT","Parallel_AWBT","Series_AWBT","Ideal_AW","Parallel_AW","Series_AW"],
				:Default=>"Ideal"
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Controller action",
				:Valid=>["Direct","Reverse"],
				:Default=>"Reverse"
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Controller mode",
				:Valid=>["Automatic","Manual"],
				:Default=>"Automatic"
			)),
			DanaSwitcher (Dict{Symbol,Any}(
				:Brief=>"Controller mode",
				:Valid=>["Clipped","Unclipped"],
				:Default=>"Clipped"
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Derivative term filter constant",
				:Default=>1
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Proportional term setPoint change filter"
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Previous scaled bias",
				:Default=>0.5
			)),
			time_sec (Dict{Symbol,Any}(
				:Brief=>"Derivative time constant"
			)),
			time_sec (Dict{Symbol,Any}(
				:Brief=>"Integral time constant"
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Controller gain",
				:Default=>0.5
			)),
			positive (Dict{Symbol,Any}(
				:Brief=>"Derivative term SP change filter"
			)),
			time_sec (Dict{Symbol,Any}(
				:Brief=>"Input filter time constant"
			)),
			time_sec (Dict{Symbol,Any}(
				:Brief=>"Input filter time constant"
			)),
			control_signal (Dict{Symbol,Any}(
				:Default=>0
			)),
			control_signal (Dict{Symbol,Any}(
				:Default=>1000
			)),
			control_signal (Dict{Symbol,Any}(
				:Default=>0
			)),
			control_signal (Dict{Symbol,Any}(
				:Default=>1
			)),
			control_signal (Dict{Symbol,Any}(
				:Protected=>true,
				:PosX=>0,
				:PosY=>0.5
			)),
			control_signal (Dict{Symbol,Any}(
				:Protected=>true,
				:PosX=>0.54,
				:PosY=>1
			)),
			control_signal(),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Derivative term",
				:Unit=>"1/s",
				:Default=>0,
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Derivative term filtered",
				:Default=>0.5,
				:Unit=>"1/s",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Error definition for proportional term",
				:Unit=>"1/s",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Error definition for derivative term",
				:Unit=>"1/s",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Error definition for integral term",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Filtered input",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Integral term",
				:Default=>0,
				:Unit=>"1/s",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Sum of proportional, integral and derivative terms",
				:Unit=>"1/s",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Variable outp scaled between -1 and 1",
				:Hidden=>true,
				:Default=>0.5
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Variable outp",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Proportional term",
				:Default=>0,
				:Unit=>"1/s",
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Filtered setPoint",
				:Default=>0,
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Previous scaled input signal",
				:Default=>0.5,
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Scaled output signal",
				:Default=>0.5,
				:Hidden=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Scaled setPoint",
				:Default=>0.5,
				:Hidden=>true
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Integral term multiplier used in anti-reset windup",
				:Hidden=>true
			)),
			DanaReal (Dict{Symbol,Any}(
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
				:(PID_error*"s" = PID_inputFilt*(beta-1.0)),
				:(PID_errorD*"s"= PID_inputFilt*(gamma-1.0)),
				:(PID_errorI= 0),
				:(PID_error = beta*diff(PID_setPointFilt) - diff(PID_inputFilt)),
				:(PID_errorD = gamma*diff(PID_setPointFilt) - diff(PID_inputFilt)),
				:(PID_errorI = PID_setPointFilt-PID_inputFilt),
				:(PID_dpropTerm=PID_error),
				:(alpha*(derivTime + 1e-3*"s")*diff(PID_dFilt) = PID_errorD - PID_dFilt),
				:(alpha*(derivTime)*diff(PID_dFilt) = PID_errorD - PID_dFilt),
				:(PID_dderivTerm = derivTime*diff(PID_dFilt)),
				:(diff(PID_outp)=PID_doutp),
				:(PID_outps=2*PID_outp-1),
				:(PID_output=(sign(PID_outps)+1)/2),
				:(PID_output=PID_outp),
				:(PID_output=PID_outp),
				:(PID_action = -1.0),
				:(PID_action = 1.0),
				:(intTime*PID_dintTerm = PID_errorI),
				:(PID_doutp = PID_action*gain*(PID_dpropTerm + PID_dintTerm + PID_dderivTerm)),
				:(PID_AWFactor=1),
				:(intTime*PID_dintTerm = PID_errorI),
				:(PID_doutp = PID_action*(gain*PID_dpropTerm + PID_dintTerm + PID_dderivTerm)),
				:(PID_AWFactor=1),
				:(intTime*PID_dintTerm = PID_errorI),
				:(PID_doutp = PID_action*(gain*(PID_dpropTerm + PID_dintTerm)*(1/"s" + PID_dderivTerm)*"s")),
				:(PID_AWFactor=1),
				:(PID_action*gain*(intTime*PID_dintTerm-PID_errorI) = PID_output-PID_outp),
				:(PID_doutp = PID_action*gain*(PID_dpropTerm + PID_dintTerm + PID_dderivTerm)),
				:(PID_AWFactor=1),
				:(PID_action*gain*(intTime*PID_dintTerm-PID_errorI) = PID_output-PID_outp),
				:(PID_doutp = PID_action*(gain*PID_dpropTerm + PID_dintTerm + PID_dderivTerm)),
				:(PID_AWFactor=1),
				:(PID_action*gain*(intTime*PID_dintTerm-PID_errorI) = PID_output-PID_outp),
				:(PID_doutp = PID_action*(gain*(PID_dpropTerm + PID_dintTerm)*(1/"s" + PID_dderivTerm)*"s")),
				:(PID_AWFactor=1),
				:(intTime*PID_dintTerm = PID_AWFactor*PID_errorI),
				:(PID_doutp = PID_action*gain*(PID_dpropTerm + PID_dintTerm + PID_dderivTerm)),
				:(PID_AWFactor=-tanh(sign(PID_outps)*PID_outps*100-102)),
				:(PID_AWFactor=1),
				:(intTime*PID_dintTerm = PID_AWFactor*PID_errorI),
				:(PID_doutp = PID_action*(gain*PID_dpropTerm + PID_dintTerm + PID_dderivTerm)),
				:(PID_AWFactor=-tanh(sign(PID_outps)*PID_outps*100-102)),
				:(PID_AWFactor=1),
				:(intTime*PID_dintTerm = PID_AWFactor*PID_errorI),
				:(PID_doutp = PID_action*(gain*(PID_dpropTerm + PID_dintTerm)*(1/"s" + PID_dderivTerm)*"s")),
				:(PID_AWFactor=-tanh(sign(PID_outps)*PID_outps*100-102)),
				:(PID_AWFactor=1),
			],
			[
				"Input ","Output ","Set Point ","Input first order filter","Input first order filter","setPoint first order filter","setPoint first order filter","Error definition for proportional term","Error definition for derivative term","Error definition for integral term","Error definition for proportional term","Error definition for derivative term","Error definition for integral term","Calculate proportional term","Derivative term filter","Derivative term filter","Calculate derivative term","Unscaled output","Scale outp","Calculate clipped output when saturated","Calculate clipped output when not saturated","Calculate unclipped output","","","Calculate integral term","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term with anti-windup and bumpless transfer","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term with anti-windup and bumpless transfer","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term with anti-windup and bumpless transfer","Sum of proportional, integral and derivative terms","Calculate AWFactor - Not in use in this mode","Calculate integral term with anti-windup","Sum of proportional, integral and derivative terms","Calculate AWFactor","Calculate AWFactor","Calculate integral term with anti-windup","Sum of proportional, integral and derivative terms","Calculate AWFactor","Calculate AWFactor","Calculate integral term with anti-windup","Sum of proportional, integral and derivative terms","Calculate AWFactor","Calculate AWFactor",
			],
			[:PID_Select,:Action,:Mode,:Clip,:alpha,:beta,:bias,:derivTime,:intTime,:gain,:gamma,:tau,:tauSet,:MinInput,:MaxInput,:MinOutput,:MaxOutput,],
			[:Input,:Output,:SetPoint,:PID_dderivTerm,:PID_dFilt,:PID_error,:PID_errorD,:PID_errorI,:PID_inputFilt,:PID_dintTerm,:PID_doutp,:PID_outps,:PID_outp,:PID_dpropTerm,:PID_setPointFilt,:PID_input,:PID_output,:PID_setPoint,:PID_AWFactor,:PID_action,]
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
	PID_dderivTerm::control_signal 
	PID_dFilt::control_signal 
	PID_error::control_signal 
	PID_errorD::control_signal 
	PID_errorI::control_signal 
	PID_inputFilt::control_signal 
	PID_dintTerm::control_signal 
	PID_doutp::control_signal 
	PID_outps::control_signal 
	PID_outp::control_signal 
	PID_dpropTerm::control_signal 
	PID_setPointFilt::control_signal 
	PID_input::control_signal 
	PID_output::control_signal 
	PID_setPoint::control_signal 
	PID_AWFactor::DanaReal 
	PID_action::DanaReal 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export PIDIncr
function setEquationFlow(in::PIDIncr)
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
	addEquation(19)
	let switch=Clip
		if switch=="Clipped"
			if abs(PID_outps)>1 
				addEquation(20)
			else
				addEquation(21)
			end
			#PID_output = max([0, PID_outp]);
			
		elseif switch=="Unclipped"
			addEquation(22)
		end
	end
	let switch=Action
		if switch=="Direct"
			addEquation(23)
		elseif switch=="Reverse"
			addEquation(24)
		end
	end
	let switch=PID_Select
		if switch=="Ideal"
			addEquation(25)
			addEquation(26)
			addEquation(27)
		elseif switch=="Parallel"
			addEquation(28)
			addEquation(29)
			addEquation(30)
		elseif switch=="Series"
			addEquation(31)
			addEquation(32)
			addEquation(33)
		elseif switch=="Ideal_AWBT"
			addEquation(34)
			addEquation(35)
			addEquation(36)
		elseif switch=="Parallel_AWBT"
			addEquation(37)
			addEquation(38)
			addEquation(39)
		elseif switch=="Series_AWBT"
			addEquation(40)
			addEquation(41)
			addEquation(42)
		elseif switch=="Ideal_AW"
			addEquation(43)
			addEquation(44)
			if abs(PID_outps)>1 && (PID_action*sign(PID_outps)*PID_errorI)>0 
				addEquation(45)
			else
				addEquation(46)
			end
		elseif switch=="Parallel_AW"
			addEquation(47)
			addEquation(48)
			if abs(PID_outps)>1 && (PID_action*sign(PID_outps)*PID_errorI)>0 
				addEquation(49)
			else
				addEquation(50)
			end
		elseif switch=="Series_AW"
			addEquation(51)
			addEquation(52)
			if abs(PID_outps)>1 && (PID_action*sign(PID_outps)*PID_errorI)>0 
				addEquation(53)
			else
				addEquation(54)
			end
		end
	end
end
function initial(in::PIDIncr)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
end
function atributes(in::PIDIncr,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/PIDincr"
	fields[:Brief]="Model of incremental PIDs."
	fields[:Info]="== Inputs ==
* scaled processs variable.
* scaled bias.
* scaled setpoint.

== Outputs ==
* a scaled output.
"
	drive!(fields,_)
	return fields
end
PIDIncr(_::Dict{Symbol,Any})=begin
	newModel=PIDIncr()
	newModel.attributes=atributes(newModel,_)
	newModel
end
