include("HeartRate.jl");
include("CardiacDistribution.jl");
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
# Generation timestamp: 05-06-2016 09:57:05
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

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

# 1 vein_to_lungs
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# 2 lungs_to_artery
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# 3 artery_to_heart
tmp_flow_rate = cardiac_output*flow_parameter_array[3];
push!(q_vector,tmp_flow_rate);

# 4 heart_to_veins
tmp_flow_rate = cardiac_output*flow_parameter_array[4];
push!(q_vector,tmp_flow_rate);

# 5 artery_to_kidney
tmp_flow_rate = cardiac_output*flow_parameter_array[5];
push!(q_vector,tmp_flow_rate);

# 6 kidney_to_vein
tmp_flow_rate = cardiac_output*flow_parameter_array[6];
push!(q_vector,tmp_flow_rate);

# 7 artery_to_wound
tmp_flow_rate = cardiac_output*flow_parameter_array[7];
push!(q_vector,tmp_flow_rate);

# 8 artery_to_wound_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[8];
push!(q_vector,tmp_flow_rate);

# 9 wound_to_degredation
tmp_flow_rate = cardiac_output*flow_parameter_array[9];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# FII_vein ---------- 
tmp_flow_term = -(q_vector[1])*FII_vein+(q_vector[4]*FII_heart+q_vector[6]*FII_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_vein ---------- 
tmp_flow_term = -(q_vector[1])*FIIa_vein+(q_vector[4]*FIIa_heart+q_vector[6]*FIIa_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# PC_vein ---------- 
tmp_flow_term = -(q_vector[1])*PC_vein+(q_vector[4]*PC_heart+q_vector[6]*PC_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# APC_vein ---------- 
tmp_flow_term = -(q_vector[1])*APC_vein+(q_vector[4]*APC_heart+q_vector[6]*APC_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_vein ---------- 
tmp_flow_term = -(q_vector[1])*ATIII_vein+(q_vector[4]*ATIII_heart+q_vector[6]*ATIII_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# TM_vein ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_vein ---------- 
push!(species_flow_vector,0.0);

# Fibrin_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fibrin_vein+(q_vector[4]*Fibrin_heart+q_vector[6]*Fibrin_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_vein ---------- 
tmp_flow_term = -(q_vector[1])*Plasmin_vein+(q_vector[4]*Plasmin_heart+q_vector[6]*Plasmin_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fibrinogen_vein+(q_vector[4]*Fibrinogen_heart+q_vector[6]*Fibrinogen_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_vein ---------- 
tmp_flow_term = -(q_vector[1])*Plasminogen_vein+(q_vector[4]*Plasminogen_heart+q_vector[6]*Plasminogen_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_vein ---------- 
tmp_flow_term = -(q_vector[1])*tPA_vein+(q_vector[4]*tPA_heart+q_vector[6]*tPA_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_vein ---------- 
tmp_flow_term = -(q_vector[1])*uPA_vein+(q_vector[4]*uPA_heart+q_vector[6]*uPA_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fibrin_monomer_vein+(q_vector[4]*Fibrin_monomer_heart+q_vector[6]*Fibrin_monomer_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_vein ---------- 
tmp_flow_term = -(q_vector[1])*Protofibril_vein+(q_vector[4]*Protofibril_heart+q_vector[6]*Protofibril_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_vein ---------- 
tmp_flow_term = -(q_vector[1])*antiplasmin_vein+(q_vector[4]*antiplasmin_heart+q_vector[6]*antiplasmin_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_vein ---------- 
tmp_flow_term = -(q_vector[1])*PAI_1_vein+(q_vector[4]*PAI_1_heart+q_vector[6]*PAI_1_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_vein ---------- 
tmp_flow_term = -(q_vector[1])*Fiber_vein+(q_vector[4]*Fiber_heart+q_vector[6]*Fiber_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# TAT_vein ---------- 
tmp_flow_term = -(q_vector[1])*TAT_vein+(q_vector[4]*TAT_heart+q_vector[6]*TAT_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# PAP_vein ---------- 
tmp_flow_term = -(q_vector[1])*PAP_vein+(q_vector[4]*PAP_heart+q_vector[6]*PAP_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# FII_lungs ---------- 
tmp_flow_term = -(q_vector[2])*FII_lungs+(q_vector[1]*FII_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_lungs ---------- 
tmp_flow_term = -(q_vector[2])*FIIa_lungs+(q_vector[1]*FIIa_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# PC_lungs ---------- 
tmp_flow_term = -(q_vector[2])*PC_lungs+(q_vector[1]*PC_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# APC_lungs ---------- 
tmp_flow_term = -(q_vector[2])*APC_lungs+(q_vector[1]*APC_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_lungs ---------- 
tmp_flow_term = -(q_vector[2])*ATIII_lungs+(q_vector[1]*ATIII_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# TM_lungs ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_lungs ---------- 
push!(species_flow_vector,0.0);

# Fibrin_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Fibrin_lungs+(q_vector[1]*Fibrin_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Plasmin_lungs+(q_vector[1]*Plasmin_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Fibrinogen_lungs+(q_vector[1]*Fibrinogen_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Plasminogen_lungs+(q_vector[1]*Plasminogen_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_lungs ---------- 
tmp_flow_term = -(q_vector[2])*tPA_lungs+(q_vector[1]*tPA_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_lungs ---------- 
tmp_flow_term = -(q_vector[2])*uPA_lungs+(q_vector[1]*uPA_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Fibrin_monomer_lungs+(q_vector[1]*Fibrin_monomer_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Protofibril_lungs+(q_vector[1]*Protofibril_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_lungs ---------- 
tmp_flow_term = -(q_vector[2])*antiplasmin_lungs+(q_vector[1]*antiplasmin_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_lungs ---------- 
tmp_flow_term = -(q_vector[2])*PAI_1_lungs+(q_vector[1]*PAI_1_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Fiber_lungs+(q_vector[1]*Fiber_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# TAT_lungs ---------- 
tmp_flow_term = -(q_vector[2])*TAT_lungs+(q_vector[1]*TAT_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# PAP_lungs ---------- 
tmp_flow_term = -(q_vector[2])*PAP_lungs+(q_vector[1]*PAP_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# FII_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*FII_artery+(q_vector[2]*FII_lungs+q_vector[8]*FII_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*FIIa_artery+(q_vector[2]*FIIa_lungs+q_vector[8]*FIIa_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# PC_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*PC_artery+(q_vector[2]*PC_lungs+q_vector[8]*PC_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# APC_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*APC_artery+(q_vector[2]*APC_lungs+q_vector[8]*APC_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*ATIII_artery+(q_vector[2]*ATIII_lungs+q_vector[8]*ATIII_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# TM_artery ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_artery ---------- 
push!(species_flow_vector,0.0);

# Fibrin_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*Fibrin_artery+(q_vector[2]*Fibrin_lungs+q_vector[8]*Fibrin_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*Plasmin_artery+(q_vector[2]*Plasmin_lungs+q_vector[8]*Plasmin_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*Fibrinogen_artery+(q_vector[2]*Fibrinogen_lungs+q_vector[8]*Fibrinogen_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*Plasminogen_artery+(q_vector[2]*Plasminogen_lungs+q_vector[8]*Plasminogen_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*tPA_artery+(q_vector[2]*tPA_lungs+q_vector[8]*tPA_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*uPA_artery+(q_vector[2]*uPA_lungs+q_vector[8]*uPA_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*Fibrin_monomer_artery+(q_vector[2]*Fibrin_monomer_lungs+q_vector[8]*Fibrin_monomer_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*Protofibril_artery+(q_vector[2]*Protofibril_lungs+q_vector[8]*Protofibril_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*antiplasmin_artery+(q_vector[2]*antiplasmin_lungs+q_vector[8]*antiplasmin_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*PAI_1_artery+(q_vector[2]*PAI_1_lungs+q_vector[8]*PAI_1_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*Fiber_artery+(q_vector[2]*Fiber_lungs+q_vector[8]*Fiber_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# TAT_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*TAT_artery+(q_vector[2]*TAT_lungs+q_vector[8]*TAT_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# PAP_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7])*PAP_artery+(q_vector[2]*PAP_lungs+q_vector[8]*PAP_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# FII_heart ---------- 
tmp_flow_term = -(q_vector[4])*FII_heart+(q_vector[3]*FII_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_heart ---------- 
tmp_flow_term = -(q_vector[4])*FIIa_heart+(q_vector[3]*FIIa_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# PC_heart ---------- 
tmp_flow_term = -(q_vector[4])*PC_heart+(q_vector[3]*PC_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# APC_heart ---------- 
tmp_flow_term = -(q_vector[4])*APC_heart+(q_vector[3]*APC_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_heart ---------- 
tmp_flow_term = -(q_vector[4])*ATIII_heart+(q_vector[3]*ATIII_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# TM_heart ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_heart ---------- 
push!(species_flow_vector,0.0);

# Fibrin_heart ---------- 
tmp_flow_term = -(q_vector[4])*Fibrin_heart+(q_vector[3]*Fibrin_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_heart ---------- 
tmp_flow_term = -(q_vector[4])*Plasmin_heart+(q_vector[3]*Plasmin_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_heart ---------- 
tmp_flow_term = -(q_vector[4])*Fibrinogen_heart+(q_vector[3]*Fibrinogen_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_heart ---------- 
tmp_flow_term = -(q_vector[4])*Plasminogen_heart+(q_vector[3]*Plasminogen_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_heart ---------- 
tmp_flow_term = -(q_vector[4])*tPA_heart+(q_vector[3]*tPA_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_heart ---------- 
tmp_flow_term = -(q_vector[4])*uPA_heart+(q_vector[3]*uPA_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_heart ---------- 
tmp_flow_term = -(q_vector[4])*Fibrin_monomer_heart+(q_vector[3]*Fibrin_monomer_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_heart ---------- 
tmp_flow_term = -(q_vector[4])*Protofibril_heart+(q_vector[3]*Protofibril_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_heart ---------- 
tmp_flow_term = -(q_vector[4])*antiplasmin_heart+(q_vector[3]*antiplasmin_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_heart ---------- 
tmp_flow_term = -(q_vector[4])*PAI_1_heart+(q_vector[3]*PAI_1_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_heart ---------- 
tmp_flow_term = -(q_vector[4])*Fiber_heart+(q_vector[3]*Fiber_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# TAT_heart ---------- 
tmp_flow_term = -(q_vector[4])*TAT_heart+(q_vector[3]*TAT_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# PAP_heart ---------- 
tmp_flow_term = -(q_vector[4])*PAP_heart+(q_vector[3]*PAP_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
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

# TAT_kidney ---------- 
tmp_flow_term = -(q_vector[6])*TAT_kidney+(q_vector[5]*TAT_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# PAP_kidney ---------- 
tmp_flow_term = -(q_vector[6])*PAP_kidney+(q_vector[5]*PAP_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# FII_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*FII_wound+(q_vector[7]*FII_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*FIIa_wound+(q_vector[7]*FIIa_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# PC_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*PC_wound+(q_vector[7]*PC_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# APC_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*APC_wound+(q_vector[7]*APC_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*ATIII_wound+(q_vector[7]*ATIII_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# TM_wound ---------- 
push!(species_flow_vector,0.0);

# TRIGGER_wound ---------- 
push!(species_flow_vector,0.0);

# Fibrin_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*Fibrin_wound+(q_vector[7]*Fibrin_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*Plasmin_wound+(q_vector[7]*Plasmin_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*Fibrinogen_wound+(q_vector[7]*Fibrinogen_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*Plasminogen_wound+(q_vector[7]*Plasminogen_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*tPA_wound+(q_vector[7]*tPA_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*uPA_wound+(q_vector[7]*uPA_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*Fibrin_monomer_wound+(q_vector[7]*Fibrin_monomer_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*Protofibril_wound+(q_vector[7]*Protofibril_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*antiplasmin_wound+(q_vector[7]*antiplasmin_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*PAI_1_wound+(q_vector[7]*PAI_1_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Fiber_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*Fiber_wound+(q_vector[7]*Fiber_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# TAT_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*TAT_wound+(q_vector[7]*TAT_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# PAP_wound ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*PAP_wound+(q_vector[7]*PAP_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
