#Julia port of code by Professor Man Hoi Lee
#modifications by Rachael Mansbach
#just rewrite the fortran code in julia so that I can go through it and understand it
#then possibly try to run both?
using Debug
using PyPlot
#rate function currently set for linear kernel
function rate(i,j)
	return 1.0
end

#preallocate arrays, SET ALL VARIABLES TO ZERO INITIALLY
NBMAX=1024
ndec=0
nbdec=0
nbin=0
nbin1=0
imin=0
imax=0
iminold=0
imaxold=0
time=0.0
dt=0.0
dt2=0.0
tmax=0.0
tprint=0.0
tnext=0.0
dmmax=0.0
dlogm=0.0
mmerge=0.0
#rate=0.0
rateav=0.0
nmin=0.0
dmfrac=0.0
dm=0.0
lossmx=0.0
ntot=0.0
ntot2=0.0
mtot=0.0
m2tot=0.0
njmhalf=0.0
njphalf=0.0
njtmp=0.0
nitmp=0.0
w1=0.0
w2=0.0
ratio=0.0
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
for i = 1:(NBMAX+1)
	massb[i] = 0.0
	massc[i] = 0.0
	#delm[i] = 0.0
	#dlnm[i] = 0.0
	mden[i] = 0.0
	mtmp[i] = 0.0
	gain[i] = 0.0
	loss[i] = 0.0
	c[i] = 0.0
	q[i] = 0.0
	nden[i] = 0.0
	rho[i] = 0.0
end
for j = 1:NBMAX
	delm[j] = 0.0
	dlnm[j] = 0.0
	for i = 1:NBMAX
		index[i,j] = 0.0
	end
end
ndec = 5
nbdec = 40
dmmax = 0.05
tmax = 10.0
tprint = 5.0
tnext = 0
nbin = nbdec*ndec
nbin1 = nbin+1
if nbin > NBMAX
	println("nbin > NBMAX")
	return
end

dlogm = 1.0/nbdec

#set up mass bins, where c is the central (average?) of the bin and b is the edges of the bins
function initMassBins(massb,massc,nbdec,nbin,dlogm,nbin1,dlnm)
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
end

initMassBins(massb,massc,nbdec,nbin,dlogm,nbin1,dlnm)

function initializeKs(massb,massc,index,delm,nbdec,nbin1)
#Store index(i,j) = k such that m_(k-1/2) < m_i + m_(j-1/2) <= m_(k+1/2).
#index(i,j) = -k if m_i + m_(j+1/2) <= m_(k+1/2).
mmax = massb[nbin1]
s = size(index)
for j = 1:s[1]
	for i = 1:s[2]
		index[i,j] = 0.0
	end
end
#both fortran and julia are column-major order
for j = nbin:-1:1
	for i = j:-1:1
		#println("(i,j): "*string(i)*" "*string(j))
		mass = massc[i] + massb[j] + 0.01
		#println("mass = "*string(mass))
		if i+j < nbdec #both of them are non-log-bins
			#println("non-log-bins")
			index[i,j] = -(i+j)
		elseif massc[i] < delm[j] #not quite clear on what we're testing here, but it appears to be if everything (?) goes back into j
			#println("second test")
			index[i,j] = j
		elseif mass > mmax #dropping things outside
			#println("falls outside")
			index[i,j] = 0
		else #do a binary search -- not quite clear on this either
			#println("bin. search")
			ip = j
			iq = min(2*j+1,nbin1)
			while iq - ip > 1
				k = Int(floor((ip+iq)/2)) #do integer division
				#println("k is: "*string(k))
				#println("massb[k] is: "*string(massb[int(k)]))
				if mass < massb[k]
					iq = k
				else
					ip = k
				end
			end

			if massc[i] + massb[j+1] - 1.0 - 2 > massb[iq]
				index[i,j] = ip
			else
				index[i,j] = -ip
			end
		end
	end
end
end


initializeKs(massb,massc,index,delm,nbdec,nbin1)
#Initialize mden, nden, timestep, etc.
#mden(i) = mass in bin i.
#nden(i) = number (density?) of particles in bin i
#initial conditions get toggled here
mass=0
mmax=0
qj=0
qjp1=0

function main(ndec,nbdec,nbin,nbin1,imin,imax,iminold,imaxold,time,dt,dt2,tmax,tprint,tnext,dmmax,dlogm,mmerge,rateav,nmin,dmfrac,dm,lossmx,ntot,ntot2,mtot,m2tot,massb,massc,delm,dlnm,mmax,mass,mden,mtmp,gain,loss,c,q,nden,rho,qj,qjp1,njmhalf,njphalf,njtmp,nitmp,w1,w2,ratio)
imin = 1
imax = 1 #for non monodisperse, this = bin-number of largest bin containing mass
nmin = 1.0e-30
mden[1] = 1.0 #monodisperse initial conditions
mtmp[1] = 0.0
nden[1] = 1.0
step = 1
for i = 2:nbin1
	mden[i] = 0.0
	mtmp[i] = 0.0
	nden[i] = 0.0
end

time = 0.0
dt = 0.01*dmmax/(nden[1]*rate(massc[1],massc[1])) 
tnext = tnext + tprint

#Open output file

f = open("merge1.out","w")
@printf(f,"ndec,nbdec = %10d,%10d \n",ndec,nbdec)
@printf(f,"dmmax,dt,tmax,tprint = %13.5f %13.5f %13.5f %13.5f\n",dmmax,dt,tmax,tprint)

#Integration loop
fig = figure()
ax = axes()
while time < tmax #100
 	# First compute mden (called mtmp) at half the timestep

	dt2 = 0.5*dt

	#Clear gain and loss terms

	for i = 1:nbin1 #200
		gain[i] = 0.0
		loss[i] = 0.0
	end #200
	#Loop over all relevant merger interactions and compute the appropriate gains and losses
	for j = imax:-1:imin #300
		if (j > nbdec)
			#Compute weight factors proportional to the number density at the boundaries of bin j
			njmhalf = 1.0
			njphalf = (massb[j+1]/massb[j])^(q[j]-1.0) #q is initialized to zeros by definition, I believe
		#slightly concerned about normalization -- may want to check on this
			
		end
		for i=j:-1:imin
			k = index[i,j]
			if k < 0
			#put merger products into bin k			
				k = -1*k
				#compute effective rate coefficient approximately
				if (j <= nbdec)#easy version
					rateav = rate(massc[i],massc[j])
				else
					w1 = njmhalf*(massc[i]+massb[j])
					w2 = njphalf*(massc[i]+massb[j+1])
					rateav = (w1*rate(massc[i],massb[j])+w2*rate(massc[i],massb[j+1]))/(w1+w2)
				end

				mmerge = (dt2*rateav*mden[i])*nden[j]#loss/gain from bin i -> k
				if i==j
					#half the amount of mass because we're only dealing with one bin
					mmerge = 0.5*mmerge
				end
				#if isnan(mmerge)
				#	@bp
				#end
				loss[i] += mmerge
				gain[k] += mmerge
				mmerge = (dt2*rateav*mden[i]/massc[i])*mden[j]#loss/gain from bin j ->k
				if i==j
					mmerge = 0.5*mmerge
				end
				#if isnan(mmerge)
				#	@bp
				#end
				loss[j] += mmerge
				gain[k] += mmerge
			elseif k > 0
			#divide merger products between bins k and k+1
		 		qj = q[j]
				qjp1 = qj + 1.0
				mass = massb[k+1] - massc[i]
				njtmp = (mass/massb[j])^(qj-1.0)

				#compute mass moving from bin i to bin k
				w1 = njmhalf*(massc[i]+massb[j])
				w2 = njtmp*(massc[i]+mass)
				rateav = (w1*rate(massc[i],massb[j])+w2*rate(massc[i],mass))/(w1+w2)
				mmerge = (dt2*rateav*mden[i])*(c[j]/qj)*((mass/massb[j])^qj - 1.0)
				if (i==j)
					mmerge = 0.5*mmerge
				end
				#if isnan(mmerge)
				#	@bp
				#end
				loss[i] += mmerge
				gain[k] += mmerge
				
				if k!=j
					#compute mass moving from bin j to bin k
					mmerge = (dt2*rateav*mden[i]/massc[i])*(massb[j]*c[j]/qjp1)*((mass/massb[j])^qjp1 - 1.0)
					if i==j
						mmerge = 0.5*mmerge
					end
					#if isnan(mmerge)
					#	@bp
					#end
					loss[j] += mmerge
					gain[k] += mmerge
				end
				
				w1 = njtmp*(massc[i]+mass)
				w2 = njphalf*(massc[i]+massb[j+1])
				rateav = (w1*rate(massc[i],mass)+w2*rate(massc[i],massb[j+1]))/(w1+w2)
				if (k==j) && (massc[i] < 1.0e-7*massb[j+1]) #if k is j and massc is small
					#Use series expansion
					ratio = massc[i]/massb[j+1]
					
					#Compute mass moving from bin i to bin k+1

					t1 = dt2*rateav*mden[i]*c[j]
					t2 = (massb[j+1]/massb[j])^qj
					t3 = ratio*(1.0-0.5*(qj-1.0)*ratio*(1.0-(qj-2.0)*ratio/3.0))
					mmerge = t1*t2*t3
					if (i==j)
						mmerge = 0.5*mmerge
					end
					#if isnan(mmerge)
					#	@bp
					#end
					loss[i] += mmerge
					gain[k+1] += mmerge

					#Compute mass moving from bin j to bin k+1

					t1 = (dt2*rateav*mden[i]/massc[i])*massb[j]
					t2 = c[j]*(massb[j+1]/massb[j])^qjp1
					t3 = ratio*(1.0-0.5*(qjp1-1.0)*ratio*(1.0-(qjp1-2.0)*ratio/3.0))
					mmerge = t1*t2*t3

					if i==j 
						mmerge = 0.5*mmerge
					end
					#if isnan(mmerge)
					#	@bp
					#end
					loss[j] += mmerge
					gain[k+1] += mmerge

				else
					#Compute mass moving from bin i to bin k+1
					t1 = (dt2*rateav*mden[i])*(c[j]/qj)
					t2 = ((massb[j+1]/massb[j])^qj - (mass/massb[j])^qj)
					mmerge = t1*t2
					if (i==j)
						mmerge = 0.5*mmerge
					end
					#if isnan(mmerge)
					#	@bp
					#end
					loss[i] += mmerge
					gain[k+1] += mmerge

					#Compute mass moving from bin j to bin k+1
					t1 = (dt2*rateav*mden[i]/massc[i])
					t2 = (massb[j]*c[j]/qjp1)
					t3 = ((massb[j+1]/massb[j])^qjp1 - (mass/massb[j])^qjp1)
					mmerge = t1*t2*t3
					
					if (i==j)
						mmerge = 0.5*mmerge
					end
					#if isnan(mmerge)
					#	@bp
					#end

					loss[j] += mmerge
					gain[k+1] += mmerge
		
				end
					
			end

		end

	end

	#Add net change to each mass bin	

	for i=1:nbin
		#if isnan(gain[i]) || isnan(loss[i])
		#	@bp
		#end
		mtmp[i] = mden[i] + gain[i] - loss[i]
		nden[i] = mtmp[i]/massc[i]
	end

	imaxold = imax
	#updating which bins need to be considered
	for i = imaxold+1:nbin
		if (nden[i] > nmin) || (nden[i]*massc[i]^2/delm[i] > 1e-10)
			imax = i
		end
	end

	#convert from mden to mass spectrum by assuming that the mass spectrum is locally a power law with index q
	for i = nbdec:imax
		rho[i] = mtmp[i]/delm[i]
	end

	for j = max(imin,nbdec+1):imax
		if (j==imin)
			qj = log(rho[j+1]/rho[j])/log(massc[j+1]/massc[j])
		elseif (j==imax)
			qj = log(rho[j]/rho[j-1])/log(massc[j]/massc[j-1])
		else
			log(rho[j+1]/rho[j-1])/dlnm[j]
		end
		qjp1 = qj + 1.0
		q[j] = qj
		c[j] = (mtmp[j]/massb[j])*qjp1/((massb[j+1]/massb[j])^qjp1-1.0)
	end
	nmin = 1e-30
	
	if (imax > nbdec)
		qj = min(q[imax],-1.0)
		nmin = min(nmin,nden[imax]*(massc[imax+1]/massc[imax])^qj)
	end

	#Calculate nden assuming power law

	for j = max(imin,nbdec+1):imax
		nden[j] = (c[j]/q[j])*((massb[j+1]/massb[j])^q[j]-1.0)
	end

	#Now take the whole timestep

	time += dt
	
	#Clear gain and loss terms

	for i = 1:nbin1 #200
		gain[i] = 0.0
		loss[i] = 0.0
	end #200
	#Loop over all relevant merger interactions and compute the appropriate gains and losses
	for j = imax:-1:imin #300
		if (j > nbdec)
			#Compute weight factors proportional to the number density at the boundaries of bin j
			njmhalf = 1.0
			njphalf = (massb[j+1]/massb[j])^(q[j]-1.0) #q is initialized to zeros by definition, I believe
		#slightly concerned about normalization -- may want to check on this
		end
		for i=j:-1:imin
			k = index[i,j]
			if k < 0
			#put merger products into bin k			
				k = -1*k
				#compute effective rate coefficient approximately
				if (j <= nbdec)#easy version
					rateav = rate(massc[i],massc[j])
				else
					w1 = njmhalf*(massc[i]+massb[j])
					w2 = njphalf*(massc[i]+massb[j+1])
					rateav = (w1*rate(massc[i],massb[j])+w2*rate(massc[i],massb[j+1]))/(w1+w2)
				end

				mmerge = (dt*rateav*mtmp[i])*nden[j]#loss/gain from bin i -> k
				if i==j
					#half the amount of mass because we're only dealing with one bin
					mmerge = 0.5*mmerge
				end
				loss[i] += mmerge
				gain[k] += mmerge
				mmerge = (dt*rateav*mtmp[i]/massc[i])*mtmp[j]#loss/gain from bin j ->k
				if i==j
					mmerge = 0.5*mmerge
				end
				loss[j] += mmerge
				gain[k] += mmerge
			elseif k > 0
			#divide merger products between bins k and k+1
		 		qj = q[j]
				qjp1 = qj + 1.0
				mass = massb[k+1] - massc[i]
				njtmp = (mass/massb[j])^(qj-1.0)

				#compute mass moving from bin i to bin k
				w1 = njmhalf*(massc[i]+massb[j])
				w2 = njtmp*(massc[i]+mass)
				rateav = (w1*rate(massc[i],massb[j])+w2*rate(massc[i],mass))/(w1+w2)
				mmerge = (dt*rateav*mtmp[i])*(c[j]/qj)*((mass/massb[j])^qj - 1.0)
				if (i==j)
					mmerge = 0.5*mmerge
				end
				loss[i] += mmerge
				gain[k] += mmerge
				
				if k!=j
					#compute mass moving from bin j to bin k
					mmerge = (dt*rateav*mtmp[i]/massc[i])*(massb[j]*c[j]/qjp1)*((mass/massb[j])^qjp1 - 1.0)
					if i==j
						mmerge = 0.5*mmerge
					end
					loss[j] += mmerge
					gain[k] += mmerge
				end
				
				w1 = njtmp*(massc[i]+mass)
				w2 = njphalf*(massc[i]+massb[j+1])
				rateav = (w1*rate(massc[i],mass)+w2*rate(massc[i],massb[j+1]))/(w1+w2)
				if (k==j) && (massc[i] < 1.0e-7*massb[j+1]) #if k is j and massc is small
					#Use series expansion
					ratio = massc[i]/massb[j+1]
					
					#Compute mass moving from bin i to bin k+1

					t1 = dt*rateav*mtmp[i]*c[j]
					t2 = (massb[j+1]/massb[j])^qj
					t3 = ratio*(1.0-0.5*(qj-1.0)*ratio*(1.0-(qj-2.0)*ratio/3.0))
					mmerge = t1*t2*t3
					if (i==j)
						mmerge = 0.5*mmerge
					end
					loss[i] += mmerge
					gain[k+1] += mmerge

					#Compute mass moving from bin j to bin k+1

					t1 = (dt*rateav*mtmp[i]/massc[i])*massb[j]
					t2 = c[j]*(massb[j+1]/massb[j])^qjp1
					t3 = ratio*(1.0-0.5*(qjp1-1.0)*ratio*(1.0-(qjp1-2.0)*ratio/3.0))
					mmerge = t1*t2*t3

					if i==j 
						mmerge = 0.5*mmerge
					end
					loss[j] += mmerge
					gain[k+1] += mmerge

				else
					#Compute mass moving from bin i to bin k+1
					t1 = (dt*rateav*mtmp[i])*(c[j]/qj)
					t2 = ((massb[j+1]/massb[j])^qj - (mass/massb[j])^qj)
					mmerge = t1*t2
					if (i==j)
						mmerge = 0.5*mmerge
					end
					loss[i] += mmerge
					gain[k+1] += mmerge

					#Compute mass moving from bin j to bin k+1
					t1 = (dt*rateav*mtmp[i]/massc[i])
					t2 = (massb[j]*c[j]/qjp1)
					t3 = ((massb[j+1]/massb[j])^qjp1 - (mass/massb[j])^qjp1)
					mmerge = t1*t2*t3
					
					if (i==j)
						mmerge = 0.5*mmerge
					end

					loss[j] += mmerge
					gain[k+1] += mmerge
		
				end
					
			end

		end

	end

	dmfrac = 0.0
	lossmx = 0.0
	for i = 1:nbin #700
		dm = gain[i] - loss[i]
		if i < imaxold
			dmfrac = max(abs(dm/mden[i]),dmfrac)
			lossmx = max(loss[i]/mden[i],lossmx)
		end
		mden[i] = mden[i] + dm
		nden[i] = mden[i]/massc[i]
	end #700
	imaxold = imax

	for i = (imaxold+1):nbin #720
		if (nden[i] > nmin) || (nden[i]*massc[i]^2/delm[i] > 1e-10) 
			imax = i
		end
	end #720

	iminold = imin #update imin as well as imax that makes SENSE
	for i=iminold:imax #730
		if (nden[i] > 1e-50)
			imin = i
			break
		end
	end #730
	dt = min(dmmax/dmfrac,0.9/lossmx,1.2)*dt
	#Convert from mden to mass spectrum by assuming that the mass spectrum is locally a power law with index q
	for i=nbdec:imax #740
		rho[i] = mden[i]/delm[i]
	end #740

	for j = max(imin,nbdec+1):imax #760
		if (j==imin)
			qj = log(rho[j+1]/rho[j])/log(massc[j+1]/massc[j])
		elseif (j==imax)
			qj = log(rho[j]/rho[j-1])/log(massc[j]/massc[j-1])
		else
			qj = log(rho[j+1]/rho[j-1])/dlnm[j]
		end
		qjp1 = qj + 1.0
		q[j] = qj
		c[j] = (mden[j]/massb[j])*qjp1/((massb[j+1]/massb[j])^qjp1 - 1.0)
	end #760
	nmin = 1e-30
	if (imax > nbdec)
		qj = min(q[imax],-1.0)
		nmin = min(nmin,nden[imax]*(massc[imax+1]/massc[imax])^qj)
	end
	for j=max(imin,nbdec+1):imax #780
		nden[j] = (c[j]/q[j])*((massb[j+1]/massb[j])^q[j] - 1.0)
	end #780
	#Check for output
	if (time >= tnext)
		ntot = 0.0
		mtot = 0.0
		m2tot = 0.0
		for i = nbin:-1:imin #800
			ntot += nden[i]
			mtot += mden[i]
		end #800
		ntot2 = 0.0
		for i=imax:-1:imin #820
			if i > nbdec
				ntot2 += (c[i]/q[i])*((massb[i+1]/massb[i])^q[i]-1.0)
			else
				ntot2 += nden[i]
			end
		end #820
		@printf(f,"\nTime = %14.6f, N=%14.6f, M=%14.6f, M2=%14.6f\nN=%14.6f\n",time,ntot,mtot,m2tot,ntot2)
		j = min(imax+2,nbin)
		nitmps = Array(Float64,length(imin:j),1)
		ind = 1
		for i = imin:j #900
			if (i > nbdec) && (i <= imax)
				nitmp = (c[i]/massb[i])*(massc[i]/massb[i])^(q[i]-1)
			else
				nitmp = nden[i]/delm[i]
			end
			nitmps[ind] = nitmp*massc[i]^2
			ind+=1
			@printf(f,"%14.6f %14.6f %14.6f %14.6f\n",massc[i],nitmp,mden[i],nitmp*massc[i]^2)
		end #900
		#@bp
		plot(log(massc[imin:j]),log(nitmps),linestyle=":")
		nal10 = analyticA1log(time,log(massc[imin:j]))
		plot(log(massc[imin:j]),nal10,linestyle="--")	
		tnext += tprint
	end
	step+=1
end
println(step)
close(f)
end

function analyticA1log(t,lms)
	nt = zeros(size(lms))
	for i = 1:length(nt)
		nt[i] = 2*lms[i] + (exp(lms[i])-1)*log(t/(t+2))+log(4/(t+2)^2)
	end
	return nt
end
#main(
#main(ndec,nbdec,nbin,nbin1,imin,imax,iminold,imaxold,time,dt,dt2,tmax,tprint,tnext,dmmax,dlogm,mmerge,rateav,nmin,dmfrac,dm,lossmx,ntot,ntot2,mtot,m2tot,massb,massc,delm,dlnm,mmax,mass,mden,mtmp,gain,loss,c,q,nden,rho,qj,qjp1,njmhalf,njphalf,njtmp,nitmp,w1,w2,ratio)
