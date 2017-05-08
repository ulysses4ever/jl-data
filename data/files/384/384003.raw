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
# Username: jeffreyvarner
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 02-24-2016 16:42:14
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
push!(flow_parameter_array,1.0);	# 1	C1C2: compartment_1 -> compartment_2
push!(flow_parameter_array,0.0);	# 2	C1C2_reverse: compartment_2 -> compartment_1
push!(flow_parameter_array,1.0);	# 3	C2C3: compartment_2 -> compartment_3
push!(flow_parameter_array,0.0);	# 4	C2C3_reverse: compartment_3 -> compartment_2
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/simplecase/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/simplecase/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*5.0);	#	1	compartment_1 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.1);	#	2	compartment_1 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	3	compartment_1 E

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	4	compartment_2 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	5	compartment_2 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.1);	#	6	compartment_2 E

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	7	compartment_3 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	8	compartment_3 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	compartment_3 E

push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	10	compartment_1 volume_compartment_1
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	11	compartment_2 volume_compartment_2
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	12	compartment_3 volume_compartment_3
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	compartment_1 A
push!(time_constant_array,1.0);	#	2	compartment_1 B
push!(time_constant_array,1.0);	#	3	compartment_1 E

push!(time_constant_array,1.0);	#	4	compartment_2 A
push!(time_constant_array,1.0);	#	5	compartment_2 B
push!(time_constant_array,1.0);	#	6	compartment_2 E

push!(time_constant_array,1.0);	#	7	compartment_3 A
push!(time_constant_array,1.0);	#	8	compartment_3 B
push!(time_constant_array,1.0);	#	9	compartment_3 E

push!(time_constant_array,1.0);	#	10	compartment_1 volume_compartment_1
push!(time_constant_array,1.0);	#	11	compartment_2 volume_compartment_2
push!(time_constant_array,1.0);	#	12	compartment_3 volume_compartment_3
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# compartment_1
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 1	compartment_1	conversion_of_A_to_B_with_E: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 2	compartment_1	conversion_of_B_to_A: compartment: * B -([])-> A

# compartment_2
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 3	compartment_2	conversion_of_A_to_B_with_E: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 4	compartment_2	conversion_of_B_to_A: compartment: * B -([])-> A

# compartment_3
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 5	compartment_3	conversion_of_A_to_B_with_E: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 6	compartment_3	conversion_of_B_to_A: compartment: * B -([])-> A

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[1,1] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[2,2] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[3,4] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[4,5] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[5,7] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[6,8] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(3,2);
# ------------------------------------------------------------------------------------------------ #
# compartment_1
control_parameter_array[1,1] = 0.1;	#	1 Gain: 	B --> conversion_of_A_to_B_with_E type:activation (activation_of_B_by_B_B_compartment_1)
control_parameter_array[1,2] = 1.0;	#	1 Order: 	B --> conversion_of_A_to_B_with_E type:activation (activation_of_B_by_B_B_compartment_1)

# compartment_2
control_parameter_array[2,1] = 0.1;	#	2 Gain: 	B --> conversion_of_A_to_B_with_E type:activation (activation_of_B_by_B_B_compartment_2)
control_parameter_array[2,2] = 1.0;	#	2 Order: 	B --> conversion_of_A_to_B_with_E type:activation (activation_of_B_by_B_B_compartment_2)

# compartment_3
control_parameter_array[3,1] = 0.1;	#	3 Gain: 	B --> conversion_of_A_to_B_with_E type:activation (activation_of_B_by_B_B_compartment_3)
control_parameter_array[3,2] = 1.0;	#	3 Order: 	B --> conversion_of_A_to_B_with_E type:activation (activation_of_B_by_B_B_compartment_3)

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
