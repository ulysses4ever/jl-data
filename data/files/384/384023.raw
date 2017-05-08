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
# Generation timestamp: 03-02-2016 14:35:17
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

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_1 actor:B target:conversion_of_A_to_B type:activation compartment:compartment_1
push!(transfer_function_vector,(control_parameter_array[1,1]*(B_compartment_1)^control_parameter_array[1,2])/(1+control_parameter_array[1,1]*(B_compartment_1)^control_parameter_array[1,2]));

# name: deactivation_of_B_Gen_AI_compartment_1 actor:AI target:conversion_of_A_to_B type:inhibition compartment:compartment_1
if (AI_compartment_1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[2,1]*(AI_compartment_1)^control_parameter_array[2,2])/(1+control_parameter_array[2,1]*(AI_compartment_1)^control_parameter_array[2,2]));
end

control_vector[2] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: deactivation_of_B_Gen_AI_slow_compartment_1 actor:AI target:conversion_of_A_to_B_slow type:inhibition compartment:compartment_1
if (AI_compartment_1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[3,1]*(AI_compartment_1)^control_parameter_array[3,2])/(1+control_parameter_array[3,1]*(AI_compartment_1)^control_parameter_array[3,2]));
end

control_vector[1] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_2 actor:B target:conversion_of_A_to_B type:activation compartment:compartment_2
push!(transfer_function_vector,(control_parameter_array[4,1]*(B_compartment_2)^control_parameter_array[4,2])/(1+control_parameter_array[4,1]*(B_compartment_2)^control_parameter_array[4,2]));

# name: deactivation_of_B_Gen_AI_compartment_2 actor:AI target:conversion_of_A_to_B type:inhibition compartment:compartment_2
if (AI_compartment_2<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[5,1]*(AI_compartment_2)^control_parameter_array[5,2])/(1+control_parameter_array[5,1]*(AI_compartment_2)^control_parameter_array[5,2]));
end

control_vector[7] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: deactivation_of_B_Gen_AI_slow_compartment_2 actor:AI target:conversion_of_A_to_B_slow type:inhibition compartment:compartment_2
if (AI_compartment_2<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[6,1]*(AI_compartment_2)^control_parameter_array[6,2])/(1+control_parameter_array[6,1]*(AI_compartment_2)^control_parameter_array[6,2]));
end

control_vector[6] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_3 actor:B target:conversion_of_A_to_B type:activation compartment:compartment_3
push!(transfer_function_vector,(control_parameter_array[7,1]*(B_compartment_3)^control_parameter_array[7,2])/(1+control_parameter_array[7,1]*(B_compartment_3)^control_parameter_array[7,2]));

# name: deactivation_of_B_Gen_AI_compartment_3 actor:AI target:conversion_of_A_to_B type:inhibition compartment:compartment_3
if (AI_compartment_3<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[8,1]*(AI_compartment_3)^control_parameter_array[8,2])/(1+control_parameter_array[8,1]*(AI_compartment_3)^control_parameter_array[8,2]));
end

control_vector[12] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: deactivation_of_B_Gen_AI_slow_compartment_3 actor:AI target:conversion_of_A_to_B_slow type:inhibition compartment:compartment_3
if (AI_compartment_3<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[9,1]*(AI_compartment_3)^control_parameter_array[9,2])/(1+control_parameter_array[9,1]*(AI_compartment_3)^control_parameter_array[9,2]));
end

control_vector[11] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_4 actor:B target:conversion_of_A_to_B type:activation compartment:compartment_4
push!(transfer_function_vector,(control_parameter_array[10,1]*(B_compartment_4)^control_parameter_array[10,2])/(1+control_parameter_array[10,1]*(B_compartment_4)^control_parameter_array[10,2]));

# name: deactivation_of_B_Gen_AI_compartment_4 actor:AI target:conversion_of_A_to_B type:inhibition compartment:compartment_4
if (AI_compartment_4<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[11,1]*(AI_compartment_4)^control_parameter_array[11,2])/(1+control_parameter_array[11,1]*(AI_compartment_4)^control_parameter_array[11,2]));
end

control_vector[17] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: deactivation_of_B_Gen_AI_slow_compartment_4 actor:AI target:conversion_of_A_to_B_slow type:inhibition compartment:compartment_4
if (AI_compartment_4<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[12,1]*(AI_compartment_4)^control_parameter_array[12,2])/(1+control_parameter_array[12,1]*(AI_compartment_4)^control_parameter_array[12,2]));
end

control_vector[16] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_compartment_5 actor:B target:conversion_of_A_to_B type:activation compartment:compartment_5
push!(transfer_function_vector,(control_parameter_array[13,1]*(B_compartment_5)^control_parameter_array[13,2])/(1+control_parameter_array[13,1]*(B_compartment_5)^control_parameter_array[13,2]));

# name: deactivation_of_B_Gen_AI_compartment_5 actor:AI target:conversion_of_A_to_B type:inhibition compartment:compartment_5
if (AI_compartment_5<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[14,1]*(AI_compartment_5)^control_parameter_array[14,2])/(1+control_parameter_array[14,1]*(AI_compartment_5)^control_parameter_array[14,2]));
end

control_vector[25] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: deactivation_of_B_Gen_AI_slow_compartment_5 actor:AI target:conversion_of_A_to_B_slow type:inhibition compartment:compartment_5
if (AI_compartment_5<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[15,1]*(AI_compartment_5)^control_parameter_array[15,2])/(1+control_parameter_array[15,1]*(AI_compartment_5)^control_parameter_array[15,2]));
end

control_vector[24] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: activation_of_B_by_B_B_wound_compartment actor:B target:conversion_of_A_to_B type:activation compartment:wound_compartment
push!(transfer_function_vector,(control_parameter_array[16,1]*(B_wound_compartment)^control_parameter_array[16,2])/(1+control_parameter_array[16,1]*(B_wound_compartment)^control_parameter_array[16,2]));

# name: deactivation_of_B_Gen_AI_wound_compartment actor:AI target:conversion_of_A_to_B type:inhibition compartment:wound_compartment
if (AI_wound_compartment<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[17,1]*(AI_wound_compartment)^control_parameter_array[17,2])/(1+control_parameter_array[17,1]*(AI_wound_compartment)^control_parameter_array[17,2]));
end

control_vector[31] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: deactivation_of_B_Gen_AI_slow_wound_compartment actor:AI target:conversion_of_A_to_B_slow type:inhibition compartment:wound_compartment
if (AI_wound_compartment<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[18,1]*(AI_wound_compartment)^control_parameter_array[18,2])/(1+control_parameter_array[18,1]*(AI_wound_compartment)^control_parameter_array[18,2]));
end

control_vector[30] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# Modify the rate_vector with the control variables - 
rate_vector = rate_vector.*control_vector;

# Return the modified rate vector - 
return rate_vector;
end
