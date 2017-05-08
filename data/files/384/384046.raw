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
function Dilution(t,x,dvdt_vector,data_dictionary)
# ---------------------------------------------------------------------- #
# Dilution.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 04-06-2016 09:04:51
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

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

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(inactive_initiator_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(active_initiator_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(trigger_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(FII_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(FIIa_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(PL_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(PLa_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(PC_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(APC_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(ATIII_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(TFPI_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(Fibrinogen_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(Fibrin_monomer_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(Protofibril_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(Fibrin_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(D_dimer_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(Plasmin_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(Plasminogen_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(tPA_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(uPA_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(antiplasmin_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(TAFI_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(PAI_1_C1/volume_C1)*dvdt_vector[1]);
push!(species_dilution_array,(fXIII_C1/volume_C1)*dvdt_vector[1]);
return (species_dilution_array);
end;
