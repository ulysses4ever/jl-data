type PI
	PI()=begin
		[
			:(intTerm = 0),
		],
		[
			"",
		],
		new(
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
			positive(Dict{Symbol,Any}(
				:Brief=>"Previous scaled bias",
				:Lower=>0,
				:Upper=>1,
				:Default=>0.5
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Proportional term setPoint change filter",
				:Default=>1
			)),
			positive(Dict{Symbol,Any}(
				:Brief=>"Controller gain",
				:Lower=>0,
				:Upper=>1,
				:Default=>0.5
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Integral time constant",
				:Unit=>"s"
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>-1000
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>1000
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Previous scaled input signal",
				:Default=>0.5,
				:PosX=>0,
				:PosY=>0.5,
				:Protected=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Scaled output signal",
				:Default=>0,
				:PosX=>0.54,
				:PosY=>1,
				:Protected=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Scaled setPoint",
				:Lower=>0,
				:Upper=>1,
				:Default=>0.5
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Proportional term",
				:Default=>0,
				:Protected=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Integral term",
				:Default=>0,
				:Protected=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Scaled input variable",
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Scaled set point",
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Controller action: (-1) Direct,(1) Reverse",
				:Default=>-1,
				:Hidden=>true
			)),
			control_signal(Dict{Symbol,Any}(
				:Brief=>"Sum of proportional, integral and derivative terms",
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Error definition for proportional term",
				:Hidden=>true
			)),
			DanaReal(Dict{Symbol,Any}(
				:Brief=>"Variable outp scaled between -1 and 1",
				:Hidden=>true
			)),
			[
				:(input*(MaxInput-MinInput) = Input-MinInput),
				:(setPoint*(MaxInput-MinInput) = SetPoint-MinInput),
				:(error = beta*setPoint - input),
				:(error = input*(beta-1.0)),
				:(action = -1.0),
				:(action = 1.0),
				:(propTerm=error),
				:(outps=outp),
				:(Output = 1),
				:(Output = -1),
				:(Output = outps),
				:(intTime*diff(intTerm) = setPoint - input),
				:(outp = bias + action*gain*(propTerm + intTerm)),
			],
			[
				"","","Error definition","Error definition","","","Calculate proportional term","Scale outp","","","","Calculate integral term","Sum of proportional, integral and derivative terms",
			],
			[:Action,:Mode,:bias,:beta,:gain,:intTime,:MinInput,:MaxInput,],
			[:Input,:Output,:SetPoint,:propTerm,:intTerm,:input,:setPoint,:action,:outp,:error,:outps,]
		)
	end
	Action::DanaSwitcher 
	Mode::DanaSwitcher 
	bias::positive 
	beta::positive 
	gain::positive 
	intTime::DanaReal 
	MinInput::control_signal 
	MaxInput::control_signal 
	Input::control_signal 
	Output::control_signal 
	SetPoint::DanaReal 
	propTerm::DanaReal 
	intTerm::DanaReal 
	input::DanaReal 
	setPoint::DanaReal 
	action::DanaReal 
	outp::control_signal 
	error::DanaReal 
	outps::DanaReal 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export PI
function setEquationFlow(in::PI)
	addEquation(1)
	addEquation(2)
	let switch=Mode
		if switch=="Automatic"
			addEquation(3)
		elseif switch=="Manual"
			addEquation(4)
		end
	end
	let switch=Action
		if switch=="Direct"
			addEquation(5)
		elseif switch=="Reverse"
			addEquation(6)
		end
	end
	addEquation(7)
	#outps=2*outp-1;
	addEquation(8)
	if outps > 1 
		addEquation(9)
	else
		if outps < -1 
			addEquation(10)
		else
			addEquation(11)
		end
	end
	addEquation(12)
	addEquation(13)
end
function initial(in::PI)
	addEquation(1)
end
function atributes(in::PI,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/PI"
	drive!(fields,_)
	return fields
end
PI(_::Dict{Symbol,Any})=begin
	newModel=PI()
	newModel.attributes=atributes(newModel,_)
	newModel
end
