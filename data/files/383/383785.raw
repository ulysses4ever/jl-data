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
# Generation timestamp: 05-25-2016 18:04:41
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
push!(flow_parameter_array,1.0);	# 1	vein_to_heart: vein -> heart
push!(flow_parameter_array,1.0);	# 2	heart_to_lungs: heart -> lungs
push!(flow_parameter_array,1.0);	# 3	lungs_to_heart: lungs -> heart
push!(flow_parameter_array,1.0);	# 4	heart_to_artery: heart -> artery
push!(flow_parameter_array,0.175);	# 5	artery_to_kidney: artery -> kidney
push!(flow_parameter_array,0.175);	# 6	kidney_to_vein: kidney -> vein
push!(flow_parameter_array,0.227);	# 7	artery_to_liver: artery -> liver
push!(flow_parameter_array,0.227);	# 8	liver_to_vein: artery -> vein
push!(flow_parameter_array,0.597);	# 9	artery_to_bulk: artery -> bulk
push!(flow_parameter_array,0.598);	# 10	bulk_to_vein: bulk -> vein
push!(flow_parameter_array,0.007);	# 11	artery_to_wound: artery -> wound
push!(flow_parameter_array,0.0005);	# 12	artery_to_wound_reverse: wound -> artery
push!(flow_parameter_array,0.007);	# 13	wound_to_degredation: wound -> []
#flow_parameter_array = zeros(1,13)
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
#S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/ReducedOrderModelBetterBody/network/Network.dat"));
S = float(open(readdlm,"../network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix -
#C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/ReducedOrderModelBetterBody/network/Connectivity.dat"));
C = float(open(readdlm,"../network/Connectivity.dat"));

# Formulate the initial condition array -
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
fIIa_inital = 1400
PC_inital = 60
ATIII_inital = 5000
TM_inital=12

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	1	vein FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	2	vein FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	3	vein PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	4	vein APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	5	vein ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	6	vein TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	7	vein TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	8	heart FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	heart FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	10	heart PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	11	heart APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	12	heart ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	13	heart TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	heart TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	15	lungs FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	lungs FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	17	lungs PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	18	lungs APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	19	lungs ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	20	lungs TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	21	lungs TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	22	artery FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	23	artery FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	24	artery PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	25	artery APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	26	artery ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	27	artery TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	28	artery TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	29	kidney FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	30	kidney FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	31	kidney PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	32	kidney APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	33	kidney ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	34	kidney TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	35	kidney TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	36	liver FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	37	liver FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	38	liver PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	39	liver APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	40	liver ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	41	liver TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	42	liver TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	43	bulk FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	44	bulk FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	45	bulk PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	46	bulk APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	47	bulk ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	48	bulk TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	49	bulk TRIGGER

push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	50	wound FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	51	wound FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	52	wound PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	53	wound APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	54	wound ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	55	wound TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.05);	#	56	wound TRIGGER

#volumes of blood from "Suggested Reference Values For Regional Blood Volumes in Humans"
#
bodymass = 70 #In kg
bloodvolume= 6.234 #in L, from Total blood volume in healthy young and older men
push!(initial_condition_array,(1.0/characteristic_volume)*.18*bloodvolume);	#	57	vein volume_vein
push!(initial_condition_array,(1.0/characteristic_volume)*.10*bloodvolume);	#	58	heart volume_heart
push!(initial_condition_array,(1.0/characteristic_volume)*.125*bloodvolume);	#	59	lungs volume_lungs
push!(initial_condition_array,(1.0/characteristic_volume)*.06*bloodvolume);	#	60	artery volume_artery
push!(initial_condition_array,(1.0/characteristic_volume)*.02*bloodvolume);	#	61	kidney volume_kidney
push!(initial_condition_array,(1.0/characteristic_volume)*.1*bloodvolume);	#	62	liver volume_liver
push!(initial_condition_array,(1.0/characteristic_volume)*.41*bloodvolume);	#	63	bulk volume_bulk
push!(initial_condition_array,(1.0/characteristic_volume)*.009*bloodvolume);	#	64	wound volume_wound
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

push!(time_constant_array,1.0);	#	8	heart FII
push!(time_constant_array,1.0);	#	9	heart FIIa
push!(time_constant_array,1.0);	#	10	heart PC
push!(time_constant_array,1.0);	#	11	heart APC
push!(time_constant_array,1.0);	#	12	heart ATIII
push!(time_constant_array,1.0);	#	13	heart TM
push!(time_constant_array,1.0);	#	14	heart TRIGGER

push!(time_constant_array,1.0);	#	15	lungs FII
push!(time_constant_array,1.0);	#	16	lungs FIIa
push!(time_constant_array,1.0);	#	17	lungs PC
push!(time_constant_array,1.0);	#	18	lungs APC
push!(time_constant_array,1.0);	#	19	lungs ATIII
push!(time_constant_array,1.0);	#	20	lungs TM
push!(time_constant_array,1.0);	#	21	lungs TRIGGER

push!(time_constant_array,1.0);	#	22	artery FII
push!(time_constant_array,1.0);	#	23	artery FIIa
push!(time_constant_array,1.0);	#	24	artery PC
push!(time_constant_array,1.0);	#	25	artery APC
push!(time_constant_array,1.0);	#	26	artery ATIII
push!(time_constant_array,1.0);	#	27	artery TM
push!(time_constant_array,1.0);	#	28	artery TRIGGER

push!(time_constant_array,1.0);	#	29	kidney FII
push!(time_constant_array,1.0);	#	30	kidney FIIa
push!(time_constant_array,1.0);	#	31	kidney PC
push!(time_constant_array,1.0);	#	32	kidney APC
push!(time_constant_array,1.0);	#	33	kidney ATIII
push!(time_constant_array,1.0);	#	34	kidney TM
push!(time_constant_array,1.0);	#	35	kidney TRIGGER

push!(time_constant_array,1.0);	#	36	liver FII
push!(time_constant_array,1.0);	#	37	liver FIIa
push!(time_constant_array,1.0);	#	38	liver PC
push!(time_constant_array,1.0);	#	39	liver APC
push!(time_constant_array,1.0);	#	40	liver ATIII
push!(time_constant_array,1.0);	#	41	liver TM
push!(time_constant_array,1.0);	#	42	liver TRIGGER

push!(time_constant_array,1.0);	#	43	bulk FII
push!(time_constant_array,1.0);	#	44	bulk FIIa
push!(time_constant_array,1.0);	#	45	bulk PC
push!(time_constant_array,1.0);	#	46	bulk APC
push!(time_constant_array,1.0);	#	47	bulk ATIII
push!(time_constant_array,1.0);	#	48	bulk TM
push!(time_constant_array,1.0);	#	49	bulk TRIGGER

push!(time_constant_array,1.0);	#	50	wound FII
push!(time_constant_array,1.0);	#	51	wound FIIa
push!(time_constant_array,1.0);	#	52	wound PC
push!(time_constant_array,1.0);	#	53	wound APC
push!(time_constant_array,1.0);	#	54	wound ATIII
push!(time_constant_array,1.0);	#	55	wound TM
push!(time_constant_array,1.0);	#	56	wound TRIGGER

push!(time_constant_array,1.0);	#	57	vein volume_vein
push!(time_constant_array,1.0);	#	58	heart volume_heart
push!(time_constant_array,1.0);	#	59	lungs volume_lungs
push!(time_constant_array,1.0);	#	60	artery volume_artery
push!(time_constant_array,1.0);	#	61	kidney volume_kidney
push!(time_constant_array,1.0);	#	62	liver volume_liver
push!(time_constant_array,1.0);	#	63	bulk volume_bulk
push!(time_constant_array,1.0);	#	64	wound volume_wound
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

# heart
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 8	heart	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 9	heart	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 10	heart	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 11	heart	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 12	heart	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 13	heart	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 14	heart	reaction7: compartment: * [] -([])-> TRIGGER

# lungs
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 15	lungs	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 16	lungs	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 17	lungs	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 18	lungs	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 19	lungs	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 20	lungs	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 21	lungs	reaction7: compartment: * [] -([])-> TRIGGER

# artery
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 22	artery	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 23	artery	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 24	artery	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 25	artery	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 26	artery	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 27	artery	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 28	artery	reaction7: compartment: * [] -([])-> TRIGGER

# kidney
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 29	kidney	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 30	kidney	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 31	kidney	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 32	kidney	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 33	kidney	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 34	kidney	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 35	kidney	reaction7: compartment: * [] -([])-> TRIGGER

# liver
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 36	liver	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 37	liver	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 38	liver	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 39	liver	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 40	liver	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 41	liver	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 42	liver	reaction7: compartment: * [] -([])-> TRIGGER

# bulk
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 43	bulk	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 44	bulk	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 45	bulk	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 46	bulk	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 47	bulk	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 48	bulk	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 49	bulk	reaction7: compartment: * [] -([])-> TRIGGER

# wound
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 50	wound	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 51	wound	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 52	wound	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 53	wound	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 54	wound	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 55	wound	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 56	wound	reaction7: compartment: * [] -([])-> TRIGGER

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array -
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
# ------------------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array -
control_parameter_array = zeros(0,2);
# ------------------------------------------------------------------------------------------------ #
# vein

# heart

# lungs

# artery

# kidney

# liver

# bulk

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
