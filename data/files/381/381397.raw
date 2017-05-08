#just rewrite the fortran code in julia so that I can go through it and understand it
#then possibly try to run both?
#preallocate arrays
NBMAX=1024
index = Array(Int,NBMAX,NBMAX)
massb = Array(Float64,NBMAX+1)
massc = Array(Float64,NBMAX+1)
delm = Array(Float64,NBMAX)
dlnm = Array(Float64,NBMAX)
mden = Array(Float64,NBMAX+1)
mtmp = Array(Float64,NBMAX+1)
gain = Array(Float64,NBMAX+1)
loss = Array(Float64,NBMAX+1)
c = Array(Float64,NBMAX+1)
q = Array(Float64,NBMAX+1)
nden = Array(Float64,NBMAX+1)
rho = Array(Float64,NBMAX+1)
ndec = 6
nbdec = 40
dmmax = 0.05
tmax = 10000
tprint = 99.99999
tnext = 0
nbin = nbdec*ndec
nbd1 = nbin+1
if nbin > NBMAX
	println("nbin > NBMAX")
	return
end

dlogm = 1.0/nbdec

#set up mass bins, where c is the central (average?) of the bin and b is the edges of the bins

for i = 1:nbdec
	massb[i] = i - 0.5
	massc[i] = i
end
massb[nbdec+1] = massc[nbdec] + 0.5

for i = (nbdec+1):nbin
	mass = massc[nbdec]*10.0^((i-nbdec)*dlogm)
	if mass < 1.0e6
		massb[i+1] = float(int(mass))+0.5
	else
		massb[i+1] = mass+0.5
	end
	massc[i] = 0.5*(massb[i+1]+massb[i])
end
mass = massc[nbdec]*10.0^((nbin1-nbdec)*dlogm) + 0.5 #this is the mass for the bin past the last one (all the extra, I think?)
massc[nbin1] = 0.5*(mass+massb[nbin1])
for i = 1:nbin
	delm[i] = massb[i+1] - massb[i] #change in mass from bin to bin getting set up
	if i > nbdec
		dlnm[i] = log(massc[i+1]/massc[i-1])
	end
end


