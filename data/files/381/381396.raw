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

@debug function main()
	tmax = 2400
	Nbins = 10
	Nmax = 800
	Nbd = 40
	dt = 0.5
	nmin = 10.0^(-30)
	n0s = zeros(1,Nmax)
	n0s[1] = 1.0
	dm = 0.01
	#bins is a Nmax x tmax matrix to keep track of the masses at each timestep
	bins = zeros(Nmax,tmax)
	bins[:,1] = n0s
	ts = zeros(tmax,1)
	function A(i,j)
		return (i+j)
	end
	for t = 1:(tmax-1)
		(masschange,dt) = rk1(transpose(bins[:,t]),Nbins,Nbd,dt,A,dm,t,nmin) #this is a vector of length Nmax
		bins[:,t+1] = bins[:,t]+masschange
		
		for n = (Nbins+1):length(bins[:,t+1])
			if bins[n,t+1] > nmin
				Nbins = n
			end
		end
		if isComp(bins[Nbins,t+1],bins[Nbins+1,t+1])
			Nbins = Nbins+1
		end
		ts[t+1] = ts[t]+dt
	end
	fig = figure("nconcs")
	ax = axes()
	cmax = 126
	for ci=1:cmax
		#println(bins[c,:]/c)
		#@bp
		y = transpose(bins[ci,:])	
		#y = bins[ci,:]
		plot(ts,y/ci,linestyle=":")
		plot(ts,analyticp(ts,1,ci),linestyle="--")
	end
	fig = figure()
	ax = axes()
	plotM(10,ts,bins,nmin,Nbd,ax)
	plotM(100,ts,bins,nmin,Nbd,ax)
	plotM(1000,ts,bins,nmin,Nbd,ax)
	plotM(2000,ts,bins,nmin,Nbd,ax)
	return (ts,bins)
end

function plotM(t,ts,bins,nmin,Nbd,ax)

	b10 = bins[:,t]
	for i = 1:length(b10)
		if abs(b10[i]) < nmin
			b10[i] = 0.0
		end
	end
	m10 = zeros(length(b10))
	n10 = zeros(length(b10))
	for i=1:length(b10)
		
		m10[i] = mtilde(i,Nbd)
		if (i <= Nbd)
			n10[i] = M(i,b10)/i
		else
			n10[i] = n(i,m10[i],b10,Nbd,nmin)
		end
	end
	plot(log(m10),log((m10.^2).*n10),linestyle=":")
	#println(m10[1:10])
	#println(n10[1:10])
	nal10 = analyticAplog(ts[t],log(m10))
	plot(log(m10),nal10,linestyle="--")
	ax[:set_xlim]([0,6])
	ax[:set_ylim]([-25,5])
end

function isComp(bin1,bin2)
	#currently returning a dummy
	return false
end

function analytic(ts,A,r)
	c = zeros(size(ts))
	for i = 1:length(c)
		tsi = ts[i]
		c[i] = (4/(A*tsi+2)^2)*((A*tsi)/(A*tsi+2))^(r-1)
	end
	return c
end

function analyticp(ts,A,r)
	c = zeros(size(ts))
	for i = 1:length(c)
		c[i] = exp(-1*ts[i])*B(1-exp(-1*ts[i]),r)
	end
	return c
end

function B(l,m)
	b = ((m*l)^(m-1))*exp(-m*l)/factorial(float(m))
	return b
end

function analyticA1(t,ms)
	nt = zeros(size(ms))
	for i = 1:length(nt)
		nt[i] = ((1+t/2)^(-2))*(t/(2+t))^(ms[i]-1)
	end
	return nt
end

function analyticA1log(t,lms)
	nt = zeros(size(lms))
	for i = 1:length(nt)
		nt[i] = 2*lms[i]+(exp(lms[i])-1)*log(t/(t+2))+log(4/(t+2)^2)
	end	
	return nt

end

function analyticAplog(t,lms)
	nt = zeros(size(lms))
	for i = 1:length(nt)
		x = lms[i]
		nt[i] = 2*x -t + (exp(x)-1)*log(1-exp(-t))+(exp(x)-1)*x - exp(x)*(1-exp(-t))-log(factorial(exp(x)))
	end
	return nt
end	

function rk2(binst,Nbins,Nbd,dt,A,dm,t,nmin)
	#function that performs second-order RK to calculate mass loss & gain of each bin from all combinations of bins i and j
	println("under construction")
end

function rk1(binst,Nbins,Nbd,dt,A,dm,t,nmin)
	#function that performs a first-order pass to calculate the mass loss and gain of each bin from all combinations of bins i and j where i < Nbins and j < Nbins.  Also updates Nbins as more mass are added to higher-level bins
	Nmax = length(binst)
	masschange = zeros(Nmax,1)
	flag = false #hurr hurr hurr
	at = -1
	while at!=dt
	masschange = zeros(Nmax,1)
	if at != -1
		dt = at
	else
		at = dt
	end
	for j = 1:Nbins
		if dt!=at
			break
		end
		for i = 1:j
			
			#merger depends on whether j is greater than or less than Nbd
			if (binst[i]>nmin)&&(binst[j]>nmin)
				if  (j <= Nbd)
					k = binplus(i,j,Nbd,length(binst))
					try
					mi = M(i,binst)*N(j,binst,Nbd,mtilde(j-1/2,Nbd),mtilde(j+1/2,Nbd),nmin)*A(i,j)*dt
					catch
							println("t ",t)
							println("i ",i)
							println("j ",j)

					end
					mj = M(j,binst)*N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd),nmin)*A(i,j)*dt
					if (i==j)
						try
						mi = mi/2
						catch 
							println("t ",t)
							println("i ",i)
							println("j ",j)
						end
						mj = mj/2
					end
					#adjust timestep to correct for too-fast flow of mass
					at = adjustT(mi,mj,dm,M(i,binst),M(j,binst),dt,nmin)
					if at != -1
						break
					else
						at = dt
					end
					try
					masschange[i]-=mi
					catch
							println("t ",t)
							println("i ",i)
							println("j ",j)
					end
					masschange[j]-=mj
					if (k > 0) && (k <= Nmax)
						#right now I'm just bleeding off into space/nothing when we get past the largest bin
						masschange[k]+=mi+mj
					end
				
				else
					#merger can be added to one bin or spread between two bins
					kmin = binplus(mtilde(i,Nbd),mtilde(j-1/2,Nbd),Nbd,length(binst))
					kmax = binplus(mtilde(i,Nbd),mtilde(j+1/2,Nbd),Nbd,length(binst))
					if kmin==kmax
						# okay, it's a little unclear what they're using for Aijbar--let's try using a weighted average everywhere, and if that totally fails, we'll go back and reprogram as an integral
						Abar = Abarm(i,j,mtilde(j-1/2,Nbd),mtilde(j+1/2,Nbd),1,1,0,binst,nmin,Nbd)
						mi = M(i,binst)*N(j,binst,Nbd,mtilde(j-1/2,Nbd),mtilde(j+1/2,Nbd),nmin)*Abar#*Abar(i,j,binst,Nbd,A,nmin)*dt
						mj = M(j,binst)*N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd),nmin)*Abar#*Abar(i,j,binst,Nbd,A,nmin)*dt
						if (i==j)
							mi=mi/2
							mj=mj/2
						end
						at = adjustT(mi,mj,dm,M(i,binst),M(j,binst),dt,nmin)
						if at != -1
							break
						else
							at = dt
						end
						masschange[i]-=mi
						masschange[j]-=mj
						if (kmin>0)&&(kmin <= Nmax)
							masschange[kmin]+=mi+mj
						end
					else
						mp = mtilde(kmin+1/2,Nbd)-mtilde(i,Nbd)
						Mlt = M(j,binst,Nbd,mtilde(j-1/2,Nbd),mp,nmin)
						Mgt = M(j,binst)-Mlt
						Nlt = M(j,binst,Nbd,mtilde(j-1/2,Nbd),mp,nmin)
						Ngt = N(j,binst,Nbd,mp,mtilde(j+1/2,Nbd),nmin)
						Ablt = Abarm(i,j,mtilde(j-1/2,Nbd),mp,1,1,0,binst,nmin,Nbd)
						Abmt = Abarm(i,j,mp,mtilde(j+1/2,Nbd),1,1,0,binst,nmin,Nbd)
						mi = (M(i,binst)*Nlt*Ablt+M(i,binst)*Ngt*Abmt)*dt
						mj = (N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd),nmin)*Mlt*Ablt+N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd),nmin)*Mgt*Abmt)*dt
						at = adjustT(mi,mj,dm,M(i,binst),M(j,binst),dt,nmin)
						if at != -1
							break
						else
							at = dt
						end
						mk = (M(i,binst)*Nlt+N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd),nmin)*Mlt)*Ablt*dt
						mk1 = (M(i,binst)*Ngt+N(i,binst,Nbd,mtilde(i-1/2,Nbd),mtilde(i+1/2,Nbd),nmin)*Mgt)*Abmt*dt
						if (i==j)
							mi = mi/2
							mj = mj/2
							mk = mk/2
							mk1 = mk1/2
						end		
						masschange[i]-=mi
						masschange[j]-=mj
						if (kmin>0) && (kmin <= Nmax)
							masschange[kmin]+=mk
						end
						if (kmin+1 > 0) && (kmin+1 <= Nmax)
							masschange[kmin+1]+=mk1
						end
					end	
				end
			end
			if (in(true,isnan(masschange)))
				println("t ",t)
				println("i ",i)
				println("j ",j)
				println(masschange)
			end
		end
	end
	end
	return (masschange,dt)
end

function adjustT(mi,mj,dm,Mi,Mj,dt,nmin)
	#function that determines if mass is flowing too quickly and returns what dt should be if it is
	if (mi > Mi) && (Mi <= nmin)
		#if we can remove all the necessary mass in one step, then do so
		dt = Mi/(mi/dt)
	elseif (mj > Mj) && (Mj <= nmin)
		dt = Mj/(mj/dt)
	elseif (mi/Mi > dm)
		dt = (dm*Mi)/(mi/dt)
	elseif (mj/Mj > dm)
		dt = (dm*Mj)/(mj/dt)
	else
		dt = -1
	end	

end

function binplus(i,j,Nbd,Nmax)
	#function that returns the bin containing mk = mi+mj
	if (i+j) <= Nbd
		return i+j
	else
		k10 = 10^(1/Nbd)
		highest = (k10^(Nmax-Nbd))*(Nbd+1/2)
		if (i+j) > highest
			return -1
		end
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

function M(k,bins,Nbd,ma,mb,nmin)
	#function that returns mass in bin k between ma and mb
	qk = q(k,bins,Nbd,nmin)	
	return M(k,bins)*(mb^(qk+1)-ma^(qk+1))/(mtilde(k+1/2,Nbd)^(qk+1)-mtilde(k-1/2,Nbd)^(qk+1))
end

function rho(k,m,bins,Nbd,nmin)
	#returns the mass distribution based on a power law for the kth bin
	
		qk = q(k,bins,Nbd,nmin)
	if qk == -Inf
		rhok = 0
	elseif M(k,bins) == 0
		rhok = 0
		
	else
		rhok = (M(k,bins)*(qk+1)*m^qk)/(mtilde(k+1/2,Nbd)^(qk+1)-mtilde(k-1/2,Nbd)^(qk+1))
	end
	return rhok
end

function n(k,m,bins,Nbd,nmin)
	#returns number distribution which is just mass distribution/mass
	return rho(k,m,bins,Nbd,nmin)/m
end

function q(k,bins,Nbd,nmin)
	#q as defined in the Lee paper
	#approximations made at the end
	Nmax = length(bins)
	if k == Nmax
		n = log(nmin/dmtilde(k+1,Nbd)/(M(k-1,bins)/dmtilde(k-1,Nbd)))
		d = log(mtilde(k+1,Nbd)/mtilde(k-1,Nbd))
	else
		n = log((M(k+1,bins)/dmtilde(k+1,Nbd))/(M(k-1,bins)/dmtilde(k-1,Nbd)))
		d = log(mtilde(k+1,Nbd)/mtilde(k-1,Nbd))
		return n/d
	end
end

function N(k,bins,Nbd,ma,mb,nmin)
	#return total number of particles in kth bin with mass between ma and mb
	#for total number overall use mk-1/2 and mk+1/2
	if k <= Nbd
		Np =  M(k,bins)/mtilde(k,Nbd)
	elseif k==length(bins)
		Np = 0
	else
		qk = q(k,bins,Nbd,nmin)
		Np = M(k,bins)*(1+1/qk)*(ma^qk-mb^qk)/(mtilde(k+1/2,Nbd)^(qk+1)-mtilde(k-1/2,Nbd)^(qk+1))
	end
	return Np
end

function Abar(i,j,bins,Nbd,A,nmin)
	#returns the approximate Abarij as defined in the Lee paper (weighted average of Ami,mj-1/2 and Ami,mj+1/2)
	#assumes A is a function of two numbers
	numa = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd,nmin)*A(mtilde(i,Nbd),mtilde(j-1/2,Nbd))
	numb = (mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd,nmin)*A(mtilde(i,Nbd),mtilde(j+1/2,Nbd))
	denom = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd,nmin)+(mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd,nmin)
	return (numa+numb)/denom
end

function Abarlt(i,j,bins,Nbd,A,mp,nmin)
	#returns the approx. Abarltij, assuming a weighted average of Aij's
	numa = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd,nmin)*A(mtilde(i,Nbd),mtilde(j-1/2,Nbd))
	numb = (mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd,nmin)*A(mtilde(i,Nbd),mp)
	denom = (mtilde(i,Nbd)+mtilde(j-1/2,Nbd))*n(j,mtilde(j-1/2,Nbd),bins,Nbd,nmin)+(mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd,nmin)
	return (numa+numb)/denom
end

function Abarmt(i,j,bins,Nbd,A,mp,nmin)
	#returns the approx. Abarmtij, assuming a weighted average of Aij's
	numa = (mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd,nmin)*A(mtilde(i,Nbd),mp)
	numb = (mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd,nmin)*A(mtilde(i,Nbd),mtilde(j+1/2,Nbd))
	denom = (mtilde(i,Nbd)+mp)*n(j,mp,bins,Nbd,nmin)+(mtilde(i,Nbd)+mtilde(j+1/2,Nbd))*n(j,mtilde(j+1/2,Nbd),bins,Nbd,nmin)	
	return (numa+numb)/denom
end

function Abarm(i,j,ma,mb,ca,mu,nu,bins,nmin,Nbd)
	#integral for Abar or Abar< or Abar> assuming Aij = ca(i^mu j^nu + i^nu j^mu)
	qj = q(j,bins,Nbd,nmin)
	mi = mtilde(i,Nbd)
	t1 = (mi^(mu+1))*(mb^(qj+nu)-ma^(qj+nu))/(qj+nu)
	t2 = (mi^(nu+1))*(mb^(qj+mu)-ma^(qj+mu))/(qj+mu)
	t3 = (mi^mu)*(mb^(qj+nu+1)-ma^(qj+nu+1))/(qj+nu+1)
	t4 = (mi^nu)*(mb^(qj+mu+1)-ma^(qj+mu+1))/(qj+mu+1)
	d1 = (mi/qj)*(mb^qj-ma^qj)
	d2 = (mb^(qj+1)-ma^(qj+1))/(qj+1)
	A = ca*(t1+t2+t3+t4)/(d1+d2)
	return A
end

#main()
