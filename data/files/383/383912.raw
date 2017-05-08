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
# Generation timestamp: 03-07-2016 12:40:35
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
push!(flow_parameter_array,0.0);	# 1	C1_C2: C1 -> C2
push!(flow_parameter_array,0.0);	# 2	C1_C2_reverse: C2 -> C1
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/compliment/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/compliment/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	1	C1 MBL
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	2	C1 MASP1_2
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	3	C1 C1_a_similar
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	4	C1 C4
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	5	C1 C4a
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	6	C1 C4b
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	7	C1 C4b2
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	8	C1 C2
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	9	C1 C2b
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	10	C1 C4b2a
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	11	C1 C1a
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	12	C1 C3
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	13	C1 C3a
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	14	C1 C3b
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	15	C1 C4b2a3b
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	16	C1 C3bBb3b
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	17	C1 C5
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	18	C1 C4bBb3b
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	19	C1 C5a
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	20	C1 C5b
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	21	C1 MAC
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	22	C1 C6_C9

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	23	C2 MBL
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	24	C2 MASP1_2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	25	C2 C1_a_similar
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	26	C2 C4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	27	C2 C4a
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	28	C2 C4b
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	29	C2 C4b2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	30	C2 C2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	31	C2 C2b
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	32	C2 C4b2a
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	33	C2 C1a
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	34	C2 C3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	35	C2 C3a
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	36	C2 C3b
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	37	C2 C4b2a3b
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	38	C2 C3bBb3b
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	39	C2 C5
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	40	C2 C4bBb3b
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	41	C2 C5a
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	42	C2 C5b
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	43	C2 MAC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	44	C2 C6_C9

push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	45	C1 volume_C1
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	46	C2 volume_C2
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	C1 MBL
push!(time_constant_array,1.0);	#	2	C1 MASP1_2
push!(time_constant_array,1.0);	#	3	C1 C1_a_similar
push!(time_constant_array,1.0);	#	4	C1 C4
push!(time_constant_array,1.0);	#	5	C1 C4a
push!(time_constant_array,1.0);	#	6	C1 C4b
push!(time_constant_array,1.0);	#	7	C1 C4b2
push!(time_constant_array,1.0);	#	8	C1 C2
push!(time_constant_array,1.0);	#	9	C1 C2b
push!(time_constant_array,1.0);	#	10	C1 C4b2a
push!(time_constant_array,1.0);	#	11	C1 C1a
push!(time_constant_array,1.0);	#	12	C1 C3
push!(time_constant_array,1.0);	#	13	C1 C3a
push!(time_constant_array,1.0);	#	14	C1 C3b
push!(time_constant_array,1.0);	#	15	C1 C4b2a3b
push!(time_constant_array,1.0);	#	16	C1 C3bBb3b
push!(time_constant_array,1.0);	#	17	C1 C5
push!(time_constant_array,1.0);	#	18	C1 C4bBb3b
push!(time_constant_array,1.0);	#	19	C1 C5a
push!(time_constant_array,1.0);	#	20	C1 C5b
push!(time_constant_array,1.0);	#	21	C1 MAC
push!(time_constant_array,1.0);	#	22	C1 C6_C9

push!(time_constant_array,1.0);	#	23	C2 MBL
push!(time_constant_array,1.0);	#	24	C2 MASP1_2
push!(time_constant_array,1.0);	#	25	C2 C1_a_similar
push!(time_constant_array,1.0);	#	26	C2 C4
push!(time_constant_array,1.0);	#	27	C2 C4a
push!(time_constant_array,1.0);	#	28	C2 C4b
push!(time_constant_array,1.0);	#	29	C2 C4b2
push!(time_constant_array,1.0);	#	30	C2 C2
push!(time_constant_array,1.0);	#	31	C2 C2b
push!(time_constant_array,1.0);	#	32	C2 C4b2a
push!(time_constant_array,1.0);	#	33	C2 C1a
push!(time_constant_array,1.0);	#	34	C2 C3
push!(time_constant_array,1.0);	#	35	C2 C3a
push!(time_constant_array,1.0);	#	36	C2 C3b
push!(time_constant_array,1.0);	#	37	C2 C4b2a3b
push!(time_constant_array,1.0);	#	38	C2 C3bBb3b
push!(time_constant_array,1.0);	#	39	C2 C5
push!(time_constant_array,1.0);	#	40	C2 C4bBb3b
push!(time_constant_array,1.0);	#	41	C2 C5a
push!(time_constant_array,1.0);	#	42	C2 C5b
push!(time_constant_array,1.0);	#	43	C2 MAC
push!(time_constant_array,1.0);	#	44	C2 C6_C9

push!(time_constant_array,1.0);	#	45	C1 volume_C1
push!(time_constant_array,1.0);	#	46	C2 volume_C2
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# C1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 1	C1	generation_of_MBL: compartment: C1 [] -(MASP1_2)-> MBL
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 2	C1	generation_of_C1_a_similar: compartment: C1 [] -(MBL)-> C1_a_similar
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 3	C1	cleavage_of_C4: compartment: C1 C4 -(C1_a_similar)-> C4a+C4b
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 4	C1	generation_of_C4b2: compartment: C1 C4b -(C2)-> C4b2
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 5	C1	generation_of_C4b2a: compartment: C1 C4b2 -(C1a)-> C2b+C4b2a
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 6	C1	cleavage_of_C3: compartment: C1 C3 -(C4b2a)-> C3a+C3b
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 7	C1	C3b_activation_way1: compartment: C1 C3b -([])-> C4b2a3b
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 8	C1	C3b_activation_way2: compartment: C1 C3b -([])-> C3bBb3b
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 9	C1	C5_generation_way1: compartment: C1 [] -(C4b2a3b)-> C5
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 10	C1	C5_generation_way2: compartment: C1 [] -(C4bBb3b)-> C5
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 11	C1	C5_cleavage: compartment: C1 C5 -([])-> C5a+C5b
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 12	C1	C5b_to_MAC: compartment: C1 C5b -(C6_C9)-> MAC

# C2

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[3,4] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[4,6] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[5,7] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[6,12] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[7,14] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[8,14] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[11,17] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[12,20] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(0,2);
# ------------------------------------------------------------------------------------------------ #
# C1

# C2

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
