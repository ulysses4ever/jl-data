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
#	Psi = y[14]
#	Pra = y[15]
#	Vrv = y[16]
#	Psquiggle = y[17]
#	fac = y[18]
#	fap = y[19]
#	fsp = y[20]
#	fsh = y[21]
#	fv = y[22]
#	Thetasp = y[23]
#	Thetash = y[24]
#	deltaVT = y[25]
#	deltaEmaxlv = y[26]
#	deltaEmaxrv = y[27]
#	deltaRsp = y[28]
#	deltaRep = y[29]
#	deltaRmp = y[30]
#	deltaVusv = y[31]
#	deltaVuev = y[32]
#	deltaVumv = y[33]
#	deltaTs = y[34]
#	deltaTv = y[35]
#	xb = y[36]
#	xh = y[37]
#	xm = y[38]
#	Wh = y[39]
	ic_arr = fill(.1,1,size)
	ic_arr[1] = 25 #PPA = 25 mmHg, from http://www.rnceus.com/hemo/term.htm
	ic_arr[3] = 25 #Ppp
	ic_arr[4] = 5#Ppv from http://www.acbrown.com/lung/Lectures/RsCrcl/RsCrclFlow.htm
	ic_arr[5] = 95# Psa from http://www.acbrown.com/lung/Lectures/RsCrcl/RsCrclFlow.htm
	ic_arr[7]= 80 #Psp
	ic_arr[8] = 5 #veins Psv 
	ic_arr[9] = 5 #Pmv veins
	ic_arr[10] = 5 #Pbv veins
	ic_arr[11] = 5 #Phv veins
	ic_arr[12] = 1.5 #left atrium
	ic_arr[13]=16.77 #using unstressed conditions
	ic_arr[16]=40.8
	ic_arr[15]= 1.5 #right atrium 
	ic_arr[14] =.5 #Psi
	return (transpose(ic_arr))
	
end
