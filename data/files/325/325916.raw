using PyPlot
using Debug
function remove(item,array)
	tarray = trues(size(array));
	tarray[findin(array,item)] = false
	array = array[tarray]
end

function calcmerge(a,b,activebins,bins,t)
	bin1 = activebins[a]
	bin2 = activebins[b]
	if (a==b)
		bins[t+1,bin1] = bins[t,bin1] - bins[t,bin1]*(bins[t,bin2]/bin2)*A[bin1,bin2]*dt
		bins[t+1,bin1+bin2] = bins[t,bin1+bin2]+bins[t,bin1]*(bins[t,bin2]/bin2)*A[bin1,bin2]*dt
	else
		bins[t+1,bin1] -= bins[bin1]*(bins[bin2]/bin2)*A[bin1,bin2]*dt
		bins[bin2] -= bins[bin2]*(bins[bin1]/bin1)*A[bin1,bin2]*dt
		bins[bin1+bin2] += (bins[bin1]*(bins[bin2]/bin2)+bins[bin2]*(bins[bin1]/bin1))*A[bin1,bin2]*dt
	end
end

function main()
	tmax = 1000
	Nbins = 10
	Nmax = 126
	Nbd = 120
	dt = 0.1
	nmin = 10.0^(-30)
	n0s = zeros(1,Nmax)
	n0s[1] = 1.0
	dm = 0.01
	#bins is a tmax x Nmax matrix to keep track of the masses at each timestep
	bins = zeros(tmax,Nmax)
	bins[1,:] = n0s
	ts = zeros(tmax,1)
	function A(i,j)
		return 1
	end
	for t = 1:(tmax-1)
		#println(dt)
		#rk1(bins[t,:],Nbins,Nbd,dt,A,dm)
		#println("runs fine")
		println("t is ",t)
		(masschange,dt) = rk1(bins[t,:],Nbins,Nbd,dt,A,dm,t) #this is a vector of length Nmax
		#println(masschange)
		bins[t+1,:] = bins[t,:]+masschange
		
		for n = (Nbins+1):length(bins[t+1,:])
			if bins[t+1,n] > nmin
				Nbins = n
			end
		end
		if isComp(bins[t+1,Nbins],bins[t+1,Nbins+1])
			Nbins = Nbins+1
		end
		ts[t+1] = ts[t]+dt
	end
	println(ts)
	#println(bins)
	fig = figure("nconcs")
	ax = axes()
	cmax = 126
	for c=1:cmax
		plot(ts,bins[:,c]/c,linestyle=":")
		plot(ts,analytic(ts,1,c),linestyle="--")
	end
	fig = figure()
	ax = axes()
	b10 = bins[10,:]
	println(b10)
	m10 = zeros(length(b10))
	n10 = zeros(length(b10))
	for i=1:length(b10)
		
		m10[i] = mtilde(i,Nbd)
		#println(i)
		if (i <= Nbd)
			n10[i] = M(i,b10)/i
		else
			n10[i] = n(i,m10[i],b10,Nbd)
		end
	end
	#println(m10)
	#println(n10)
	plot(log(m10),log((m10.^2).*n10))
	b10 = bins[1000,:]
	println(length(b10))
	m10 = zeros(length(b10))
	n10 = zeros(length(b10))
	for i=1:length(b10)
		
		m10[i] = mtilde(i,Nbd)
		#println(i)
		if (i <= Nbd)
			n10[i] = M(i,b10)/i
		else
			n10[i] = n(i,m10[i],b10,Nbd)
		end
	end
	#println(m10)
	#println(n1)
	plot(log(m10),log((m10.^2).*n10))
	ax[:set_ylim]([-25,5])
	return (ts,bins)
end

function isComp(bin1,bin2)
	#currently returning a dummy
	return false
end

function analytic(ts,A,r)
	c = (4./(A*ts+2).^2).*((A*ts)./(A*ts+2)).^(r-1)
end



function rk1(binst,Nbins,Nbd,dt,A,dm,t)
	#function that performs a first-order pass to calculate the mass loss and gain of each bin from all combinations of bins i and j where i < Nbins and j < Nbins.  Also updates Nbins as more mass are added to higher-level bins
	
	Nmax = length(binst)
	masschange = zeros(1,Nmax)
	#println(masschange)i
	flag = false #hurr hurr hurr
	#println(!flag)
	while !flag
	#println("in flag")
	masschange = zeros(1,Nmax)
	for j = 1:Nbins
		for i = 1:j
			#merger depends on whether j is greater than or less than Nbd
			#println("(",i,",",j,")")	
			if (binst[i]>10.0^(-30))&&(binst[j]>10.0^(-30))
			if  (j <= Nbd)
				k = binplus(i,j,Nbd,length(binst))
				
				#println("k is ",binplus(i,j,Nbd,length(binst)))
				mi = M(i,binst)*N(j,binst,Nbd,mtilde(j-1/2,Nbd),mtilde(j+1/2,Nbd))*A(i,j)*dt
				mj = M(j,binst)*N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd))*A(i,j)*dt
				if (i==j)
					mi = mi/2
					mj = mj/2
				end
				masschange[i]-=mi
				masschange[j]-=mj
				#println("k is still ",k)
				#adjust dt to avoid negative mass or too fast flow of mass
				if (mi/M(i,binst) > dm)
					#println("dt1 ",dt)
					#println("mi ",mi)
					#println("M ",M(i,binst))
					#println("dm ",dm)
					dt = (dm*M(i,binst))/(mi/dt)
					#println("dt2 ",dt)
					break
				elseif (mj/M(j,binst) > dm)
					#println("dt1 ",dt)
					#println("mj ",mj)
					#println("M ",M(j,binst))
					#println("dm ",dm)
					dt = (dm*M(j,binst))/(mj/dt)
					#println("dt2 ",dt)
					break
				elseif (mi > M(i,binst))
					#println("dt1 ",dt)
					dt = M(i,binst)/(mi/dt)
					#println("dt2 ",dt)
					mi = M(i,binst)
					break
				elseif (mj > M(j,binst))
					#println("dt1 ",dt)
					dt = M(j,binst)/(mj/dt)
					#println("dt2 ",dt)
					mj = M(j,binst)
					break
				end
				#if t==241 && i==120 && j == 120
					#println("i ",i)
					#println("j ",j)
					
				#end	
					#println("k is now ",k)
					#test = (k > 0) && (k <= Nmax)
			
					
					#println("testing")
					#@bp
			
				#println(0<k<=Nmax)
				if (k > 0) && (k <= Nmax)
					#right now I'm just bleeding off into space/nothing when we get past the largest bin
					masschange[k]+=mi+mj
				end
				#println(masschange)	
				
			else
				#merger can be added to one bin or spread between two bins
				#k = binplus(mtilde(i,Nbd),mtilde(j,Nbd),Nbd,length(binst))
				kmin = binplus(mtilde(i,Nbd),mtilde(j-1/2,Nbd),Nbd,length(binst))
				kmax = binplus(mtilde(i,Nbd),mtilde(j+1/2,Nbd),Nbd,length(binst))
				if kmin==kmax
					# okay, it's a little unclear what they're using for Aijbar--let's try using a weighted average everywhere, and if that totally fails, we'll go back and reprogram as an integral
					mi = M(i,binst)*N(j,binst,Nbd,mtilde(j-1/2,Nbd),mtilde(j+1/2,Nbd))*Abar(i,j,binst,Nbd,A)*dt
					mj = M(j,binst)*N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd))*Abar(i,j,binst,Nbd,A)*dt
					if (i==j)
						mi=mi/2
						mj=mj/2
					end
				if (mi/M(i,binst) > dm)
					#println("dt1 ",dt)
					#println("mi ",mi)
					#println("M ",M(i,binst))
					#println("dm ",dm)
					dt = (dm*M(i,binst))/(mi/dt)
					#println("dt2 ",dt)
					break
				elseif (mj/M(j,binst) > dm)
					#println("dt1 ",dt)
					#println("mj ",mj)
					#println("M ",M(j,binst))
					#println("dm ",dm)
					dt = (dm*M(j,binst))/(mj/dt)
					#println("dt2 ",dt)
					break
				elseif (mi > M(i,binst))
					#println("dt1 ",dt)
					dt = M(i,binst)/(mi/dt)
					#println("dt2 ",dt)
					mi = M(i,binst)
					break
				elseif (mj > M(j,binst))
					#println("dt1 ",dt)
					dt = M(j,binst)/(mj/dt)
					#println("dt2 ",dt)
					mj = M(j,binst)
					break
				end
					masschange[i]-=mi
					masschange[j]-=mj
					if (kmin>0)&&(kmin <= Nmax)
						masschange[kmin]+=mi+mj
					end
				else
					mp = mtilde(kmin+1/2,Nbd)-mtilde(i,Nbd)
					Mlt = M(j,binst,Nbd,mtilde(j-1/2,Nbd),mp)
					Mgt = M(j,binst)-Mlt
					Nlt = M(j,binst,Nbd,mtilde(j-1/2,Nbd),mp)
					Ngt = N(j,binst,Nbd,mp,mtilde(j+1/2,Nbd))
					Ablt = Abarlt(i,j,binst,Nbd,A,mp)
					Abmt = Abarmt(i,j,binst,Nbd,A,mp)
					mi = (M(i,binst)*Nlt*Ablt+M(i,binst)*Ngt*Abmt)*dt
					mj = (N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd))*Mlt*Ablt+N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd))*Mgt*Abmt)*dt
					
					mk = (M(i,binst)*Nlt+N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd))*Mlt)*Ablt*dt
					mk1 = (M(i,binst)*Ngt+N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd))*Mgt)*Abmt*dt
					if (i==j)
						mi = mi/2
						mj = mj/2
						mk = mk/2
						mk1 = mk1/2
					end		
					masschange[i]-=mi
				if (mi/M(i,binst) > dm)
					#println("dt1 ",dt)
					#println("mi ",mi)
					#println("M ",M(i,binst))
					#println("dm ",dm)
					dt = (dm*M(i,binst))/(mi/dt)
					#println("dt2 ",dt)
					break
				elseif (mj/M(j,binst) > dm)
					#println("dt1 ",dt)
					#println("mj ",mj)
					#println("M ",M(j,binst))
					#println("dm ",dm)
					dt = (dm*M(j,binst))/(mj/dt)
					#println("dt2 ",dt)
					break
				elseif (mi > M(i,binst))
					#println("dt1 ",dt)
					dt = M(i,binst)/(mi/dt)
					#println("dt2 ",dt)
					mi = M(i,binst)
					break
				elseif (mj > M(j,binst))
					#println("dt1 ",dt)
					dt = M(j,binst)/(mj/dt)
					#println("dt2 ",dt)
					mj = M(j,binst)
					break
				end
					masschange[j]-=mj
					println("made it here")
					if (kmin>0) && (kmin <= Nmax)
						masschange[kmin]+=mk
					end
					if (kmin+1 > 0) && (kmin+1 <= Nmax)
						masschange[kmin+1]+=mk1
					end
				end	
				#println("Under construction")
				return -1	
			end
			end
		end
	end
	flag = true
	#println(masschange)
	end
	#println(dt)
	#println(masschange)
	#println(size(masschange))
	return (masschange,dt)
end

function binplus(i,j,Nbd,Nmax)
	#function that returns the bin containing mk = mi+mj
	if (i+j) <= Nbd
		return i+j
	else
		k10 = 10^(1/Nbd)
		for b = Nmax:-1:(Nbd+1)
			lower = (k10^(b-Nbd-1))*(Nbd+1/2)
			if (i+j) > lower
				return b
			end	
		end
	end
	return -1	
end

function edges(Nmax,Nbd)
	#get back bin edges, lin/log spacing
	b = Array(Float64,Nmax+1)
	b[1:Nbd+1] = 0.5:(Nbd+0.5)
	for j = Nbd+2:Nmax+1
		b[j] = b[j-1]*10^(1/Nbd)
	end
	return b
end

function mtilde(k::Int,Nbd)
	#get back the average mass of a single aggregate in the bin
	c10 = 10^(1/Nbd)
	k = float(k)
	if k <= Nbd
		m = k
	else
		c = k - Nbd
		m = ((c10^(c-1))*(Nbd+1/2)+(c10^c)*(Nbd+1/2))/2
	end
	return m
end

function mtilde(k::Float64,Nbd)
	#get back the edge of a bin
	c10 = 10^(1/Nbd)
	if k <= (Nbd+1/2)
		m = k
	else
		c = k - (Nbd+1/2)
		m = (c10^c)*(Nbd+1/2)
	end

	return m
end

function dmtilde(k,Nbd)
	#get back kth bin width
	c10 = 10^(1/Nbd)
	if k <= Nbd
		dm = 1
	else
		c = k - Nbd
		dm = (c10^c)*(Nbd+1/2)-(c10^(c-1))*(Nbd+1/2)
	end	
	return dm
end

function M(k,bins)
	#wrapper function to make it clearer what the code is doing.  Simply returns the total mass in the kth bin
	return bins[k]
end

function M(k,bins,Nbd,ma,mb)
	#function that returns mass in bin k between ma and mb
	qk = q(k,bins,Nbd)	
	return M(k,bins)*(mb^(qk+1)-ma^(qk+1))/(mtilde(k+1/2,Nbd)^(qk+1)-mtilde(k-1/2,Nbd)^(qk+1))
end

function rho(k,m,bins,Nbd)
	#returns the mass distribution based on a power law for the kth bin
	if k >= length(bins)
	rhok = 0
	else
	qk = q(k,bins,Nbd)
	rhok = (M(k,bins)*(qk+1)*m^qk)/(mtilde(k+1/2,Nbd)^(qk+1)-mtilde(k-1/2,Nbd)^(qk+1))
	end
	return rhok
end

function n(k,m,bins,Nbd)
	#returns number distribution which is just mass distribution/mass
	return rho(k,m,bins,Nbd)/m
end

function q(k,bins,Nbd)
	#q as defined in the Lee paper
	Nmax = length(bins)
	if k==Nmax
		return -Inf
	else
		n = log((M(k+1,bins)/dmtilde(k+1,Nbd))/(M(k-1,bins)/dmtilde(k-1,Nbd)))
		d = log(mtilde(k+1,Nbd)/mtilde(k-1,Nbd))
		return n/d
	end
end

function N(k,bins,Nbd,ma,mb)
	#return total number of particles in kth bin with mass between ma and mb
	#for total number overall use mk-1/2 and mk+1/2
	if k <= Nbd
		Np =  M(k,bins)/mtilde(k,Nbd)
	else
		qk = q(k,bins,Nbd)
		Np = M(k,bins)*(1+1/qk)*(ma^qk-mb^qk)/(mtilde(k+1/2,Nbd)^(qk+1)-mtilde(k-1/2,Nbd)^(qk+1))
	end
	return Np
end

function Abar(i,j,bins,Nbd,A)
	#returns the approximate Abarij as defined in the Lee paper (weighted average of Ami,mj-1/2 and Ami,mj+1/2)
	#assumes A is a function of two numbers
	numa = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd)*A(mtilde(i,Nbd),mtilde(j-1/2,Nbd))
	numb = (mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd)*A(mtilde(i,Nbd),mtilde(j+1/2,Nbd))
	denom = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd)+(mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd)
	return (numa+numb)/denom
end

function Abarlt(i,j,bins,Nbd,A,mp)
	#returns the approx. Abarltij, assuming a weighted average of Aij's
	numa = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd)*A(mtilde(i,Nbd),mtilde(j-1/2,Nbd))
	numb = (mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd)*A(mtilde(i,Nbd),mp)
	denom = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd)+(mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd)
	return (numa+numb)/denom
end

function Abarmt(i,j,bins,Nbd,A,mp)
	#returns the approx. Abarmtij, assuming a weighted average of Aij's
	numa = (mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd)*A(mtilde(i,Nbd),mp)
	numb = (mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd)*A(mtilde(i,Nbd),mtilde(j+1/2,Nbd))
	denom = (mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd)+(mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd)	
	return (numa+numb)/denom
end

#main()
