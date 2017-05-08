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
# Username: jeffreyvarner
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-02-2016 14:35:17
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
# compartment_1
A_compartment_1 = x[1];
B_compartment_1 = x[2];
E_compartment_1 = x[3];
II_compartment_1 = x[4];
AI_compartment_1 = x[5];

# compartment_2
A_compartment_2 = x[6];
B_compartment_2 = x[7];
E_compartment_2 = x[8];
II_compartment_2 = x[9];
AI_compartment_2 = x[10];

# compartment_3
A_compartment_3 = x[11];
B_compartment_3 = x[12];
E_compartment_3 = x[13];
II_compartment_3 = x[14];
AI_compartment_3 = x[15];

# compartment_4
A_compartment_4 = x[16];
B_compartment_4 = x[17];
E_compartment_4 = x[18];
II_compartment_4 = x[19];
AI_compartment_4 = x[20];

# compartment_5
A_compartment_5 = x[21];
B_compartment_5 = x[22];
E_compartment_5 = x[23];
II_compartment_5 = x[24];
AI_compartment_5 = x[25];

# wound_compartment
A_wound_compartment = x[26];
B_wound_compartment = x[27];
E_wound_compartment = x[28];
II_wound_compartment = x[29];
AI_wound_compartment = x[30];
volume_compartment_1 = x[31];
volume_compartment_2 = x[32];
volume_compartment_3 = x[33];
volume_compartment_4 = x[34];
volume_compartment_5 = x[35];
volume_wound_compartment = x[36];

# Alias the species input vector - 
input_concentration_array = data_dictionary["INPUT_CONCENTRATION_ARRAY"]
A_input_compartment_1 = input_concentration_array[1];
B_input_compartment_1 = input_concentration_array[2];
E_input_compartment_1 = input_concentration_array[3];
II_input_compartment_1 = input_concentration_array[4];
AI_input_compartment_1 = input_concentration_array[5];

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

# 1 C1C2
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# 2 C2C3
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# 3 C3C4
tmp_flow_rate = cardiac_output*flow_parameter_array[3];
push!(q_vector,tmp_flow_rate);

# 4 C3C5
tmp_flow_rate = cardiac_output*flow_parameter_array[4];
push!(q_vector,tmp_flow_rate);

# 5 C4C1
tmp_flow_rate = cardiac_output*flow_parameter_array[5];
push!(q_vector,tmp_flow_rate);

# 6 C5C1
tmp_flow_rate = cardiac_output*flow_parameter_array[6];
push!(q_vector,tmp_flow_rate);

# 7 C1W
tmp_flow_rate = cardiac_output*flow_parameter_array[7];
push!(q_vector,tmp_flow_rate);

# 8 C1W_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[8];
push!(q_vector,tmp_flow_rate);

# 9 Loss_W
tmp_flow_rate = cardiac_output*flow_parameter_array[9];
push!(q_vector,tmp_flow_rate);

# 10 addition_of_fluid
tmp_flow_rate = flow_parameter_array[10];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# A_compartment_1 ---------- 
tmp_flow_term = -(q_vector[1]+q_vector[7])*A_compartment_1+(q_vector[5]*A_compartment_4+q_vector[6]*A_compartment_5+q_vector[8]*A_wound_compartment+q_vector[10]*A_input_compartment_1);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_1 ---------- 
tmp_flow_term = -(q_vector[1]+q_vector[7])*B_compartment_1+(q_vector[5]*B_compartment_4+q_vector[6]*B_compartment_5+q_vector[8]*B_wound_compartment+q_vector[10]*B_input_compartment_1);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_1 ---------- 
push!(species_flow_vector,0.0);

# II_compartment_1 ---------- 
push!(species_flow_vector,0.0);

# AI_compartment_1 ---------- 
tmp_flow_term = -(q_vector[1]+q_vector[7])*AI_compartment_1+(q_vector[5]*AI_compartment_4+q_vector[6]*AI_compartment_5+q_vector[8]*AI_wound_compartment+q_vector[10]*AI_input_compartment_1);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# A_compartment_2 ---------- 
tmp_flow_term = -(q_vector[2])*A_compartment_2+(q_vector[1]*A_compartment_1);
push!(species_flow_vector,(1.0/volume_compartment_2)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_2 ---------- 
tmp_flow_term = -(q_vector[2])*B_compartment_2+(q_vector[1]*B_compartment_1);
push!(species_flow_vector,(1.0/volume_compartment_2)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_2 ---------- 
push!(species_flow_vector,0.0);

# II_compartment_2 ---------- 
push!(species_flow_vector,0.0);

# AI_compartment_2 ---------- 
tmp_flow_term = -(q_vector[2])*AI_compartment_2+(q_vector[1]*AI_compartment_1);
push!(species_flow_vector,(1.0/volume_compartment_2)*tmp_flow_term);
tmp_flow_term = 0;

# A_compartment_3 ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[4])*A_compartment_3+(q_vector[2]*A_compartment_2);
push!(species_flow_vector,(1.0/volume_compartment_3)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_3 ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[4])*B_compartment_3+(q_vector[2]*B_compartment_2);
push!(species_flow_vector,(1.0/volume_compartment_3)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_3 ---------- 
push!(species_flow_vector,0.0);

# II_compartment_3 ---------- 
push!(species_flow_vector,0.0);

# AI_compartment_3 ---------- 
tmp_flow_term = -(q_vector[3]+q_vector[4])*AI_compartment_3+(q_vector[2]*AI_compartment_2);
push!(species_flow_vector,(1.0/volume_compartment_3)*tmp_flow_term);
tmp_flow_term = 0;

# A_compartment_4 ---------- 
tmp_flow_term = -(q_vector[5])*A_compartment_4+(q_vector[3]*A_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_4)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_4 ---------- 
tmp_flow_term = -(q_vector[5])*B_compartment_4+(q_vector[3]*B_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_4)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_4 ---------- 
push!(species_flow_vector,0.0);

# II_compartment_4 ---------- 
push!(species_flow_vector,0.0);

# AI_compartment_4 ---------- 
tmp_flow_term = -(q_vector[5])*AI_compartment_4+(q_vector[3]*AI_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_4)*tmp_flow_term);
tmp_flow_term = 0;

# A_compartment_5 ---------- 
tmp_flow_term = -(q_vector[6])*A_compartment_5+(q_vector[4]*A_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_5)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_5 ---------- 
tmp_flow_term = -(q_vector[6])*B_compartment_5+(q_vector[4]*B_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_5)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_5 ---------- 
push!(species_flow_vector,0.0);

# II_compartment_5 ---------- 
push!(species_flow_vector,0.0);

# AI_compartment_5 ---------- 
tmp_flow_term = -(q_vector[6])*AI_compartment_5+(q_vector[4]*AI_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_5)*tmp_flow_term);
tmp_flow_term = 0;

# A_wound_compartment ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*A_wound_compartment+(q_vector[7]*A_compartment_1);
push!(species_flow_vector,(1.0/volume_wound_compartment)*tmp_flow_term);
tmp_flow_term = 0;

# B_wound_compartment ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*B_wound_compartment+(q_vector[7]*B_compartment_1);
push!(species_flow_vector,(1.0/volume_wound_compartment)*tmp_flow_term);
tmp_flow_term = 0;

# E_wound_compartment ---------- 
push!(species_flow_vector,0.0);

# II_wound_compartment ---------- 
push!(species_flow_vector,0.0);

# AI_wound_compartment ---------- 
tmp_flow_term = -(q_vector[8]+q_vector[9])*AI_wound_compartment+(q_vector[7]*AI_compartment_1);
push!(species_flow_vector,(1.0/volume_wound_compartment)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
