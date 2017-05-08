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
# Generation timestamp: 03-23-2016 13:31:28
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

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

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(Z1_supply/volume_supply)*dvdt_vector[1]);
push!(species_dilution_array,(E1_supply/volume_supply)*dvdt_vector[1]);
push!(species_dilution_array,(E0_supply/volume_supply)*dvdt_vector[1]);
push!(species_dilution_array,(Z2_supply/volume_supply)*dvdt_vector[1]);
push!(species_dilution_array,(E2_supply/volume_supply)*dvdt_vector[1]);
push!(species_dilution_array,(D1_supply/volume_supply)*dvdt_vector[1]);
push!(species_dilution_array,(D2_supply/volume_supply)*dvdt_vector[1]);
push!(species_dilution_array,(Z1_C1/volume_C1)*dvdt_vector[2]);
push!(species_dilution_array,(E1_C1/volume_C1)*dvdt_vector[2]);
push!(species_dilution_array,(E0_C1/volume_C1)*dvdt_vector[2]);
push!(species_dilution_array,(Z2_C1/volume_C1)*dvdt_vector[2]);
push!(species_dilution_array,(E2_C1/volume_C1)*dvdt_vector[2]);
push!(species_dilution_array,(D1_C1/volume_C1)*dvdt_vector[2]);
push!(species_dilution_array,(D2_C1/volume_C1)*dvdt_vector[2]);
push!(species_dilution_array,(Z1_wound/volume_wound)*dvdt_vector[3]);
push!(species_dilution_array,(E1_wound/volume_wound)*dvdt_vector[3]);
push!(species_dilution_array,(E0_wound/volume_wound)*dvdt_vector[3]);
push!(species_dilution_array,(Z2_wound/volume_wound)*dvdt_vector[3]);
push!(species_dilution_array,(E2_wound/volume_wound)*dvdt_vector[3]);
push!(species_dilution_array,(D1_wound/volume_wound)*dvdt_vector[3]);
push!(species_dilution_array,(D2_wound/volume_wound)*dvdt_vector[3]);
push!(species_dilution_array,(Z1_C2/volume_C2)*dvdt_vector[4]);
push!(species_dilution_array,(E1_C2/volume_C2)*dvdt_vector[4]);
push!(species_dilution_array,(E0_C2/volume_C2)*dvdt_vector[4]);
push!(species_dilution_array,(Z2_C2/volume_C2)*dvdt_vector[4]);
push!(species_dilution_array,(E2_C2/volume_C2)*dvdt_vector[4]);
push!(species_dilution_array,(D1_C2/volume_C2)*dvdt_vector[4]);
push!(species_dilution_array,(D2_C2/volume_C2)*dvdt_vector[4]);
return (species_dilution_array);
end;
