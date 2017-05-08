include("HeartRate.jl");
include("CardiacDistribution.jl");
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
function Flow(t,x,data_dictionary)
# ---------------------------------------------------------------------- #
# Flow.jl was generated using the Kwatee code generation system.
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

# Characteristic variables - 
characteristic_variable_array = data_dictionary["CHARACTERISTIC_VARIABLE_ARRAY"];
characteristic_flow_rate = characteristic_variable_array[3];

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

# Alias the species input vector - 
input_concentration_array = data_dictionary["INPUT_CONCENTRATION_ARRAY"]
inactive_initiator_input_C1 = input_concentration_array[1];
active_initiator_input_C1 = input_concentration_array[2];
trigger_input_C1 = input_concentration_array[3];
FII_input_C1 = input_concentration_array[4];
FIIa_input_C1 = input_concentration_array[5];
PL_input_C1 = input_concentration_array[6];
PLa_input_C1 = input_concentration_array[7];
PC_input_C1 = input_concentration_array[8];
APC_input_C1 = input_concentration_array[9];
ATIII_input_C1 = input_concentration_array[10];
TFPI_input_C1 = input_concentration_array[11];
Fibrinogen_input_C1 = input_concentration_array[12];
Fibrin_monomer_input_C1 = input_concentration_array[13];
Protofibril_input_C1 = input_concentration_array[14];
Fibrin_input_C1 = input_concentration_array[15];
D_dimer_input_C1 = input_concentration_array[16];
Plasmin_input_C1 = input_concentration_array[17];
Plasminogen_input_C1 = input_concentration_array[18];
tPA_input_C1 = input_concentration_array[19];
uPA_input_C1 = input_concentration_array[20];
antiplasmin_input_C1 = input_concentration_array[21];
TAFI_input_C1 = input_concentration_array[22];
PAI_1_input_C1 = input_concentration_array[23];
fXIII_input_C1 = input_concentration_array[24];

# Get data we need from the data_dictionary - 
default_bpm = data_dictionary["DEFAULT_BEATS_PER_MINUTE"];
default_stroke_volume = data_dictionary["DEFAULT_STROKE_VOLUME"];
default_flow_parameter_array = data_dictionary["FLOW_PARAMETER_ARRAY"];

# Update the heart rate, and stroke volume - 
(bpm,stroke_volume) = HeartRate(t,x,default_bpm,default_stroke_volume,data_dictionary);

# Update the fraction of cardiac output going to each organ - 
(flow_parameter_array) = CardiacDistribution(t,x,default_flow_parameter_array,data_dictionary);

# Calculate the q_vector - 
q_vector = Float64[];
cardiac_output = (1.0/characteristic_flow_rate)*bpm*stroke_volume;

# 1 C1IN
tmp_flow_rate = flow_parameter_array[1];
push!(q_vector,tmp_flow_rate);

# 2 C1OUT
tmp_flow_rate = cardiac_output*flow_parameter_array[2];
push!(q_vector,tmp_flow_rate);

# Calculate the species_flow_terms - 
species_flow_vector = Float64[];

# inactive_initiator_C1 ---------- 
tmp_flow_term = -(q_vector[2])*inactive_initiator_C1+(q_vector[1]*inactive_initiator_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# active_initiator_C1 ---------- 
tmp_flow_term = -(q_vector[2])*active_initiator_C1+(q_vector[1]*active_initiator_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# trigger_C1 ---------- 
push!(species_flow_vector,0.0);

# FII_C1 ---------- 
tmp_flow_term = -(q_vector[2])*FII_C1+(q_vector[1]*FII_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# FIIa_C1 ---------- 
tmp_flow_term = -(q_vector[2])*FIIa_C1+(q_vector[1]*FIIa_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# PL_C1 ---------- 
tmp_flow_term = -(q_vector[2])*PL_C1+(q_vector[1]*PL_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# PLa_C1 ---------- 
tmp_flow_term = -(q_vector[2])*PLa_C1+(q_vector[1]*PLa_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# PC_C1 ---------- 
push!(species_flow_vector,0.0);

# APC_C1 ---------- 
tmp_flow_term = -(q_vector[2])*APC_C1+(q_vector[1]*APC_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# ATIII_C1 ---------- 
tmp_flow_term = -(q_vector[2])*ATIII_C1+(q_vector[1]*ATIII_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# TFPI_C1 ---------- 
tmp_flow_term = -(q_vector[2])*TFPI_C1+(q_vector[1]*TFPI_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrinogen_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Fibrinogen_C1+(q_vector[1]*Fibrinogen_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_monomer_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Fibrin_monomer_C1+(q_vector[1]*Fibrin_monomer_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# Protofibril_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Protofibril_C1+(q_vector[1]*Protofibril_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# Fibrin_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Fibrin_C1+(q_vector[1]*Fibrin_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# D_dimer_C1 ---------- 
tmp_flow_term = -(q_vector[2])*D_dimer_C1+(q_vector[1]*D_dimer_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# Plasmin_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Plasmin_C1+(q_vector[1]*Plasmin_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# Plasminogen_C1 ---------- 
tmp_flow_term = -(q_vector[2])*Plasminogen_C1+(q_vector[1]*Plasminogen_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# tPA_C1 ---------- 
tmp_flow_term = -(q_vector[2])*tPA_C1+(q_vector[1]*tPA_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# uPA_C1 ---------- 
tmp_flow_term = -(q_vector[2])*uPA_C1+(q_vector[1]*uPA_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# antiplasmin_C1 ---------- 
tmp_flow_term = -(q_vector[2])*antiplasmin_C1+(q_vector[1]*antiplasmin_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# TAFI_C1 ---------- 
tmp_flow_term = -(q_vector[2])*TAFI_C1+(q_vector[1]*TAFI_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# PAI_1_C1 ---------- 
tmp_flow_term = -(q_vector[2])*PAI_1_C1+(q_vector[1]*PAI_1_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

# fXIII_C1 ---------- 
tmp_flow_term = -(q_vector[2])*fXIII_C1+(q_vector[1]*fXIII_input_C1);
push!(species_flow_vector,(1.0/volume_C1)*tmp_flow_term);
tmp_flow_term = 0;

return (species_flow_vector,q_vector);
end;
