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
# Generation timestamp: 04-06-2016 09:04:51
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
push!(flow_parameter_array,0.0);	# 1	C1IN: [] -> C1
push!(flow_parameter_array,0.0);	# 2	C1OUT: C1 -> []
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/wPlatelets/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/wPlatelets/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*10.01);	#	1	C1 inactive_initiator
push!(initial_condition_array,(1.0/characteristic_concentration)*.01);	#	2	C1 active_initiator
push!(initial_condition_array,(1.0/characteristic_concentration)*1.0);	#	3	C1 trigger
push!(initial_condition_array,(1.0/characteristic_concentration)*1400.0);	#	4	C1 FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0);	#	5	C1 FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*.024);	#	6	C1 PL
push!(initial_condition_array,(1.0/characteristic_concentration)*0.00);	#	7	C1 PLa
push!(initial_condition_array,(1.0/characteristic_concentration)*60.0);	#	8	C1 PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	C1 APC
push!(initial_condition_array,(1.0/characteristic_concentration)*2500.0);	#	10	C1 ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*2.5);	#	11	C1 TFPI
push!(initial_condition_array,(1.0/characteristic_concentration)*8800.0);	#	12	C1 Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	13	C1 Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	C1 Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	15	C1 Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	C1 D_dimer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	17	C1 Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	18	C1 Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	19	C1 tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	20	C1 uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	21	C1 antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*73);	#	22	C1 TAFI
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	23	C1 PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*70.);	#	24	C1 fXIII

push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	25	C1 volume_C1
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	C1 inactive_initiator
push!(time_constant_array,1.0);	#	2	C1 active_initiator
push!(time_constant_array,1.0);	#	3	C1 trigger
push!(time_constant_array,1.0);	#	4	C1 FII
push!(time_constant_array,1.0);	#	5	C1 FIIa
push!(time_constant_array,1.0);	#	6	C1 PL
push!(time_constant_array,1.0);	#	7	C1 PLa
push!(time_constant_array,1.0);	#	8	C1 PC
push!(time_constant_array,1.0);	#	9	C1 APC
push!(time_constant_array,1.0);	#	10	C1 ATIII
push!(time_constant_array,1.0);	#	11	C1 TFPI
push!(time_constant_array,1.0);	#	12	C1 Fibrinogen
push!(time_constant_array,1.0);	#	13	C1 Fibrin_monomer
push!(time_constant_array,1.0);	#	14	C1 Protofibril
push!(time_constant_array,1.0);	#	15	C1 Fibrin
push!(time_constant_array,1.0);	#	16	C1 D_dimer
push!(time_constant_array,1.0);	#	17	C1 Plasmin
push!(time_constant_array,1.0);	#	18	C1 Plasminogen
push!(time_constant_array,1.0);	#	19	C1 tPA
push!(time_constant_array,1.0);	#	20	C1 uPA
push!(time_constant_array,1.0);	#	21	C1 antiplasmin
push!(time_constant_array,1.0);	#	22	C1 TAFI
push!(time_constant_array,1.0);	#	23	C1 PAI_1
push!(time_constant_array,1.0);	#	24	C1 fXIII

push!(time_constant_array,1.0);	#	25	C1 volume_C1
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# C1
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 1	C1	activation_initiator: compartment: C1 inactive_initiator -(trigger)-> active_initiator
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 2	C1	slow_thrombin_generation: compartment: C1 FII -(active_initiator)-> FIIa
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 3	C1	platelet_activation: compartment: C1 PL -(FIIa)-> PLa
push!(rate_constant_array,(1.0/characteristic_time)*200.0);	# 4	C1	fast_thrombin_generation: compartment: C1 FII -(PLa)-> FIIa
push!(rate_constant_array,(1.0/characteristic_time)*.10);	# 5	C1	activation_of_APC: compartment: C1 PC -(FIIa)-> APC
push!(rate_constant_array,(characteristic_time)*.01);	# 6	C1	deactivation_of_FIIa_by_ATIII: compartment: C1 FIIa+ATIII -([])-> []
push!(rate_constant_array,(characteristic_time)*0.1);	# 7	C1	deactivation_by_TFPI: compartment: C1 TFPI+active_initiator -([])-> []
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 8	C1	fibrin_monomer_formation: compartment: C1 Fibrinogen -(FIIa)-> Fibrin_monomer
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 9	C1	protofibril_formation: compartment: C1 Fibrin_monomer -([])-> Protofibril
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 10	C1	protofibril_formation_reverse: compartment: C1 Protofibril -([])-> Fibrin
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 11	C1	fibrin_degradation_FDPs_Ddimer: compartment: C1 Fibrin -(Plasmin)-> D_dimer
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 12	C1	plasmin_generation_tPA: compartment: C1 Plasminogen -(tPA)-> Plasmin
push!(rate_constant_array,(1.0/characteristic_time)*1.0);	# 13	C1	plasmin_generation_uPA: compartment: C1 Plasminogen -(uPA)-> Plasmin

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
saturation_constant_array[1,1] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[2,4] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[3,6] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[4,4] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[5,8] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[8,12] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[9,13] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[10,14] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[11,15] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[12,18] = 1.0*(1.0/characteristic_concentration);
saturation_constant_array[13,18] = 1.0*(1.0/characteristic_concentration);
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(10,2);
# ------------------------------------------------------------------------------------------------ #
# C1
control_parameter_array[1,1] = 0.1;	#	1 Gain: 	APC --> fast_thrombin_generation type:inhibition (deactive_by_APC_C1)
control_parameter_array[1,2] = 1.0;	#	1 Order: 	APC --> fast_thrombin_generation type:inhibition (deactive_by_APC_C1)
control_parameter_array[2,1] = 0.1;	#	2 Gain: 	antiplasmin --> plasmin_generation_tPA type:inhibition (plasmin_inhibition_C1)
control_parameter_array[2,2] = 1.0;	#	2 Order: 	antiplasmin --> plasmin_generation_tPA type:inhibition (plasmin_inhibition_C1)
control_parameter_array[3,1] = 0.1;	#	3 Gain: 	antiplasmin --> plasmin_generation_uPA type:inhibition (plasmin_inhibition_C1)
control_parameter_array[3,2] = 1.0;	#	3 Order: 	antiplasmin --> plasmin_generation_uPA type:inhibition (plasmin_inhibition_C1)
control_parameter_array[4,1] = 0.1;	#	4 Gain: 	TAFI --> plasmin_generation_tPA type:inhibition (plasminogen_activation_inhibition_C1)
control_parameter_array[4,2] = 1.0;	#	4 Order: 	TAFI --> plasmin_generation_tPA type:inhibition (plasminogen_activation_inhibition_C1)
control_parameter_array[5,1] = 0.1;	#	5 Gain: 	TAFI --> plasmin_generation_uPA type:inhibition (plasminogen_activation_inhibition_C1)
control_parameter_array[5,2] = 1.0;	#	5 Order: 	TAFI --> plasmin_generation_uPA type:inhibition (plasminogen_activation_inhibition_C1)
control_parameter_array[6,1] = 0.1;	#	6 Gain: 	PAI_1 --> plasmin_generation_tPA type:inhibition (tPA-inhibition_C1)
control_parameter_array[6,2] = 1.0;	#	6 Order: 	PAI_1 --> plasmin_generation_tPA type:inhibition (tPA-inhibition_C1)
control_parameter_array[7,1] = 0.1;	#	7 Gain: 	PAI_1 --> plasmin_generation_uPA type:inhibition (uPA-inhibition_C1)
control_parameter_array[7,2] = 1.0;	#	7 Order: 	PAI_1 --> plasmin_generation_uPA type:inhibition (uPA-inhibition_C1)
control_parameter_array[8,1] = 0.1;	#	8 Gain: 	APC --> plasmin_generation_tPA type:activation (activation_plasmin_tPA_APC_C1)
control_parameter_array[8,2] = 1.0;	#	8 Order: 	APC --> plasmin_generation_tPA type:activation (activation_plasmin_tPA_APC_C1)
control_parameter_array[9,1] = 0.1;	#	9 Gain: 	APC --> plasmin_generation_uPA type:activation (activation_plasmin_uPA_APC_C1)
control_parameter_array[9,2] = 1.0;	#	9 Order: 	APC --> plasmin_generation_uPA type:activation (activation_plasmin_uPA_APC_C1)
control_parameter_array[10,1] = 0.1;	#	10 Gain: 	fXIII --> fibrin_degradation_FDPs_Ddimer type:inhibition (fibrinolysis_inhibition_by_fXIII_C1)
control_parameter_array[10,2] = 1.0;	#	10 Order: 	fXIII --> fibrin_degradation_FDPs_Ddimer type:inhibition (fibrinolysis_inhibition_by_fXIII_C1)

# ------------------------------------------------------------------------------------------------ #

# Input concentration array - 
input_concentration_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 1 inactive_initiator_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 2 active_initiator_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 3 trigger_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 4 FII_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 5 FIIa_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 6 PL_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 7 PLa_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 8 PC_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 9 APC_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 10 ATIII_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 11 TFPI_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 12 Fibrinogen_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 13 Fibrin_monomer_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 14 Protofibril_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 15 Fibrin_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 16 D_dimer_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 17 Plasmin_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 18 Plasminogen_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 19 tPA_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 20 uPA_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 21 antiplasmin_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 22 TAFI_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 23 PAI_1_input_C1
push!(input_concentration_array,(1.0/characteristic_concentration)*0.0);	# 24 fXIII_input_C1
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
