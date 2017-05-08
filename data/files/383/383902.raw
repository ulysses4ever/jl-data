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
# Generation timestamp: 03-11-2016 14:23:53
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
ATP_cell = x[2];
B_cell = x[3];
NADH_cell = x[4];
C_cell = x[5];
F_cell = x[6];
G_cell = x[7];
D_cell = x[8];
E_cell = x[9];
H_cell = x[10];
O2_cell = x[11];
Carbon1_cell = x[12];
Carbon2_cell = x[13];
Fext_cell = x[14];
Dext_cell = x[15];
Ext_cell = x[16];
Hext_cell = x[17];
Oxygen_cell = x[18];
biomass_cell = x[19];
volume_cell = x[20];

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

# 1 cell
tmp_flow_rate = cardiac_output*flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# A_cell ---------- 
tmp_flow_term = -(q_vector[1])*A_cell+(q_vector[1]*A_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# ATP_cell ---------- 
tmp_flow_term = -(q_vector[1])*ATP_cell+(q_vector[1]*ATP_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# B_cell ---------- 
tmp_flow_term = -(q_vector[1])*B_cell+(q_vector[1]*B_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# NADH_cell ---------- 
tmp_flow_term = -(q_vector[1])*NADH_cell+(q_vector[1]*NADH_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# C_cell ---------- 
tmp_flow_term = -(q_vector[1])*C_cell+(q_vector[1]*C_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# F_cell ---------- 
tmp_flow_term = -(q_vector[1])*F_cell+(q_vector[1]*F_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# G_cell ---------- 
tmp_flow_term = -(q_vector[1])*G_cell+(q_vector[1]*G_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# D_cell ---------- 
tmp_flow_term = -(q_vector[1])*D_cell+(q_vector[1]*D_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# E_cell ---------- 
tmp_flow_term = -(q_vector[1])*E_cell+(q_vector[1]*E_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# H_cell ---------- 
tmp_flow_term = -(q_vector[1])*H_cell+(q_vector[1]*H_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# O2_cell ---------- 
tmp_flow_term = -(q_vector[1])*O2_cell+(q_vector[1]*O2_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# Carbon1_cell ---------- 
tmp_flow_term = -(q_vector[1])*Carbon1_cell+(q_vector[1]*Carbon1_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# Carbon2_cell ---------- 
tmp_flow_term = -(q_vector[1])*Carbon2_cell+(q_vector[1]*Carbon2_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# Fext_cell ---------- 
tmp_flow_term = -(q_vector[1])*Fext_cell+(q_vector[1]*Fext_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# Dext_cell ---------- 
tmp_flow_term = -(q_vector[1])*Dext_cell+(q_vector[1]*Dext_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# Ext_cell ---------- 
tmp_flow_term = -(q_vector[1])*Ext_cell+(q_vector[1]*Ext_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# Hext_cell ---------- 
tmp_flow_term = -(q_vector[1])*Hext_cell+(q_vector[1]*Hext_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# Oxygen_cell ---------- 
tmp_flow_term = -(q_vector[1])*Oxygen_cell+(q_vector[1]*Oxygen_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

# biomass_cell ---------- 
tmp_flow_term = -(q_vector[1])*biomass_cell+(q_vector[1]*biomass_cell);
push!(species_flow_vector,(1.0/volume_cell)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
