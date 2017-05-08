include("HeartRate.jl");
include("CardiacDistribution.jl");

#to stop bleeding after a certain time
include("stopBleeding.jl")
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
function Flow(t,x,data_dictionary)
# ---------------------------------------------------------------------- #
# Flow.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 07-26-2016 09:08:18
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #
stoptime = 15# stop bleeding after 30 minutes
#data_dictionary=stopBleeding(t,stoptime,data_dictionary)
data_dictionary=stopBleedingSlowly(t,stoptime,data_dictionary)


# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_flow_rate = characteristic_variable_array[3];

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

# Alias the species input vector - 
input_concentration_array = data_dictionary["INPUT_CONCENTRATION_ARRAY"]

# Get data we need from the data_dictionary - 
default_bpm = data_dictionary["DEFAULT_BEATS_PER_MINUTE"];
default_stroke_volume = data_dictionary["DEFAULT_STROKE_VOLUME"];
default_flow_parameter_array = data_dictionary["FLOW_PARAMETER_ARRAY"];

# Update the heart rate, and stroke volume - 
(bpm,stroke_volume) = HeartRate(t,x,default_bpm,default_stroke_volume,data_dictionary);

# Update the fraction of cardiac output going to each organ - 
(flow_parameter_array) = CardiacDistribution(t,x,default_flow_parameter_array,data_dictionary);

# Calculate the q_vector - 
q_vector = Float64[];
cardiac_output = (1.0/characteristic_flow_rate)*bpm*stroke_volume;

# 1 vein_to_heart
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# 2 heart_to_lungs
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# 3 lungs_to_heart
tmp_flow_rate = cardiac_output*flow_parameter_array[3];
push!(q_vector,tmp_flow_rate);

# 4 heart_to_artery
tmp_flow_rate = cardiac_output*flow_parameter_array[4];
push!(q_vector,tmp_flow_rate);

# 5 artery_to_kidney
tmp_flow_rate = cardiac_output*flow_parameter_array[5];
push!(q_vector,tmp_flow_rate);

# 6 kidney_to_vein
tmp_flow_rate = cardiac_output*flow_parameter_array[6];
push!(q_vector,tmp_flow_rate);

# 7 artery_to_liver
tmp_flow_rate = cardiac_output*flow_parameter_array[7];
push!(q_vector,tmp_flow_rate);

# 8 liver_to_vein
tmp_flow_rate = cardiac_output*flow_parameter_array[8];
push!(q_vector,tmp_flow_rate);

# 9 artery_to_bulk
tmp_flow_rate = cardiac_output*flow_parameter_array[9];
push!(q_vector,tmp_flow_rate);

# 10 bulk_to_vein
tmp_flow_rate = cardiac_output*flow_parameter_array[10];
push!(q_vector,tmp_flow_rate);

# 11 artery_to_wound
tmp_flow_rate = cardiac_output*flow_parameter_array[11];
push!(q_vector,tmp_flow_rate);

# 12 artery_to_wound_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[12];
push!(q_vector,tmp_flow_rate);

# 13 wound_to_degredation
tmp_flow_rate = cardiac_output*flow_parameter_array[13];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# FII_vein ---------- 
tmp_flow_term = -(q_vector[1])*FII_vein+(q_vector[6]*FII_kidney+q_vector[8]*FII_liver+q_vector[10]*FII_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_vein ---------- 
tmp_flow_term = -(q_vector[1])*FIIa_vein+(q_vector[6]*FIIa_kidney+q_vector[8]*FIIa_liver+q_vector[10]*FIIa_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# PC_vein ---------- 
tmp_flow_term = -(q_vector[1])*PC_vein+(q_vector[6]*PC_kidney+q_vector[8]*PC_liver+q_vector[10]*PC_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# APC_vein ---------- 
tmp_flow_term = -(q_vector[1])*APC_vein+(q_vector[6]*APC_kidney+q_vector[8]*APC_liver+q_vector[10]*APC_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_vein ---------- 
tmp_flow_term = -(q_vector[1])*ATIII_vein+(q_vector[6]*ATIII_kidney+q_vector[8]*ATIII_liver+q_vector[10]*ATIII_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# TM_vein ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_vein ---------- 
push!(species_flow_vector,0.0);

# Fibrin_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fibrin_vein+(q_vector[6]*Fibrin_kidney+q_vector[8]*Fibrin_liver+q_vector[10]*Fibrin_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_vein ---------- 
tmp_flow_term = -(q_vector[1])*Plasmin_vein+(q_vector[6]*Plasmin_kidney+q_vector[8]*Plasmin_liver+q_vector[10]*Plasmin_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fibrinogen_vein+(q_vector[6]*Fibrinogen_kidney+q_vector[8]*Fibrinogen_liver+q_vector[10]*Fibrinogen_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_vein ---------- 
tmp_flow_term = -(q_vector[1])*Plasminogen_vein+(q_vector[6]*Plasminogen_kidney+q_vector[8]*Plasminogen_liver+q_vector[10]*Plasminogen_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_vein ---------- 
tmp_flow_term = -(q_vector[1])*tPA_vein+(q_vector[6]*tPA_kidney+q_vector[8]*tPA_liver+q_vector[10]*tPA_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_vein ---------- 
tmp_flow_term = -(q_vector[1])*uPA_vein+(q_vector[6]*uPA_kidney+q_vector[8]*uPA_liver+q_vector[10]*uPA_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fibrin_monomer_vein+(q_vector[6]*Fibrin_monomer_kidney+q_vector[8]*Fibrin_monomer_liver+q_vector[10]*Fibrin_monomer_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_vein ---------- 
tmp_flow_term = -(q_vector[1])*Protofibril_vein+(q_vector[6]*Protofibril_kidney+q_vector[8]*Protofibril_liver+q_vector[10]*Protofibril_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_vein ---------- 
tmp_flow_term = -(q_vector[1])*antiplasmin_vein+(q_vector[6]*antiplasmin_kidney+q_vector[8]*antiplasmin_liver+q_vector[10]*antiplasmin_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_vein ---------- 
tmp_flow_term = -(q_vector[1])*PAI_1_vein+(q_vector[6]*PAI_1_kidney+q_vector[8]*PAI_1_liver+q_vector[10]*PAI_1_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fiber_vein+(q_vector[6]*Fiber_kidney+q_vector[8]*Fiber_liver+q_vector[10]*Fiber_bulk);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# FII_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*FII_heart+(q_vector[1]*FII_vein+q_vector[3]*FII_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*FIIa_heart+(q_vector[1]*FIIa_vein+q_vector[3]*FIIa_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# PC_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*PC_heart+(q_vector[1]*PC_vein+q_vector[3]*PC_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# APC_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*APC_heart+(q_vector[1]*APC_vein+q_vector[3]*APC_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*ATIII_heart+(q_vector[1]*ATIII_vein+q_vector[3]*ATIII_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# TM_heart ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_heart ---------- 
push!(species_flow_vector,0.0);

# Fibrin_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*Fibrin_heart+(q_vector[1]*Fibrin_vein+q_vector[3]*Fibrin_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*Plasmin_heart+(q_vector[1]*Plasmin_vein+q_vector[3]*Plasmin_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*Fibrinogen_heart+(q_vector[1]*Fibrinogen_vein+q_vector[3]*Fibrinogen_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*Plasminogen_heart+(q_vector[1]*Plasminogen_vein+q_vector[3]*Plasminogen_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*tPA_heart+(q_vector[1]*tPA_vein+q_vector[3]*tPA_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*uPA_heart+(q_vector[1]*uPA_vein+q_vector[3]*uPA_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*Fibrin_monomer_heart+(q_vector[1]*Fibrin_monomer_vein+q_vector[3]*Fibrin_monomer_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*Protofibril_heart+(q_vector[1]*Protofibril_vein+q_vector[3]*Protofibril_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*antiplasmin_heart+(q_vector[1]*antiplasmin_vein+q_vector[3]*antiplasmin_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*PAI_1_heart+(q_vector[1]*PAI_1_vein+q_vector[3]*PAI_1_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_heart ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[4])*Fiber_heart+(q_vector[1]*Fiber_vein+q_vector[3]*Fiber_lungs);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# FII_lungs ---------- 
tmp_flow_term = -(q_vector[3])*FII_lungs+(q_vector[2]*FII_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_lungs ---------- 
tmp_flow_term = -(q_vector[3])*FIIa_lungs+(q_vector[2]*FIIa_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# PC_lungs ---------- 
tmp_flow_term = -(q_vector[3])*PC_lungs+(q_vector[2]*PC_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# APC_lungs ---------- 
tmp_flow_term = -(q_vector[3])*APC_lungs+(q_vector[2]*APC_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_lungs ---------- 
tmp_flow_term = -(q_vector[3])*ATIII_lungs+(q_vector[2]*ATIII_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# TM_lungs ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_lungs ---------- 
push!(species_flow_vector,0.0);

# Fibrin_lungs ---------- 
tmp_flow_term = -(q_vector[3])*Fibrin_lungs+(q_vector[2]*Fibrin_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_lungs ---------- 
tmp_flow_term = -(q_vector[3])*Plasmin_lungs+(q_vector[2]*Plasmin_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_lungs ---------- 
tmp_flow_term = -(q_vector[3])*Fibrinogen_lungs+(q_vector[2]*Fibrinogen_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_lungs ---------- 
tmp_flow_term = -(q_vector[3])*Plasminogen_lungs+(q_vector[2]*Plasminogen_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_lungs ---------- 
tmp_flow_term = -(q_vector[3])*tPA_lungs+(q_vector[2]*tPA_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_lungs ---------- 
tmp_flow_term = -(q_vector[3])*uPA_lungs+(q_vector[2]*uPA_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_lungs ---------- 
tmp_flow_term = -(q_vector[3])*Fibrin_monomer_lungs+(q_vector[2]*Fibrin_monomer_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_lungs ---------- 
tmp_flow_term = -(q_vector[3])*Protofibril_lungs+(q_vector[2]*Protofibril_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_lungs ---------- 
tmp_flow_term = -(q_vector[3])*antiplasmin_lungs+(q_vector[2]*antiplasmin_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_lungs ---------- 
tmp_flow_term = -(q_vector[3])*PAI_1_lungs+(q_vector[2]*PAI_1_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_lungs ---------- 
tmp_flow_term = -(q_vector[3])*Fiber_lungs+(q_vector[2]*Fiber_heart);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# FII_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*FII_artery+(q_vector[4]*FII_heart+q_vector[12]*FII_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*FIIa_artery+(q_vector[4]*FIIa_heart+q_vector[12]*FIIa_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# PC_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*PC_artery+(q_vector[4]*PC_heart+q_vector[12]*PC_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# APC_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*APC_artery+(q_vector[4]*APC_heart+q_vector[12]*APC_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*ATIII_artery+(q_vector[4]*ATIII_heart+q_vector[12]*ATIII_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# TM_artery ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_artery ---------- 
push!(species_flow_vector,0.0);

# Fibrin_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*Fibrin_artery+(q_vector[4]*Fibrin_heart+q_vector[12]*Fibrin_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*Plasmin_artery+(q_vector[4]*Plasmin_heart+q_vector[12]*Plasmin_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*Fibrinogen_artery+(q_vector[4]*Fibrinogen_heart+q_vector[12]*Fibrinogen_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*Plasminogen_artery+(q_vector[4]*Plasminogen_heart+q_vector[12]*Plasminogen_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*tPA_artery+(q_vector[4]*tPA_heart+q_vector[12]*tPA_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*uPA_artery+(q_vector[4]*uPA_heart+q_vector[12]*uPA_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*Fibrin_monomer_artery+(q_vector[4]*Fibrin_monomer_heart+q_vector[12]*Fibrin_monomer_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*Protofibril_artery+(q_vector[4]*Protofibril_heart+q_vector[12]*Protofibril_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*antiplasmin_artery+(q_vector[4]*antiplasmin_heart+q_vector[12]*antiplasmin_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*PAI_1_artery+(q_vector[4]*PAI_1_heart+q_vector[12]*PAI_1_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_artery ---------- 
tmp_flow_term = -(q_vector[5]+q_vector[7]+q_vector[9]+q_vector[11])*Fiber_artery+(q_vector[4]*Fiber_heart+q_vector[12]*Fiber_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# FII_kidney ---------- 
tmp_flow_term = -(q_vector[6])*FII_kidney+(q_vector[5]*FII_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_kidney ---------- 
tmp_flow_term = -(q_vector[6])*FIIa_kidney+(q_vector[5]*FIIa_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# PC_kidney ---------- 
tmp_flow_term = -(q_vector[6])*PC_kidney+(q_vector[5]*PC_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# APC_kidney ---------- 
tmp_flow_term = -(q_vector[6])*APC_kidney+(q_vector[5]*APC_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_kidney ---------- 
tmp_flow_term = -(q_vector[6])*ATIII_kidney+(q_vector[5]*ATIII_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# TM_kidney ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_kidney ---------- 
push!(species_flow_vector,0.0);

# Fibrin_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Fibrin_kidney+(q_vector[5]*Fibrin_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Plasmin_kidney+(q_vector[5]*Plasmin_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Fibrinogen_kidney+(q_vector[5]*Fibrinogen_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Plasminogen_kidney+(q_vector[5]*Plasminogen_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_kidney ---------- 
tmp_flow_term = -(q_vector[6])*tPA_kidney+(q_vector[5]*tPA_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_kidney ---------- 
tmp_flow_term = -(q_vector[6])*uPA_kidney+(q_vector[5]*uPA_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Fibrin_monomer_kidney+(q_vector[5]*Fibrin_monomer_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Protofibril_kidney+(q_vector[5]*Protofibril_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_kidney ---------- 
tmp_flow_term = -(q_vector[6])*antiplasmin_kidney+(q_vector[5]*antiplasmin_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_kidney ---------- 
tmp_flow_term = -(q_vector[6])*PAI_1_kidney+(q_vector[5]*PAI_1_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Fiber_kidney+(q_vector[5]*Fiber_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# FII_liver ---------- 
tmp_flow_term = -(q_vector[8])*FII_liver+(q_vector[7]*FII_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_liver ---------- 
tmp_flow_term = -(q_vector[8])*FIIa_liver+(q_vector[7]*FIIa_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# PC_liver ---------- 
tmp_flow_term = -(q_vector[8])*PC_liver+(q_vector[7]*PC_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# APC_liver ---------- 
tmp_flow_term = -(q_vector[8])*APC_liver+(q_vector[7]*APC_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_liver ---------- 
tmp_flow_term = -(q_vector[8])*ATIII_liver+(q_vector[7]*ATIII_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# TM_liver ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_liver ---------- 
push!(species_flow_vector,0.0);

# Fibrin_liver ---------- 
tmp_flow_term = -(q_vector[8])*Fibrin_liver+(q_vector[7]*Fibrin_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_liver ---------- 
tmp_flow_term = -(q_vector[8])*Plasmin_liver+(q_vector[7]*Plasmin_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_liver ---------- 
tmp_flow_term = -(q_vector[8])*Fibrinogen_liver+(q_vector[7]*Fibrinogen_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_liver ---------- 
tmp_flow_term = -(q_vector[8])*Plasminogen_liver+(q_vector[7]*Plasminogen_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_liver ---------- 
tmp_flow_term = -(q_vector[8])*tPA_liver+(q_vector[7]*tPA_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_liver ---------- 
tmp_flow_term = -(q_vector[8])*uPA_liver+(q_vector[7]*uPA_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_liver ---------- 
tmp_flow_term = -(q_vector[8])*Fibrin_monomer_liver+(q_vector[7]*Fibrin_monomer_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_liver ---------- 
tmp_flow_term = -(q_vector[8])*Protofibril_liver+(q_vector[7]*Protofibril_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_liver ---------- 
tmp_flow_term = -(q_vector[8])*antiplasmin_liver+(q_vector[7]*antiplasmin_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_liver ---------- 
tmp_flow_term = -(q_vector[8])*PAI_1_liver+(q_vector[7]*PAI_1_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_liver ---------- 
tmp_flow_term = -(q_vector[8])*Fiber_liver+(q_vector[7]*Fiber_artery);
push!(species_flow_vector,(1.0/volume_liver)*tmp_flow_term);
tmp_flow_term = 0;

# FII_bulk ---------- 
tmp_flow_term = -(q_vector[10])*FII_bulk+(q_vector[9]*FII_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_bulk ---------- 
tmp_flow_term = -(q_vector[10])*FIIa_bulk+(q_vector[9]*FIIa_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# PC_bulk ---------- 
tmp_flow_term = -(q_vector[10])*PC_bulk+(q_vector[9]*PC_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# APC_bulk ---------- 
tmp_flow_term = -(q_vector[10])*APC_bulk+(q_vector[9]*APC_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_bulk ---------- 
tmp_flow_term = -(q_vector[10])*ATIII_bulk+(q_vector[9]*ATIII_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# TM_bulk ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_bulk ---------- 
push!(species_flow_vector,0.0);

# Fibrin_bulk ---------- 
tmp_flow_term = -(q_vector[10])*Fibrin_bulk+(q_vector[9]*Fibrin_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_bulk ---------- 
tmp_flow_term = -(q_vector[10])*Plasmin_bulk+(q_vector[9]*Plasmin_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_bulk ---------- 
tmp_flow_term = -(q_vector[10])*Fibrinogen_bulk+(q_vector[9]*Fibrinogen_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_bulk ---------- 
tmp_flow_term = -(q_vector[10])*Plasminogen_bulk+(q_vector[9]*Plasminogen_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_bulk ---------- 
tmp_flow_term = -(q_vector[10])*tPA_bulk+(q_vector[9]*tPA_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_bulk ---------- 
tmp_flow_term = -(q_vector[10])*uPA_bulk+(q_vector[9]*uPA_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_bulk ---------- 
tmp_flow_term = -(q_vector[10])*Fibrin_monomer_bulk+(q_vector[9]*Fibrin_monomer_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_bulk ---------- 
tmp_flow_term = -(q_vector[10])*Protofibril_bulk+(q_vector[9]*Protofibril_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_bulk ---------- 
tmp_flow_term = -(q_vector[10])*antiplasmin_bulk+(q_vector[9]*antiplasmin_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_bulk ---------- 
tmp_flow_term = -(q_vector[10])*PAI_1_bulk+(q_vector[9]*PAI_1_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_bulk ---------- 
tmp_flow_term = -(q_vector[10])*Fiber_bulk+(q_vector[9]*Fiber_artery);
push!(species_flow_vector,(1.0/volume_bulk)*tmp_flow_term);
tmp_flow_term = 0;

# FII_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*FII_wound+(q_vector[11]*FII_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*FIIa_wound+(q_vector[11]*FIIa_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# PC_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*PC_wound+(q_vector[11]*PC_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# APC_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*APC_wound+(q_vector[11]*APC_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*ATIII_wound+(q_vector[11]*ATIII_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# TM_wound ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_wound ---------- 
push!(species_flow_vector,0.0);

# Fibrin_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*Fibrin_wound+(q_vector[11]*Fibrin_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*Plasmin_wound+(q_vector[11]*Plasmin_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*Fibrinogen_wound+(q_vector[11]*Fibrinogen_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*Plasminogen_wound+(q_vector[11]*Plasminogen_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*tPA_wound+(q_vector[11]*tPA_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*uPA_wound+(q_vector[11]*uPA_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*Fibrin_monomer_wound+(q_vector[11]*Fibrin_monomer_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*Protofibril_wound+(q_vector[11]*Protofibril_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*antiplasmin_wound+(q_vector[11]*antiplasmin_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*PAI_1_wound+(q_vector[11]*PAI_1_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_wound ---------- 
tmp_flow_term = -(q_vector[12]+q_vector[13])*Fiber_wound+(q_vector[11]*Fiber_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
