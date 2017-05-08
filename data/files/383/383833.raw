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
# Generation timestamp: 03-28-2016 17:09:37
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
push!(flow_parameter_array,1.0);	# 1	vein_to_lungs: vein -> lungs
push!(flow_parameter_array,1.0);	# 2	lungs_to_artery: lungs -> artery
push!(flow_parameter_array,.5);	# 3	artery_to_heart: artery -> heart
push!(flow_parameter_array,.5);	# 4	heart_to_veins: heart -> vein
push!(flow_parameter_array,.5);	# 5	artery_to_kidney: artery -> kidney
push!(flow_parameter_array,.5);	# 6	kideny_to_vein: kidney -> vein
push!(flow_parameter_array,0.01);	# 7	artery_to_wound: artery -> wound
push!(flow_parameter_array,0.01);	# 8	artery_to_wound_reverse: wound -> artery
push!(flow_parameter_array,0.001);	# 9	artery_to_degredation: artery -> []
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/ReducedOrderModel/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/ReducedOrderModel/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(initial_condition_array,(1.0/characteristic_concentration)*1400);	#	1	vein FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	2	vein FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*60.0);	#	3	vein PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	4	vein APC
push!(initial_condition_array,(1.0/characteristic_concentration)*3400.0);	#	5	vein ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*12.0);	#	6	vein TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	7	vein TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*1400.0);	#	8	lungs FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	lungs FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*60.0);	#	10	lungs PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	11	lungs APC
push!(initial_condition_array,(1.0/characteristic_concentration)*3400.0);	#	12	lungs ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*12.0);	#	13	lungs TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	lungs TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*1400.0);	#	15	artery FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	artery FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*60.0);	#	17	artery PC
push!(initial_condition_array,(1.0/characteristic_concentration)*3400.0);	#	18	artery APC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	19	artery ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*12.0);	#	20	artery TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	21	artery TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*1400.0);	#	22	heart FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	23	heart FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*60.0);	#	24	heart PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	25	heart APC
push!(initial_condition_array,(1.0/characteristic_concentration)*3400.0);	#	26	heart ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*12.0);	#	27	heart TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	28	heart TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*1400.0);	#	29	kidney FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	30	kidney FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*60.0);	#	31	kidney PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	32	kidney APC
push!(initial_condition_array,(1.0/characteristic_concentration)*3400.0);	#	33	kidney ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*12.0);	#	34	kidney TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	35	kidney TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*1400);	#	36	wound FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	37	wound FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*60.0);	#	38	wound PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	39	wound APC
push!(initial_condition_array,(1.0/characteristic_concentration)*3400.0);	#	40	wound ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*12.0);	#	41	wound TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.005);	#	42	wound TRIGGER

#volume in L/kg of body weight
bodymass = 70 #In kg
push!(initial_condition_array,(1.0/characteristic_volume)*.0514*bodymass);	#	43	vein volume_vein
push!(initial_condition_array,(1.0/characteristic_volume)*.0076*bodymass);	#	44	lungs volume_lungs
push!(initial_condition_array,(1.0/characteristic_volume)*.0257*bodymass);	#	45	artery volume_artery
push!(initial_condition_array,(1.0/characteristic_volume)*.0047*bodymass);	#	46	heart volume_heart
push!(initial_condition_array,(1.0/characteristic_volume)*.0044*bodymass);	#	47	kidney volume_kidney
push!(initial_condition_array,(1.0/characteristic_volume)*.0001*bodymass);	#	48	wound volume_wound
# ------------------------------------------------------------------------------------------------ #

# Formulate the time constant array - 
time_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0);	#	1	vein FII
push!(time_constant_array,1.0);	#	2	vein FIIa
push!(time_constant_array,1.0);	#	3	vein PC
push!(time_constant_array,1.0);	#	4	vein APC
push!(time_constant_array,1.0);	#	5	vein ATIII
push!(time_constant_array,1.0);	#	6	vein TM
push!(time_constant_array,1.0);	#	7	vein TRIGGER

push!(time_constant_array,1.0);	#	8	lungs FII
push!(time_constant_array,1.0);	#	9	lungs FIIa
push!(time_constant_array,1.0);	#	10	lungs PC
push!(time_constant_array,1.0);	#	11	lungs APC
push!(time_constant_array,1.0);	#	12	lungs ATIII
push!(time_constant_array,1.0);	#	13	lungs TM
push!(time_constant_array,1.0);	#	14	lungs TRIGGER

push!(time_constant_array,1.0);	#	15	artery FII
push!(time_constant_array,1.0);	#	16	artery FIIa
push!(time_constant_array,1.0);	#	17	artery PC
push!(time_constant_array,1.0);	#	18	artery APC
push!(time_constant_array,1.0);	#	19	artery ATIII
push!(time_constant_array,1.0);	#	20	artery TM
push!(time_constant_array,1.0);	#	21	artery TRIGGER

push!(time_constant_array,1.0);	#	22	heart FII
push!(time_constant_array,1.0);	#	23	heart FIIa
push!(time_constant_array,1.0);	#	24	heart PC
push!(time_constant_array,1.0);	#	25	heart APC
push!(time_constant_array,1.0);	#	26	heart ATIII
push!(time_constant_array,1.0);	#	27	heart TM
push!(time_constant_array,1.0);	#	28	heart TRIGGER

push!(time_constant_array,1.0);	#	29	kidney FII
push!(time_constant_array,1.0);	#	30	kidney FIIa
push!(time_constant_array,1.0);	#	31	kidney PC
push!(time_constant_array,1.0);	#	32	kidney APC
push!(time_constant_array,1.0);	#	33	kidney ATIII
push!(time_constant_array,1.0);	#	34	kidney TM
push!(time_constant_array,1.0);	#	35	kidney TRIGGER

push!(time_constant_array,1.0);	#	36	wound FII
push!(time_constant_array,1.0);	#	37	wound FIIa
push!(time_constant_array,1.0);	#	38	wound PC
push!(time_constant_array,1.0);	#	39	wound APC
push!(time_constant_array,1.0);	#	40	wound ATIII
push!(time_constant_array,1.0);	#	41	wound TM
push!(time_constant_array,1.0);	#	42	wound TRIGGER

push!(time_constant_array,1.0);	#	43	vein volume_vein
push!(time_constant_array,1.0);	#	44	lungs volume_lungs
push!(time_constant_array,1.0);	#	45	artery volume_artery
push!(time_constant_array,1.0);	#	46	heart volume_heart
push!(time_constant_array,1.0);	#	47	kidney volume_kidney
push!(time_constant_array,1.0);	#	48	wound volume_wound
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
# vein
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 1	vein	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 2	vein	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 3	vein	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 4	vein	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 5	vein	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 6	vein	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 7	vein	reaction7: compartment: * [] -([])-> TRIGGER

# lungs
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 8	lungs	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 9	lungs	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 10	lungs	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 11	lungs	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 12	lungs	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 13	lungs	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 14	lungs	reaction7: compartment: * [] -([])-> TRIGGER

# artery
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 15	artery	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 16	artery	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 17	artery	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 18	artery	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 19	artery	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 20	artery	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 21	artery	reaction7: compartment: * [] -([])-> TRIGGER

# heart
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 22	heart	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 23	heart	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 24	heart	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 25	heart	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 26	heart	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 27	heart	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 28	heart	reaction7: compartment: * [] -([])-> TRIGGER

# kidney
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 29	kidney	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 30	kidney	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 31	kidney	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 32	kidney	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 33	kidney	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 34	kidney	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 35	kidney	reaction7: compartment: * [] -([])-> TRIGGER

# wound
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 36	wound	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 37	wound	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 38	wound	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 39	wound	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 40	wound	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 41	wound	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 42	wound	reaction7: compartment: * [] -([])-> TRIGGER

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
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
