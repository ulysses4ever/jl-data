function buildIC(size)
#	Ppa = y[1]
#	Fpa = y[2]
#	Ppp = y[3]
#	Ppv = y[4]
#	Psa = y[5]
#	Fsa = y[6]
#	Psp = y[7]
#	Psv = y[8]
#	Pmv = y[9]
#	Pbv = y[10]
#	Phv = y[11]
#	Pla = y[12]
#	Vlv = y[13]
#	Psi = mod(y[14],1)
#	Pra = y[15]
#	Vrv = y[16]
#	Psquiggle = y[17]
#	fac = y[18]
#	fap = y[19]
#	Thetasp = y[20]
#	Thetash = y[21]
#	deltaVT = y[22]
#	deltaEmaxlv = y[23]
#	deltaEmaxrv = y[24]
#	deltaRsp = y[25]
#	deltaRep = y[26]
#	deltaRmp = y[27]
#	deltaVusv = y[28]
#	deltaVuev = y[29]
#	deltaVumv = y[30]
#	deltaTs = y[31]
#	deltaTv = y[32]
#	xb = y[33]
#	xh = y[34]
#	xm = y[35]
#	Wh = y[36]
	ic_arr = fill(0.0,1,size)
	#now using steady state values from running out model for 3600 sec (1 hr)
	ic_arr[1] = 25 #PPA = 25 mmHg, from http://www.rnceus.com/hemo/term.htm
	ic_arr[2] =100/60 #Fpa is 100 mL/min
	ic_arr[3] = 10 #Ppp
	ic_arr[4] = 2#Ppv from http://www.acbrown.com/lung/Lectures/RsCrcl/RsCrclFlow.htm
	ic_arr[5] = 150# Psa from http://www.acbrown.com/lung/Lectures/RsCrcl/RsCrclFlow.htm
	ic_arr[6] = 75.6# Fsa is 75.6 mL/sec
	ic_arr[7]= 70 #Psp
	ic_arr[8] = 5 #veins Psv-doesn't appear to reach ss' 
	ic_arr[9] = 3 #Pmv veins
	ic_arr[10] = 4 #Pbv veins
	ic_arr[11] = 4 #Phv veins
	ic_arr[12] = 1.5 #left atrium
	ic_arr[13]=14 #Vlv using unstressed conditions
	ic_arr[16]=35 #Vrv
	ic_arr[15]= 1.5 #right atrium 
	ic_arr[14] =0.0 #Psi
	ic_arr[17] =70 #Psquiggle
	ic_arr[18] = 1.6 #fac
	ic_arr[19] = 7.0 #fap
	ic_arr[25] = 0
	ic_arr[26] = 0.0
	ic_arr[27] = 0.0
	ic_arr[33] = 3.0 #xb
	ic_arr[34] = 3.0#xh
	ic_arr[35] = 3.0#xm
	return (transpose(ic_arr))
	
end
