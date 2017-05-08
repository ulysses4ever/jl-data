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
# Username: jeffreyvarner
# Type: CFPS-JULIA
# Version: 1.0
# Generation timestamp: 03-11-2016 15:19:32
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# rate_vector - vector of reaction rates 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Set a default value for the allosteric control variables - 
const number_of_reactions = length(rate_vector);
control_vector = ones(number_of_reactions);
const control_parameter_array = data_dictionary["CONTROL_PARAMETER_ARRAY"];

# Alias the species vector - 
A = x[1];
ATP = x[2];
B = x[3];
NADH = x[4];
C = x[5];
F = x[6];
G = x[7];
D = x[8];
E = x[9];
H = x[10];
O2 = x[11];
Carbon1 = x[12];
Carbon2 = x[13];
Fext = x[14];
Dext = x[15];
Ext = x[16];
Hext = x[17];
Oxygen = x[18];
biomass = x[19];
E_R1 = x[20];
E_R2a = x[21];
E_R2b = x[22];
E_R3 = x[23];
E_R4 = x[24];
E_R5a = x[25];
E_R5b = x[26];
E_R6 = x[27];
E_R7 = x[28];
E_R8a = x[29];
E_R8b = x[30];
E_Rres = x[31];
E_Tc1 = x[32];
E_Tc2 = x[33];
E_Tf = x[34];
E_Td = x[35];
E_Te = x[36];
E_Th = x[37];
E_TO2 = x[38];
E_growth = x[39];

# Modify the rate_vector with the control variables - 
rate_vector = rate_vector.*control_vector;

# Return the modified rate vector - 
return rate_vector;
end
