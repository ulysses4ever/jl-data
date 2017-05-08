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
# Generation timestamp: 04-06-2016 09:04:51
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
# C1
inactive_initiator_C1 = x[1];
active_initiator_C1 = x[2];
trigger_C1 = x[3];
FII_C1 = x[4];
FIIa_C1 = x[5];
PL_C1 = x[6];
PLa_C1 = x[7];
PC_C1 = x[8];
APC_C1 = x[9];
ATIII_C1 = x[10];
TFPI_C1 = x[11];
Fibrinogen_C1 = x[12];
Fibrin_monomer_C1 = x[13];
Protofibril_C1 = x[14];
Fibrin_C1 = x[15];
D_dimer_C1 = x[16];
Plasmin_C1 = x[17];
Plasminogen_C1 = x[18];
tPA_C1 = x[19];
uPA_C1 = x[20];
antiplasmin_C1 = x[21];
TAFI_C1 = x[22];
PAI_1_C1 = x[23];
fXIII_C1 = x[24];
volume_C1 = x[25];

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: deactive_by_APC_C1 actor:APC target:fast_thrombin_generation type:inhibition compartment:C1
if (APC_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[1,1]*(APC_C1)^control_parameter_array[1,2])/(1+control_parameter_array[1,1]*(APC_C1)^control_parameter_array[1,2]));
end

control_vector[4] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: plasmin_inhibition_C1 actor:antiplasmin target:plasmin_generation_tPA type:inhibition compartment:C1
if (antiplasmin_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[2,1]*(antiplasmin_C1)^control_parameter_array[2,2])/(1+control_parameter_array[2,1]*(antiplasmin_C1)^control_parameter_array[2,2]));
end

# name: plasminogen_activation_inhibition_C1 actor:TAFI target:plasmin_generation_tPA type:inhibition compartment:C1
if (TAFI_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[3,1]*(TAFI_C1)^control_parameter_array[3,2])/(1+control_parameter_array[3,1]*(TAFI_C1)^control_parameter_array[3,2]));
end

# name: tPA-inhibition_C1 actor:PAI_1 target:plasmin_generation_tPA type:inhibition compartment:C1
if (PAI_1_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[4,1]*(PAI_1_C1)^control_parameter_array[4,2])/(1+control_parameter_array[4,1]*(PAI_1_C1)^control_parameter_array[4,2]));
end

# name: activation_plasmin_tPA_APC_C1 actor:APC target:plasmin_generation_tPA type:activation compartment:C1
push!(transfer_function_vector,(control_parameter_array[5,1]*(APC_C1)^control_parameter_array[5,2])/(1+control_parameter_array[5,1]*(APC_C1)^control_parameter_array[5,2]));

control_vector[12] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: plasmin_inhibition_C1 actor:antiplasmin target:plasmin_generation_uPA type:inhibition compartment:C1
if (antiplasmin_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[6,1]*(antiplasmin_C1)^control_parameter_array[6,2])/(1+control_parameter_array[6,1]*(antiplasmin_C1)^control_parameter_array[6,2]));
end

# name: plasminogen_activation_inhibition_C1 actor:TAFI target:plasmin_generation_uPA type:inhibition compartment:C1
if (TAFI_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[7,1]*(TAFI_C1)^control_parameter_array[7,2])/(1+control_parameter_array[7,1]*(TAFI_C1)^control_parameter_array[7,2]));
end

# name: uPA-inhibition_C1 actor:PAI_1 target:plasmin_generation_uPA type:inhibition compartment:C1
if (PAI_1_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[8,1]*(PAI_1_C1)^control_parameter_array[8,2])/(1+control_parameter_array[8,1]*(PAI_1_C1)^control_parameter_array[8,2]));
end

# name: activation_plasmin_uPA_APC_C1 actor:APC target:plasmin_generation_uPA type:activation compartment:C1
push!(transfer_function_vector,(control_parameter_array[9,1]*(APC_C1)^control_parameter_array[9,2])/(1+control_parameter_array[9,1]*(APC_C1)^control_parameter_array[9,2]));

control_vector[13] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# ----------------------------------------------------------------------------------- #
transfer_function_vector = Float64[];

# name: fibrinolysis_inhibition_by_fXIII_C1 actor:fXIII target:fibrin_degradation_FDPs_Ddimer type:inhibition compartment:C1
if (fXIII_C1<EPSILON);
	push!(transfer_function_vector,1.0);
else
	push!(transfer_function_vector,1.0 - (control_parameter_array[10,1]*(fXIII_C1)^control_parameter_array[10,2])/(1+control_parameter_array[10,1]*(fXIII_C1)^control_parameter_array[10,2]));
end

control_vector[11] = minimum(transfer_function_vector);
transfer_function_vector = 0;
# ----------------------------------------------------------------------------------- #

# Modify the rate_vector with the control variables - 
rate_vector = rate_vector.*control_vector;

# Return the modified rate vector - 
return rate_vector;
end
