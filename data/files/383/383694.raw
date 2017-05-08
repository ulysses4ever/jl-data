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
# Generation timestamp: 07-26-2016 09:08:18
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
default_beats_per_minute = 100.0
default_stroke_volume = 70*(1/1000)
flow_parameter_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
push!(flow_parameter_array,1.0)	# 1	vein_to_heart: vein -> heart
push!(flow_parameter_array,1.0)	# 2	heart_to_lungs: heart -> lungs
push!(flow_parameter_array,1.0)	# 3	lungs_to_heart: lungs -> heart
push!(flow_parameter_array,1.0)	# 4	heart_to_artery: heart -> artery
push!(flow_parameter_array,0.175)	# 5	artery_to_kidney: artery -> kidney
push!(flow_parameter_array,0.175)	# 6	kidney_to_vein: kidney -> vein
push!(flow_parameter_array,0.227)	# 7	artery_to_liver: artery -> liver
push!(flow_parameter_array,0.227)	# 8	liver_to_vein: artery -> vein
push!(flow_parameter_array,0.597)	# 9	artery_to_bulk: artery -> bulk
push!(flow_parameter_array,0.598)	# 10	bulk_to_vein: bulk -> vein
push!(flow_parameter_array,0.002)	# 11	artery_to_wound: artery -> wound
push!(flow_parameter_array,0.0005)	# 12	artery_to_wound_reverse: wound -> artery
push!(flow_parameter_array,0.0015)	# 13	wound_to_degredation: wound -> []
# ------------------------------------------------------------------------------------------------ #

# Characteristic variables array - 
characteristic_variable_array = zeros(4)
# ------------------------------------------------------------------------------------------------ #
characteristic_volume = 1.0
characteristic_concentration = 1.0
characteristic_flow_rate = default_beats_per_minute*default_stroke_volume
characteristic_time = characteristic_volume/characteristic_flow_rate
characteristic_variable_array[1] = characteristic_volume
characteristic_variable_array[2] = characteristic_concentration
characteristic_variable_array[3] = characteristic_flow_rate
characteristic_variable_array[4] = characteristic_time
# ------------------------------------------------------------------------------------------------ #

# Load the stoichiometric matrix - 
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/Fibrinolysis/network/Network.dat"))
(NSPECIES,NREACTIONS) = size(S)

# Load the stoichiometric matrix - 
C = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/Fibrinolysis/network/Connectivity.dat"))

# Formulate the initial condition array - 
initial_condition_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
FII_initial = 1400.0
FIIa_initial=0.0
PC_initial=0.0
APC_initial = 0.0
ATIII_initial = 3400.0
TM_initial = 1.0
TRIGGER_initial = .5
Fibrin_initial = 0.0
Plasmin_initial = 0.0
Fibrinogen_initial =10000.0
Plasminogen_initial = 2000.0
tPA_initial = 8.0
uPA_initial = 0.0
Fibrin_monomer_initial = 0.0
Protofibril_initial = 0.0
antiplasmin_initial = 1180.0
PAI_1_initial = .56
Fiber_initial = 0.0

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	1	vein FII
push!(initial_condition_array,(1.0/characteristic_concentration)*FIIa_initial)	#	2	vein FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	3	vein PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	4	vein APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	5	vein ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	6	vein TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0)	#	7	vein TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	8	vein Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	9	vein Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	10	vein Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	11	vein Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	12	vein tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	13	vein uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	14	vein Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	15	vein Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	16	vein antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	17	vein PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	18	vein Fiber

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	19	heart FII
push!(initial_condition_array,(1.0/characteristic_concentration)*FIIa_initial)	#	20	heart FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	21	heart PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	22	heart APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	23	heart ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	24	heart TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0)	#	25	heart TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	26	heart Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	27	heart Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	28	heart Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	29	heart Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	30	heart tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	31	heart uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	32	heart Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	33	heart Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	34	heart antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	35	heart PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	36	heart Fiber

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	37	lungs FII
push!(initial_condition_array,(1.0/characteristic_concentration)*FIIa_initial)	#	38	lungs FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	39	lungs PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	40	lungs APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	41	lungs ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	42	lungs TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0)	#	43	lungs TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	44	lungs Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	45	lungs Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	46	lungs Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	47	lungs Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	48	lungs tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	49	lungs uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	50	lungs Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	51	lungs Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	52	lungs antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	53	lungs PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	54	lungs Fiber

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	55	artery FII
push!(initial_condition_array,(1.0/characteristic_concentration)FIIa_initial)	#	56	artery FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	57	artery PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	58	artery APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	59	artery ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	60	artery TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0)	#	61	artery TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	62	artery Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	63	artery Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	64	artery Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	65	artery Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	66	artery tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	67	artery uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	68	artery Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	69	artery Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	70	artery antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	71	artery PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	72	artery Fiber

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	73	kidney FII
push!(initial_condition_array,(1.0/characteristic_concentration)FIIa_initial)	#	74	kidney FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	75	kidney PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	76	kidney APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	77	kidney ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	78	kidney TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0)	#	79	kidney TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	80	kidney Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	81	kidney Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	82	kidney Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	83	kidney Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	84	kidney tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	85	kidney uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	86	kidney Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	87	kidney Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	88	kidney antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	89	kidney PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	90	kidney Fiber

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	91	liver FII
push!(initial_condition_array,(1.0/characteristic_concentration)*FIIa_initial)	#	92	liver FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	93	liver PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	94	liver APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	95	liver ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	96	liver TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0)	#	97	liver TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	98	liver Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	99	liver Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	100	liver Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	101	liver Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	102	liver tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	103	liver uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	104	liver Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	105	liver Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	106	liver antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	107	liver PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	108	liver Fiber

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	109	bulk FII
push!(initial_condition_array,(1.0/characteristic_concentration)*FIIa_initial)	#	110	bulk FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	111	bulk PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	112	bulk APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	113	bulk ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	114	bulk TM
push!(initial_condition_array,(1.0/characteristic_concentration)*0.0)	#	115	bulk TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	116	bulk Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	117	bulk Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	118	bulk Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	119	bulk Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	120	bulk tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	121	bulk uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	122	bulk Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	123	bulk Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	124	bulk antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	125	bulk PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	126	bulk Fiber

push!(initial_condition_array,(1.0/characteristic_concentration)*FII_initial)	#	127	wound FII
push!(initial_condition_array,(1.0/characteristic_concentration)FIIa_initial)	#	128	wound FIIa
push!(initial_condition_array,(1.0/characteristic_concentration)*PC_initial)	#	129	wound PC
push!(initial_condition_array,(1.0/characteristic_concentration)*APC_initial)	#	130	wound APC
push!(initial_condition_array,(1.0/characteristic_concentration)*ATIII_initial)	#	131	wound ATIII
push!(initial_condition_array,(1.0/characteristic_concentration)*TM_initial)	#	132	wound TM
push!(initial_condition_array,(1.0/characteristic_concentration)*5)	#	133	wound TRIGGER
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_initial)	#	134	wound Fibrin
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasmin_initial)	#	135	wound Plasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrinogen_initial)	#	136	wound Fibrinogen
push!(initial_condition_array,(1.0/characteristic_concentration)*Plasminogen_initial)	#	137	wound Plasminogen
push!(initial_condition_array,(1.0/characteristic_concentration)*tPA_initial)	#	138	wound tPA
push!(initial_condition_array,(1.0/characteristic_concentration)*uPA_initial)	#	139	wound uPA
push!(initial_condition_array,(1.0/characteristic_concentration)*Fibrin_monomer_initial)	#	140	wound Fibrin_monomer
push!(initial_condition_array,(1.0/characteristic_concentration)*Protofibril_initial)	#	141	wound Protofibril
push!(initial_condition_array,(1.0/characteristic_concentration)*antiplasmin_initial)	#	142	wound antiplasmin
push!(initial_condition_array,(1.0/characteristic_concentration)*PAI_1_initial)	#	143	wound PAI_1
push!(initial_condition_array,(1.0/characteristic_concentration)*Fiber_initial)	#	144	wound Fiber

#volumes of blood from "Suggested Reference Values For Regional Blood Volumes in Humans"
#
bodymass = 70 #In kg
bloodvolume= 6.234 #in L, from Total blood volume in healthy young and older men
push!(initial_condition_array,(1.0/characteristic_volume)*.18*bloodvolume)	#	57	vein volume_vein
push!(initial_condition_array,(1.0/characteristic_volume)*.10*bloodvolume)	#	58	heart volume_heart
push!(initial_condition_array,(1.0/characteristic_volume)*.125*bloodvolume)	#	59	lungs volume_lungs
push!(initial_condition_array,(1.0/characteristic_volume)*.06*bloodvolume)	#	60	artery volume_artery
push!(initial_condition_array,(1.0/characteristic_volume)*.02*bloodvolume)	#	61	kidney volume_kidney
push!(initial_condition_array,(1.0/characteristic_volume)*.1*bloodvolume)	#	62	liver volume_liver
push!(initial_condition_array,(1.0/characteristic_volume)*.41*bloodvolume)	#	63	bulk volume_bulk
push!(initial_condition_array,(1.0/characteristic_volume)*.005*bloodvolume)	#	64	wound volume_wound
# ------------------------------------------------------------------------------------------------ #
# Formulate the time constant array - 
time_constant_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
push!(time_constant_array,1.0)	#	1	vein FII
push!(time_constant_array,1.0)	#	2	vein FIIa
push!(time_constant_array,1.0)	#	3	vein PC
push!(time_constant_array,1.0)	#	4	vein APC
push!(time_constant_array,1.0)	#	5	vein ATIII
push!(time_constant_array,1.0)	#	6	vein TM
push!(time_constant_array,1.0)	#	7	vein TRIGGER
push!(time_constant_array,1.0)	#	8	vein Fibrin
push!(time_constant_array,1.0)	#	9	vein Plasmin
push!(time_constant_array,1.0)	#	10	vein Fibrinogen
push!(time_constant_array,1.0)	#	11	vein Plasminogen
push!(time_constant_array,1.0)	#	12	vein tPA
push!(time_constant_array,1.0)	#	13	vein uPA
push!(time_constant_array,1.0)	#	14	vein Fibrin_monomer
push!(time_constant_array,1.0)	#	15	vein Protofibril
push!(time_constant_array,1.0)	#	16	vein antiplasmin
push!(time_constant_array,1.0)	#	17	vein PAI_1
push!(time_constant_array,1.0)	#	18	vein Fiber

push!(time_constant_array,1.0)	#	19	heart FII
push!(time_constant_array,1.0)	#	20	heart FIIa
push!(time_constant_array,1.0)	#	21	heart PC
push!(time_constant_array,1.0)	#	22	heart APC
push!(time_constant_array,1.0)	#	23	heart ATIII
push!(time_constant_array,1.0)	#	24	heart TM
push!(time_constant_array,1.0)	#	25	heart TRIGGER
push!(time_constant_array,1.0)	#	26	heart Fibrin
push!(time_constant_array,1.0)	#	27	heart Plasmin
push!(time_constant_array,1.0)	#	28	heart Fibrinogen
push!(time_constant_array,1.0)	#	29	heart Plasminogen
push!(time_constant_array,1.0)	#	30	heart tPA
push!(time_constant_array,1.0)	#	31	heart uPA
push!(time_constant_array,1.0)	#	32	heart Fibrin_monomer
push!(time_constant_array,1.0)	#	33	heart Protofibril
push!(time_constant_array,1.0)	#	34	heart antiplasmin
push!(time_constant_array,1.0)	#	35	heart PAI_1
push!(time_constant_array,1.0)	#	36	heart Fiber

push!(time_constant_array,1.0)	#	37	lungs FII
push!(time_constant_array,1.0)	#	38	lungs FIIa
push!(time_constant_array,1.0)	#	39	lungs PC
push!(time_constant_array,1.0)	#	40	lungs APC
push!(time_constant_array,1.0)	#	41	lungs ATIII
push!(time_constant_array,1.0)	#	42	lungs TM
push!(time_constant_array,1.0)	#	43	lungs TRIGGER
push!(time_constant_array,1.0)	#	44	lungs Fibrin
push!(time_constant_array,1.0)	#	45	lungs Plasmin
push!(time_constant_array,1.0)	#	46	lungs Fibrinogen
push!(time_constant_array,1.0)	#	47	lungs Plasminogen
push!(time_constant_array,1.0)	#	48	lungs tPA
push!(time_constant_array,1.0)	#	49	lungs uPA
push!(time_constant_array,1.0)	#	50	lungs Fibrin_monomer
push!(time_constant_array,1.0)	#	51	lungs Protofibril
push!(time_constant_array,1.0)	#	52	lungs antiplasmin
push!(time_constant_array,1.0)	#	53	lungs PAI_1
push!(time_constant_array,1.0)	#	54	lungs Fiber

push!(time_constant_array,1.0)	#	55	artery FII
push!(time_constant_array,1.0)	#	56	artery FIIa
push!(time_constant_array,1.0)	#	57	artery PC
push!(time_constant_array,1.0)	#	58	artery APC
push!(time_constant_array,1.0)	#	59	artery ATIII
push!(time_constant_array,1.0)	#	60	artery TM
push!(time_constant_array,1.0)	#	61	artery TRIGGER
push!(time_constant_array,1.0)	#	62	artery Fibrin
push!(time_constant_array,1.0)	#	63	artery Plasmin
push!(time_constant_array,1.0)	#	64	artery Fibrinogen
push!(time_constant_array,1.0)	#	65	artery Plasminogen
push!(time_constant_array,1.0)	#	66	artery tPA
push!(time_constant_array,1.0)	#	67	artery uPA
push!(time_constant_array,1.0)	#	68	artery Fibrin_monomer
push!(time_constant_array,1.0)	#	69	artery Protofibril
push!(time_constant_array,1.0)	#	70	artery antiplasmin
push!(time_constant_array,1.0)	#	71	artery PAI_1
push!(time_constant_array,1.0)	#	72	artery Fiber

push!(time_constant_array,1.0)	#	73	kidney FII
push!(time_constant_array,1.0)	#	74	kidney FIIa
push!(time_constant_array,1.0)	#	75	kidney PC
push!(time_constant_array,1.0)	#	76	kidney APC
push!(time_constant_array,1.0)	#	77	kidney ATIII
push!(time_constant_array,1.0)	#	78	kidney TM
push!(time_constant_array,1.0)	#	79	kidney TRIGGER
push!(time_constant_array,1.0)	#	80	kidney Fibrin
push!(time_constant_array,1.0)	#	81	kidney Plasmin
push!(time_constant_array,1.0)	#	82	kidney Fibrinogen
push!(time_constant_array,1.0)	#	83	kidney Plasminogen
push!(time_constant_array,1.0)	#	84	kidney tPA
push!(time_constant_array,1.0)	#	85	kidney uPA
push!(time_constant_array,1.0)	#	86	kidney Fibrin_monomer
push!(time_constant_array,1.0)	#	87	kidney Protofibril
push!(time_constant_array,1.0)	#	88	kidney antiplasmin
push!(time_constant_array,1.0)	#	89	kidney PAI_1
push!(time_constant_array,1.0)	#	90	kidney Fiber

push!(time_constant_array,1.0)	#	91	liver FII
push!(time_constant_array,1.0)	#	92	liver FIIa
push!(time_constant_array,1.0)	#	93	liver PC
push!(time_constant_array,1.0)	#	94	liver APC
push!(time_constant_array,1.0)	#	95	liver ATIII
push!(time_constant_array,1.0)	#	96	liver TM
push!(time_constant_array,1.0)	#	97	liver TRIGGER
push!(time_constant_array,1.0)	#	98	liver Fibrin
push!(time_constant_array,1.0)	#	99	liver Plasmin
push!(time_constant_array,1.0)	#	100	liver Fibrinogen
push!(time_constant_array,1.0)	#	101	liver Plasminogen
push!(time_constant_array,1.0)	#	102	liver tPA
push!(time_constant_array,1.0)	#	103	liver uPA
push!(time_constant_array,1.0)	#	104	liver Fibrin_monomer
push!(time_constant_array,1.0)	#	105	liver Protofibril
push!(time_constant_array,1.0)	#	106	liver antiplasmin
push!(time_constant_array,1.0)	#	107	liver PAI_1
push!(time_constant_array,1.0)	#	108	liver Fiber

push!(time_constant_array,1.0)	#	109	bulk FII
push!(time_constant_array,1.0)	#	110	bulk FIIa
push!(time_constant_array,1.0)	#	111	bulk PC
push!(time_constant_array,1.0)	#	112	bulk APC
push!(time_constant_array,1.0)	#	113	bulk ATIII
push!(time_constant_array,1.0)	#	114	bulk TM
push!(time_constant_array,1.0)	#	115	bulk TRIGGER
push!(time_constant_array,1.0)	#	116	bulk Fibrin
push!(time_constant_array,1.0)	#	117	bulk Plasmin
push!(time_constant_array,1.0)	#	118	bulk Fibrinogen
push!(time_constant_array,1.0)	#	119	bulk Plasminogen
push!(time_constant_array,1.0)	#	120	bulk tPA
push!(time_constant_array,1.0)	#	121	bulk uPA
push!(time_constant_array,1.0)	#	122	bulk Fibrin_monomer
push!(time_constant_array,1.0)	#	123	bulk Protofibril
push!(time_constant_array,1.0)	#	124	bulk antiplasmin
push!(time_constant_array,1.0)	#	125	bulk PAI_1
push!(time_constant_array,1.0)	#	126	bulk Fiber

push!(time_constant_array,1.0)	#	127	wound FII
push!(time_constant_array,1.0)	#	128	wound FIIa
push!(time_constant_array,1.0)	#	129	wound PC
push!(time_constant_array,1.0)	#	130	wound APC
push!(time_constant_array,1.0)	#	131	wound ATIII
push!(time_constant_array,1.0)	#	132	wound TM
push!(time_constant_array,1.0)	#	133	wound TRIGGER
push!(time_constant_array,1.0)	#	134	wound Fibrin
push!(time_constant_array,1.0)	#	135	wound Plasmin
push!(time_constant_array,1.0)	#	136	wound Fibrinogen
push!(time_constant_array,1.0)	#	137	wound Plasminogen
push!(time_constant_array,1.0)	#	138	wound tPA
push!(time_constant_array,1.0)	#	139	wound uPA
push!(time_constant_array,1.0)	#	140	wound Fibrin_monomer
push!(time_constant_array,1.0)	#	141	wound Protofibril
push!(time_constant_array,1.0)	#	142	wound antiplasmin
push!(time_constant_array,1.0)	#	143	wound PAI_1
push!(time_constant_array,1.0)	#	144	wound Fiber

push!(time_constant_array,1.0)	#	145	vein volume_vein
push!(time_constant_array,1.0)	#	146	heart volume_heart
push!(time_constant_array,1.0)	#	147	lungs volume_lungs
push!(time_constant_array,1.0)	#	148	artery volume_artery
push!(time_constant_array,1.0)	#	149	kidney volume_kidney
push!(time_constant_array,1.0)	#	150	liver volume_liver
push!(time_constant_array,1.0)	#	151	bulk volume_bulk
push!(time_constant_array,1.0)	#	152	wound volume_wound
# ------------------------------------------------------------------------------------------------ #

# Formulate the rate constant array - 
rate_constant_array = Float64[]
# ------------------------------------------------------------------------------------------------ #
# vein
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 1	vein	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 2	vein	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 3	vein	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 4	vein	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 5	vein	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 6	vein	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 7	vein	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 8	vein	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 9	vein	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 10	vein	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 11	vein	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 12	vein	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 13	vein	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 14	vein	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 15	vein	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 16	vein	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 17	vein	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 18	vein	reaction18: compartment: * [] -([])-> Fiber

# heart
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 19	heart	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 20	heart	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 21	heart	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 22	heart	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 23	heart	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 24	heart	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 25	heart	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 26	heart	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 27	heart	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 28	heart	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 29	heart	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 30	heart	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 31	heart	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 32	heart	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 33	heart	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 34	heart	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 35	heart	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 36	heart	reaction18: compartment: * [] -([])-> Fiber

# lungs
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 37	lungs	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 38	lungs	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 39	lungs	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 40	lungs	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 41	lungs	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 42	lungs	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 43	lungs	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 44	lungs	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 45	lungs	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 46	lungs	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 47	lungs	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 48	lungs	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 49	lungs	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 50	lungs	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 51	lungs	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 52	lungs	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 53	lungs	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 54	lungs	reaction18: compartment: * [] -([])-> Fiber

# artery
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 55	artery	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 56	artery	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 57	artery	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 58	artery	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 59	artery	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 60	artery	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 61	artery	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 62	artery	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 63	artery	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 64	artery	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 65	artery	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 66	artery	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 67	artery	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 68	artery	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 69	artery	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 70	artery	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 71	artery	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 72	artery	reaction18: compartment: * [] -([])-> Fiber

# kidney
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 73	kidney	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 74	kidney	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 75	kidney	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 76	kidney	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 77	kidney	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 78	kidney	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 79	kidney	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 80	kidney	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 81	kidney	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 82	kidney	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 83	kidney	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 84	kidney	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 85	kidney	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 86	kidney	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 87	kidney	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 88	kidney	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 89	kidney	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 90	kidney	reaction18: compartment: * [] -([])-> Fiber

# liver
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 91	liver	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 92	liver	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 93	liver	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 94	liver	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 95	liver	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 96	liver	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 97	liver	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 98	liver	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 99	liver	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 100	liver	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 101	liver	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 102	liver	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 103	liver	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 104	liver	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 105	liver	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 106	liver	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 107	liver	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 108	liver	reaction18: compartment: * [] -([])-> Fiber

# bulk
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 109	bulk	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 110	bulk	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 111	bulk	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 112	bulk	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 113	bulk	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 114	bulk	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 115	bulk	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 116	bulk	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 117	bulk	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 118	bulk	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 119	bulk	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 120	bulk	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 121	bulk	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 122	bulk	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 123	bulk	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 124	bulk	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 125	bulk	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 126	bulk	reaction18: compartment: * [] -([])-> Fiber

# wound
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 127	wound	reaction1: compartment: * [] -([])-> FII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 128	wound	reaction2: compartment: * [] -([])-> FIIa
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 129	wound	reaction3: compartment: * [] -([])-> PC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 130	wound	reaction4: compartment: * [] -([])-> APC
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 131	wound	reaction5: compartment: * [] -([])-> ATIII
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 132	wound	reaction6: compartment: * [] -([])-> TM
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 133	wound	reaction7: compartment: * [] -([])-> TRIGGER
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 134	wound	reaction8: compartment: * [] -([])-> Fibrin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 135	wound	reaction9: compartment: * [] -([])-> Plasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 136	wound	reaction10: compartment: * [] -([])-> Fibrinogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 137	wound	reaction11: compartment: * [] -([])-> Plasminogen
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 138	wound	reaction12: compartment: * [] -([])-> tPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 139	wound	reaction13: compartment: * [] -([])-> uPA
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 140	wound	reaction14: compartment: * [] -([])-> Fibrin_monomer
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 141	wound	reaction15: compartment: * [] -([])-> Protofibril
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 142	wound	reaction16: compartment: * [] -([])-> antiplasmin
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 143	wound	reaction17: compartment: * [] -([])-> PAI_1
push!(rate_constant_array,(characteristic_time/characteristic_concentration)*1.0)	# 144	wound	reaction18: compartment: * [] -([])-> Fiber

# ------------------------------------------------------------------------------------------------ #

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES)
# ------------------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------------------ #

# Formulate control parameter array - 
control_parameter_array = zeros(0,2)
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
data_dictionary = Dict()
data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"] = characteristic_variable_array
data_dictionary["INPUT_CONCENTRATION_ARRAY"] = input_concentration_array
data_dictionary["DEFAULT_BEATS_PER_MINUTE"] = default_beats_per_minute
data_dictionary["DEFAULT_STROKE_VOLUME"] = default_stroke_volume
data_dictionary["FLOW_PARAMETER_ARRAY"] = flow_parameter_array
data_dictionary["STOICHIOMETRIC_MATRIX"] = S
data_dictionary["FLOW_CONNECTIVITY_MATRIX"] = C
data_dictionary["RATE_CONSTANT_ARRAY"] = rate_constant_array
data_dictionary["SATURATION_CONSTANT_ARRAY"] = saturation_constant_array
data_dictionary["INITIAL_CONDITION_ARRAY"] = initial_condition_array
data_dictionary["TIME_CONSTANT_ARRAY"] = time_constant_array
data_dictionary["CONTROL_PARAMETER_ARRAY"] = control_parameter_array
# ------------------------------------------------------------------------------------------------ #
return data_dictionary
end
