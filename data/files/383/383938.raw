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
# Generation timestamp: 03-03-2016 08:31:04
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

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_concentration = characteristic_variable_array[2];
characteristic_time = characteristic_variable_array[4];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# -------------------------------------------------------------------------- # 
# cell
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B: compartment: cell A -(E1)-> B
tmp_reaction = rate_constant_array[1]*(E1_cell)*((A_cell)/(saturation_constant_array[1,1] + A_cell));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_B_to_A: compartment: cell B -(E4)-> A
tmp_reaction = rate_constant_array[2]*(E4_cell)*((B_cell)/(saturation_constant_array[2,2] + B_cell));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_A_to_C: compartment: cell A -(E2)-> C
tmp_reaction = rate_constant_array[3]*(E2_cell)*((A_cell)/(saturation_constant_array[3,1] + A_cell));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_C_to_B: compartment: cell C -(E3)-> B
tmp_reaction = rate_constant_array[4]*(E3_cell)*((C_cell)/(saturation_constant_array[4,5] + C_cell));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# growth: compartment: cell A+B+C -([])-> G
tmp_reaction = rate_constant_array[5]*((A_cell)/(saturation_constant_array[5,1] + A_cell))*((B_cell)/(saturation_constant_array[5,2] + B_cell))*((C_cell)/(saturation_constant_array[5,5] + C_cell));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# production_of_E1: compartment: cell [] -([])-> E1
tmp_reaction = rate_constant_array[6];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# production_of_E2: compartment: cell [] -([])-> E2
tmp_reaction = rate_constant_array[7];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# production_of_E3: compartment: cell [] -([])-> E3
tmp_reaction = rate_constant_array[8];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# production_of_E4: compartment: cell [] -([])-> E4
tmp_reaction = rate_constant_array[9];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# destruction_of_E1: compartment: cell E1 -([])-> []
tmp_reaction = rate_constant_array[10]*(E1_cell);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# destruction_of_E2: compartment: cell E2 -([])-> []
tmp_reaction = rate_constant_array[11]*(E2_cell);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# destruction_of_E3: compartment: cell E3 -([])-> []
tmp_reaction = rate_constant_array[12]*(E3_cell);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# destruction_of_E4: compartment: cell E4 -([])-> []
tmp_reaction = rate_constant_array[13]*(E4_cell);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# outside
# -------------------------------------------------------------------------- # 
# return the kinetics vector -
return rate_vector;
end
