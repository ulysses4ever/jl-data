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
function Kinetics(t,x,data_dictionary)
# --------------------------------------------------------------------- #
# Kinetics.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-10-2016 15:38:03
# 
# Input arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary - parameter vector 
# 
# Return arguments: 
# rate_vector - rate vector 
# --------------------------------------------------------------------- #
# 
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

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_concentration = characteristic_variable_array[2];
characteristic_time = characteristic_variable_array[4];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# -------------------------------------------------------------------------- # 
# vein
# -------------------------------------------------------------------------- # 
# -------------------------------------------------------------------------- # 
# lungs
# -------------------------------------------------------------------------- # 
# generation_of_Z1: compartment: lungs [] -([])-> Z1
tmp_reaction = rate_constant_array[1];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_Z2: compartment: lungs [] -([])-> Z2
tmp_reaction = rate_constant_array[2];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# artery
# -------------------------------------------------------------------------- # 
# -------------------------------------------------------------------------- # 
# heart
# -------------------------------------------------------------------------- # 
# -------------------------------------------------------------------------- # 
# kidney
# -------------------------------------------------------------------------- # 
# degredation_of_Z1: compartment: kidney Z1 -([])-> []
tmp_reaction = rate_constant_array[3]*(Z1_kidney);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# wound
# -------------------------------------------------------------------------- # 
# conversion_of_Z1_to_E1_fast: compartment: wound Z1 -(E1)-> E1
tmp_reaction = rate_constant_array[4]*(E1_wound)*((Z1_wound)/(saturation_constant_array[4,56] + Z1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E1: compartment: wound E1 -([])-> D1
tmp_reaction = rate_constant_array[5]*((E1_wound)/(saturation_constant_array[5,57] + E1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_E2: compartment: wound Z2 -(E1)-> E2
tmp_reaction = rate_constant_array[6]*(E1_wound)*((Z2_wound)/(saturation_constant_array[6,59] + Z2_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# E2_cataylzed_conversion_of_Z1_to_E1: compartment: wound Z1 -(E2)-> E1
tmp_reaction = rate_constant_array[7]*(E2_wound)*((Z1_wound)/(saturation_constant_array[7,56] + Z1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# E2_degregation: compartment: wound E2 -([])-> D2
tmp_reaction = rate_constant_array[8]*((E2_wound)/(saturation_constant_array[8,60] + E2_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# production_of_E3: compartment: wound E2 -(E4)-> E3
tmp_reaction = rate_constant_array[9]*(E4_wound)*((E2_wound)/(saturation_constant_array[9,60] + E2_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E3: compartment: wound E3 -([])-> D3
tmp_reaction = rate_constant_array[10]*((E3_wound)/(saturation_constant_array[10,62] + E3_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# production_of_E4: compartment: wound Z4 -(E3)-> E4
tmp_reaction = rate_constant_array[11]*(E3_wound)*((Z4_wound)/(saturation_constant_array[11,65] + Z4_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degreation_of_E4: compartment: wound E4 -([])-> D4
tmp_reaction = rate_constant_array[12]*((E4_wound)/(saturation_constant_array[12,63] + E4_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# long_range_production_of_E1: compartment: wound Z1 -(E4)-> E1
tmp_reaction = rate_constant_array[13]*(E4_wound)*((Z1_wound)/(saturation_constant_array[13,56] + Z1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
