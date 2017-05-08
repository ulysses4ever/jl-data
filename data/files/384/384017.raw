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
function HeartRate(t,x,beats_per_minute,stroke_volume,data_dictionary)
# ---------------------------------------------------------------------- #
# HeartRate.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-04-2016 11:06:30
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# beats_per_minute - heart beats per minute
# stoke_volume - stroke volume per beat
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Alias the species vector - 
# cell
A_cell = x[1];
B_cell = x[2];
E1_cell = x[3];
C_cell = x[4];
E2_cell = x[5];
D_cell = x[6];
E3_cell = x[7];
E4_cell = x[8];

# outside
A_outside = x[9];
B_outside = x[10];
E1_outside = x[11];
C_outside = x[12];
E2_outside = x[13];
D_outside = x[14];
E3_outside = x[15];
E4_outside = x[16];
volume_cell = x[17];
volume_outside = x[18];

# Update the beats_per_minute - 
beats_per_minute = beats_per_minute;

# Update the stroke volume - 
stroke_volume = stroke_volume;

return (beats_per_minute,stroke_volume);
end;
