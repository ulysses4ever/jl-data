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
# Generation timestamp: 03-10-2016 15:38:03
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
Z1_vein = x[1];
E1_vein = x[2];
D1_vein = x[3];
Z2_vein = x[4];
E2_vein = x[5];
D2_vein = x[6];
E3_vein = x[7];
E4_vein = x[8];
D3_vein = x[9];
Z4_vein = x[10];
D4_vein = x[11];

# lungs
Z1_lungs = x[12];
E1_lungs = x[13];
D1_lungs = x[14];
Z2_lungs = x[15];
E2_lungs = x[16];
D2_lungs = x[17];
E3_lungs = x[18];
E4_lungs = x[19];
D3_lungs = x[20];
Z4_lungs = x[21];
D4_lungs = x[22];

# artery
Z1_artery = x[23];
E1_artery = x[24];
D1_artery = x[25];
Z2_artery = x[26];
E2_artery = x[27];
D2_artery = x[28];
E3_artery = x[29];
E4_artery = x[30];
D3_artery = x[31];
Z4_artery = x[32];
D4_artery = x[33];

# heart
Z1_heart = x[34];
E1_heart = x[35];
D1_heart = x[36];
Z2_heart = x[37];
E2_heart = x[38];
D2_heart = x[39];
E3_heart = x[40];
E4_heart = x[41];
D3_heart = x[42];
Z4_heart = x[43];
D4_heart = x[44];

# kidney
Z1_kidney = x[45];
E1_kidney = x[46];
D1_kidney = x[47];
Z2_kidney = x[48];
E2_kidney = x[49];
D2_kidney = x[50];
E3_kidney = x[51];
E4_kidney = x[52];
D3_kidney = x[53];
Z4_kidney = x[54];
D4_kidney = x[55];

# wound
Z1_wound = x[56];
E1_wound = x[57];
D1_wound = x[58];
Z2_wound = x[59];
E2_wound = x[60];
D2_wound = x[61];
E3_wound = x[62];
E4_wound = x[63];
D3_wound = x[64];
Z4_wound = x[65];
D4_wound = x[66];
volume_vein = x[67];
volume_lungs = x[68];
volume_artery = x[69];
volume_heart = x[70];
volume_kidney = x[71];
volume_wound = x[72];

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

# 6 kideny_to_vein
tmp_flow_rate = cardiac_output*flow_parameter_array[6];
push!(q_vector,tmp_flow_rate);

# 7 artery_to_wound
tmp_flow_rate = cardiac_output*flow_parameter_array[7];
push!(q_vector,tmp_flow_rate);

# 8 artery_to_wound_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[8];
push!(q_vector,tmp_flow_rate);

# 9 artery_to_degredation
tmp_flow_rate = cardiac_output*flow_parameter_array[9];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# Z1_vein ---------- 
tmp_flow_term = -(q_vector[1])*Z1_vein+(q_vector[4]*Z1_heart+q_vector[6]*Z1_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# E1_vein ---------- 
tmp_flow_term = -(q_vector[1])*E1_vein+(q_vector[4]*E1_heart+q_vector[6]*E1_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# D1_vein ---------- 
tmp_flow_term = -(q_vector[1])*D1_vein+(q_vector[4]*D1_heart+q_vector[6]*D1_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Z2_vein ---------- 
tmp_flow_term = -(q_vector[1])*Z2_vein+(q_vector[4]*Z2_heart+q_vector[6]*Z2_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# E2_vein ---------- 
tmp_flow_term = -(q_vector[1])*E2_vein+(q_vector[4]*E2_heart+q_vector[6]*E2_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# D2_vein ---------- 
tmp_flow_term = -(q_vector[1])*D2_vein+(q_vector[4]*D2_heart+q_vector[6]*D2_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# E3_vein ---------- 
tmp_flow_term = -(q_vector[1])*E3_vein+(q_vector[4]*E3_heart+q_vector[6]*E3_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# E4_vein ---------- 
tmp_flow_term = -(q_vector[1])*E4_vein+(q_vector[4]*E4_heart+q_vector[6]*E4_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# D3_vein ---------- 
tmp_flow_term = -(q_vector[1])*D3_vein+(q_vector[4]*D3_heart+q_vector[6]*D3_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Z4_vein ---------- 
tmp_flow_term = -(q_vector[1])*Z4_vein+(q_vector[4]*Z4_heart+q_vector[6]*Z4_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# D4_vein ---------- 
tmp_flow_term = -(q_vector[1])*D4_vein+(q_vector[4]*D4_heart+q_vector[6]*D4_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Z1_lungs+(q_vector[1]*Z1_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# E1_lungs ---------- 
tmp_flow_term = -(q_vector[2])*E1_lungs+(q_vector[1]*E1_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# D1_lungs ---------- 
tmp_flow_term = -(q_vector[2])*D1_lungs+(q_vector[1]*D1_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Z2_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Z2_lungs+(q_vector[1]*Z2_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# E2_lungs ---------- 
tmp_flow_term = -(q_vector[2])*E2_lungs+(q_vector[1]*E2_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# D2_lungs ---------- 
tmp_flow_term = -(q_vector[2])*D2_lungs+(q_vector[1]*D2_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# E3_lungs ---------- 
tmp_flow_term = -(q_vector[2])*E3_lungs+(q_vector[1]*E3_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# E4_lungs ---------- 
tmp_flow_term = -(q_vector[2])*E4_lungs+(q_vector[1]*E4_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# D3_lungs ---------- 
tmp_flow_term = -(q_vector[2])*D3_lungs+(q_vector[1]*D3_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Z4_lungs ---------- 
tmp_flow_term = -(q_vector[2])*Z4_lungs+(q_vector[1]*Z4_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# D4_lungs ---------- 
tmp_flow_term = -(q_vector[2])*D4_lungs+(q_vector[1]*D4_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*Z1_artery+(q_vector[2]*Z1_lungs+q_vector[8]*Z1_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# E1_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*E1_artery+(q_vector[2]*E1_lungs+q_vector[8]*E1_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# D1_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*D1_artery+(q_vector[2]*D1_lungs+q_vector[8]*D1_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Z2_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*Z2_artery+(q_vector[2]*Z2_lungs+q_vector[8]*Z2_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# E2_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*E2_artery+(q_vector[2]*E2_lungs+q_vector[8]*E2_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# D2_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*D2_artery+(q_vector[2]*D2_lungs+q_vector[8]*D2_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# E3_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*E3_artery+(q_vector[2]*E3_lungs+q_vector[8]*E3_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# E4_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*E4_artery+(q_vector[2]*E4_lungs+q_vector[8]*E4_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# D3_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*D3_artery+(q_vector[2]*D3_lungs+q_vector[8]*D3_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Z4_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*Z4_artery+(q_vector[2]*Z4_lungs+q_vector[8]*Z4_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# D4_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*D4_artery+(q_vector[2]*D4_lungs+q_vector[8]*D4_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_heart ---------- 
tmp_flow_term = -(q_vector[4])*Z1_heart+(q_vector[3]*Z1_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# E1_heart ---------- 
tmp_flow_term = -(q_vector[4])*E1_heart+(q_vector[3]*E1_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# D1_heart ---------- 
tmp_flow_term = -(q_vector[4])*D1_heart+(q_vector[3]*D1_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Z2_heart ---------- 
tmp_flow_term = -(q_vector[4])*Z2_heart+(q_vector[3]*Z2_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# E2_heart ---------- 
tmp_flow_term = -(q_vector[4])*E2_heart+(q_vector[3]*E2_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# D2_heart ---------- 
tmp_flow_term = -(q_vector[4])*D2_heart+(q_vector[3]*D2_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# E3_heart ---------- 
tmp_flow_term = -(q_vector[4])*E3_heart+(q_vector[3]*E3_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# E4_heart ---------- 
tmp_flow_term = -(q_vector[4])*E4_heart+(q_vector[3]*E4_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# D3_heart ---------- 
tmp_flow_term = -(q_vector[4])*D3_heart+(q_vector[3]*D3_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Z4_heart ---------- 
tmp_flow_term = -(q_vector[4])*Z4_heart+(q_vector[3]*Z4_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# D4_heart ---------- 
tmp_flow_term = -(q_vector[4])*D4_heart+(q_vector[3]*D4_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Z1_kidney+(q_vector[5]*Z1_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# E1_kidney ---------- 
tmp_flow_term = -(q_vector[6])*E1_kidney+(q_vector[5]*E1_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# D1_kidney ---------- 
tmp_flow_term = -(q_vector[6])*D1_kidney+(q_vector[5]*D1_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Z2_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Z2_kidney+(q_vector[5]*Z2_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# E2_kidney ---------- 
tmp_flow_term = -(q_vector[6])*E2_kidney+(q_vector[5]*E2_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# D2_kidney ---------- 
tmp_flow_term = -(q_vector[6])*D2_kidney+(q_vector[5]*D2_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# E3_kidney ---------- 
tmp_flow_term = -(q_vector[6])*E3_kidney+(q_vector[5]*E3_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# E4_kidney ---------- 
tmp_flow_term = -(q_vector[6])*E4_kidney+(q_vector[5]*E4_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# D3_kidney ---------- 
tmp_flow_term = -(q_vector[6])*D3_kidney+(q_vector[5]*D3_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Z4_kidney ---------- 
tmp_flow_term = -(q_vector[6])*Z4_kidney+(q_vector[5]*Z4_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# D4_kidney ---------- 
tmp_flow_term = -(q_vector[6])*D4_kidney+(q_vector[5]*D4_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_wound ---------- 
tmp_flow_term = -(q_vector[8])*Z1_wound+(q_vector[7]*Z1_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E1_wound ---------- 
tmp_flow_term = -(q_vector[8])*E1_wound+(q_vector[7]*E1_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D1_wound ---------- 
tmp_flow_term = -(q_vector[8])*D1_wound+(q_vector[7]*D1_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Z2_wound ---------- 
tmp_flow_term = -(q_vector[8])*Z2_wound+(q_vector[7]*Z2_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E2_wound ---------- 
tmp_flow_term = -(q_vector[8])*E2_wound+(q_vector[7]*E2_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D2_wound ---------- 
tmp_flow_term = -(q_vector[8])*D2_wound+(q_vector[7]*D2_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E3_wound ---------- 
tmp_flow_term = -(q_vector[8])*E3_wound+(q_vector[7]*E3_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E4_wound ---------- 
tmp_flow_term = -(q_vector[8])*E4_wound+(q_vector[7]*E4_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D3_wound ---------- 
tmp_flow_term = -(q_vector[8])*D3_wound+(q_vector[7]*D3_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Z4_wound ---------- 
tmp_flow_term = -(q_vector[8])*Z4_wound+(q_vector[7]*Z4_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D4_wound ---------- 
tmp_flow_term = -(q_vector[8])*D4_wound+(q_vector[7]*D4_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
