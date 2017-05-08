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
# Generation timestamp: 03-09-2016 10:34:11
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

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_concentration = characteristic_variable_array[2];
characteristic_time = characteristic_variable_array[4];

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# -------------------------------------------------------------------------- # 
# wound
# -------------------------------------------------------------------------- # 
# conversion_of_Z1_to_E1_slow: compartment: wound Z1 -(E0)-> E1
tmp_reaction = rate_constant_array[1]*(E0_wound)*((Z1_wound)/(saturation_constant_array[1,1] + Z1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# conversion_of_Z1_to_E1_fast: compartment: wound Z1 -(E1)-> E1
tmp_reaction = rate_constant_array[2]*(E1_wound)*((Z1_wound)/(saturation_constant_array[2,1] + Z1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# generation_of_E0: compartment: wound [] -([])-> E0
tmp_reaction = rate_constant_array[3];
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degredation_of_E1: compartment: wound E1 -([])-> D1
tmp_reaction = rate_constant_array[4]*((E1_wound)/(saturation_constant_array[4,2] + E1_wound));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# degreation_of_E0: compartment: wound E0 -([])-> []
tmp_reaction = rate_constant_array[5]*(E0_wound);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# -------------------------------------------------------------------------- # 
# compartment_1
# -------------------------------------------------------------------------- # 
# return the kinetics vector -
return rate_vector;
end
