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
# Generation timestamp: 03-07-2016 15:51:05
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
# C1
MBL_C1 = x[1];
MASP1_2_C1 = x[2];
C1_a_similar_C1 = x[3];
C4_C1 = x[4];
C4a_C1 = x[5];
C4b_C1 = x[6];
C4b2_C1 = x[7];
C2_C1 = x[8];
C1_C1 = x[9];
C1a_C1 = x[10];
Ag_Ab_C1 = x[11];
C3_C1 = x[12];
C3a_C1 = x[13];
C3b_C1 = x[14];
microbes_C1 = x[15];
Bb_C1 = x[16];
factor_B_C1 = x[17];
factor_D_C1 = x[18];
Ba_C1 = x[19];
properdin_C1 = x[20];
C3bBb_C1 = x[21];
C2b_C1 = x[22];
C4b2a_C1 = x[23];
C4b2a3b_C1 = x[24];
C3bBb3b_C1 = x[25];
C5_C1 = x[26];
C4bBb3b_C1 = x[27];
C5a_C1 = x[28];
C5b_C1 = x[29];
MAC_C1 = x[30];
C6_C9_C1 = x[31];

# C2
MBL_C2 = x[32];
MASP1_2_C2 = x[33];
C1_a_similar_C2 = x[34];
C4_C2 = x[35];
C4a_C2 = x[36];
C4b_C2 = x[37];
C4b2_C2 = x[38];
C2_C2 = x[39];
C1_C2 = x[40];
C1a_C2 = x[41];
Ag_Ab_C2 = x[42];
C3_C2 = x[43];
C3a_C2 = x[44];
C3b_C2 = x[45];
microbes_C2 = x[46];
Bb_C2 = x[47];
factor_B_C2 = x[48];
factor_D_C2 = x[49];
Ba_C2 = x[50];
properdin_C2 = x[51];
C3bBb_C2 = x[52];
C2b_C2 = x[53];
C4b2a_C2 = x[54];
C4b2a3b_C2 = x[55];
C3bBb3b_C2 = x[56];
C5_C2 = x[57];
C4bBb3b_C2 = x[58];
C5a_C2 = x[59];
C5b_C2 = x[60];
MAC_C2 = x[61];
C6_C9_C2 = x[62];

volume_C1 = x[63];
volume_C2 = x[64];

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_concentration = characteristic_variable_array[2];
characteristic_time = characteristic_variable_array[4];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# -------------------------------------------------------------------------- # 
# C1
# -------------------------------------------------------------------------- # 
# generation_of_MBL: compartment: C1 [] -(MASP1_2)-> MBL
tmp_reaction = rate_constant_array[1]*(MASP1_2_C1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_C1_a_similar: compartment: C1 [] -(MBL)-> C1_a_similar
tmp_reaction = rate_constant_array[2]*(MBL_C1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# cleavage_of_C4: compartment: C1 C4 -(C1_a_similar)-> 1.0*C4a+1.0*C4b
tmp_reaction = rate_constant_array[3]*(C1_a_similar_C1)*((C4_C1)/(saturation_constant_array[3,4] + C4_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_C4b2: compartment: C1 C4b -(C2)-> C4b2
tmp_reaction = rate_constant_array[4]*(C2_C1)*((C4b_C1)/(saturation_constant_array[4,6] + C4b_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_C1: compartment: C1 [] -([])-> C1
tmp_reaction = rate_constant_array[5];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_C1a: compartment: C1 C1 -(Ag_Ab)-> C1a
tmp_reaction = rate_constant_array[6]*(Ag_Ab_C1)*((C1_C1)/(saturation_constant_array[6,9] + C1_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# cleavage_of_C3_alt: compartment: C1 C3 -(microbes)-> C3a+C3b
tmp_reaction = rate_constant_array[7]*(microbes_C1)*((C3_C1)/(saturation_constant_array[7,12] + C3_C1))*((C3_C1)/(saturation_constant_array[7,12] + C3_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_C3_to_Bb: compartment: C1 C3b -([])-> Bb
tmp_reaction = rate_constant_array[8]*((C3b_C1)/(saturation_constant_array[8,14] + C3b_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_factor_B: compartment: C1 [] -([])-> factor_B
tmp_reaction = rate_constant_array[9];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_factor_D: compartment: C1 [] -([])-> factor_D
tmp_reaction = rate_constant_array[10];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_factor_B: compartment: C1 factor_B -(factor_D)-> Ba+Bb
tmp_reaction = rate_constant_array[11]*(factor_D_C1)*((factor_B_C1)/(saturation_constant_array[11,17] + factor_B_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_properdin: compartment: C1 [] -([])-> properdin
tmp_reaction = rate_constant_array[12];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_C3bBb: compartment: C1 Bb -(properdin)-> C3bBb
tmp_reaction = rate_constant_array[13]*(properdin_C1)*((Bb_C1)/(saturation_constant_array[13,16] + Bb_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_C4b2a: compartment: C1 C4b2 -(C1a)-> 1.0*C2b+1.0*C4b2a
tmp_reaction = rate_constant_array[14]*(C1a_C1)*((C4b2_C1)/(saturation_constant_array[14,7] + C4b2_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# cleavage_of_C3: compartment: C1 C3 -(C4b2a)-> C3a+C3b
tmp_reaction = rate_constant_array[15]*(C4b2a_C1)*((C3_C1)/(saturation_constant_array[15,12] + C3_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# cleavage_of_C3_alt: compartment: C1 C3 -(microbes)-> C3a+C3b
tmp_reaction = rate_constant_array[16]*(microbes_C1)*((C3_C1)/(saturation_constant_array[16,12] + C3_C1))*((C3_C1)/(saturation_constant_array[16,12] + C3_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# C3b_activation_way1: compartment: C1 C3b -([])-> C4b2a3b
tmp_reaction = rate_constant_array[17]*((C3b_C1)/(saturation_constant_array[17,14] + C3b_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# C3b_activation_way2: compartment: C1 C3b -([])-> C3bBb3b
tmp_reaction = rate_constant_array[18]*((C3b_C1)/(saturation_constant_array[18,14] + C3b_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# C5_generation_way1: compartment: C1 [] -(C4b2a3b)-> C5
tmp_reaction = rate_constant_array[19]*(C4b2a3b_C1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# C5_generation_way2: compartment: C1 [] -(C4bBb3b)-> C5
tmp_reaction = rate_constant_array[20]*(C4bBb3b_C1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# C5_cleavage: compartment: C1 C5 -([])-> 1.0*C5a+1.0*C5b
tmp_reaction = rate_constant_array[21]*((C5_C1)/(saturation_constant_array[21,26] + C5_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# C5b_to_MAC: compartment: C1 C5b -(C6_C9)-> MAC
tmp_reaction = rate_constant_array[22]*(C6_C9_C1)*((C5b_C1)/(saturation_constant_array[22,29] + C5b_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# C2
# -------------------------------------------------------------------------- # 
# return the kinetics vector -
return rate_vector;
end
