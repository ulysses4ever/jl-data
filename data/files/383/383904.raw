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
# Username: jeffreyvarner
# Type: CFPS-JULIA
# Version: 1.0
# Generation timestamp: 03-11-2016 15:19:32
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

# Formulate the kinetic rate vector - 
rate_constant_array = data_dictionary["RATE_CONSTANT_ARRAY"];
saturation_constant_array = data_dictionary["SATURATION_CONSTANT_ARRAY"];
rate_vector = Float64[];

# R1: A+ATP = B
tmp_reaction = rate_constant_array[1]*(E_R1)*(A/(saturation_constant_array[1,1] + A))*(ATP/(saturation_constant_array[1,2] + ATP));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R2a: B = 2*ATP+2*NADH+C
tmp_reaction = rate_constant_array[2]*(E_R2a)*(B/(saturation_constant_array[2,3] + B));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R2b: C+2*ATP+2*NADH = B
tmp_reaction = rate_constant_array[3]*(E_R2b)*(C/(saturation_constant_array[3,5] + C))*(ATP/(saturation_constant_array[3,2] + ATP))*(NADH/(saturation_constant_array[3,4] + NADH));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R3: B = F
tmp_reaction = rate_constant_array[4]*(E_R3)*(B/(saturation_constant_array[4,3] + B));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R4: C = G
tmp_reaction = rate_constant_array[5]*(E_R4)*(C/(saturation_constant_array[5,5] + C));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R5a: G = .8*C+2*NADH
tmp_reaction = rate_constant_array[6]*(E_R5a)*(G/(saturation_constant_array[6,7] + G));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R5b: G = .8*C+2*NADH
tmp_reaction = rate_constant_array[7]*(E_R5b)*(G/(saturation_constant_array[7,7] + G));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R6: C = 2*ATP+3*D
tmp_reaction = rate_constant_array[8]*(E_R6)*(C/(saturation_constant_array[8,5] + C));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R7: C+4*NADH = E
tmp_reaction = rate_constant_array[9]*(E_R7)*(C/(saturation_constant_array[9,5] + C))*(NADH/(saturation_constant_array[9,4] + NADH));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R8a: G+ATP+2*NADH = H
tmp_reaction = rate_constant_array[10]*(E_R8a)*(G/(saturation_constant_array[10,7] + G))*(ATP/(saturation_constant_array[10,2] + ATP))*(NADH/(saturation_constant_array[10,4] + NADH));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# R8b: H = G+ATP+2*NADH
tmp_reaction = rate_constant_array[11]*(E_R8b)*(H/(saturation_constant_array[11,10] + H));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Rres: NADH+O2 = ATP
tmp_reaction = rate_constant_array[12]*(E_Rres)*(NADH/(saturation_constant_array[12,4] + NADH))*(O2/(saturation_constant_array[12,11] + O2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Tc1: Carbon1 = A
tmp_reaction = rate_constant_array[13]*(E_Tc1)*(Carbon1/(saturation_constant_array[13,12] + Carbon1));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Tc2: Carbon2 = A
tmp_reaction = rate_constant_array[14]*(E_Tc2)*(Carbon2/(saturation_constant_array[14,13] + Carbon2));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Tf: Fext = F
tmp_reaction = rate_constant_array[15]*(E_Tf)*(Fext/(saturation_constant_array[15,14] + Fext));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Td: D = Dext
tmp_reaction = rate_constant_array[16]*(E_Td)*(D/(saturation_constant_array[16,8] + D));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Te: E = Ext
tmp_reaction = rate_constant_array[17]*(E_Te)*(E/(saturation_constant_array[17,9] + E));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Th: Hext = H
tmp_reaction = rate_constant_array[18]*(E_Th)*(Hext/(saturation_constant_array[18,17] + Hext));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# TO2: Oxygen = O2
tmp_reaction = rate_constant_array[19]*(E_TO2)*(Oxygen/(saturation_constant_array[19,18] + Oxygen));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# growth: C+F+H+10*ATP = biomass
tmp_reaction = rate_constant_array[20]*(E_growth)*(C/(saturation_constant_array[20,5] + C))*(F/(saturation_constant_array[20,6] + F))*(H/(saturation_constant_array[20,10] + H))*(ATP/(saturation_constant_array[20,2] + ATP));
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R1 = []
tmp_reaction = rate_constant_array[21]*E_R1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R2a = []
tmp_reaction = rate_constant_array[22]*E_R2a;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R2b = []
tmp_reaction = rate_constant_array[23]*E_R2b;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R3 = []
tmp_reaction = rate_constant_array[24]*E_R3;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R4 = []
tmp_reaction = rate_constant_array[25]*E_R4;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R5a = []
tmp_reaction = rate_constant_array[26]*E_R5a;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R5b = []
tmp_reaction = rate_constant_array[27]*E_R5b;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R6 = []
tmp_reaction = rate_constant_array[28]*E_R6;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R7 = []
tmp_reaction = rate_constant_array[29]*E_R7;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R8a = []
tmp_reaction = rate_constant_array[30]*E_R8a;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_R8b = []
tmp_reaction = rate_constant_array[31]*E_R8b;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Rres = []
tmp_reaction = rate_constant_array[32]*E_Rres;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Tc1 = []
tmp_reaction = rate_constant_array[33]*E_Tc1;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Tc2 = []
tmp_reaction = rate_constant_array[34]*E_Tc2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Tf = []
tmp_reaction = rate_constant_array[35]*E_Tf;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Td = []
tmp_reaction = rate_constant_array[36]*E_Td;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Te = []
tmp_reaction = rate_constant_array[37]*E_Te;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_Th = []
tmp_reaction = rate_constant_array[38]*E_Th;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_TO2 = []
tmp_reaction = rate_constant_array[39]*E_TO2;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# Degradation: E_growth = []
tmp_reaction = rate_constant_array[40]*E_growth;
push!(rate_vector,tmp_reaction);
tmp_reaction = 0;

# return the kinetics vector -
return rate_vector;
end
