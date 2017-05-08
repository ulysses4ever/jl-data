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
# Generation timestamp: 03-10-2016 11:38:01
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
E0_vein = x[3];
D1_vein = x[4];

# lungs
Z1_lungs = x[5];
E1_lungs = x[6];
E0_lungs = x[7];
D1_lungs = x[8];

# artery
Z1_artery = x[9];
E1_artery = x[10];
E0_artery = x[11];
D1_artery = x[12];

# heart
Z1_heart = x[13];
E1_heart = x[14];
E0_heart = x[15];
D1_heart = x[16];

# kidney
Z1_kidney = x[17];
E1_kidney = x[18];
E0_kidney = x[19];
D1_kidney = x[20];

# wound
Z1_wound = x[21];
E1_wound = x[22];
E0_wound = x[23];
D1_wound = x[24];
volume_vein = x[25];
volume_lungs = x[26];
volume_artery = x[27];
volume_heart = x[28];
volume_kidney = x[29];
volume_wound = x[30];

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

# E0_vein ---------- 
tmp_flow_term = -(q_vector[1])*E0_vein+(q_vector[4]*E0_heart+q_vector[6]*E0_kidney);
push!(species_flow_vector,(1.0/volume_vein)*tmp_flow_term);
tmp_flow_term = 0;

# D1_vein ---------- 
tmp_flow_term = -(q_vector[1])*D1_vein+(q_vector[4]*D1_heart+q_vector[6]*D1_kidney);
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

# E0_lungs ---------- 
tmp_flow_term = -(q_vector[2])*E0_lungs+(q_vector[1]*E0_vein);
push!(species_flow_vector,(1.0/volume_lungs)*tmp_flow_term);
tmp_flow_term = 0;

# D1_lungs ---------- 
tmp_flow_term = -(q_vector[2])*D1_lungs+(q_vector[1]*D1_vein);
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

# E0_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*E0_artery+(q_vector[2]*E0_lungs+q_vector[8]*E0_wound);
push!(species_flow_vector,(1.0/volume_artery)*tmp_flow_term);
tmp_flow_term = 0;

# D1_artery ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[5]+q_vector[7]+q_vector[9])*D1_artery+(q_vector[2]*D1_lungs+q_vector[8]*D1_wound);
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

# E0_heart ---------- 
tmp_flow_term = -(q_vector[4])*E0_heart+(q_vector[3]*E0_artery);
push!(species_flow_vector,(1.0/volume_heart)*tmp_flow_term);
tmp_flow_term = 0;

# D1_heart ---------- 
tmp_flow_term = -(q_vector[4])*D1_heart+(q_vector[3]*D1_artery);
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

# E0_kidney ---------- 
tmp_flow_term = -(q_vector[6])*E0_kidney+(q_vector[5]*E0_artery);
push!(species_flow_vector,(1.0/volume_kidney)*tmp_flow_term);
tmp_flow_term = 0;

# D1_kidney ---------- 
tmp_flow_term = -(q_vector[6])*D1_kidney+(q_vector[5]*D1_artery);
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

# E0_wound ---------- 
tmp_flow_term = -(q_vector[8])*E0_wound+(q_vector[7]*E0_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D1_wound ---------- 
tmp_flow_term = -(q_vector[8])*D1_wound+(q_vector[7]*D1_artery);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
