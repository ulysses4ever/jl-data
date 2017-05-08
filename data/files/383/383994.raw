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
# Generation timestamp: 03-23-2016 13:31:28
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

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_concentration = characteristic_variable_array[2];
characteristic_time = characteristic_variable_array[4];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# -------------------------------------------------------------------------- # 
# supply
# -------------------------------------------------------------------------- # 
# conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
tmp_reaction = rate_constant_array[1]*(E0_supply)*((Z1_supply)/(saturation_constant_array[1,1] + Z1_supply));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
tmp_reaction = rate_constant_array[2]*(E1_supply)*((Z1_supply)/(saturation_constant_array[2,1] + Z1_supply));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
tmp_reaction = rate_constant_array[3]*(E1_supply)*((Z2_supply)/(saturation_constant_array[3,4] + Z2_supply));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E1: compartment: * E1 -([])-> D1
tmp_reaction = rate_constant_array[4]*((E1_supply)/(saturation_constant_array[4,2] + E1_supply));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E2: compartment: * E2 -([])-> D2
tmp_reaction = rate_constant_array[5]*((E2_supply)/(saturation_constant_array[5,5] + E2_supply));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# C1
# -------------------------------------------------------------------------- # 
# conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
tmp_reaction = rate_constant_array[6]*(E0_C1)*((Z1_C1)/(saturation_constant_array[6,8] + Z1_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
tmp_reaction = rate_constant_array[7]*(E1_C1)*((Z1_C1)/(saturation_constant_array[7,8] + Z1_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
tmp_reaction = rate_constant_array[8]*(E1_C1)*((Z2_C1)/(saturation_constant_array[8,11] + Z2_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E1: compartment: * E1 -([])-> D1
tmp_reaction = rate_constant_array[9]*((E1_C1)/(saturation_constant_array[9,9] + E1_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E2: compartment: * E2 -([])-> D2
tmp_reaction = rate_constant_array[10]*((E2_C1)/(saturation_constant_array[10,12] + E2_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# wound
# -------------------------------------------------------------------------- # 
# conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
tmp_reaction = rate_constant_array[11]*(E0_wound)*((Z1_wound)/(saturation_constant_array[11,15] + Z1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
tmp_reaction = rate_constant_array[12]*(E1_wound)*((Z1_wound)/(saturation_constant_array[12,15] + Z1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
tmp_reaction = rate_constant_array[13]*(E1_wound)*((Z2_wound)/(saturation_constant_array[13,18] + Z2_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E1: compartment: * E1 -([])-> D1
tmp_reaction = rate_constant_array[14]*((E1_wound)/(saturation_constant_array[14,16] + E1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E2: compartment: * E2 -([])-> D2
tmp_reaction = rate_constant_array[15]*((E2_wound)/(saturation_constant_array[15,19] + E2_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degreation_of_E0: compartment: wound E0 -([])-> []
tmp_reaction = rate_constant_array[16]*(E0_wound);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# C2
# -------------------------------------------------------------------------- # 
# conversion_of_Z1_to_E1_slow: compartment: * Z1 -(E0)-> E1
tmp_reaction = rate_constant_array[17]*(E0_C2)*((Z1_C2)/(saturation_constant_array[17,22] + Z1_C2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z1_to_E1_fast: compartment: * Z1 -(E1)-> E1
tmp_reaction = rate_constant_array[18]*(E1_C2)*((Z1_C2)/(saturation_constant_array[18,22] + Z1_C2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z2_to_E2: compartment: * Z2 -(E1)-> E2
tmp_reaction = rate_constant_array[19]*(E1_C2)*((Z2_C2)/(saturation_constant_array[19,25] + Z2_C2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E1: compartment: * E1 -([])-> D1
tmp_reaction = rate_constant_array[20]*((E1_C2)/(saturation_constant_array[20,23] + E1_C2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E2: compartment: * E2 -([])-> D2
tmp_reaction = rate_constant_array[21]*((E2_C2)/(saturation_constant_array[21,26] + E2_C2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_Z1: compartment: C2 [] -([])-> Z1
tmp_reaction = rate_constant_array[22];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_Z2: compartment: C2 [] -([])-> Z2
tmp_reaction = rate_constant_array[23];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_E1: compartment: C2 [] -([])-> E1
tmp_reaction = rate_constant_array[24];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_E2: compartment: C2 [] -([])-> E2
tmp_reaction = rate_constant_array[25];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
