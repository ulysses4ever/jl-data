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
function Kinetics(t,x,data_dictionary)
# --------------------------------------------------------------------- #
# Kinetics.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 05-06-2016 09:57:05
# 
# Input arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary - parameter vector 
# 
# Return arguments: 
# rate_vector - rate vector 
# --------------------------------------------------------------------- #
# 
# Alias the species vector - 
# vein
FII_vein = x[1];
FIIa_vein = x[2];
PC_vein = x[3];
APC_vein = x[4];
ATIII_vein = x[5];
TM_vein = x[6];
TRIGGER_vein = x[7];
Fibrin_vein = x[8];
Plasmin_vein = x[9];
Fibrinogen_vein = x[10];
Plasminogen_vein = x[11];
tPA_vein = x[12];
uPA_vein = x[13];
Fibrin_monomer_vein = x[14];
Protofibril_vein = x[15];
antiplasmin_vein = x[16];
PAI_1_vein = x[17];
Fiber_vein = x[18];
TAT_vein = x[19];
PAP_vein = x[20];

# lungs
FII_lungs = x[21];
FIIa_lungs = x[22];
PC_lungs = x[23];
APC_lungs = x[24];
ATIII_lungs = x[25];
TM_lungs = x[26];
TRIGGER_lungs = x[27];
Fibrin_lungs = x[28];
Plasmin_lungs = x[29];
Fibrinogen_lungs = x[30];
Plasminogen_lungs = x[31];
tPA_lungs = x[32];
uPA_lungs = x[33];
Fibrin_monomer_lungs = x[34];
Protofibril_lungs = x[35];
antiplasmin_lungs = x[36];
PAI_1_lungs = x[37];
Fiber_lungs = x[38];
TAT_lungs = x[39];
PAP_lungs = x[40];

# artery
FII_artery = x[41];
FIIa_artery = x[42];
PC_artery = x[43];
APC_artery = x[44];
ATIII_artery = x[45];
TM_artery = x[46];
TRIGGER_artery = x[47];
Fibrin_artery = x[48];
Plasmin_artery = x[49];
Fibrinogen_artery = x[50];
Plasminogen_artery = x[51];
tPA_artery = x[52];
uPA_artery = x[53];
Fibrin_monomer_artery = x[54];
Protofibril_artery = x[55];
antiplasmin_artery = x[56];
PAI_1_artery = x[57];
Fiber_artery = x[58];
TAT_artery = x[59];
PAP_artery = x[60];

# heart
FII_heart = x[61];
FIIa_heart = x[62];
PC_heart = x[63];
APC_heart = x[64];
ATIII_heart = x[65];
TM_heart = x[66];
TRIGGER_heart = x[67];
Fibrin_heart = x[68];
Plasmin_heart = x[69];
Fibrinogen_heart = x[70];
Plasminogen_heart = x[71];
tPA_heart = x[72];
uPA_heart = x[73];
Fibrin_monomer_heart = x[74];
Protofibril_heart = x[75];
antiplasmin_heart = x[76];
PAI_1_heart = x[77];
Fiber_heart = x[78];
TAT_heart = x[79];
PAP_heart = x[80];

# kidney
FII_kidney = x[81];
FIIa_kidney = x[82];
PC_kidney = x[83];
APC_kidney = x[84];
ATIII_kidney = x[85];
TM_kidney = x[86];
TRIGGER_kidney = x[87];
Fibrin_kidney = x[88];
Plasmin_kidney = x[89];
Fibrinogen_kidney = x[90];
Plasminogen_kidney = x[91];
tPA_kidney = x[92];
uPA_kidney = x[93];
Fibrin_monomer_kidney = x[94];
Protofibril_kidney = x[95];
antiplasmin_kidney = x[96];
PAI_1_kidney = x[97];
Fiber_kidney = x[98];
TAT_kidney = x[99];
PAP_kidney = x[100];

# wound
FII_wound = x[101];
FIIa_wound = x[102];
PC_wound = x[103];
APC_wound = x[104];
ATIII_wound = x[105];
TM_wound = x[106];
TRIGGER_wound = x[107];
Fibrin_wound = x[108];
Plasmin_wound = x[109];
Fibrinogen_wound = x[110];
Plasminogen_wound = x[111];
tPA_wound = x[112];
uPA_wound = x[113];
Fibrin_monomer_wound = x[114];
Protofibril_wound = x[115];
antiplasmin_wound = x[116];
PAI_1_wound = x[117];
Fiber_wound = x[118];
TAT_wound = x[119];
PAP_wound = x[120];

volume_vein = x[121];
volume_lungs = x[122];
volume_artery = x[123];
volume_heart = x[124];
volume_kidney = x[125];
volume_wound = x[126];

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_concentration = characteristic_variable_array[2];
characteristic_time = characteristic_variable_array[4];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# -------------------------------------------------------------------------- # 
# vein
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[1];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[2];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[3];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[4];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[5];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[6];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[7];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction8: compartment: * [] -([])-> Fibrin
tmp_reaction = rate_constant_array[8];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction9: compartment: * [] -([])-> Plasmin
tmp_reaction = rate_constant_array[9];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction10: compartment: * [] -([])-> Fibrinogen
tmp_reaction = rate_constant_array[10];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction11: compartment: * [] -([])-> Plasminogen
tmp_reaction = rate_constant_array[11];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction12: compartment: * [] -([])-> tPA
tmp_reaction = rate_constant_array[12];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction13: compartment: * [] -([])-> uPA
tmp_reaction = rate_constant_array[13];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction14: compartment: * [] -([])-> Fibrin_monomer
tmp_reaction = rate_constant_array[14];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction15: compartment: * [] -([])-> Protofibril
tmp_reaction = rate_constant_array[15];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction16: compartment: * [] -([])-> antiplasmin
tmp_reaction = rate_constant_array[16];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction17: compartment: * [] -([])-> PAI_1
tmp_reaction = rate_constant_array[17];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction18: compartment: * [] -([])-> Fiber
tmp_reaction = rate_constant_array[18];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction19: compartment: * [] -([])-> TAT
tmp_reaction = rate_constant_array[19];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction20: compartment: * [] -([])-> PAP
tmp_reaction = rate_constant_array[20];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# lungs
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[21];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[22];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[23];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[24];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[25];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[26];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[27];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction8: compartment: * [] -([])-> Fibrin
tmp_reaction = rate_constant_array[28];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction9: compartment: * [] -([])-> Plasmin
tmp_reaction = rate_constant_array[29];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction10: compartment: * [] -([])-> Fibrinogen
tmp_reaction = rate_constant_array[30];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction11: compartment: * [] -([])-> Plasminogen
tmp_reaction = rate_constant_array[31];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction12: compartment: * [] -([])-> tPA
tmp_reaction = rate_constant_array[32];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction13: compartment: * [] -([])-> uPA
tmp_reaction = rate_constant_array[33];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction14: compartment: * [] -([])-> Fibrin_monomer
tmp_reaction = rate_constant_array[34];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction15: compartment: * [] -([])-> Protofibril
tmp_reaction = rate_constant_array[35];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction16: compartment: * [] -([])-> antiplasmin
tmp_reaction = rate_constant_array[36];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction17: compartment: * [] -([])-> PAI_1
tmp_reaction = rate_constant_array[37];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction18: compartment: * [] -([])-> Fiber
tmp_reaction = rate_constant_array[38];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction19: compartment: * [] -([])-> TAT
tmp_reaction = rate_constant_array[39];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction20: compartment: * [] -([])-> PAP
tmp_reaction = rate_constant_array[40];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# artery
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[41];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[42];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[43];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[44];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[45];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[46];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[47];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction8: compartment: * [] -([])-> Fibrin
tmp_reaction = rate_constant_array[48];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction9: compartment: * [] -([])-> Plasmin
tmp_reaction = rate_constant_array[49];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction10: compartment: * [] -([])-> Fibrinogen
tmp_reaction = rate_constant_array[50];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction11: compartment: * [] -([])-> Plasminogen
tmp_reaction = rate_constant_array[51];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction12: compartment: * [] -([])-> tPA
tmp_reaction = rate_constant_array[52];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction13: compartment: * [] -([])-> uPA
tmp_reaction = rate_constant_array[53];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction14: compartment: * [] -([])-> Fibrin_monomer
tmp_reaction = rate_constant_array[54];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction15: compartment: * [] -([])-> Protofibril
tmp_reaction = rate_constant_array[55];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction16: compartment: * [] -([])-> antiplasmin
tmp_reaction = rate_constant_array[56];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction17: compartment: * [] -([])-> PAI_1
tmp_reaction = rate_constant_array[57];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction18: compartment: * [] -([])-> Fiber
tmp_reaction = rate_constant_array[58];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction19: compartment: * [] -([])-> TAT
tmp_reaction = rate_constant_array[59];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction20: compartment: * [] -([])-> PAP
tmp_reaction = rate_constant_array[60];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# heart
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[61];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[62];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[63];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[64];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[65];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[66];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[67];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction8: compartment: * [] -([])-> Fibrin
tmp_reaction = rate_constant_array[68];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction9: compartment: * [] -([])-> Plasmin
tmp_reaction = rate_constant_array[69];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction10: compartment: * [] -([])-> Fibrinogen
tmp_reaction = rate_constant_array[70];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction11: compartment: * [] -([])-> Plasminogen
tmp_reaction = rate_constant_array[71];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction12: compartment: * [] -([])-> tPA
tmp_reaction = rate_constant_array[72];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction13: compartment: * [] -([])-> uPA
tmp_reaction = rate_constant_array[73];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction14: compartment: * [] -([])-> Fibrin_monomer
tmp_reaction = rate_constant_array[74];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction15: compartment: * [] -([])-> Protofibril
tmp_reaction = rate_constant_array[75];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction16: compartment: * [] -([])-> antiplasmin
tmp_reaction = rate_constant_array[76];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction17: compartment: * [] -([])-> PAI_1
tmp_reaction = rate_constant_array[77];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction18: compartment: * [] -([])-> Fiber
tmp_reaction = rate_constant_array[78];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction19: compartment: * [] -([])-> TAT
tmp_reaction = rate_constant_array[79];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction20: compartment: * [] -([])-> PAP
tmp_reaction = rate_constant_array[80];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# kidney
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[81];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[82];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[83];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[84];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[85];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[86];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[87];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction8: compartment: * [] -([])-> Fibrin
tmp_reaction = rate_constant_array[88];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction9: compartment: * [] -([])-> Plasmin
tmp_reaction = rate_constant_array[89];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction10: compartment: * [] -([])-> Fibrinogen
tmp_reaction = rate_constant_array[90];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction11: compartment: * [] -([])-> Plasminogen
tmp_reaction = rate_constant_array[91];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction12: compartment: * [] -([])-> tPA
tmp_reaction = rate_constant_array[92];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction13: compartment: * [] -([])-> uPA
tmp_reaction = rate_constant_array[93];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction14: compartment: * [] -([])-> Fibrin_monomer
tmp_reaction = rate_constant_array[94];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction15: compartment: * [] -([])-> Protofibril
tmp_reaction = rate_constant_array[95];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction16: compartment: * [] -([])-> antiplasmin
tmp_reaction = rate_constant_array[96];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction17: compartment: * [] -([])-> PAI_1
tmp_reaction = rate_constant_array[97];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction18: compartment: * [] -([])-> Fiber
tmp_reaction = rate_constant_array[98];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction19: compartment: * [] -([])-> TAT
tmp_reaction = rate_constant_array[99];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction20: compartment: * [] -([])-> PAP
tmp_reaction = rate_constant_array[100];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# wound
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[101];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[102];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[103];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[104];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[105];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[106];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[107];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction8: compartment: * [] -([])-> Fibrin
tmp_reaction = rate_constant_array[108];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction9: compartment: * [] -([])-> Plasmin
tmp_reaction = rate_constant_array[109];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction10: compartment: * [] -([])-> Fibrinogen
tmp_reaction = rate_constant_array[110];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction11: compartment: * [] -([])-> Plasminogen
tmp_reaction = rate_constant_array[111];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction12: compartment: * [] -([])-> tPA
tmp_reaction = rate_constant_array[112];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction13: compartment: * [] -([])-> uPA
tmp_reaction = rate_constant_array[113];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction14: compartment: * [] -([])-> Fibrin_monomer
tmp_reaction = rate_constant_array[114];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction15: compartment: * [] -([])-> Protofibril
tmp_reaction = rate_constant_array[115];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction16: compartment: * [] -([])-> antiplasmin
tmp_reaction = rate_constant_array[116];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction17: compartment: * [] -([])-> PAI_1
tmp_reaction = rate_constant_array[117];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction18: compartment: * [] -([])-> Fiber
tmp_reaction = rate_constant_array[118];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction19: compartment: * [] -([])-> TAT
tmp_reaction = rate_constant_array[119];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction20: compartment: * [] -([])-> PAP
tmp_reaction = rate_constant_array[120];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
