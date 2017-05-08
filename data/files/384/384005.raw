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
# Generation timestamp: 02-25-2016 11:20:11
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

# compartment_2
A_compartment_2 = x[4];
B_compartment_2 = x[5];
E_compartment_2 = x[6];

# compartment_3
A_compartment_3 = x[7];
B_compartment_3 = x[8];
E_compartment_3 = x[9];
volume_compartment_1 = x[10];
volume_compartment_2 = x[11];
volume_compartment_3 = x[12];

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

# 1 C1C2
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# 2 C1C2_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# 3 C2C3
tmp_flow_rate = cardiac_output*flow_parameter_array[3];
push!(q_vector,tmp_flow_rate);

# 4 C2C3_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[4];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# A_compartment_1 ---------- 
tmp_flow_term = -(q_vector[1])*A_compartment_1+(q_vector[2]*A_compartment_2);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_1 ---------- 
tmp_flow_term = -(q_vector[1])*B_compartment_1+(q_vector[2]*B_compartment_2);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_1 ---------- 
push!(species_flow_vector,0.0);

# A_compartment_2 ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[3])*A_compartment_2+(q_vector[1]*A_compartment_1+q_vector[4]*A_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_2)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_2 ---------- 
tmp_flow_term = -(q_vector[2]+q_vector[3])*B_compartment_2+(q_vector[1]*B_compartment_1+q_vector[4]*B_compartment_3);
push!(species_flow_vector,(1.0/volume_compartment_2)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_2 ---------- 
push!(species_flow_vector,0.0);

# A_compartment_3 ---------- 
tmp_flow_term = -(q_vector[4])*A_compartment_3+(q_vector[3]*A_compartment_2);
push!(species_flow_vector,(1.0/volume_compartment_3)*tmp_flow_term);
tmp_flow_term = 0;

# B_compartment_3 ---------- 
tmp_flow_term = -(q_vector[4])*B_compartment_3+(q_vector[3]*B_compartment_2);
push!(species_flow_vector,(1.0/volume_compartment_3)*tmp_flow_term);
tmp_flow_term = 0;

# E_compartment_3 ---------- 
push!(species_flow_vector,0.0);

return (species_flow_vector,q_vector);
end;
