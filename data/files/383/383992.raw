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
# Generation timestamp: 03-23-2016 13:31:28
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
# supply
Z1_supply = x[1];
E1_supply = x[2];
E0_supply = x[3];
Z2_supply = x[4];
E2_supply = x[5];
D1_supply = x[6];
D2_supply = x[7];

# C1
Z1_C1 = x[8];
E1_C1 = x[9];
E0_C1 = x[10];
Z2_C1 = x[11];
E2_C1 = x[12];
D1_C1 = x[13];
D2_C1 = x[14];

# wound
Z1_wound = x[15];
E1_wound = x[16];
E0_wound = x[17];
Z2_wound = x[18];
E2_wound = x[19];
D1_wound = x[20];
D2_wound = x[21];

# C2
Z1_C2 = x[22];
E1_C2 = x[23];
E0_C2 = x[24];
Z2_C2 = x[25];
E2_C2 = x[26];
D1_C2 = x[27];
D2_C2 = x[28];
volume_supply = x[29];
volume_C1 = x[30];
volume_wound = x[31];
volume_C2 = x[32];

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

# 1 supply_to_C1
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
if(t < 2)
	tmp_flow_rate = 0 #no fluid injection before t = 2
end

push!(q_vector,tmp_flow_rate);

# 2 C1_to_wound
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# 3 wound_to_C2
tmp_flow_rate = cardiac_output*flow_parameter_array[3];
push!(q_vector,tmp_flow_rate);

# 4 C2_to_C1
tmp_flow_rate = cardiac_output*flow_parameter_array[4];
push!(q_vector,tmp_flow_rate);

# 5 C2_to_clearance
tmp_flow_rate = cardiac_output*flow_parameter_array[5];
push!(q_vector,tmp_flow_rate);

# 6 bleed_out
tmp_flow_rate = cardiac_output*flow_parameter_array[6];
if(t < 2)
	tmp_flow_rate = 0 #no fluid injection before t = 2
end
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# Z1_supply ---------- 
tmp_flow_term = -(q_vector[1])*Z1_supply;
push!(species_flow_vector,(1.0/volume_supply)*tmp_flow_term);
tmp_flow_term = 0;

# E1_supply ---------- 
tmp_flow_term = -(q_vector[1])*E1_supply;
push!(species_flow_vector,(1.0/volume_supply)*tmp_flow_term);
tmp_flow_term = 0;

# E0_supply ---------- 
push!(species_flow_vector,0.0);

# Z2_supply ---------- 
tmp_flow_term = -(q_vector[1])*Z2_supply;
push!(species_flow_vector,(1.0/volume_supply)*tmp_flow_term);
tmp_flow_term = 0;

# E2_supply ---------- 
tmp_flow_term = -(q_vector[1])*E2_supply;
push!(species_flow_vector,(1.0/volume_supply)*tmp_flow_term);
tmp_flow_term = 0;

# D1_supply ---------- 
tmp_flow_term = -(q_vector[1])*D1_supply;
push!(species_flow_vector,(1.0/volume_supply)*tmp_flow_term);
tmp_flow_term = 0;

# D2_supply ---------- 
tmp_flow_term = -(q_vector[1])*D2_supply;
push!(species_flow_vector,(1.0/volume_supply)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Z1_C1+(q_vector[1]*Z1_supply+q_vector[4]*Z1_C2);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# E1_C1 ---------- 
tmp_flow_term = -(q_vector[2])*E1_C1+(q_vector[1]*E1_supply+q_vector[4]*E1_C2);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# E0_C1 ---------- 
push!(species_flow_vector,0.0);

# Z2_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Z2_C1+(q_vector[1]*Z2_supply+q_vector[4]*Z2_C2);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# E2_C1 ---------- 
tmp_flow_term = -(q_vector[2])*E2_C1+(q_vector[1]*E2_supply+q_vector[4]*E2_C2);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# D1_C1 ---------- 
tmp_flow_term = -(q_vector[2])*D1_C1+(q_vector[1]*D1_supply+q_vector[4]*D1_C2);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# D2_C1 ---------- 
tmp_flow_term = -(q_vector[2])*D2_C1+(q_vector[1]*D2_supply+q_vector[4]*D2_C2);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_wound ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[6])*Z1_wound+(q_vector[2]*Z1_C1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E1_wound ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[6])*E1_wound+(q_vector[2]*E1_C1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E0_wound ---------- 
push!(species_flow_vector,0.0);

# Z2_wound ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[6])*Z2_wound+(q_vector[2]*Z2_C1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E2_wound ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[6])*E2_wound+(q_vector[2]*E2_C1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D1_wound ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[6])*D1_wound+(q_vector[2]*D1_C1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D2_wound ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[6])*D2_wound+(q_vector[2]*D2_C1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_C2 ---------- 
tmp_flow_term = -(q_vector[4]+q_vector[5])*Z1_C2+(q_vector[3]*Z1_wound);
push!(species_flow_vector,(1.0/volume_C2)*tmp_flow_term);
tmp_flow_term = 0;

# E1_C2 ---------- 
tmp_flow_term = -(q_vector[4]+q_vector[5])*E1_C2+(q_vector[3]*E1_wound);
push!(species_flow_vector,(1.0/volume_C2)*tmp_flow_term);
tmp_flow_term = 0;

# E0_C2 ---------- 
push!(species_flow_vector,0.0);

# Z2_C2 ---------- 
tmp_flow_term = -(q_vector[4]+q_vector[5])*Z2_C2+(q_vector[3]*Z2_wound);
push!(species_flow_vector,(1.0/volume_C2)*tmp_flow_term);
tmp_flow_term = 0;

# E2_C2 ---------- 
tmp_flow_term = -(q_vector[4]+q_vector[5])*E2_C2+(q_vector[3]*E2_wound);
push!(species_flow_vector,(1.0/volume_C2)*tmp_flow_term);
tmp_flow_term = 0;

# D1_C2 ---------- 
tmp_flow_term = -(q_vector[4]+q_vector[5])*D1_C2+(q_vector[3]*D1_wound);
push!(species_flow_vector,(1.0/volume_C2)*tmp_flow_term);
tmp_flow_term = 0;

# D2_C2 ---------- 
tmp_flow_term = -(q_vector[4]+q_vector[5])*D2_C2+(q_vector[3]*D2_wound);
push!(species_flow_vector,(1.0/volume_C2)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
