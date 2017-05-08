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
function Dilution(t,x,dvdt_vector,data_dictionary)
# ---------------------------------------------------------------------- #
# Dilution.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 05-06-2016 09:57:05
# 
# Arguments: 
# t  - current time 
# x  - state vector 
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

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(FII_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(FIIa_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(PC_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(APC_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(ATIII_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(TM_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(TRIGGER_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Fibrin_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Plasmin_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Fibrinogen_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Plasminogen_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(tPA_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(uPA_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Fibrin_monomer_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Protofibril_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(antiplasmin_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(PAI_1_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Fiber_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(TAT_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(PAP_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(FII_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(FIIa_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(PC_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(APC_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(ATIII_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(TM_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(TRIGGER_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Fibrin_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Plasmin_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Fibrinogen_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Plasminogen_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(tPA_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(uPA_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Fibrin_monomer_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Protofibril_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(antiplasmin_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(PAI_1_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Fiber_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(TAT_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(PAP_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(FII_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(FIIa_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(PC_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(APC_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(ATIII_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(TM_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(TRIGGER_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Fibrin_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Plasmin_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Fibrinogen_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Plasminogen_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(tPA_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(uPA_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Fibrin_monomer_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Protofibril_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(antiplasmin_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(PAI_1_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Fiber_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(TAT_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(PAP_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(FII_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(FIIa_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(PC_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(APC_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(ATIII_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(TM_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(TRIGGER_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Fibrin_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Plasmin_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Fibrinogen_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Plasminogen_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(tPA_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(uPA_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Fibrin_monomer_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Protofibril_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(antiplasmin_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(PAI_1_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Fiber_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(TAT_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(PAP_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(FII_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(FIIa_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(PC_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(APC_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(ATIII_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(TM_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(TRIGGER_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Fibrin_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Plasmin_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Fibrinogen_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Plasminogen_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(tPA_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(uPA_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Fibrin_monomer_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Protofibril_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(antiplasmin_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(PAI_1_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Fiber_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(TAT_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(PAP_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(FII_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(FIIa_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(PC_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(APC_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(ATIII_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(TM_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(TRIGGER_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Fibrin_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Plasmin_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Fibrinogen_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Plasminogen_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(tPA_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(uPA_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Fibrin_monomer_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Protofibril_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(antiplasmin_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(PAI_1_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Fiber_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(TAT_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(PAP_wound/volume_wound)*dvdt_vector[6]);
return (species_dilution_array);
end;
