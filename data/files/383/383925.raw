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
# Generation timestamp: 03-10-2016 15:38:03
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
push!(flow_parameter_array,2.6+1.17);	# 1	vein_to_lungs: vein -> lungs
push!(flow_parameter_array,2.60+1.17);	# 2	lungs_to_artery: lungs -> artery
push!(flow_parameter_array,2.6);	# 3	artery_to_heart: artery -> heart
push!(flow_parameter_array,2.6);	# 4	heart_to_veins: heart -> vein
push!(flow_parameter_array,1.17);	# 5	artery_to_kidney: artery -> kidney
push!(flow_parameter_array,1.17);	# 6	kideny_to_vein: kidney -> vein
push!(flow_parameter_array,0.01);	# 7	artery_to_wound: artery -> wound
push!(flow_parameter_array,0.01);	# 8	artery_to_wound_reverse: wound -> artery
push!(flow_parameter_array,0.03);	# 9	artery_to_degredation: artery -> []
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/fullFeedbackCoagulation/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/fullFeedbackCoagulation/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	1	vein Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	2	vein E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	3	vein D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	4	vein Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	5	vein E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	6	vein D2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	7	vein E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	8	vein E4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	9	vein D3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	10	vein Z4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	11	vein D4

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	12	lungs Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	13	lungs E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	lungs D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	15	lungs Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	lungs E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	17	lungs D2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	18	lungs E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	19	lungs E4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	20	lungs D3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	21	lungs Z4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	22	lungs D4

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	23	artery Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	24	artery E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	25	artery D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	26	artery Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	27	artery E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	28	artery D2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	29	artery E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	30	artery E4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	31	artery D3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	32	artery Z4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	33	artery D4

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	34	heart Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	35	heart E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	36	heart D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	37	heart Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	38	heart E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	39	heart D2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	40	heart E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	41	heart E4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	42	heart D3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	43	heart Z4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	44	heart D4

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	45	kidney Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	46	kidney E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	47	kidney D1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	48	kidney Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	49	kidney E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	50	kidney D2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	51	kidney E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	52	kidney E4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	53	kidney D3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	54	kidney Z4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	55	kidney D4

push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	56	wound Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	57	wound E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	58	wound D1
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	59	wound Z2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	60	wound E2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	61	wound D2
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	62	wound E3
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	63	wound E4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	64	wound D3
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	65	wound Z4
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	66	wound D4

push!(initial_condition_array,(1.0/characteristic_volume)*5.82/2);	#	67	vein volume_vein
push!(initial_condition_array,(1.0/characteristic_volume)*1.01);	#	68	lungs volume_lungs
push!(initial_condition_array,(1.0/characteristic_volume)*5.82/2.);	#	69	artery volume_artery
push!(initial_condition_array,(1.0/characteristic_volume)*.36);	#	70	heart volume_heart
push!(initial_condition_array,(1.0/characteristic_volume)*.32);	#	71	kidney volume_kidney
push!(initial_condition_array,(1.0/characteristic_volume)*.005);	#	72	wound volume_wound
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	vein Z1
push!(time_constant_array,1.0);	#	2	vein E1
push!(time_constant_array,1.0);	#	3	vein D1
push!(time_constant_array,1.0);	#	4	vein Z2
push!(time_constant_array,1.0);	#	5	vein E2
push!(time_constant_array,1.0);	#	6	vein D2
push!(time_constant_array,1.0);	#	7	vein E3
push!(time_constant_array,1.0);	#	8	vein E4
push!(time_constant_array,1.0);	#	9	vein D3
push!(time_constant_array,1.0);	#	10	vein Z4
push!(time_constant_array,1.0);	#	11	vein D4

push!(time_constant_array,1.0);	#	12	lungs Z1
push!(time_constant_array,1.0);	#	13	lungs E1
push!(time_constant_array,1.0);	#	14	lungs D1
push!(time_constant_array,1.0);	#	15	lungs Z2
push!(time_constant_array,1.0);	#	16	lungs E2
push!(time_constant_array,1.0);	#	17	lungs D2
push!(time_constant_array,1.0);	#	18	lungs E3
push!(time_constant_array,1.0);	#	19	lungs E4
push!(time_constant_array,1.0);	#	20	lungs D3
push!(time_constant_array,1.0);	#	21	lungs Z4
push!(time_constant_array,1.0);	#	22	lungs D4

push!(time_constant_array,1.0);	#	23	artery Z1
push!(time_constant_array,1.0);	#	24	artery E1
push!(time_constant_array,1.0);	#	25	artery D1
push!(time_constant_array,1.0);	#	26	artery Z2
push!(time_constant_array,1.0);	#	27	artery E2
push!(time_constant_array,1.0);	#	28	artery D2
push!(time_constant_array,1.0);	#	29	artery E3
push!(time_constant_array,1.0);	#	30	artery E4
push!(time_constant_array,1.0);	#	31	artery D3
push!(time_constant_array,1.0);	#	32	artery Z4
push!(time_constant_array,1.0);	#	33	artery D4

push!(time_constant_array,1.0);	#	34	heart Z1
push!(time_constant_array,1.0);	#	35	heart E1
push!(time_constant_array,1.0);	#	36	heart D1
push!(time_constant_array,1.0);	#	37	heart Z2
push!(time_constant_array,1.0);	#	38	heart E2
push!(time_constant_array,1.0);	#	39	heart D2
push!(time_constant_array,1.0);	#	40	heart E3
push!(time_constant_array,1.0);	#	41	heart E4
push!(time_constant_array,1.0);	#	42	heart D3
push!(time_constant_array,1.0);	#	43	heart Z4
push!(time_constant_array,1.0);	#	44	heart D4

push!(time_constant_array,1.0);	#	45	kidney Z1
push!(time_constant_array,1.0);	#	46	kidney E1
push!(time_constant_array,1.0);	#	47	kidney D1
push!(time_constant_array,1.0);	#	48	kidney Z2
push!(time_constant_array,1.0);	#	49	kidney E2
push!(time_constant_array,1.0);	#	50	kidney D2
push!(time_constant_array,1.0);	#	51	kidney E3
push!(time_constant_array,1.0);	#	52	kidney E4
push!(time_constant_array,1.0);	#	53	kidney D3
push!(time_constant_array,1.0);	#	54	kidney Z4
push!(time_constant_array,1.0);	#	55	kidney D4

push!(time_constant_array,1.0);	#	56	wound Z1
push!(time_constant_array,1.0);	#	57	wound E1
push!(time_constant_array,1.0);	#	58	wound D1
push!(time_constant_array,1.0);	#	59	wound Z2
push!(time_constant_array,1.0);	#	60	wound E2
push!(time_constant_array,1.0);	#	61	wound D2
push!(time_constant_array,1.0);	#	62	wound E3
push!(time_constant_array,1.0);	#	63	wound E4
push!(time_constant_array,1.0);	#	64	wound D3
push!(time_constant_array,1.0);	#	65	wound Z4
push!(time_constant_array,1.0);	#	66	wound D4

push!(time_constant_array,1.0);	#	67	vein volume_vein
push!(time_constant_array,1.01);	#	68	lungs volume_lungs
push!(time_constant_array,1.0);	#	69	artery volume_artery
push!(time_constant_array,1.0);	#	70	heart volume_heart
push!(time_constant_array,1.0);	#	71	kidney volume_kidney
push!(time_constant_array,1.0);	#	72	wound volume_wound
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# vein

# lungs
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 1	lungs	generation_of_Z1: compartment: lungs [] -([])-> Z1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 2	lungs	generation_of_Z2: compartment: lungs [] -([])-> Z2

# artery

# heart

# kidney
push!(rate_constant_array,(characteristic_time)*0.1);	# 3	kidney	degredation_of_Z1: compartment: kidney Z1 -([])-> []

# wound
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 4	wound	conversion_of_Z1_to_E1_fast: compartment: wound Z1 -(E1)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 5	wound	degredation_of_E1: compartment: wound E1 -([])-> D1
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 6	wound	generation_of_E2: compartment: wound Z2 -(E1)-> E2
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 7	wound	E2_cataylzed_conversion_of_Z1_to_E1: compartment: wound Z1 -(E2)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 8	wound	E2_degregation: compartment: wound E2 -([])-> D2
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 9	wound	production_of_E3: compartment: wound E2 -(E4)-> E3
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 10	wound	degredation_of_E3: compartment: wound E3 -([])-> D3
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 11	wound	production_of_E4: compartment: wound Z4 -(E3)-> E4
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 12	wound	degreation_of_E4: compartment: wound E4 -([])-> D4
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 13	wound	long_range_production_of_E1: compartment: wound Z1 -(E4)-> E1

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[4,56] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[5,57] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[6,59] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[7,56] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[8,60] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[9,60] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[10,62] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[11,65] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[12,63] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[13,56] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(0,2);
# ------------------------------------------------------------------------------------------------ #
# vein

# lungs

# artery

# heart

# kidney

# wound

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
