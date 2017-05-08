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
# Generation timestamp: 03-23-2016 13:22:13
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
push!(flow_parameter_array,0.25);	# 1	supply_to_C1: [] -> C1
push!(flow_parameter_array,1.0);	# 2	C1_to_wound: C1 -> wound
push!(flow_parameter_array,0.9);	# 3	wound_to_C2: wound -> C2
push!(flow_parameter_array,0.8);	# 4	C2_to_C1: C2 -> C1
push!(flow_parameter_array,0.1);	# 5	C2_to_clearance: C2 -> []
push!(flow_parameter_array,0.1);	# 6	bleed_out: wound -> []
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/simpleCoagulation_Three_Compartment/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/simpleCoagulation_Three_Compartment/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	1	supply Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	2	supply E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	3	supply E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	4	supply Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	5	supply E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	6	supply D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	7	supply D2

push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	8	C1 Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	C1 E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	10	C1 E0
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	11	C1 Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	12	C1 E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	13	C1 D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	C1 D2

push!(initial_condition_array,(1.0/characteristic_concentration)*10.0);	#	15	wound Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.10);	#	16	wound E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.10);	#	17	wound E0
push!(initial_condition_array,(1.0/characteristic_concentration)*10.0);	#	18	wound Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.1);	#	19	wound E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	20	wound D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	21	wound D2

push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	22	C2 Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	23	C2 E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	24	C2 E0
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	25	C2 Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	26	C2 E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	27	C2 D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	28	C2 D2

push!(initial_condition_array,(1.0/characteristic_volume)*100.0);	#	29	supply volume_supply
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	30	C1 volume_C1
push!(initial_condition_array,(1.0/characteristic_volume)*.20);	#	31	wound volume_wound
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	32	C2 volume_C2
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	supply Z1
push!(time_constant_array,1.0);	#	2	supply E1
push!(time_constant_array,1.0);	#	3	supply E0
push!(time_constant_array,1.0);	#	4	supply Z2
push!(time_constant_array,1.0);	#	5	supply E2
push!(time_constant_array,1.0);	#	6	supply D1
push!(time_constant_array,1.0);	#	7	supply D2

push!(time_constant_array,1.0);	#	8	C1 Z1
push!(time_constant_array,1.0);	#	9	C1 E1
push!(time_constant_array,1.0);	#	10	C1 E0
push!(time_constant_array,1.0);	#	11	C1 Z2
push!(time_constant_array,1.0);	#	12	C1 E2
push!(time_constant_array,1.0);	#	13	C1 D1
push!(time_constant_array,1.0);	#	14	C1 D2

push!(time_constant_array,1.0);	#	15	wound Z1
push!(time_constant_array,1.0);	#	16	wound E1
push!(time_constant_array,1.0);	#	17	wound E0
push!(time_constant_array,1.0);	#	18	wound Z2
push!(time_constant_array,1.0);	#	19	wound E2
push!(time_constant_array,1.0);	#	20	wound D1
push!(time_constant_array,1.0);	#	21	wound D2

push!(time_constant_array,1.0);	#	22	C2 Z1
push!(time_constant_array,1.0);	#	23	C2 E1
push!(time_constant_array,1.0);	#	24	C2 E0
push!(time_constant_array,1.0);	#	25	C2 Z2
push!(time_constant_array,1.0);	#	26	C2 E2
push!(time_constant_array,1.0);	#	27	C2 D1
push!(time_constant_array,1.0);	#	28	C2 D2

push!(time_constant_array,1.0);	#	29	supply volume_supply
push!(time_constant_array,1.0);	#	30	C1 volume_C1
push!(time_constant_array,1.0);	#	31	wound volume_wound
push!(time_constant_array,1.0);	#	32	C2 volume_C2
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# supply
#no reactions should occur within supply
push!(rate_constant_array,(1.0/characteristic_time)*0.0);	# 1	supply	conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*0.0);	# 2	supply	conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*0.0);	# 3	supply	conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
push!(rate_constant_array,(1.0/characteristic_time)*0.0);	# 4	supply	degredation_of_E1: compartment: * E1 -([])-> D1
push!(rate_constant_array,(1.0/characteristic_time)*0.0);	# 5	supply	degredation_of_E2: compartment: * E2 -([])-> D2
push!(rate_constant_array,(characteristic_time)*0.0);	# 6	supply	degreation_of_E0: compartment: * E0 -([])-> []

# C1
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 7	C1	conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*10.0);	# 8	C1	conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 9	C1	conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 10	C1	degredation_of_E1: compartment: * E1 -([])-> D1
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 11	C1	degredation_of_E2: compartment: * E2 -([])-> D2
push!(rate_constant_array,(characteristic_time)*0.1);	# 12	C1	degreation_of_E0: compartment: * E0 -([])-> []

# wound
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 13	wound	conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*10.0);	# 14	wound	conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 15	wound	conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 16	wound	degredation_of_E1: compartment: * E1 -([])-> D1
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 17	wound	degredation_of_E2: compartment: * E2 -([])-> D2
push!(rate_constant_array,(characteristic_time)*0.1);	# 18	wound	degreation_of_E0: compartment: * E0 -([])-> []

# C2
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 19	C2	conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*10.0);	# 20	C2	conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 21	C2	conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 22	C2	degredation_of_E1: compartment: * E1 -([])-> D1
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 23	C2	degredation_of_E2: compartment: * E2 -([])-> D2
push!(rate_constant_array,(characteristic_time)*0.1);	# 24	C2	degreation_of_E0: compartment: * E0 -([])-> []
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*5.0);	# 25	C2	generation_of_Z1: compartment: C2 [] -([])-> Z1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*5.0);	# 26	C2	generation_of_Z2: compartment: C2 [] -([])-> Z2
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*5.0);	# 27	C2	generation_of_E0: compartment: C2 [] -([])-> E0
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*5.0);	# 28	C2	generation_of_E1: compartment: C2 [] -([])-> E1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*5.0);	# 29	C2	generation_of_E2: compartment: C2 [] -([])-> E2

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[1,1] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[2,1] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[3,4] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[4,2] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[5,5] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[7,8] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[8,8] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[9,11] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[10,9] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[11,12] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[13,15] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[14,15] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[15,18] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[16,16] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[17,19] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[19,22] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[20,22] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[21,25] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[22,23] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[23,26] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(0,2);
# ------------------------------------------------------------------------------------------------ #
# supply

# C1

# wound

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
