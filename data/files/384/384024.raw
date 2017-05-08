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
# Generation timestamp: 03-02-2016 14:35:17
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
push!(flow_parameter_array,0.0);	# 1	C1C2: compartment_1 -> compartment_2
push!(flow_parameter_array,0.0);	# 2	C2C3: compartment_2 -> compartment_3
push!(flow_parameter_array,0.0);	# 3	C3C4: compartment_3 -> compartment_4
push!(flow_parameter_array,0.0);	# 4	C3C5: compartment_3 -> compartment_5
push!(flow_parameter_array,0.0);	# 5	C4C1: compartment_4 -> compartment_1
push!(flow_parameter_array,0.0);	# 6	C5C1: compartment_5 -> compartment_1
push!(flow_parameter_array,0.0);	# 7	C1W: compartment_1 -> wound_compartment
push!(flow_parameter_array,0.0);	# 8	C1W_reverse: wound_compartment -> compartment_1
push!(flow_parameter_array,0.0);	# 9	Loss_W: wound_compartment -> []
push!(flow_parameter_array,0.0);	# 10	addition_of_fluid: [] -> compartment_1
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/testcase/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/testcase/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	1	compartment_1 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	2	compartment_1 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	3	compartment_1 E
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	4	compartment_1 II
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	5	compartment_1 AI

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	6	compartment_2 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	7	compartment_2 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	8	compartment_2 E
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	compartment_2 II
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	10	compartment_2 AI

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	11	compartment_3 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	12	compartment_3 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	13	compartment_3 E
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	compartment_3 II
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	15	compartment_3 AI

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	compartment_4 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	17	compartment_4 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	18	compartment_4 E
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	19	compartment_4 II
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	20	compartment_4 AI

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	21	compartment_5 A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	22	compartment_5 B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	23	compartment_5 E
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	24	compartment_5 II
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	25	compartment_5 AI

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	26	wound_compartment A
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	27	wound_compartment B
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	28	wound_compartment E
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	29	wound_compartment II
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	30	wound_compartment AI

push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	31	compartment_1 volume_compartment_1
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	32	compartment_2 volume_compartment_2
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	33	compartment_3 volume_compartment_3
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	34	compartment_4 volume_compartment_4
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	35	compartment_5 volume_compartment_5
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	36	wound_compartment volume_wound_compartment
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	compartment_1 A
push!(time_constant_array,1.0);	#	2	compartment_1 B
push!(time_constant_array,1.0);	#	3	compartment_1 E
push!(time_constant_array,1.0);	#	4	compartment_1 II
push!(time_constant_array,1.0);	#	5	compartment_1 AI

push!(time_constant_array,1.0);	#	6	compartment_2 A
push!(time_constant_array,1.0);	#	7	compartment_2 B
push!(time_constant_array,1.0);	#	8	compartment_2 E
push!(time_constant_array,1.0);	#	9	compartment_2 II
push!(time_constant_array,1.0);	#	10	compartment_2 AI

push!(time_constant_array,1.0);	#	11	compartment_3 A
push!(time_constant_array,1.0);	#	12	compartment_3 B
push!(time_constant_array,1.0);	#	13	compartment_3 E
push!(time_constant_array,1.0);	#	14	compartment_3 II
push!(time_constant_array,1.0);	#	15	compartment_3 AI

push!(time_constant_array,1.0);	#	16	compartment_4 A
push!(time_constant_array,1.0);	#	17	compartment_4 B
push!(time_constant_array,1.0);	#	18	compartment_4 E
push!(time_constant_array,1.0);	#	19	compartment_4 II
push!(time_constant_array,1.0);	#	20	compartment_4 AI

push!(time_constant_array,1.0);	#	21	compartment_5 A
push!(time_constant_array,1.0);	#	22	compartment_5 B
push!(time_constant_array,1.0);	#	23	compartment_5 E
push!(time_constant_array,1.0);	#	24	compartment_5 II
push!(time_constant_array,1.0);	#	25	compartment_5 AI

push!(time_constant_array,1.0);	#	26	wound_compartment A
push!(time_constant_array,1.0);	#	27	wound_compartment B
push!(time_constant_array,1.0);	#	28	wound_compartment E
push!(time_constant_array,1.0);	#	29	wound_compartment II
push!(time_constant_array,1.0);	#	30	wound_compartment AI

push!(time_constant_array,1.0);	#	31	compartment_1 volume_compartment_1
push!(time_constant_array,1.0);	#	32	compartment_2 volume_compartment_2
push!(time_constant_array,1.0);	#	33	compartment_3 volume_compartment_3
push!(time_constant_array,1.0);	#	34	compartment_4 volume_compartment_4
push!(time_constant_array,1.0);	#	35	compartment_5 volume_compartment_5
push!(time_constant_array,1.0);	#	36	wound_compartment volume_wound_compartment
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# compartment_1
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 1	compartment_1	conversion_of_A_to_B_slow: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 2	compartment_1	conversion_of_A_to_B: compartment: * A -(E)-> B
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 3	compartment_1	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time)*0.1);	# 4	compartment_1	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 5	compartment_1	activation_of_I: compartment: * II -(B)-> AI

# compartment_2
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 6	compartment_2	conversion_of_A_to_B_slow: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 7	compartment_2	conversion_of_A_to_B: compartment: * A -(E)-> B
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 8	compartment_2	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time)*0.1);	# 9	compartment_2	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 10	compartment_2	activation_of_I: compartment: * II -(B)-> AI

# compartment_3
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 11	compartment_3	conversion_of_A_to_B_slow: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 12	compartment_3	conversion_of_A_to_B: compartment: * A -(E)-> B
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 13	compartment_3	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time)*0.1);	# 14	compartment_3	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 15	compartment_3	activation_of_I: compartment: * II -(B)-> AI

# compartment_4
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 16	compartment_4	conversion_of_A_to_B_slow: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 17	compartment_4	conversion_of_A_to_B: compartment: * A -(E)-> B
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 18	compartment_4	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time)*0.1);	# 19	compartment_4	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time)*0.1);	# 20	compartment_4	clearance_of_A: compartment: compartment_4 A -([])-> []
push!(rate_constant_array,(characteristic_time)*0.1);	# 21	compartment_4	clearance_of_B: compartment: compartment_4 B -([])-> []
push!(rate_constant_array,(characteristic_time)*0.1);	# 22	compartment_4	clearance_of_AI: compartment: compartment_4 AI -([])-> []
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 23	compartment_4	activation_of_I: compartment: * II -(B)-> AI

# compartment_5
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 24	compartment_5	conversion_of_A_to_B_slow: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 25	compartment_5	conversion_of_A_to_B: compartment: * A -(E)-> B
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 26	compartment_5	generation_of_A: compartment: compartment_5 [] -([])-> A
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 27	compartment_5	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time)*0.1);	# 28	compartment_5	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 29	compartment_5	activation_of_I: compartment: * II -(B)-> AI

# wound_compartment
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 30	wound_compartment	conversion_of_A_to_B_slow: compartment: * A -(E)-> B
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 31	wound_compartment	conversion_of_A_to_B: compartment: * A -(E)-> B
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 32	wound_compartment	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time)*0.1);	# 33	wound_compartment	generation_of_II: compartment: * [] -([])-> II
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 34	wound_compartment	generation_of_E: compartment: wound_compartment [] -([])-> E
push!(rate_constant_array,(characteristic_time)*0.1);	# 35	wound_compartment	generation_of_E: compartment: wound_compartment [] -([])-> E
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 36	wound_compartment	activation_of_I: compartment: * II -(B)-> AI

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[1,1] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[2,1] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[5,4] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[6,6] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[7,6] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[10,9] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[11,11] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[12,11] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[15,14] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[16,16] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[17,16] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[23,19] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[24,21] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[25,21] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[29,24] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[30,26] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[31,26] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[36,29] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(18,2);
# ------------------------------------------------------------------------------------------------ #
# compartment_1
control_parameter_array[1,1] = 0.1;	#	1 Gain: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_1)
control_parameter_array[1,2] = 1.0;	#	1 Order: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_1)
control_parameter_array[2,1] = 0.1;	#	2 Gain: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_1)
control_parameter_array[2,2] = 1.0;	#	2 Order: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_1)
control_parameter_array[3,1] = 0.1;	#	3 Gain: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_1)
control_parameter_array[3,2] = 1.0;	#	3 Order: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_1)

# compartment_2
control_parameter_array[4,1] = 0.1;	#	4 Gain: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_2)
control_parameter_array[4,2] = 1.0;	#	4 Order: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_2)
control_parameter_array[5,1] = 0.1;	#	5 Gain: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_2)
control_parameter_array[5,2] = 1.0;	#	5 Order: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_2)
control_parameter_array[6,1] = 0.1;	#	6 Gain: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_2)
control_parameter_array[6,2] = 1.0;	#	6 Order: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_2)

# compartment_3
control_parameter_array[7,1] = 0.1;	#	7 Gain: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_3)
control_parameter_array[7,2] = 1.0;	#	7 Order: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_3)
control_parameter_array[8,1] = 0.1;	#	8 Gain: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_3)
control_parameter_array[8,2] = 1.0;	#	8 Order: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_3)
control_parameter_array[9,1] = 0.1;	#	9 Gain: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_3)
control_parameter_array[9,2] = 1.0;	#	9 Order: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_3)

# compartment_4
control_parameter_array[10,1] = 0.1;	#	10 Gain: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_4)
control_parameter_array[10,2] = 1.0;	#	10 Order: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_4)
control_parameter_array[11,1] = 0.1;	#	11 Gain: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_4)
control_parameter_array[11,2] = 1.0;	#	11 Order: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_4)
control_parameter_array[12,1] = 0.1;	#	12 Gain: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_4)
control_parameter_array[12,2] = 1.0;	#	12 Order: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_4)

# compartment_5
control_parameter_array[13,1] = 0.1;	#	13 Gain: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_5)
control_parameter_array[13,2] = 1.0;	#	13 Order: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_compartment_5)
control_parameter_array[14,1] = 0.1;	#	14 Gain: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_5)
control_parameter_array[14,2] = 1.0;	#	14 Order: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_compartment_5)
control_parameter_array[15,1] = 0.1;	#	15 Gain: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_5)
control_parameter_array[15,2] = 1.0;	#	15 Order: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_compartment_5)

# wound_compartment
control_parameter_array[16,1] = 0.1;	#	16 Gain: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_wound_compartment)
control_parameter_array[16,2] = 1.0;	#	16 Order: 	B --> conversion_of_A_to_B type:activation (activation_of_B_by_B_B_wound_compartment)
control_parameter_array[17,1] = 0.1;	#	17 Gain: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_wound_compartment)
control_parameter_array[17,2] = 1.0;	#	17 Order: 	AI --> conversion_of_A_to_B type:inhibition (deactivation_of_B_Gen_AI_wound_compartment)
control_parameter_array[18,1] = 0.1;	#	18 Gain: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_wound_compartment)
control_parameter_array[18,2] = 1.0;	#	18 Order: 	AI --> conversion_of_A_to_B_slow type:inhibition (deactivation_of_B_Gen_AI_slow_wound_compartment)

# ------------------------------------------------------------------------------------------------ #

# Input concentration array - 
input_concentration_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 1 A_input_compartment_1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 2 B_input_compartment_1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 3 E_input_compartment_1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 4 II_input_compartment_1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 5 AI_input_compartment_1
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
