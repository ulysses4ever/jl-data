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
# Generation timestamp: 03-02-2016 14:37:14
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
# cell
A_cell = x[1];
B_cell = x[2];
E1_cell = x[3];
E4_cell = x[4];
C_cell = x[5];
E2_cell = x[6];
E3_cell = x[7];
G_cell = x[8];

# outside
A_outside = x[9];
B_outside = x[10];
E1_outside = x[11];
E4_outside = x[12];
C_outside = x[13];
E2_outside = x[14];
E3_outside = x[15];
G_outside = x[16];
volume_cell = x[17];
volume_outside = x[18];

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

# 1 cell_to_outside
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# 2 cell_to_outside_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# A_cell ---------- 
tmp_flow_term = -(q_vector[1])*A_cell+(q_vector[2]*A_outside);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# B_cell ---------- 
tmp_flow_term = -(q_vector[1])*B_cell+(q_vector[2]*B_outside);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# E1_cell ---------- 
push!(species_flow_vector,0.0);

# E4_cell ---------- 
push!(species_flow_vector,0.0);

# C_cell ---------- 
tmp_flow_term = -(q_vector[1])*C_cell+(q_vector[2]*C_outside);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# E2_cell ---------- 
push!(species_flow_vector,0.0);

# E3_cell ---------- 
push!(species_flow_vector,0.0);

# G_cell ---------- 
push!(species_flow_vector,0.0);

# A_outside ---------- 
tmp_flow_term = -(q_vector[2])*A_outside+(q_vector[1]*A_cell);
push!(species_flow_vector,(1.0/volume_outside)*tmp_flow_term);
tmp_flow_term = 0;

# B_outside ---------- 
tmp_flow_term = -(q_vector[2])*B_outside+(q_vector[1]*B_cell);
push!(species_flow_vector,(1.0/volume_outside)*tmp_flow_term);
tmp_flow_term = 0;

# E1_outside ---------- 
push!(species_flow_vector,0.0);

# E4_outside ---------- 
push!(species_flow_vector,0.0);

# C_outside ---------- 
tmp_flow_term = -(q_vector[2])*C_outside+(q_vector[1]*C_cell);
push!(species_flow_vector,(1.0/volume_outside)*tmp_flow_term);
tmp_flow_term = 0;

# E2_outside ---------- 
push!(species_flow_vector,0.0);

# E3_outside ---------- 
push!(species_flow_vector,0.0);

# G_outside ---------- 
push!(species_flow_vector,0.0);

return (species_flow_vector,q_vector);
end;
