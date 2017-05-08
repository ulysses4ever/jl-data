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
# Generation timestamp: 03-09-2016 10:34:11
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
# wound
Z1_wound = x[1];
E1_wound = x[2];
E0_wound = x[3];
D1_wound = x[4];

# compartment_1
Z1_compartment_1 = x[5];
E1_compartment_1 = x[6];
E0_compartment_1 = x[7];
D1_compartment_1 = x[8];
volume_wound = x[9];
volume_compartment_1 = x[10];

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

# 1 wound_to_C1
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# 2 wound_to_C1_reverse
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# Z1_wound ---------- 
tmp_flow_term = -(q_vector[1])*Z1_wound+(q_vector[2]*Z1_compartment_1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E1_wound ---------- 
tmp_flow_term = -(q_vector[1])*E1_wound+(q_vector[2]*E1_compartment_1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# E0_wound ---------- 
tmp_flow_term = -(q_vector[1])*E0_wound+(q_vector[2]*E0_compartment_1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# D1_wound ---------- 
tmp_flow_term = -(q_vector[1])*D1_wound+(q_vector[2]*D1_compartment_1);
push!(species_flow_vector,(1.0/volume_wound)*tmp_flow_term);
tmp_flow_term = 0;

# Z1_compartment_1 ---------- 
tmp_flow_term = -(q_vector[2])*Z1_compartment_1+(q_vector[1]*Z1_wound);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# E1_compartment_1 ---------- 
tmp_flow_term = -(q_vector[2])*E1_compartment_1+(q_vector[1]*E1_wound);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# E0_compartment_1 ---------- 
tmp_flow_term = -(q_vector[2])*E0_compartment_1+(q_vector[1]*E0_wound);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

# D1_compartment_1 ---------- 
tmp_flow_term = -(q_vector[2])*D1_compartment_1+(q_vector[1]*D1_wound);
push!(species_flow_vector,(1.0/volume_compartment_1)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
