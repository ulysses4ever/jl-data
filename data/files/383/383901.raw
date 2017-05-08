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
# Username: jeffreyvarner
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-11-2016 14:23:53
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Alias the species vector - 
# cell
A_cell = x[1];
ATP_cell = x[2];
B_cell = x[3];
NADH_cell = x[4];
C_cell = x[5];
F_cell = x[6];
G_cell = x[7];
D_cell = x[8];
E_cell = x[9];
H_cell = x[10];
O2_cell = x[11];
Carbon1_cell = x[12];
Carbon2_cell = x[13];
Fext_cell = x[14];
Dext_cell = x[15];
Ext_cell = x[16];
Hext_cell = x[17];
Oxygen_cell = x[18];
biomass_cell = x[19];
volume_cell = x[20];

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(A_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(ATP_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(B_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(NADH_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(C_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(F_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(G_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(D_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(E_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(H_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(O2_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(Carbon1_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(Carbon2_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(Fext_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(Dext_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(Ext_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(Hext_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(Oxygen_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(biomass_cell/volume_cell)*dvdt_vector[1]);
return (species_dilution_array);
end;
