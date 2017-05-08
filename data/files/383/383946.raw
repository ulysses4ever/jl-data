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
# Generation timestamp: 03-03-2016 11:23:49
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Alias the species vector - 
# cell
A_cell = x[1];
B_cell = x[2];
E1_cell = x[3];
E4_cell = x[4];
C_cell = x[5];
E2_cell = x[6];
E3_cell = x[7];
G_cell = x[8];

# outside
A_outside = x[9];
B_outside = x[10];
E1_outside = x[11];
E4_outside = x[12];
C_outside = x[13];
E2_outside = x[14];
E3_outside = x[15];
G_outside = x[16];
volume_cell = x[17];
volume_outside = x[18];

# Write the species dilution vector - 
species_dilution_array = Float64[];
push!(species_dilution_array,(A_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(B_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(E1_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(E4_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(C_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(E2_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(E3_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(G_cell/volume_cell)*dvdt_vector[1]);
push!(species_dilution_array,(A_outside/volume_outside)*dvdt_vector[2]);
push!(species_dilution_array,(B_outside/volume_outside)*dvdt_vector[2]);
push!(species_dilution_array,(E1_outside/volume_outside)*dvdt_vector[2]);
push!(species_dilution_array,(E4_outside/volume_outside)*dvdt_vector[2]);
push!(species_dilution_array,(C_outside/volume_outside)*dvdt_vector[2]);
push!(species_dilution_array,(E2_outside/volume_outside)*dvdt_vector[2]);
push!(species_dilution_array,(E3_outside/volume_outside)*dvdt_vector[2]);
push!(species_dilution_array,(G_outside/volume_outside)*dvdt_vector[2]);
return (species_dilution_array);
end;
