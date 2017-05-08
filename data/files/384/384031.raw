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
function Control(t,x,rate_vector,data_dictionary)
# ---------------------------------------------------------------------- #
# Control.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 05-06-2016 09:57:05
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# rate_vector - vector of reaction rates 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Set a default value for the allosteric control variables - 
EPSILON = 1.0e-3;
number_of_reactions = length(rate_vector);
control_vector = ones(number_of_reactions);
control_parameter_array = data_dictionary["CONTROL_PARAMETER_ARRAY"];

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

# Modify the rate_vector with the control variables - 
rate_vector = rate_vector.*control_vector;

# Return the modified rate vector - 
return rate_vector;
end
