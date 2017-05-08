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
function CardiacDistribution(t,x,default_flow_parameter_array,data_dictionary)
# ---------------------------------------------------------------------- #
# CardiacDistribution.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-10-2016 11:38:01
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# default_flow_parameter_array - default flow parameters 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Alias the species vector - 
# vein
Z1_vein = x[1];
E1_vein = x[2];
E0_vein = x[3];
D1_vein = x[4];

# lungs
Z1_lungs = x[5];
E1_lungs = x[6];
E0_lungs = x[7];
D1_lungs = x[8];

# artery
Z1_artery = x[9];
E1_artery = x[10];
E0_artery = x[11];
D1_artery = x[12];

# heart
Z1_heart = x[13];
E1_heart = x[14];
E0_heart = x[15];
D1_heart = x[16];

# kidney
Z1_kidney = x[17];
E1_kidney = x[18];
E0_kidney = x[19];
D1_kidney = x[20];

# wound
Z1_wound = x[21];
E1_wound = x[22];
E0_wound = x[23];
D1_wound = x[24];
volume_vein = x[25];
volume_lungs = x[26];
volume_artery = x[27];
volume_heart = x[28];
volume_kidney = x[29];
volume_wound = x[30];

# Update the flow parameter array - 
flow_parameter_array = default_flow_parameter_array
return (flow_parameter_array);
end;
