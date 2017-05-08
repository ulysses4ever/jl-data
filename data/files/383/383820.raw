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
# Generation timestamp: 03-30-2016 10:35:36
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

# lungs
FII_lungs = x[8];
FIIa_lungs = x[9];
PC_lungs = x[10];
APC_lungs = x[11];
ATIII_lungs = x[12];
TM_lungs = x[13];
TRIGGER_lungs = x[14];

# artery
FII_artery = x[15];
FIIa_artery = x[16];
PC_artery = x[17];
APC_artery = x[18];
ATIII_artery = x[19];
TM_artery = x[20];
TRIGGER_artery = x[21];

# heart
FII_heart = x[22];
FIIa_heart = x[23];
PC_heart = x[24];
APC_heart = x[25];
ATIII_heart = x[26];
TM_heart = x[27];
TRIGGER_heart = x[28];

# kidney
FII_kidney = x[29];
FIIa_kidney = x[30];
PC_kidney = x[31];
APC_kidney = x[32];
ATIII_kidney = x[33];
TM_kidney = x[34];
TRIGGER_kidney = x[35];

# wound
FII_wound = x[36];
FIIa_wound = x[37];
PC_wound = x[38];
APC_wound = x[39];
ATIII_wound = x[40];
TM_wound = x[41];
TRIGGER_wound = x[42];
volume_vein = x[43];
volume_lungs = x[44];
volume_artery = x[45];
volume_heart = x[46];
volume_kidney = x[47];
volume_wound = x[48];

# Alias the species input vector - 
input_concentration_array = data_dictionary["INPUT_CONCENTRATION_ARRAY"]

# Get data we need from the data_dictionary - 
default_bpm = data_dictionary["DEFAULT_BEATS_PER_MINUTE"];
default_stroke_volume = data_dictionary["DEFAULT_STROKE_VOLUME"];
default_flow_parameter_array = data_dictionary["FLOW_PARAMETER_ARRAY"];

# Update the heart rate, and stroke volume - 
(bpm,stroke_volume,Cnor,Cach) = HeartRate(t,x,default_bpm,default_stroke_volume,data_dictionary);

# Update the fraction of cardiac output going to each organ - 
(flow_parameter_array,x) = CardiacDistribution(t,x,default_flow_parameter_array,data_dictionary,Cnor,Cach);

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

return (x,species_flow_vector,q_vector);
end;
