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
# Generation timestamp: 05-25-2016 18:04:41
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

# heart
FII_heart = x[8];
FIIa_heart = x[9];
PC_heart = x[10];
APC_heart = x[11];
ATIII_heart = x[12];
TM_heart = x[13];
TRIGGER_heart = x[14];

# lungs
FII_lungs = x[15];
FIIa_lungs = x[16];
PC_lungs = x[17];
APC_lungs = x[18];
ATIII_lungs = x[19];
TM_lungs = x[20];
TRIGGER_lungs = x[21];

# artery
FII_artery = x[22];
FIIa_artery = x[23];
PC_artery = x[24];
APC_artery = x[25];
ATIII_artery = x[26];
TM_artery = x[27];
TRIGGER_artery = x[28];

# kidney
FII_kidney = x[29];
FIIa_kidney = x[30];
PC_kidney = x[31];
APC_kidney = x[32];
ATIII_kidney = x[33];
TM_kidney = x[34];
TRIGGER_kidney = x[35];

# liver
FII_liver = x[36];
FIIa_liver = x[37];
PC_liver = x[38];
APC_liver = x[39];
ATIII_liver = x[40];
TM_liver = x[41];
TRIGGER_liver = x[42];

# bulk
FII_bulk = x[43];
FIIa_bulk = x[44];
PC_bulk = x[45];
APC_bulk = x[46];
ATIII_bulk = x[47];
TM_bulk = x[48];
TRIGGER_bulk = x[49];

# wound
FII_wound = x[50];
FIIa_wound = x[51];
PC_wound = x[52];
APC_wound = x[53];
ATIII_wound = x[54];
TM_wound = x[55];
TRIGGER_wound = x[56];
volume_vein = x[57];
volume_heart = x[58];
volume_lungs = x[59];
volume_artery = x[60];
volume_kidney = x[61];
volume_liver = x[62];
volume_bulk = x[63];
volume_wound = x[64];

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(FII_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(FIIa_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(PC_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(APC_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(ATIII_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(TM_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(TRIGGER_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(FII_heart/volume_heart)*dvdt_vector[2]);
push!(species_dilution_array,(FIIa_heart/volume_heart)*dvdt_vector[2]);
push!(species_dilution_array,(PC_heart/volume_heart)*dvdt_vector[2]);
push!(species_dilution_array,(APC_heart/volume_heart)*dvdt_vector[2]);
push!(species_dilution_array,(ATIII_heart/volume_heart)*dvdt_vector[2]);
push!(species_dilution_array,(TM_heart/volume_heart)*dvdt_vector[2]);
push!(species_dilution_array,(TRIGGER_heart/volume_heart)*dvdt_vector[2]);
push!(species_dilution_array,(FII_lungs/volume_lungs)*dvdt_vector[3]);
push!(species_dilution_array,(FIIa_lungs/volume_lungs)*dvdt_vector[3]);
push!(species_dilution_array,(PC_lungs/volume_lungs)*dvdt_vector[3]);
push!(species_dilution_array,(APC_lungs/volume_lungs)*dvdt_vector[3]);
push!(species_dilution_array,(ATIII_lungs/volume_lungs)*dvdt_vector[3]);
push!(species_dilution_array,(TM_lungs/volume_lungs)*dvdt_vector[3]);
push!(species_dilution_array,(TRIGGER_lungs/volume_lungs)*dvdt_vector[3]);
push!(species_dilution_array,(FII_artery/volume_artery)*dvdt_vector[4]);
push!(species_dilution_array,(FIIa_artery/volume_artery)*dvdt_vector[4]);
push!(species_dilution_array,(PC_artery/volume_artery)*dvdt_vector[4]);
push!(species_dilution_array,(APC_artery/volume_artery)*dvdt_vector[4]);
push!(species_dilution_array,(ATIII_artery/volume_artery)*dvdt_vector[4]);
push!(species_dilution_array,(TM_artery/volume_artery)*dvdt_vector[4]);
push!(species_dilution_array,(TRIGGER_artery/volume_artery)*dvdt_vector[4]);
push!(species_dilution_array,(FII_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(FIIa_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(PC_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(APC_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(ATIII_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(TM_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(TRIGGER_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(FII_liver/volume_liver)*dvdt_vector[6]);
push!(species_dilution_array,(FIIa_liver/volume_liver)*dvdt_vector[6]);
push!(species_dilution_array,(PC_liver/volume_liver)*dvdt_vector[6]);
push!(species_dilution_array,(APC_liver/volume_liver)*dvdt_vector[6]);
push!(species_dilution_array,(ATIII_liver/volume_liver)*dvdt_vector[6]);
push!(species_dilution_array,(TM_liver/volume_liver)*dvdt_vector[6]);
push!(species_dilution_array,(TRIGGER_liver/volume_liver)*dvdt_vector[6]);
push!(species_dilution_array,(FII_bulk/volume_bulk)*dvdt_vector[7]);
push!(species_dilution_array,(FIIa_bulk/volume_bulk)*dvdt_vector[7]);
push!(species_dilution_array,(PC_bulk/volume_bulk)*dvdt_vector[7]);
push!(species_dilution_array,(APC_bulk/volume_bulk)*dvdt_vector[7]);
push!(species_dilution_array,(ATIII_bulk/volume_bulk)*dvdt_vector[7]);
push!(species_dilution_array,(TM_bulk/volume_bulk)*dvdt_vector[7]);
push!(species_dilution_array,(TRIGGER_bulk/volume_bulk)*dvdt_vector[7]);
push!(species_dilution_array,(FII_wound/volume_wound)*dvdt_vector[8]);
push!(species_dilution_array,(FIIa_wound/volume_wound)*dvdt_vector[8]);
push!(species_dilution_array,(PC_wound/volume_wound)*dvdt_vector[8]);
push!(species_dilution_array,(APC_wound/volume_wound)*dvdt_vector[8]);
push!(species_dilution_array,(ATIII_wound/volume_wound)*dvdt_vector[8]);
push!(species_dilution_array,(TM_wound/volume_wound)*dvdt_vector[8]);
push!(species_dilution_array,(TRIGGER_wound/volume_wound)*dvdt_vector[8]);
return (species_dilution_array);
end;
