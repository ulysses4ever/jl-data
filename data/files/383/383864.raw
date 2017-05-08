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
# Generation timestamp: 05-25-2016 16:51:18
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
# Alias the species vector - 
# vein
FII_vein = x[1];
FIIa_vein = x[2];
PC_vein = x[3];
APC_vein = x[4];
ATIII_vein = x[5];
TM_vein = x[6];
TRIGGER_vein = x[7];

# heart
FII_heart = x[8];
FIIa_heart = x[9];
PC_heart = x[10];
APC_heart = x[11];
ATIII_heart = x[12];
TM_heart = x[13];
TRIGGER_heart = x[14];

# lungs
FII_lungs = x[15];
FIIa_lungs = x[16];
PC_lungs = x[17];
APC_lungs = x[18];
ATIII_lungs = x[19];
TM_lungs = x[20];
TRIGGER_lungs = x[21];

# artery
FII_artery = x[22];
FIIa_artery = x[23];
PC_artery = x[24];
APC_artery = x[25];
ATIII_artery = x[26];
TM_artery = x[27];
TRIGGER_artery = x[28];

# kidney
FII_kidney = x[29];
FIIa_kidney = x[30];
PC_kidney = x[31];
APC_kidney = x[32];
ATIII_kidney = x[33];
TM_kidney = x[34];
TRIGGER_kidney = x[35];

# liver
FII_liver = x[36];
FIIa_liver = x[37];
PC_liver = x[38];
APC_liver = x[39];
ATIII_liver = x[40];
TM_liver = x[41];
TRIGGER_liver = x[42];

# bulk
FII_bulk = x[43];
FIIa_bulk = x[44];
PC_bulk = x[45];
APC_bulk = x[46];
ATIII_bulk = x[47];
TM_bulk = x[48];
TRIGGER_bulk = x[49];

# wound
FII_wound = x[50];
FIIa_wound = x[51];
PC_wound = x[52];
APC_wound = x[53];
ATIII_wound = x[54];
TM_wound = x[55];
TRIGGER_wound = x[56];
volume_vein = x[57];
volume_heart = x[58];
volume_lungs = x[59];
volume_artery = x[60];
volume_kidney = x[61];
volume_liver = x[62];
volume_bulk = x[63];
volume_wound = x[64];

#filename = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/s01004-2531-07-20-08-50n"
#data=getUsefulData(filename)
P = 100 #getPressureAtSelectedTime(adjustedtnoshift,data)
nextP =100+10^15*eps()#getPressureAtSelectedTime(adjustedtnoshift+10^15*eps(),data)


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
#Pdata = [P, nextP]
#tdata = [adjustedt, adjustedt+10^15*eps()]

#@show Pdata, tdata

#beats_per_minute, nsprev[1], nsprev[2], nsprev[3], bfprev[1],bfprev[2],bfprev[3] = calculateHeartRate(Pdata,tdata,nsprev, bfprev)
#Cnor = nsprev[1]
#Cach = nsprev[2]
##@show Cnor, Cach
##beats_per_minute= beats_per_minute	
#if(beats_per_minute<0)
#	println("Something went really wrong-the predicted heart rate was negative.")
#	quit()
#end


#if(beats_per_minute> 220)
#	println("Heart rate exceeded maximum. Patient is probably dead.")
#	beats_per_minute = 220
#end
beats_per_minute=beats_per_minute;

@show beats_per_minute

# Update the stroke volume - 
stroke_volume = stroke_volume;
Cnor = .4
Cach = 23E-100

return (beats_per_minute,stroke_volume,Cnor,Cach);
end;
