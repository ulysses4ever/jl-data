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
# Generation timestamp: 02-25-2016 11:20:11
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

# compartment_2
A_compartment_2 = x[4];
B_compartment_2 = x[5];
E_compartment_2 = x[6];

# compartment_3
A_compartment_3 = x[7];
B_compartment_3 = x[8];
E_compartment_3 = x[9];
volume_compartment_1 = x[10];
volume_compartment_2 = x[11];
volume_compartment_3 = x[12];

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
# conversion_of_A_to_B_with_E: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[1]*(E_compartment_1)*((A_compartment_1)/(saturation_constant_array[1,1] + A_compartment_1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_B_to_A: compartment: * B -([])-> A
tmp_reaction = rate_constant_array[2]*((B_compartment_1)/(saturation_constant_array[2,2] + B_compartment_1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# compartment_2
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_with_E: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[3]*(E_compartment_2)*((A_compartment_2)/(saturation_constant_array[3,4] + A_compartment_2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_B_to_A: compartment: * B -([])-> A
tmp_reaction = rate_constant_array[4]*((B_compartment_2)/(saturation_constant_array[4,5] + B_compartment_2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_E: compartment: compartment_2 [] -([])-> E
tmp_reaction = rate_constant_array[5];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# compartment_3
# -------------------------------------------------------------------------- # 
# conversion_of_A_to_B_with_E: compartment: * A -(E)-> B
tmp_reaction = rate_constant_array[6]*(E_compartment_3)*((A_compartment_3)/(saturation_constant_array[6,7] + A_compartment_3));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_B_to_A: compartment: * B -([])-> A
tmp_reaction = rate_constant_array[7]*((B_compartment_3)/(saturation_constant_array[7,8] + B_compartment_3));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
