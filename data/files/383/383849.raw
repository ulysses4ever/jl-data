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
# Generation timestamp: 03-16-2016 08:55:39
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
FII_vein = x[1];
FIIa_vein = x[2];
PC_vein = x[3];
APC_vein = x[4];
ATIII_vein = x[5];
TM_vein = x[6];
TRIGGER_vein = x[7];

# lungs
FII_lungs = x[8];
FIIa_lungs = x[9];
PC_lungs = x[10];
APC_lungs = x[11];
ATIII_lungs = x[12];
TM_lungs = x[13];
TRIGGER_lungs = x[14];

# artery
FII_artery = x[15];
FIIa_artery = x[16];
PC_artery = x[17];
APC_artery = x[18];
ATIII_artery = x[19];
TM_artery = x[20];
TRIGGER_artery = x[21];

# heart
FII_heart = x[22];
FIIa_heart = x[23];
PC_heart = x[24];
APC_heart = x[25];
ATIII_heart = x[26];
TM_heart = x[27];
TRIGGER_heart = x[28];

# kidney
FII_kidney = x[29];
FIIa_kidney = x[30];
PC_kidney = x[31];
APC_kidney = x[32];
ATIII_kidney = x[33];
TM_kidney = x[34];
TRIGGER_kidney = x[35];

# wound
FII_wound = x[36];
FIIa_wound = x[37];
PC_wound = x[38];
APC_wound = x[39];
ATIII_wound = x[40];
TM_wound = x[41];
TRIGGER_wound = x[42];

volume_vein = x[43];
volume_lungs = x[44];
volume_artery = x[45];
volume_heart = x[46];
volume_kidney = x[47];
volume_wound = x[48];

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
# -------------------------------------------------------------------------- # 
# artery
# -------------------------------------------------------------------------- # 
# -------------------------------------------------------------------------- # 
# heart
# -------------------------------------------------------------------------- # 
# -------------------------------------------------------------------------- # 
# kidney
# -------------------------------------------------------------------------- # 
# -------------------------------------------------------------------------- # 
# wound
# -------------------------------------------------------------------------- # 
# reaction1: compartment: wound [] -([])-> FII
tmp_reaction = rate_constant_array[1];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: wound [] -([])-> FIIa
tmp_reaction = rate_constant_array[2];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: wound [] -([])-> PC
tmp_reaction = rate_constant_array[3];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: wound [] -([])-> APC
tmp_reaction = rate_constant_array[4];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: wound [] -([])-> ATIII
tmp_reaction = rate_constant_array[5];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: wound [] -([])-> TM
tmp_reaction = rate_constant_array[6];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: wound [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[7];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
