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
function CardiacDistribution(t,x,default_flow_parameter_array,data_dictionary)
# ---------------------------------------------------------------------- #
# CardiacDistribution.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 07-26-2016 09:08:18
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# default_flow_parameter_array - default flow parameters 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

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

# heart
FII_heart = x[19];
FIIa_heart = x[20];
PC_heart = x[21];
APC_heart = x[22];
ATIII_heart = x[23];
TM_heart = x[24];
TRIGGER_heart = x[25];
Fibrin_heart = x[26];
Plasmin_heart = x[27];
Fibrinogen_heart = x[28];
Plasminogen_heart = x[29];
tPA_heart = x[30];
uPA_heart = x[31];
Fibrin_monomer_heart = x[32];
Protofibril_heart = x[33];
antiplasmin_heart = x[34];
PAI_1_heart = x[35];
Fiber_heart = x[36];

# lungs
FII_lungs = x[37];
FIIa_lungs = x[38];
PC_lungs = x[39];
APC_lungs = x[40];
ATIII_lungs = x[41];
TM_lungs = x[42];
TRIGGER_lungs = x[43];
Fibrin_lungs = x[44];
Plasmin_lungs = x[45];
Fibrinogen_lungs = x[46];
Plasminogen_lungs = x[47];
tPA_lungs = x[48];
uPA_lungs = x[49];
Fibrin_monomer_lungs = x[50];
Protofibril_lungs = x[51];
antiplasmin_lungs = x[52];
PAI_1_lungs = x[53];
Fiber_lungs = x[54];

# artery
FII_artery = x[55];
FIIa_artery = x[56];
PC_artery = x[57];
APC_artery = x[58];
ATIII_artery = x[59];
TM_artery = x[60];
TRIGGER_artery = x[61];
Fibrin_artery = x[62];
Plasmin_artery = x[63];
Fibrinogen_artery = x[64];
Plasminogen_artery = x[65];
tPA_artery = x[66];
uPA_artery = x[67];
Fibrin_monomer_artery = x[68];
Protofibril_artery = x[69];
antiplasmin_artery = x[70];
PAI_1_artery = x[71];
Fiber_artery = x[72];

# kidney
FII_kidney = x[73];
FIIa_kidney = x[74];
PC_kidney = x[75];
APC_kidney = x[76];
ATIII_kidney = x[77];
TM_kidney = x[78];
TRIGGER_kidney = x[79];
Fibrin_kidney = x[80];
Plasmin_kidney = x[81];
Fibrinogen_kidney = x[82];
Plasminogen_kidney = x[83];
tPA_kidney = x[84];
uPA_kidney = x[85];
Fibrin_monomer_kidney = x[86];
Protofibril_kidney = x[87];
antiplasmin_kidney = x[88];
PAI_1_kidney = x[89];
Fiber_kidney = x[90];

# liver
FII_liver = x[91];
FIIa_liver = x[92];
PC_liver = x[93];
APC_liver = x[94];
ATIII_liver = x[95];
TM_liver = x[96];
TRIGGER_liver = x[97];
Fibrin_liver = x[98];
Plasmin_liver = x[99];
Fibrinogen_liver = x[100];
Plasminogen_liver = x[101];
tPA_liver = x[102];
uPA_liver = x[103];
Fibrin_monomer_liver = x[104];
Protofibril_liver = x[105];
antiplasmin_liver = x[106];
PAI_1_liver = x[107];
Fiber_liver = x[108];

# bulk
FII_bulk = x[109];
FIIa_bulk = x[110];
PC_bulk = x[111];
APC_bulk = x[112];
ATIII_bulk = x[113];
TM_bulk = x[114];
TRIGGER_bulk = x[115];
Fibrin_bulk = x[116];
Plasmin_bulk = x[117];
Fibrinogen_bulk = x[118];
Plasminogen_bulk = x[119];
tPA_bulk = x[120];
uPA_bulk = x[121];
Fibrin_monomer_bulk = x[122];
Protofibril_bulk = x[123];
antiplasmin_bulk = x[124];
PAI_1_bulk = x[125];
Fiber_bulk = x[126];

# wound
FII_wound = x[127];
FIIa_wound = x[128];
PC_wound = x[129];
APC_wound = x[130];
ATIII_wound = x[131];
TM_wound = x[132];
TRIGGER_wound = x[133];
Fibrin_wound = x[134];
Plasmin_wound = x[135];
Fibrinogen_wound = x[136];
Plasminogen_wound = x[137];
tPA_wound = x[138];
uPA_wound = x[139];
Fibrin_monomer_wound = x[140];
Protofibril_wound = x[141];
antiplasmin_wound = x[142];
PAI_1_wound = x[143];
Fiber_wound = x[144];
volume_vein = x[145];
volume_heart = x[146];
volume_lungs = x[147];
volume_artery = x[148];
volume_kidney = x[149];
volume_liver = x[150];
volume_bulk = x[151];
volume_wound = x[152];

# Update the flow parameter array - 
flow_parameter_array = default_flow_parameter_array
return (flow_parameter_array);
end;
