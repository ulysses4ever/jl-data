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
# Generation timestamp: 03-30-2016 10:35:36
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Alias the species vector - 
# vein
FII_vein = x[1];
FIIa_vein = x[2];
PC_vein = x[3];
APC_vein = x[4];
ATIII_vein = x[5];
TM_vein = x[6];
TRIGGER_vein = x[7];

# lungs
FII_lungs = x[8];
FIIa_lungs = x[9];
PC_lungs = x[10];
APC_lungs = x[11];
ATIII_lungs = x[12];
TM_lungs = x[13];
TRIGGER_lungs = x[14];

# artery
FII_artery = x[15];
FIIa_artery = x[16];
PC_artery = x[17];
APC_artery = x[18];
ATIII_artery = x[19];
TM_artery = x[20];
TRIGGER_artery = x[21];

# heart
FII_heart = x[22];
FIIa_heart = x[23];
PC_heart = x[24];
APC_heart = x[25];
ATIII_heart = x[26];
TM_heart = x[27];
TRIGGER_heart = x[28];

# kidney
FII_kidney = x[29];
FIIa_kidney = x[30];
PC_kidney = x[31];
APC_kidney = x[32];
ATIII_kidney = x[33];
TM_kidney = x[34];
TRIGGER_kidney = x[35];

# wound
FII_wound = x[36];
FIIa_wound = x[37];
PC_wound = x[38];
APC_wound = x[39];
ATIII_wound = x[40];
TM_wound = x[41];
TRIGGER_wound = x[42];
volume_vein = x[43];
volume_lungs = x[44];
volume_artery = x[45];
volume_heart = x[46];
volume_kidney = x[47];
volume_wound = x[48];

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(FII_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(FIIa_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(PC_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(APC_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(ATIII_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(TM_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(TRIGGER_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(FII_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(FIIa_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(PC_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(APC_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(ATIII_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(TM_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(TRIGGER_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(FII_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(FIIa_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(PC_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(APC_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(ATIII_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(TM_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(TRIGGER_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(FII_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(FIIa_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(PC_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(APC_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(ATIII_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(TM_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(TRIGGER_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(FII_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(FIIa_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(PC_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(APC_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(ATIII_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(TM_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(TRIGGER_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(FII_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(FIIa_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(PC_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(APC_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(ATIII_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(TM_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(TRIGGER_wound/volume_wound)*dvdt_vector[6]);
return (species_dilution_array);
end;
