type PI_simple
	PI_simple()=begin
		[
			:(intTerm = 0),
		],
		[
			"",
		],
		new(
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Controller gain",
				:Default=>0.5
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Integral time constant",
				:Unit=>"s"
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Previous scaled bias",
				:Default=>0.5
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>-1000
			)),
			control_signal(Dict{Symbol,Any}(
				:Default=>1000
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Previous scaled input signal",
				:Default=>0.5,
				:PosX=>0,
				:PosY=>0.5,
				:Protected=>true
			)),
			control_signal (Dict{Symbol,Any}(
				:Brief=>"Scaled output signal",
				:Default=>0,
				:PosX=>0.54,
				:PosY=>1,
				:Protected=>true
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Scaled input variable",
				:Hidden=>true
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Scaled set point",
				:Hidden=>true
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Integral term",
				:Default=>0,
				:Protected=>true
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Variable outp scaled between 0 and 1",
				:Hidden=>true
			)),
			DanaReal (Dict{Symbol,Any}(
				:Brief=>"Scaled setPoint",
				:Lower=>0,
				:Upper=>1,
				:Default=>0.5
			)),
			[
				:(Ki*diff(intTerm) = setPoint - input),
				:(outps = bias + Kp*(setPoint - input) + intTerm),
				:(input*(MaxInput-MinInput) = Input-MinInput),
				:(setPoint*(MaxInput-MinInput) = SetPoint-MinInput),
				:(Output = 1),
				:(Output = 0),
				:(Output = outps),
			],
			[
				"Calculate integral term","Sum of proportional, integral and derivative terms","","","","","",
			],
			[:Kp,:Ki,:bias,:MinInput,:MaxInput,],
			[:Input,:Output,:input,:setPoint,:intTerm,:outps,:SetPoint,]
		)
	end
	Kp::DanaReal 
	Ki::DanaReal 
	bias::DanaReal 
	MinInput::control_signal
	MaxInput::control_signal
	Input::control_signal 
	Output::control_signal 
	input::DanaReal 
	setPoint::DanaReal 
	intTerm::DanaReal 
	outps::DanaReal 
	SetPoint::DanaReal 
	equations::Array{Expr,1}
	equationNames::Array{String,1}
	initials::Array{Expr,1}
	initialNames::Array{String,1}
	parameters::Array{Symbol,1}
	variables::Array{Symbol,1}
	attributes::Dict{Symbol,Any}
end
export PI_simple
function setEquationFlow(in::PI_simple)
	addEquation(1)
	addEquation(2)
	addEquation(3)
	addEquation(4)
	if outps > 1 
		addEquation(5)
	else
		if outps < 0 
			addEquation(6)
		else
			addEquation(7)
		end
	end
end
function initial(in::PI_simple)
	addEquation(1)
end
function atributes(in::PI_simple,_::Dict{Symbol,Any})
	fields::Dict{Symbol,Any}=Dict{Symbol,Any}()
	fields[:Pallete]=true
	fields[:Icon]="icon/PI"
	drive!(fields,_)
	return fields
end
PI_simple(_::Dict{Symbol,Any})=begin
	newModel=PI_simple()
	newModel.attributes=atributes(newModel,_)
	newModel
end
