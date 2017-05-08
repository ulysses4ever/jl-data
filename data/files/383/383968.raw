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
# Generation timestamp: 03-09-2016 11:18:15
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
push!(flow_parameter_array,0.0);	# 1	vein_to_lungs: vein -> lungs
push!(flow_parameter_array,0.0);	# 2	lungs_to_artery: lung -> artery
push!(flow_parameter_array,0.0);	# 3	artery_to_heart: artery -> heart
push!(flow_parameter_array,0.0);	# 4	heart_to_veins: heart -> vein
push!(flow_parameter_array,0.0);	# 5	artery_to_kidney: artery -> kidney
push!(flow_parameter_array,0.0);	# 6	kideny_to_vein: kidney -> vein
push!(flow_parameter_array,0.0);	# 7	artery_to_wound: artery -> wound
push!(flow_parameter_array,0.0);	# 8	artery_to_wound_reverse: wound -> artery
push!(flow_parameter_array,0.0);	# 9	artery_to_degredation: artery -> []
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/simpleCoagulationWithCompartments/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/simpleCoagulationWithCompartments/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	1	vein Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	2	vein E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	3	vein E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	4	vein D1

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	5	lungs Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	6	lungs E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	7	lungs E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	8	lungs D1

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	9	lung Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	10	lung E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	11	lung E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	12	lung D1

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	13	artery Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	14	artery E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	15	artery E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	artery D1

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	17	heart Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	18	heart E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	19	heart E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	20	heart D1

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	21	kidney Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	22	kidney E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	23	kidney E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	24	kidney D1

push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	25	wound Z1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	26	wound E1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	27	wound E0
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	28	wound D1

push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	29	vein volume_vein
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	30	lungs volume_lungs
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	31	lung volume_lung
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	32	artery volume_artery
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	33	heart volume_heart
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	34	kidney volume_kidney
push!(initial_condition_array,(1.0/characteristic_volume)*.05);	#	35	wound volume_wound
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	vein Z1
push!(time_constant_array,1.0);	#	2	vein E1
push!(time_constant_array,1.0);	#	3	vein E0
push!(time_constant_array,1.0);	#	4	vein D1

push!(time_constant_array,1.0);	#	5	lungs Z1
push!(time_constant_array,1.0);	#	6	lungs E1
push!(time_constant_array,1.0);	#	7	lungs E0
push!(time_constant_array,1.0);	#	8	lungs D1

push!(time_constant_array,1.0);	#	9	lung Z1
push!(time_constant_array,1.0);	#	10	lung E1
push!(time_constant_array,1.0);	#	11	lung E0
push!(time_constant_array,1.0);	#	12	lung D1

push!(time_constant_array,1.0);	#	13	artery Z1
push!(time_constant_array,1.0);	#	14	artery E1
push!(time_constant_array,1.0);	#	15	artery E0
push!(time_constant_array,1.0);	#	16	artery D1

push!(time_constant_array,1.0);	#	17	heart Z1
push!(time_constant_array,1.0);	#	18	heart E1
push!(time_constant_array,1.0);	#	19	heart E0
push!(time_constant_array,1.0);	#	20	heart D1

push!(time_constant_array,1.0);	#	21	kidney Z1
push!(time_constant_array,1.0);	#	22	kidney E1
push!(time_constant_array,1.0);	#	23	kidney E0
push!(time_constant_array,1.0);	#	24	kidney D1

push!(time_constant_array,1.0);	#	25	wound Z1
push!(time_constant_array,1.0);	#	26	wound E1
push!(time_constant_array,1.0);	#	27	wound E0
push!(time_constant_array,1.0);	#	28	wound D1

push!(time_constant_array,1.0);	#	29	vein volume_vein
push!(time_constant_array,1.0);	#	30	lungs volume_lungs
push!(time_constant_array,1.0);	#	31	lung volume_lung
push!(time_constant_array,1.0);	#	32	artery volume_artery
push!(time_constant_array,1.0);	#	33	heart volume_heart
push!(time_constant_array,1.0);	#	34	kidney volume_kidney
push!(time_constant_array,1.0);	#	35	wound volume_wound
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# vein

# lungs
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 1	lungs	generation_of_Z1: compartment: lungs [] -([])-> Z1

# lung

# artery

# heart

# kidney
push!(rate_constant_array,(characteristic_time)*1.0);	# 2	kidney	degredation_of_Z1: compartment: kidney Z1 -([])-> []

# wound
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 3	wound	conversion_of_Z1_to_E1_slow: compartment: wound Z1 -(E0)-> E1
push!(rate_constant_array,(1.0/characteristic_time)*5.0);	# 4	wound	conversion_of_Z1_to_E1_fast: compartment: wound Z1 -(E1)-> E1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 5	wound	generation_of_E0: compartment: wound [] -([])-> E0
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 6	wound	degredation_of_E1: compartment: wound E1 -([])-> D1
push!(rate_constant_array,(characteristic_time)*0.1);	# 7	wound	degredation_of_E0: compartment: wound E0 -([])-> []

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[3,25] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[4,25] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[6,26] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(0,2);
# ------------------------------------------------------------------------------------------------ #
# vein

# lungs

# lung

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
