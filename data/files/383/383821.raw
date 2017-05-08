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
include("OlufsenModel2011calcHR.jl")
include("helpersToReadData.jl")
# ----------------------------------------------------------------------------------- #
function HeartRate(t,x,beats_per_minute,stroke_volume,data_dictionary)
# ---------------------------------------------------------------------- #
# HeartRate.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 03-30-2016 10:35:36
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# beats_per_minute - heart beats per minute
# stoke_volume - stroke volume per beat
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

adjustedt = t*60+180; #need to convert from minutes to seconds
adjustedtnoshift = t*60.0
#if(t < 3)
#	P =70.0;
#elseif((t> 3.0) && (t <5))
#	println("in ramp")
#	P = 100.0+(adjustedt-180)
#elseif(t > 5)
#	P = 200.0
#end

#P = 30*sin(25*t/pi)+100;
#P = 100.0

# Alias the species vector - 
# vein
FII_vein = x[1];
FIIa_vein = x[2];
PC_vein = x[3];
APC_vein = x[4];
ATIII_vein = x[5];
TM_vein = x[6];
TRIGGER_vein = x[7];

# lungs
FII_lungs = x[8];
FIIa_lungs = x[9];
PC_lungs = x[10];
APC_lungs = x[11];
ATIII_lungs = x[12];
TM_lungs = x[13];
TRIGGER_lungs = x[14];

# artery
FII_artery = x[15];
FIIa_artery = x[16];
PC_artery = x[17];
APC_artery = x[18];
ATIII_artery = x[19];
TM_artery = x[20];
TRIGGER_artery = x[21];

# heart
FII_heart = x[22];
FIIa_heart = x[23];
PC_heart = x[24];
APC_heart = x[25];
ATIII_heart = x[26];
TM_heart = x[27];
TRIGGER_heart = x[28];

# kidney
FII_kidney = x[29];
FIIa_kidney = x[30];
PC_kidney = x[31];
APC_kidney = x[32];
ATIII_kidney = x[33];
TM_kidney = x[34];
TRIGGER_kidney = x[35];

# wound
FII_wound = x[36];
FIIa_wound = x[37];
PC_wound = x[38];
APC_wound = x[39];
ATIII_wound = x[40];
TM_wound = x[41];
TRIGGER_wound = x[42];
volume_vein = x[43];
volume_lungs = x[44];
volume_artery = x[45];
volume_heart = x[46];
volume_kidney = x[47];
volume_wound = x[48];

filename = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/s01004-2531-07-20-08-50n"
data=getUsefulData(filename)
P = getPressureAtSelectedTime(adjustedtnoshift,data)
nextP =getPressureAtSelectedTime(adjustedtnoshift+10^15*eps(),data)

# Update the beats_per_minute -
N = 75.0
M = 120.0 
beta = 6.0

tol = 1E-5
P0 = 100;
nsprev= collect(fill(1.0,1,3))
bfprev = collect(fill(1.0,1,3))
Pdata = fill(1.0,1,2)
tdata = fill(1.0,1,2)

if(t <=0.0+tol)
	nsprev = [(1-N/M)/(1+beta*N/M), N/M, 0.0];
	bfprev = [0.0,0.0,90.0];
end
#nextP = P+10^15*eps()
Pdata = [P, nextP]
tdata = [adjustedt, adjustedt+10^15*eps()]

@show Pdata, tdata

beats_per_minute, nsprev[1], nsprev[2], nsprev[3], bfprev[1],bfprev[2],bfprev[3] = calculateHeartRate(Pdata,tdata,nsprev, bfprev)
Cnor = nsprev[1]
Cach = nsprev[2]
#@show Cnor, Cach
#beats_per_minute= beats_per_minute	
if(beats_per_minute<0)
	println("Something went really wrong-the predicted heart rate was negative.")
	quit()
end


if(beats_per_minute> 220)
	println("Heart rate exceeded maximum. Patient is probably dead.")
	beats_per_minute = 220
end

@show beats_per_minute

# Update the stroke volume - 
stroke_volume = stroke_volume;

return (beats_per_minute,stroke_volume,Cnor,Cach);
end;
