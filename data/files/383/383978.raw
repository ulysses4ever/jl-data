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
function Control(t,x,rate_vector,data_dictionary)
# ---------------------------------------------------------------------- #
# Control.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-23-2016 17:37:36
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# rate_vector - vector of reaction rates 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Set a default value for the allosteric control variables - 
EPSILON = 1.0e-3;
number_of_reactions = length(rate_vector);
control_vector = ones(number_of_reactions);
control_parameter_array = data_dictionary["CONTROL_PARAMETER_ARRAY"];

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

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E1_by_E1_supply actor:E1 target:conversion_of_Z1_to_E1_fast type:activation compartment:supply
push!(transfer_function_vector,(control_parameter_array[1,1]*(E1_supply)^control_parameter_array[1,2])/(1+control_parameter_array[1,1]*(E1_supply)^control_parameter_array[1,2]));

control_vector[2] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E2_by_E1_supply actor:E2 target:conversion_of_Z2_to_E2 type:activation compartment:supply
push!(transfer_function_vector,(control_parameter_array[2,1]*(E2_supply)^control_parameter_array[2,2])/(1+control_parameter_array[2,1]*(E2_supply)^control_parameter_array[2,2]));

control_vector[3] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E1_by_E1_C1 actor:E1 target:conversion_of_Z1_to_E1_fast type:activation compartment:C1
push!(transfer_function_vector,(control_parameter_array[3,1]*(E1_C1)^control_parameter_array[3,2])/(1+control_parameter_array[3,1]*(E1_C1)^control_parameter_array[3,2]));

control_vector[7] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E2_by_E1_C1 actor:E2 target:conversion_of_Z2_to_E2 type:activation compartment:C1
push!(transfer_function_vector,(control_parameter_array[4,1]*(E2_C1)^control_parameter_array[4,2])/(1+control_parameter_array[4,1]*(E2_C1)^control_parameter_array[4,2]));

control_vector[8] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E1_by_E1_wound actor:E1 target:conversion_of_Z1_to_E1_fast type:activation compartment:wound
push!(transfer_function_vector,(control_parameter_array[5,1]*(E1_wound)^control_parameter_array[5,2])/(1+control_parameter_array[5,1]*(E1_wound)^control_parameter_array[5,2]));

control_vector[12] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E2_by_E1_wound actor:E2 target:conversion_of_Z2_to_E2 type:activation compartment:wound
push!(transfer_function_vector,(control_parameter_array[6,1]*(E2_wound)^control_parameter_array[6,2])/(1+control_parameter_array[6,1]*(E2_wound)^control_parameter_array[6,2]));

control_vector[13] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E1_by_E1_C2 actor:E1 target:conversion_of_Z1_to_E1_fast type:activation compartment:C2
push!(transfer_function_vector,(control_parameter_array[7,1]*(E1_C2)^control_parameter_array[7,2])/(1+control_parameter_array[7,1]*(E1_C2)^control_parameter_array[7,2]));

control_vector[18] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_E2_by_E1_C2 actor:E2 target:conversion_of_Z2_to_E2 type:activation compartment:C2
push!(transfer_function_vector,(control_parameter_array[8,1]*(E2_C2)^control_parameter_array[8,2])/(1+control_parameter_array[8,1]*(E2_C2)^control_parameter_array[8,2]));

control_vector[19] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# Modify the rate_vector with the control variables - 
rate_vector = rate_vector.*control_vector;

# Return the modified rate vector - 
return rate_vector;
end
