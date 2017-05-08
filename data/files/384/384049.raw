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
# Generation timestamp: 04-06-2016 09:04:51
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
# activation_initiator: compartment: C1 inactive_initiator -(trigger)-> active_initiator
tmp_reaction = rate_constant_array[1]*(trigger_C1)*((inactive_initiator_C1)/(saturation_constant_array[1,1] + inactive_initiator_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# slow_thrombin_generation: compartment: C1 FII -(active_initiator)-> FIIa
tmp_reaction = rate_constant_array[2]*(active_initiator_C1)*((FII_C1)/(saturation_constant_array[2,4] + FII_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# platelet_activation: compartment: C1 PL -(FIIa)-> PLa
tmp_reaction = rate_constant_array[3]*(FIIa_C1)*((PL_C1)/(saturation_constant_array[3,6] + PL_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# fast_thrombin_generation: compartment: C1 FII -(PLa)-> FIIa
tmp_reaction = rate_constant_array[4]*(PLa_C1)*((FII_C1)/(saturation_constant_array[4,4] + FII_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# activation_of_APC: compartment: C1 PC -(FIIa)-> APC
tmp_reaction = rate_constant_array[5]*(FIIa_C1)*((PC_C1)/(saturation_constant_array[5,8] + PC_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# deactivation_of_FIIa_by_ATIII: compartment: C1 FIIa+ATIII -([])-> []
tmp_reaction = rate_constant_array[6]*(FIIa_C1)*(ATIII_C1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# deactivation_by_TFPI: compartment: C1 TFPI+active_initiator -([])-> []
tmp_reaction = rate_constant_array[7]*(TFPI_C1)*(active_initiator_C1);
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# fibrin_monomer_formation: compartment: C1 Fibrinogen -(FIIa)-> Fibrin_monomer
tmp_reaction = rate_constant_array[8]*(FIIa_C1)*((Fibrinogen_C1)/(saturation_constant_array[8,12] + Fibrinogen_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# protofibril_formation: compartment: C1 Fibrin_monomer -([])-> Protofibril
tmp_reaction = rate_constant_array[9]*((Fibrin_monomer_C1)/(saturation_constant_array[9,13] + Fibrin_monomer_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# protofibril_formation_reverse: compartment: C1 Protofibril -([])-> Fibrin
tmp_reaction = rate_constant_array[10]*((Protofibril_C1)/(saturation_constant_array[10,14] + Protofibril_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# fibrin_degradation_FDPs_Ddimer: compartment: C1 Fibrin -(Plasmin)-> D_dimer
tmp_reaction = rate_constant_array[11]*(Plasmin_C1)*((Fibrin_C1)/(saturation_constant_array[11,15] + Fibrin_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# plasmin_generation_tPA: compartment: C1 Plasminogen -(tPA)-> Plasmin
tmp_reaction = rate_constant_array[12]*(tPA_C1)*((Plasminogen_C1)/(saturation_constant_array[12,18] + Plasminogen_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# plasmin_generation_uPA: compartment: C1 Plasminogen -(uPA)-> Plasmin
tmp_reaction = rate_constant_array[13]*(uPA_C1)*((Plasminogen_C1)/(saturation_constant_array[13,18] + Plasminogen_C1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
