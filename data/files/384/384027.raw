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
# Username: jeffreyvarner
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-02-2016 14:35:17
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

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_concentration = characteristic_variable_array[2];
characteristic_time = characteristic_variable_array[4];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# -------------------------------------------------------------------------- # 
# compartment_1
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_slow: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[1]*(E_compartment_1)*((A_compartment_1)/(saturation_constant_array[1,1] + A_compartment_1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_A_to_B: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[2]*(E_compartment_1)*((A_compartment_1)/(saturation_constant_array[2,1] + A_compartment_1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[3];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[4]*(II_compartment_1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# activation_of_I: compartment: * II -(B)-> AI
tmp_reaction = rate_constant_array[5]*(B_compartment_1)*((II_compartment_1)/(saturation_constant_array[5,4] + II_compartment_1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# compartment_2
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_slow: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[6]*(E_compartment_2)*((A_compartment_2)/(saturation_constant_array[6,6] + A_compartment_2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_A_to_B: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[7]*(E_compartment_2)*((A_compartment_2)/(saturation_constant_array[7,6] + A_compartment_2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[8];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[9]*(II_compartment_2);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# activation_of_I: compartment: * II -(B)-> AI
tmp_reaction = rate_constant_array[10]*(B_compartment_2)*((II_compartment_2)/(saturation_constant_array[10,9] + II_compartment_2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# compartment_3
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_slow: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[11]*(E_compartment_3)*((A_compartment_3)/(saturation_constant_array[11,11] + A_compartment_3));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_A_to_B: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[12]*(E_compartment_3)*((A_compartment_3)/(saturation_constant_array[12,11] + A_compartment_3));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[13];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[14]*(II_compartment_3);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# activation_of_I: compartment: * II -(B)-> AI
tmp_reaction = rate_constant_array[15]*(B_compartment_3)*((II_compartment_3)/(saturation_constant_array[15,14] + II_compartment_3));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# compartment_4
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_slow: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[16]*(E_compartment_4)*((A_compartment_4)/(saturation_constant_array[16,16] + A_compartment_4));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_A_to_B: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[17]*(E_compartment_4)*((A_compartment_4)/(saturation_constant_array[17,16] + A_compartment_4));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[18];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[19]*(II_compartment_4);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# clearance_of_A: compartment: compartment_4 A -([])-> []
tmp_reaction = rate_constant_array[20]*(A_compartment_4);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# clearance_of_B: compartment: compartment_4 B -([])-> []
tmp_reaction = rate_constant_array[21]*(B_compartment_4);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# clearance_of_AI: compartment: compartment_4 AI -([])-> []
tmp_reaction = rate_constant_array[22]*(AI_compartment_4);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# activation_of_I: compartment: * II -(B)-> AI
tmp_reaction = rate_constant_array[23]*(B_compartment_4)*((II_compartment_4)/(saturation_constant_array[23,19] + II_compartment_4));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# compartment_5
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_slow: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[24]*(E_compartment_5)*((A_compartment_5)/(saturation_constant_array[24,21] + A_compartment_5));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_A_to_B: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[25]*(E_compartment_5)*((A_compartment_5)/(saturation_constant_array[25,21] + A_compartment_5));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_A: compartment: compartment_5 [] -([])-> A
tmp_reaction = rate_constant_array[26];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[27];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[28]*(II_compartment_5);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# activation_of_I: compartment: * II -(B)-> AI
tmp_reaction = rate_constant_array[29]*(B_compartment_5)*((II_compartment_5)/(saturation_constant_array[29,24] + II_compartment_5));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# wound_compartment
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_slow: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[30]*(E_wound_compartment)*((A_wound_compartment)/(saturation_constant_array[30,26] + A_wound_compartment));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_A_to_B: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[31]*(E_wound_compartment)*((A_wound_compartment)/(saturation_constant_array[31,26] + A_wound_compartment));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[32];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_II: compartment: * [] -([])-> II
tmp_reaction = rate_constant_array[33]*(II_wound_compartment);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_E: compartment: wound_compartment [] -([])-> E
tmp_reaction = rate_constant_array[34];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_E: compartment: wound_compartment [] -([])-> E
tmp_reaction = rate_constant_array[35]*(E_wound_compartment);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# activation_of_I: compartment: * II -(B)-> AI
tmp_reaction = rate_constant_array[36]*(B_wound_compartment)*((II_wound_compartment)/(saturation_constant_array[36,29] + II_wound_compartment));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
