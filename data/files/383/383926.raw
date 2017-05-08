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
# Generation timestamp: 03-10-2016 15:38:03
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Alias the species vector - 
# vein
Z1_vein = x[1];
E1_vein = x[2];
D1_vein = x[3];
Z2_vein = x[4];
E2_vein = x[5];
D2_vein = x[6];
E3_vein = x[7];
E4_vein = x[8];
D3_vein = x[9];
Z4_vein = x[10];
D4_vein = x[11];

# lungs
Z1_lungs = x[12];
E1_lungs = x[13];
D1_lungs = x[14];
Z2_lungs = x[15];
E2_lungs = x[16];
D2_lungs = x[17];
E3_lungs = x[18];
E4_lungs = x[19];
D3_lungs = x[20];
Z4_lungs = x[21];
D4_lungs = x[22];

# artery
Z1_artery = x[23];
E1_artery = x[24];
D1_artery = x[25];
Z2_artery = x[26];
E2_artery = x[27];
D2_artery = x[28];
E3_artery = x[29];
E4_artery = x[30];
D3_artery = x[31];
Z4_artery = x[32];
D4_artery = x[33];

# heart
Z1_heart = x[34];
E1_heart = x[35];
D1_heart = x[36];
Z2_heart = x[37];
E2_heart = x[38];
D2_heart = x[39];
E3_heart = x[40];
E4_heart = x[41];
D3_heart = x[42];
Z4_heart = x[43];
D4_heart = x[44];

# kidney
Z1_kidney = x[45];
E1_kidney = x[46];
D1_kidney = x[47];
Z2_kidney = x[48];
E2_kidney = x[49];
D2_kidney = x[50];
E3_kidney = x[51];
E4_kidney = x[52];
D3_kidney = x[53];
Z4_kidney = x[54];
D4_kidney = x[55];

# wound
Z1_wound = x[56];
E1_wound = x[57];
D1_wound = x[58];
Z2_wound = x[59];
E2_wound = x[60];
D2_wound = x[61];
E3_wound = x[62];
E4_wound = x[63];
D3_wound = x[64];
Z4_wound = x[65];
D4_wound = x[66];
volume_vein = x[67];
volume_lungs = x[68];
volume_artery = x[69];
volume_heart = x[70];
volume_kidney = x[71];
volume_wound = x[72];

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(Z1_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(E1_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(D1_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Z2_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(E2_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(D2_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(E3_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(E4_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(D3_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Z4_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(D4_vein/volume_vein)*dvdt_vector[1]);
push!(species_dilution_array,(Z1_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(E1_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(D1_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Z2_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(E2_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(D2_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(E3_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(E4_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(D3_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Z4_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(D4_lungs/volume_lungs)*dvdt_vector[2]);
push!(species_dilution_array,(Z1_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(E1_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(D1_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Z2_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(E2_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(D2_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(E3_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(E4_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(D3_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Z4_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(D4_artery/volume_artery)*dvdt_vector[3]);
push!(species_dilution_array,(Z1_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(E1_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(D1_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Z2_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(E2_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(D2_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(E3_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(E4_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(D3_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Z4_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(D4_heart/volume_heart)*dvdt_vector[4]);
push!(species_dilution_array,(Z1_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(E1_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(D1_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Z2_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(E2_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(D2_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(E3_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(E4_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(D3_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Z4_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(D4_kidney/volume_kidney)*dvdt_vector[5]);
push!(species_dilution_array,(Z1_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(E1_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(D1_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Z2_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(E2_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(D2_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(E3_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(E4_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(D3_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(Z4_wound/volume_wound)*dvdt_vector[6]);
push!(species_dilution_array,(D4_wound/volume_wound)*dvdt_vector[6]);
return (species_dilution_array);
end;
