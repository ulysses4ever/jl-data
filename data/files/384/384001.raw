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
# Username: jeffreyvarner
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 02-25-2016 11:20:11
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

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_1 actor:B target:conversion_of_A_to_B_with_E type:activation compartment:compartment_1
push!(transfer_function_vector,(control_parameter_array[1,1]*(B_compartment_1)^control_parameter_array[1,2])/(1+control_parameter_array[1,1]*(B_compartment_1)^control_parameter_array[1,2]));

control_vector[1] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_2 actor:B target:conversion_of_A_to_B_with_E type:activation compartment:compartment_2
push!(transfer_function_vector,(control_parameter_array[2,1]*(B_compartment_2)^control_parameter_array[2,2])/(1+control_parameter_array[2,1]*(B_compartment_2)^control_parameter_array[2,2]));

control_vector[3] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_3 actor:B target:conversion_of_A_to_B_with_E type:activation compartment:compartment_3
push!(transfer_function_vector,(control_parameter_array[3,1]*(B_compartment_3)^control_parameter_array[3,2])/(1+control_parameter_array[3,1]*(B_compartment_3)^control_parameter_array[3,2]));

control_vector[6] = maximum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# Modify the rate_vector with the control variables - 
rate_vector = rate_vector.*control_vector;

# Return the modified rate vector - 
return rate_vector;
end
