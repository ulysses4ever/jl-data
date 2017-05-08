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
# Generation timestamp: 05-06-2016 09:57:05
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
push!(flow_parameter_array,0.0);	# 2	lungs_to_artery: lungs -> artery
push!(flow_parameter_array,0.0);	# 3	artery_to_heart: artery -> heart
push!(flow_parameter_array,0.0);	# 4	heart_to_veins: heart -> vein
push!(flow_parameter_array,0.0);	# 5	artery_to_kidney: artery -> kidney
push!(flow_parameter_array,0.0);	# 6	kidney_to_vein: kidney -> vein
push!(flow_parameter_array,0.0);	# 7	artery_to_wound: artery -> wound
push!(flow_parameter_array,0.0);	# 8	artery_to_wound_reverse: wound -> artery
push!(flow_parameter_array,0.0);	# 9	wound_to_degredation: wound -> []
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
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/updatedFibrinModel/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/updatedFibrinModel/network/Connectivity.dat"));

# Formulate the initial condition array - 
initial_condition_array = Float64[];
# ------------------------------------------------------------------------------------------------ #
fIIa_inital = 1400
PC_inital = 60
ATIII_inital = 5000
TM_inital=12

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	1	vein FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	2	vein FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	3	vein PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	4	vein APC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	5	vein ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	6	vein TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	7	vein TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	8	vein Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	9	vein Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	10	vein Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	11	vein Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	12	vein tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	13	vein uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	14	vein Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	15	vein Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	16	vein antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	17	vein PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	18	vein Fiber
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	19	vein TAT
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	20	vein PAP

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	21	lungs FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	22	lungs FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	23	lungs PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	24	lungs APC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	25	lungs ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	26	lungs TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	27	lungs TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	28	lungs Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	29	lungs Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	30	lungs Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	31	lungs Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	32	lungs tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	33	lungs uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	34	lungs Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	35	lungs Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	36	lungs antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	37	lungs PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	38	lungs Fiber
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	39	lungs TAT
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	40	lungs PAP

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	41	artery FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	42	artery FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	43	artery PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	44	artery APC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	45	artery ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	46	artery TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	47	artery TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	48	artery Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	49	artery Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	50	artery Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	51	artery Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	52	artery tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	53	artery uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	54	artery Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	55	artery Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	56	artery antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	57	artery PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	58	artery Fiber
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	59	artery TAT
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	60	artery PAP

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	61	heart FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	62	heart FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	63	heart PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	64	heart APC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	65	heart ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	66	heart TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	67	heart TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	68	heart Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	69	heart Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	70	heart Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	71	heart Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	72	heart tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	73	heart uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	74	heart Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	75	heart Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	76	heart antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	77	heart PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	78	heart Fiber
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	79	heart TAT
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	80	heart PAP

push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	81	kidney FII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	82	kidney FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	83	kidney PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	84	kidney APC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	85	kidney ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	86	kidney TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	87	kidney TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	88	kidney Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	89	kidney Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	90	kidney Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	91	kidney Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	92	kidney tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	93	kidney uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	94	kidney Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	95	kidney Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	96	kidney antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	97	kidney PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	98	kidney Fiber
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	99	kidney TAT
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0);	#	100	kidney PAP

push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	101	wound FII
push!(initial_condition_array,(1.0/characteristic_concentration)*fIIa_inital);	#	102	wound FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_inital);	#	103	wound PC
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	104	wound APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_inital);	#	105	wound ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_inital);	#	106	wound TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0005);	#	107	wound TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	108	wound Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	109	wound Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	110	wound Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	111	wound Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	112	wound tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	113	wound uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	114	wound Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	115	wound Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	116	wound antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	117	wound PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	118	wound Fiber
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	119	wound TAT
push!(initial_condition_array,(1.0/characteristic_concentration)*0.01);	#	120	wound PAP

push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	121	vein volume_vein
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	122	lungs volume_lungs
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	123	artery volume_artery
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	124	heart volume_heart
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	125	kidney volume_kidney
push!(initial_condition_array,(1.0/characteristic_volume)*1.0);	#	126	wound volume_wound
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
push!(time_constant_array,1.0);	#	8	vein Fibrin
push!(time_constant_array,1.0);	#	9	vein Plasmin
push!(time_constant_array,1.0);	#	10	vein Fibrinogen
push!(time_constant_array,1.0);	#	11	vein Plasminogen
push!(time_constant_array,1.0);	#	12	vein tPA
push!(time_constant_array,1.0);	#	13	vein uPA
push!(time_constant_array,1.0);	#	14	vein Fibrin_monomer
push!(time_constant_array,1.0);	#	15	vein Protofibril
push!(time_constant_array,1.0);	#	16	vein antiplasmin
push!(time_constant_array,1.0);	#	17	vein PAI_1
push!(time_constant_array,1.0);	#	18	vein Fiber
push!(time_constant_array,1.0);	#	19	vein TAT
push!(time_constant_array,1.0);	#	20	vein PAP

push!(time_constant_array,1.0);	#	21	lungs FII
push!(time_constant_array,1.0);	#	22	lungs FIIa
push!(time_constant_array,1.0);	#	23	lungs PC
push!(time_constant_array,1.0);	#	24	lungs APC
push!(time_constant_array,1.0);	#	25	lungs ATIII
push!(time_constant_array,1.0);	#	26	lungs TM
push!(time_constant_array,1.0);	#	27	lungs TRIGGER
push!(time_constant_array,1.0);	#	28	lungs Fibrin
push!(time_constant_array,1.0);	#	29	lungs Plasmin
push!(time_constant_array,1.0);	#	30	lungs Fibrinogen
push!(time_constant_array,1.0);	#	31	lungs Plasminogen
push!(time_constant_array,1.0);	#	32	lungs tPA
push!(time_constant_array,1.0);	#	33	lungs uPA
push!(time_constant_array,1.0);	#	34	lungs Fibrin_monomer
push!(time_constant_array,1.0);	#	35	lungs Protofibril
push!(time_constant_array,1.0);	#	36	lungs antiplasmin
push!(time_constant_array,1.0);	#	37	lungs PAI_1
push!(time_constant_array,1.0);	#	38	lungs Fiber
push!(time_constant_array,1.0);	#	39	lungs TAT
push!(time_constant_array,1.0);	#	40	lungs PAP

push!(time_constant_array,1.0);	#	41	artery FII
push!(time_constant_array,1.0);	#	42	artery FIIa
push!(time_constant_array,1.0);	#	43	artery PC
push!(time_constant_array,1.0);	#	44	artery APC
push!(time_constant_array,1.0);	#	45	artery ATIII
push!(time_constant_array,1.0);	#	46	artery TM
push!(time_constant_array,1.0);	#	47	artery TRIGGER
push!(time_constant_array,1.0);	#	48	artery Fibrin
push!(time_constant_array,1.0);	#	49	artery Plasmin
push!(time_constant_array,1.0);	#	50	artery Fibrinogen
push!(time_constant_array,1.0);	#	51	artery Plasminogen
push!(time_constant_array,1.0);	#	52	artery tPA
push!(time_constant_array,1.0);	#	53	artery uPA
push!(time_constant_array,1.0);	#	54	artery Fibrin_monomer
push!(time_constant_array,1.0);	#	55	artery Protofibril
push!(time_constant_array,1.0);	#	56	artery antiplasmin
push!(time_constant_array,1.0);	#	57	artery PAI_1
push!(time_constant_array,1.0);	#	58	artery Fiber
push!(time_constant_array,1.0);	#	59	artery TAT
push!(time_constant_array,1.0);	#	60	artery PAP

push!(time_constant_array,1.0);	#	61	heart FII
push!(time_constant_array,1.0);	#	62	heart FIIa
push!(time_constant_array,1.0);	#	63	heart PC
push!(time_constant_array,1.0);	#	64	heart APC
push!(time_constant_array,1.0);	#	65	heart ATIII
push!(time_constant_array,1.0);	#	66	heart TM
push!(time_constant_array,1.0);	#	67	heart TRIGGER
push!(time_constant_array,1.0);	#	68	heart Fibrin
push!(time_constant_array,1.0);	#	69	heart Plasmin
push!(time_constant_array,1.0);	#	70	heart Fibrinogen
push!(time_constant_array,1.0);	#	71	heart Plasminogen
push!(time_constant_array,1.0);	#	72	heart tPA
push!(time_constant_array,1.0);	#	73	heart uPA
push!(time_constant_array,1.0);	#	74	heart Fibrin_monomer
push!(time_constant_array,1.0);	#	75	heart Protofibril
push!(time_constant_array,1.0);	#	76	heart antiplasmin
push!(time_constant_array,1.0);	#	77	heart PAI_1
push!(time_constant_array,1.0);	#	78	heart Fiber
push!(time_constant_array,1.0);	#	79	heart TAT
push!(time_constant_array,1.0);	#	80	heart PAP

push!(time_constant_array,1.0);	#	81	kidney FII
push!(time_constant_array,1.0);	#	82	kidney FIIa
push!(time_constant_array,1.0);	#	83	kidney PC
push!(time_constant_array,1.0);	#	84	kidney APC
push!(time_constant_array,1.0);	#	85	kidney ATIII
push!(time_constant_array,1.0);	#	86	kidney TM
push!(time_constant_array,1.0);	#	87	kidney TRIGGER
push!(time_constant_array,1.0);	#	88	kidney Fibrin
push!(time_constant_array,1.0);	#	89	kidney Plasmin
push!(time_constant_array,1.0);	#	90	kidney Fibrinogen
push!(time_constant_array,1.0);	#	91	kidney Plasminogen
push!(time_constant_array,1.0);	#	92	kidney tPA
push!(time_constant_array,1.0);	#	93	kidney uPA
push!(time_constant_array,1.0);	#	94	kidney Fibrin_monomer
push!(time_constant_array,1.0);	#	95	kidney Protofibril
push!(time_constant_array,1.0);	#	96	kidney antiplasmin
push!(time_constant_array,1.0);	#	97	kidney PAI_1
push!(time_constant_array,1.0);	#	98	kidney Fiber
push!(time_constant_array,1.0);	#	99	kidney TAT
push!(time_constant_array,1.0);	#	100	kidney PAP

push!(time_constant_array,1.0);	#	101	wound FII
push!(time_constant_array,1.0);	#	102	wound FIIa
push!(time_constant_array,1.0);	#	103	wound PC
push!(time_constant_array,1.0);	#	104	wound APC
push!(time_constant_array,1.0);	#	105	wound ATIII
push!(time_constant_array,1.0);	#	106	wound TM
push!(time_constant_array,1.0);	#	107	wound TRIGGER
push!(time_constant_array,1.0);	#	108	wound Fibrin
push!(time_constant_array,1.0);	#	109	wound Plasmin
push!(time_constant_array,1.0);	#	110	wound Fibrinogen
push!(time_constant_array,1.0);	#	111	wound Plasminogen
push!(time_constant_array,1.0);	#	112	wound tPA
push!(time_constant_array,1.0);	#	113	wound uPA
push!(time_constant_array,1.0);	#	114	wound Fibrin_monomer
push!(time_constant_array,1.0);	#	115	wound Protofibril
push!(time_constant_array,1.0);	#	116	wound antiplasmin
push!(time_constant_array,1.0);	#	117	wound PAI_1
push!(time_constant_array,1.0);	#	118	wound Fiber
push!(time_constant_array,1.0);	#	119	wound TAT
push!(time_constant_array,1.0);	#	120	wound PAP

push!(time_constant_array,1.0);	#	121	vein volume_vein
push!(time_constant_array,1.0);	#	122	lungs volume_lungs
push!(time_constant_array,1.0);	#	123	artery volume_artery
push!(time_constant_array,1.0);	#	124	heart volume_heart
push!(time_constant_array,1.0);	#	125	kidney volume_kidney
push!(time_constant_array,1.0);	#	126	wound volume_wound
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
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 8	vein	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 9	vein	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 10	vein	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 11	vein	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 12	vein	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 13	vein	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 14	vein	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 15	vein	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 16	vein	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 17	vein	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 18	vein	reaction18: compartment: * [] -([])-> Fiber
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 19	vein	reaction19: compartment: * [] -([])-> TAT
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 20	vein	reaction20: compartment: * [] -([])-> PAP

# lungs
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 21	lungs	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 22	lungs	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 23	lungs	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 24	lungs	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 25	lungs	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 26	lungs	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 27	lungs	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 28	lungs	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 29	lungs	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 30	lungs	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 31	lungs	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 32	lungs	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 33	lungs	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 34	lungs	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 35	lungs	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 36	lungs	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 37	lungs	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 38	lungs	reaction18: compartment: * [] -([])-> Fiber
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 39	lungs	reaction19: compartment: * [] -([])-> TAT
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 40	lungs	reaction20: compartment: * [] -([])-> PAP

# artery
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 41	artery	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 42	artery	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 43	artery	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 44	artery	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 45	artery	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 46	artery	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 47	artery	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 48	artery	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 49	artery	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 50	artery	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 51	artery	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 52	artery	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 53	artery	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 54	artery	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 55	artery	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 56	artery	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 57	artery	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 58	artery	reaction18: compartment: * [] -([])-> Fiber
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 59	artery	reaction19: compartment: * [] -([])-> TAT
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 60	artery	reaction20: compartment: * [] -([])-> PAP

# heart
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 61	heart	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 62	heart	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 63	heart	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 64	heart	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 65	heart	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 66	heart	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 67	heart	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 68	heart	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 69	heart	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 70	heart	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 71	heart	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 72	heart	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 73	heart	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 74	heart	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 75	heart	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 76	heart	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 77	heart	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 78	heart	reaction18: compartment: * [] -([])-> Fiber
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 79	heart	reaction19: compartment: * [] -([])-> TAT
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 80	heart	reaction20: compartment: * [] -([])-> PAP

# kidney
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 81	kidney	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 82	kidney	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 83	kidney	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 84	kidney	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 85	kidney	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 86	kidney	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 87	kidney	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 88	kidney	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 89	kidney	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 90	kidney	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 91	kidney	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 92	kidney	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 93	kidney	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 94	kidney	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 95	kidney	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 96	kidney	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 97	kidney	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 98	kidney	reaction18: compartment: * [] -([])-> Fiber
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 99	kidney	reaction19: compartment: * [] -([])-> TAT
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 100	kidney	reaction20: compartment: * [] -([])-> PAP

# wound
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 101	wound	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 102	wound	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 103	wound	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 104	wound	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 105	wound	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 106	wound	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 107	wound	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 108	wound	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 109	wound	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 110	wound	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 111	wound	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 112	wound	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 113	wound	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 114	wound	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 115	wound	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 116	wound	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 117	wound	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 118	wound	reaction18: compartment: * [] -([])-> Fiber
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 119	wound	reaction19: compartment: * [] -([])-> TAT
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0);	# 120	wound	reaction20: compartment: * [] -([])-> PAP

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
