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
function DataFile(TSTART,TSTOP,Ts)
# ----------------------------------------------------------------------------------- #
# DataFile.jl was generated using the Kwatee code generation system.
# DataFile: Stores model parameters as key - value pairs in a Julia Dict() 
# Username: jeffreyvarner
# Type: CFPS-JULIA
# Version: 1.0
# Generation timestamp: 03-11-2016 15:19:32
# 
# Input arguments: 
# TSTART  - Time start 
# TSTOP  - Time stop 
# Ts - Time step 
# 
# Return arguments: 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ----------------------------------------------------------------------------------- #

# Load the stoichiometric matrix - 
S = float(open(readdlm,"/home/rachel/Desktop/KWateeServer-v1.0/RegulationOfGeneExpression/network/Network.dat"));
(NSPECIES,NREACTIONS) = size(S);

# Formulate the initial condition array - 
initial_condition_array = Float64[];
push!(initial_condition_array,0.0);	#	1	 id:A	 symbol:A
push!(initial_condition_array,0.0);	#	2	 id:ATP	 symbol:ATP
push!(initial_condition_array,0.0);	#	3	 id:B	 symbol:B
push!(initial_condition_array,0.0);	#	4	 id:NADH	 symbol:NADH
push!(initial_condition_array,0.0);	#	5	 id:C	 symbol:C
push!(initial_condition_array,0.0);	#	6	 id:F	 symbol:F
push!(initial_condition_array,0.0);	#	7	 id:G	 symbol:G
push!(initial_condition_array,0.0);	#	8	 id:D	 symbol:D
push!(initial_condition_array,0.0);	#	9	 id:E	 symbol:E
push!(initial_condition_array,0.0);	#	10	 id:H	 symbol:H
push!(initial_condition_array,0.0);	#	11	 id:O2	 symbol:O2
push!(initial_condition_array,0.0);	#	12	 id:Carbon1	 symbol:Carbon1
push!(initial_condition_array,0.0);	#	13	 id:Carbon2	 symbol:Carbon2
push!(initial_condition_array,0.0);	#	14	 id:Fext	 symbol:Fext
push!(initial_condition_array,0.0);	#	15	 id:Dext	 symbol:Dext
push!(initial_condition_array,0.0);	#	16	 id:Ext	 symbol:Ext
push!(initial_condition_array,0.0);	#	17	 id:Hext	 symbol:Hext
push!(initial_condition_array,0.0);	#	18	 id:Oxygen	 symbol:Oxygen
push!(initial_condition_array,0.0);	#	19	 id:biomass	 symbol:biomass
push!(initial_condition_array,1.0);	#	20	 id:E_R1	 symbol:E_R1
push!(initial_condition_array,1.0);	#	21	 id:E_R2a	 symbol:E_R2a
push!(initial_condition_array,1.0);	#	22	 id:E_R2b	 symbol:E_R2b
push!(initial_condition_array,1.0);	#	23	 id:E_R3	 symbol:E_R3
push!(initial_condition_array,1.0);	#	24	 id:E_R4	 symbol:E_R4
push!(initial_condition_array,1.0);	#	25	 id:E_R5a	 symbol:E_R5a
push!(initial_condition_array,1.0);	#	26	 id:E_R5b	 symbol:E_R5b
push!(initial_condition_array,1.0);	#	27	 id:E_R6	 symbol:E_R6
push!(initial_condition_array,1.0);	#	28	 id:E_R7	 symbol:E_R7
push!(initial_condition_array,1.0);	#	29	 id:E_R8a	 symbol:E_R8a
push!(initial_condition_array,1.0);	#	30	 id:E_R8b	 symbol:E_R8b
push!(initial_condition_array,1.0);	#	31	 id:E_Rres	 symbol:E_Rres
push!(initial_condition_array,1.0);	#	32	 id:E_Tc1	 symbol:E_Tc1
push!(initial_condition_array,1.0);	#	33	 id:E_Tc2	 symbol:E_Tc2
push!(initial_condition_array,1.0);	#	34	 id:E_Tf	 symbol:E_Tf
push!(initial_condition_array,1.0);	#	35	 id:E_Td	 symbol:E_Td
push!(initial_condition_array,1.0);	#	36	 id:E_Te	 symbol:E_Te
push!(initial_condition_array,1.0);	#	37	 id:E_Th	 symbol:E_Th
push!(initial_condition_array,1.0);	#	38	 id:E_TO2	 symbol:E_TO2
push!(initial_condition_array,1.0);	#	39	 id:E_growth	 symbol:E_growth

# Formulate the rate constant array - 
rate_constant_array = Float64[];
push!(rate_constant_array,0.0)	#	1	 R1: A+ATP = B
push!(rate_constant_array,0.0)	#	2	 R2a: B = 2*ATP+2*NADH+C
push!(rate_constant_array,0.0)	#	3	 R2b: C+2*ATP+2*NADH = B
push!(rate_constant_array,0.0)	#	4	 R3: B = F
push!(rate_constant_array,0.0)	#	5	 R4: C = G
push!(rate_constant_array,0.0)	#	6	 R5a: G = .8*C+2*NADH
push!(rate_constant_array,0.0)	#	7	 R5b: G = .8*C+2*NADH
push!(rate_constant_array,0.0)	#	8	 R6: C = 2*ATP+3*D
push!(rate_constant_array,0.0)	#	9	 R7: C+4*NADH = E
push!(rate_constant_array,0.0)	#	10	 R8a: G+ATP+2*NADH = H
push!(rate_constant_array,0.0)	#	11	 R8b: H = G+ATP+2*NADH
push!(rate_constant_array,0.0)	#	12	 Rres: NADH+O2 = ATP
push!(rate_constant_array,0.0)	#	13	 Tc1: Carbon1 = A
push!(rate_constant_array,0.0)	#	14	 Tc2: Carbon2 = A
push!(rate_constant_array,0.0)	#	15	 Tf: Fext = F
push!(rate_constant_array,0.0)	#	16	 Td: D = Dext
push!(rate_constant_array,0.0)	#	17	 Te: E = Ext
push!(rate_constant_array,0.0)	#	18	 Th: Hext = H
push!(rate_constant_array,0.0)	#	19	 TO2: Oxygen = O2
push!(rate_constant_array,0.0)	#	20	 growth: C+F+H+10*ATP = biomass
push!(rate_constant_array,0.0)	#	21	 Degradation: E_R1 = []
push!(rate_constant_array,0.0)	#	22	 Degradation: E_R2a = []
push!(rate_constant_array,0.0)	#	23	 Degradation: E_R2b = []
push!(rate_constant_array,0.0)	#	24	 Degradation: E_R3 = []
push!(rate_constant_array,0.0)	#	25	 Degradation: E_R4 = []
push!(rate_constant_array,0.0)	#	26	 Degradation: E_R5a = []
push!(rate_constant_array,0.0)	#	27	 Degradation: E_R5b = []
push!(rate_constant_array,0.0)	#	28	 Degradation: E_R6 = []
push!(rate_constant_array,0.0)	#	29	 Degradation: E_R7 = []
push!(rate_constant_array,0.0)	#	30	 Degradation: E_R8a = []
push!(rate_constant_array,0.0)	#	31	 Degradation: E_R8b = []
push!(rate_constant_array,0.0)	#	32	 Degradation: E_Rres = []
push!(rate_constant_array,0.0)	#	33	 Degradation: E_Tc1 = []
push!(rate_constant_array,0.0)	#	34	 Degradation: E_Tc2 = []
push!(rate_constant_array,0.0)	#	35	 Degradation: E_Tf = []
push!(rate_constant_array,0.0)	#	36	 Degradation: E_Td = []
push!(rate_constant_array,0.0)	#	37	 Degradation: E_Te = []
push!(rate_constant_array,0.0)	#	38	 Degradation: E_Th = []
push!(rate_constant_array,0.0)	#	39	 Degradation: E_TO2 = []
push!(rate_constant_array,0.0)	#	40	 Degradation: E_growth = []

# Formulate the saturation constant array - 
saturation_constant_array = zeros(NREACTIONS,NSPECIES);
saturation_constant_array[1,1] = 1.0;	#	 Name: R1: A+ATP = B Species: A
saturation_constant_array[1,2] = 1.0;	#	 Name: R1: A+ATP = B Species: ATP
saturation_constant_array[2,3] = 1.0;	#	 Name: R2a: B = 2*ATP+2*NADH+C Species: B
saturation_constant_array[3,5] = 1.0;	#	 Name: R2b: C+2*ATP+2*NADH = B Species: C
saturation_constant_array[3,2] = 1.0;	#	 Name: R2b: C+2*ATP+2*NADH = B Species: ATP
saturation_constant_array[3,4] = 1.0;	#	 Name: R2b: C+2*ATP+2*NADH = B Species: NADH
saturation_constant_array[4,3] = 1.0;	#	 Name: R3: B = F Species: B
saturation_constant_array[5,5] = 1.0;	#	 Name: R4: C = G Species: C
saturation_constant_array[6,7] = 1.0;	#	 Name: R5a: G = .8*C+2*NADH Species: G
saturation_constant_array[7,7] = 1.0;	#	 Name: R5b: G = .8*C+2*NADH Species: G
saturation_constant_array[8,5] = 1.0;	#	 Name: R6: C = 2*ATP+3*D Species: C
saturation_constant_array[9,5] = 1.0;	#	 Name: R7: C+4*NADH = E Species: C
saturation_constant_array[9,4] = 1.0;	#	 Name: R7: C+4*NADH = E Species: NADH
saturation_constant_array[10,7] = 1.0;	#	 Name: R8a: G+ATP+2*NADH = H Species: G
saturation_constant_array[10,2] = 1.0;	#	 Name: R8a: G+ATP+2*NADH = H Species: ATP
saturation_constant_array[10,4] = 1.0;	#	 Name: R8a: G+ATP+2*NADH = H Species: NADH
saturation_constant_array[11,10] = 1.0;	#	 Name: R8b: H = G+ATP+2*NADH Species: H
saturation_constant_array[12,4] = 1.0;	#	 Name: Rres: NADH+O2 = ATP Species: NADH
saturation_constant_array[12,11] = 1.0;	#	 Name: Rres: NADH+O2 = ATP Species: O2
saturation_constant_array[13,12] = 1.0;	#	 Name: Tc1: Carbon1 = A Species: Carbon1
saturation_constant_array[14,13] = 1.0;	#	 Name: Tc2: Carbon2 = A Species: Carbon2
saturation_constant_array[15,14] = 1.0;	#	 Name: Tf: Fext = F Species: Fext
saturation_constant_array[16,8] = 1.0;	#	 Name: Td: D = Dext Species: D
saturation_constant_array[17,9] = 1.0;	#	 Name: Te: E = Ext Species: E
saturation_constant_array[18,17] = 1.0;	#	 Name: Th: Hext = H Species: Hext
saturation_constant_array[19,18] = 1.0;	#	 Name: TO2: Oxygen = O2 Species: Oxygen
saturation_constant_array[20,5] = 1.0;	#	 Name: growth: C+F+H+10*ATP = biomass Species: C
saturation_constant_array[20,6] = 1.0;	#	 Name: growth: C+F+H+10*ATP = biomass Species: F
saturation_constant_array[20,10] = 1.0;	#	 Name: growth: C+F+H+10*ATP = biomass Species: H
saturation_constant_array[20,2] = 1.0;	#	 Name: growth: C+F+H+10*ATP = biomass Species: ATP

# Formulate control parameter array - 
control_parameter_array = zeros(1,2);

# ---------------------------- DO NOT EDIT BELOW THIS LINE -------------------------- #
data_dictionary = Dict();
data_dictionary["STOICHIOMETRIC_MATRIX"] = S;
data_dictionary["RATE_CONSTANT_ARRAY"] = rate_constant_array;
data_dictionary["SATURATION_CONSTANT_ARRAY"] = saturation_constant_array;
data_dictionary["INITIAL_CONDITION_ARRAY"] = initial_condition_array;
data_dictionary["CONTROL_PARAMETER_ARRAY"] = control_parameter_array;
# ----------------------------------------------------------------------------------- #
return data_dictionary;
end
