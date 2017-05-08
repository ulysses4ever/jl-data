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
# Generation timestamp: 07-12-2016 13:08:55
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

# heart
FII_heart = x[8];
FIIa_heart = x[9];
PC_heart = x[10];
APC_heart = x[11];
ATIII_heart = x[12];
TM_heart = x[13];
TRIGGER_heart = x[14];

# lungs
FII_lungs = x[15];
FIIa_lungs = x[16];
PC_lungs = x[17];
APC_lungs = x[18];
ATIII_lungs = x[19];
TM_lungs = x[20];
TRIGGER_lungs = x[21];

# artery
FII_artery = x[22];
FIIa_artery = x[23];
PC_artery = x[24];
APC_artery = x[25];
ATIII_artery = x[26];
TM_artery = x[27];
TRIGGER_artery = x[28];

# kidney
FII_kidney = x[29];
FIIa_kidney = x[30];
PC_kidney = x[31];
APC_kidney = x[32];
ATIII_kidney = x[33];
TM_kidney = x[34];
TRIGGER_kidney = x[35];

# liver
FII_liver = x[36];
FIIa_liver = x[37];
PC_liver = x[38];
APC_liver = x[39];
ATIII_liver = x[40];
TM_liver = x[41];
TRIGGER_liver = x[42];

# bulk
FII_bulk = x[43];
FIIa_bulk = x[44];
PC_bulk = x[45];
APC_bulk = x[46];
ATIII_bulk = x[47];
TM_bulk = x[48];
TRIGGER_bulk = x[49];

# wound
FII_wound = x[50];
FIIa_wound = x[51];
PC_wound = x[52];
APC_wound = x[53];
ATIII_wound = x[54];
TM_wound = x[55];
TRIGGER_wound = x[56];

volume_vein = x[57];
volume_heart = x[58];
volume_lungs = x[59];
volume_artery = x[60];
volume_kidney = x[61];
volume_liver = x[62];
volume_bulk = x[63];
volume_wound = x[64];

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
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[1];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[2];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[3];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[4];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[5];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[6];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[7];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# heart
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[8];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[9];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[10];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[11];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[12];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[13];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[14];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# lungs
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[15];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[16];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[17];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[18];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[19];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[20];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[21];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# artery
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[22];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[23];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[24];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[25];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[26];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[27];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[28];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# kidney
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[29];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[30];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[31];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[32];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[33];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[34];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[35];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# liver
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[36];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[37];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[38];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[39];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[40];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[41];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[42];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# bulk
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[43];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[44];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[45];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[46];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[47];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[48];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[49];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# wound
# -------------------------------------------------------------------------- # 
# reaction1: compartment: * [] -([])-> FII
tmp_reaction = rate_constant_array[50];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction2: compartment: * [] -([])-> FIIa
tmp_reaction = rate_constant_array[51];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction3: compartment: * [] -([])-> PC
tmp_reaction = rate_constant_array[52];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction4: compartment: * [] -([])-> APC
tmp_reaction = rate_constant_array[53];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction5: compartment: * [] -([])-> ATIII
tmp_reaction = rate_constant_array[54];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction6: compartment: * [] -([])-> TM
tmp_reaction = rate_constant_array[55];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# reaction7: compartment: * [] -([])-> TRIGGER
tmp_reaction = rate_constant_array[56];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
