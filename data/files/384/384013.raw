# ----------------------------------------------------------------------------------- #
# Copyright (c) 2016 Varnerlab
# School of Chemical Engineering Purdue University
# W. Lafayette IN 46907 USA

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
# copies of the Software, and to permit persons to whom the Software is 
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ----------------------------------------------------------------------------------- #
function DataFile(TSTART,TSTOP,Ts)
# ----------------------------------------------------------------------------------- #
# DataFile.jl was generated using the Kwatee code generation system.
# DataFile: Stores model parameters as key - value pairs in a Julia Dict() 
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-04-2016 11:06:30
# 
# Input arguments: 
# TSTART  - Time start 
# TSTOP  - Time stop 
# Ts - Time step 
# 
# Return arguments: 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ----------------------------------------------------------------------------------- #

# Flow related parameters - 
default_beats_per_minute = 100.0;
default_stroke_volume = 70*(1/1000);
flow_parameter_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
push!(flow_parameter_array,0.0);	# 1	cell_to_outside: cell -> outside
push!(flow_parameter_array,0.0);	# 2	cell_to_outside_reverse: outside -> cell
# ------------------------------------------------------------------------------------------------ #

# Characteristic variables array - 
characteristic_variable_array = zeros(4);
# ------------------------------------------------------------------------------------------------ #
characteristic_volume = 1.0;
characteristic_concentration = 1.0;
characteristic_flow_rate = default_beats_per_minute*default_stroke_volume;
characteristic_time = characteristic_volume/characteristic_flow_rate;
characteristic_variable_array[1] = characteristic_volume;
characteristic_variable_array[2] = characteristic_concentration;
characteristic_variable_array[3] = characteristic_flow_rate;
characteristic_variable_array[4] = characteristic_time;
# ------------------------------------------------------------------------------------------------ #

# Load the stoichiometric matrix - 
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/supersimple/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/supersimple/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*0.1);	#	1	cell A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.1);	#	2	cell B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	3	cell E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.1);	#	4	cell C
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	5	cell E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.1);	#	6	cell D
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	7	cell E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	8	cell E4

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	outside A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	10	outside B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	11	outside E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	12	outside C
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	13	outside E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	outside D
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	15	outside E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	outside E4

push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	17	cell volume_cell
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	18	outside volume_outside
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	cell A
push!(time_constant_array,1.0);	#	2	cell B
push!(time_constant_array,1.0);	#	3	cell E1
push!(time_constant_array,1.0);	#	4	cell C
push!(time_constant_array,1.0);	#	5	cell E2
push!(time_constant_array,1.0);	#	6	cell D
push!(time_constant_array,1.0);	#	7	cell E3
push!(time_constant_array,1.0);	#	8	cell E4

push!(time_constant_array,1.0);	#	9	outside A
push!(time_constant_array,1.0);	#	10	outside B
push!(time_constant_array,1.0);	#	11	outside E1
push!(time_constant_array,1.0);	#	12	outside C
push!(time_constant_array,1.0);	#	13	outside E2
push!(time_constant_array,1.0);	#	14	outside D
push!(time_constant_array,1.0);	#	15	outside E3
push!(time_constant_array,1.0);	#	16	outside E4

push!(time_constant_array,1.0);	#	17	cell volume_cell
push!(time_constant_array,1.0);	#	18	outside volume_outside
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# cell
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 1	cell	conversion_of_A_to_B: compartment: cell A -(E1)-> B
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 2	cell	generation_of_E1: compartment: cell [] -([])-> E1
push!(rate_constant_array,(characteristic_time)*0.1);	# 3	cell	generation_of_E1: compartment: cell [] -([])-> E1
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 4	cell	conversion_of_B_to_C: compartment: cell B -(E2)-> C
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 5	cell	conversion_of_C_to_D: compartment: cell C -(E3)-> D
push!(rate_constant_array,(1.0/characteristic_time)*10.0);	# 6	cell	conversion_of_D_to_A: compartment: cell D -(E4)-> A

# outside

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[1,1] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[4,2] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[5,4] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[6,6] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(1,2);
# ------------------------------------------------------------------------------------------------ #
# cell
control_parameter_array[1,1] = 0.1;	#	1 Gain: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_cell)
control_parameter_array[1,2] = 1.0;	#	1 Order: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_cell)

# outside

# ------------------------------------------------------------------------------------------------ #

# Input concentration array - 
input_concentration_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------------------ #

# ---------------------------- DO NOT EDIT BELOW THIS LINE --------------------------------------- #
data_dictionary = Dict();
data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"] = characteristic_variable_array;
data_dictionary["INPUT_CONCENTRATION_ARRAY"] = input_concentration_array;
data_dictionary["DEFAULT_BEATS_PER_MINUTE"] = default_beats_per_minute;
data_dictionary["DEFAULT_STROKE_VOLUME"] = default_stroke_volume;
data_dictionary["FLOW_PARAMETER_ARRAY"] = flow_parameter_array;
data_dictionary["STOICHIOMETRIC_MATRIX"] = S;
data_dictionary["FLOW_CONNECTIVITY_MATRIX"] = C;
data_dictionary["RATE_CONSTANT_ARRAY"] = rate_constant_array;
data_dictionary["SATURATION_CONSTANT_ARRAY"] = saturation_constant_array;
data_dictionary["INITIAL_CONDITION_ARRAY"] = initial_condition_array;
data_dictionary["TIME_CONSTANT_ARRAY"] = time_constant_array;
data_dictionary["CONTROL_PARAMETER_ARRAY"] = control_parameter_array;
# ------------------------------------------------------------------------------------------------ #
return data_dictionary;
end
