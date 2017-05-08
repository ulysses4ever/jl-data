using Sundials
using PyPlot

function generateGrid(xmax, ymax, numPoints)
	x = linspace(0.0, xmax, numPoints)
	y = linspace(0.0, ymax, numPoints)
	#z = linspace(0, zmax, numPoints)
	grid = Array{Array}(numPoints, numPoints) #create an array of arrays thats numpoints by numpoints
	count = 1
	for i = 1:length(x)
		for j = 1:length(y)
			#for k = 1:length(z)
				#println("cords are $x[$i], $y[$j],  $z[$k]")
				
				grid[i,j] = [x[i], y[j]]
			#end
		end
	end	

	return grid
end

function calculateGammaDot(u, v, deltaZ, deltaR, r)
	gammaDot = sqrt((v/deltaR)^2 +(v/r)^2 + (u/deltaZ)^2 + (u/deltaZ+u*deltaR)^2)
	return gammaDot
end

function calculateMu(gammaDot)
	#using Carreau model 
	#from http://www.ncbi.nlm.nih.gov/pmc/articles/PMC1552100/

	mu0 = .056 #Pa s
	lambda = 3.313 # s
	n = .2568
	
	mu = mu0+2*mu0*(1+(lambda*gammaDot)^2)^(n-1)/2
	return mu
end

function momentum(t, w, wdot, p)
	#deltaX, deltaY, deltaZ, x, y
	#p is for passing in parameters
	deltaX = p[1]
	deltaY = p[2]
	deltaZ = p[3]
	x = p[4]
	y = p[5]
	tsim = p[6]

	v = w[1]
	u = w[2]

	P = calculatePressure(tsim, 1, 1) #need to actually deal with this later
	rho = 1.05 #g/cm^3, given by GENERALIZED APPROACH TO THE MODELING OF A R T E R I A L BLOOD FLOW

	deltaR = sqrt(deltaX^2 + deltaY^2)
	r = sqrt(x^2+y^2)
	gammaDot = calculateGammaDot(u, v, deltaZ, deltaR, r)
	mu = calculateMu(gammaDot)

	tauRR = -2*mu*v/deltaR
	tauZZ = -2*mu*u/deltaZ
	tauRZ = -1*mu*(u/deltaR + v/deltaZ)
	

	dvdt = -1*(u*v/deltaZ+v*v/deltaR)-1/rho*P/deltaR - 1/rho*(1/r*1/deltaR*(r*tauRR)+1/deltaZ*tauRZ)
	dudt = -1*(v*u/deltaR+u*u/deltaZ)-1/rho*P/deltaZ - 1/rho*(1/r*1/deltaR*(r*tauRZ)-1/deltaZ*tauZZ)
	wdot = [dvdt, dudt]
	return wdot
end

function calculatePressure(t, A, B)
	# pressure is periodic, with constants A and B from a P vs t curve
	# omega is period of pressure-if assume heartrate of 120 bpm, omega =1/2 (in seconds) 
	omega = .5
	pressure = A*sin(omega*t)+B
	return pressure
end

function checkInside(x,y, R)
	#if inside, return 1, else 0
	if sqrt(x^2+y^2) < 1
		inside = 1
	else
		inside = 0
	end
	return inside
end

function CorrectIndex(num, numPoints)
		correctedIndex = mod(num, numPoints)
		if correctedIndex == 0
			correctedIndex = 1
		end
	return correctedIndex
end

function lookupIndex(grid, xcord, ycord)
	for j = 1:size(grid,1)
		for k = 1:size(grid,2)
			if(grid[j, k]==[xcord, ycord])
				return [j, k]
			end
		end
	end
end

function main()
	close("all")
	#println("In main")
	numPoints = 10
	grid = generateGrid(1,1,numPoints)
	#println(grid)
	#readline(STDIN)
	#print(length(grid))
	deltat = .1;
	deltaX = grid[1,1]-grid[1,2]
	deltaY = grid[2,1]-grid[2,2]
	deltaZ = .1
	
	tFinal = 10;
	zEnd = .4

	u0 = 1.0
	v0 = .01
	p0 = 1
	R0 = 1 #initial radius of blood vessel

	t0 = 0.0
	tsim = t0
	zSim = 0.0
	allData = Array[[ceil(tFinal/deltat)],[ceil(tFinal/deltat)]] 
	u = zeros(numPoints, numPoints)
	v = zeros(numPoints, numPoints)

	initials = [u0, v0]
	numRuns = 1

	#while tsim < tFinal
	while zSim < zEnd
		for coords in grid
			
				xcord = coords[1]
				ycord = coords[2]
				(xindex, yindex) = lookupIndex(grid, xcord, ycord)
				#print("At indices")
				#println(sub2ind(grid, coords))
				inVessel = checkInside(xcord, ycord, R0)
				if(inVessel == 1)
					#inside blood vessel, actually calculate velocity profile
					println("At cordinates $xcord, $ycord")
					p = [deltaX, deltaY, deltaZ, xcord, ycord, tsim]
					wrappedMomentum(t,w,wdot) = momentum(t,w,wdot, p)
					tspan = [t0:deltat/10:t0+deltat]
					#println(typeof(tspan)) #they're floats, like they should be
					res = Sundials.cvode(wrappedMomentum, initials, tspan)
					#print("here")
					#vAll = float([ a[1] for a in res])
					#uAll = float([ a[2] for a in res])
					
					uAll = res[:,1]
					#println(uAll[length(uAll)])
					vAll = res[:,2]
					#get last elements (the ones at tf)
					u[xindex,yindex]= uAll[length(uAll)]
					println("u is $u at $xcord, $ycord")
					v[xindex,yindex] = vAll[length(vAll)]
				elseif(inVessel ==0)
				#outside of blood vessel, set velocities to zero
					#println("skipped")
					u[xindex, yindex]= 0
					v[xindex, yindex] = 0
				end
			
		end
		println(u)
		#readline(STDIN)
#	allData[numRuns, 1] = u
#	allData[numRuns, 2] = v		
	#tsim = tsim+deltat
#	numRuns = numRuns +1
#	
	figure()
	pcolormesh(u)
	colorbar()
	title(string("z velocity at z= ", zSim ))

	figure()
	pcolormesh(v)
	colorbar()
	title(string("R velocity at z= ", zSim ))

	zSim = zSim+deltaZ
	end
#end
	
end

main()

