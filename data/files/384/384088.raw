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

function calculateU(t, w,wdot, p)
	#p is for passing in parameters
	deltaX = p[1]
	deltaY = p[2]
	deltaZ = p[3]
	currU = p[4]
	currV = p[5]
	currP = p[6]
	currX = p[7]
	currY = p[8]
	deltaR = sqrt(deltaX^2 + deltaY^2)
	R = sqrt(currX^2+currY^2)
	

	rho = 1.05 #g/cm^3, given by GENERALIZED APPROACH TO THE MODELING OF A R T E R I A L BLOOD FLOW
	gammaDot = calculateGammaDot(currU, currV, deltaZ, deltaR, R)
	mu = calculateMu(gammaDot)

	tauRR = -2*mu*currV/deltaR
	tauZZ = -2*mu*currU/deltaZ
	tauRZ = -1*mu*(currU/deltaR + currV/deltaZ)
	dudt = -1*(currV*deltaR*currU+currU*deltaZ*currU) -1/rho*deltaZ*currP -1/rho*(1/R*deltaR*(R*tauRZ)*deltaZ*tauZZ)

	wdot = [dudt]

	return wdot
end

function calculateV(currU, currV, currX, currY, deltaZ, deltaX, deltaY)
	#println("In calculateV")	
	R = sqrt(currX^2+currY^2)
	println(R)
	#println("delta X is")
	#println(deltaX)
	#println("delta Y is")
	#println(deltaY)
	deltaR = sqrt(deltaX^2+deltaY^2)
	#println(deltaR)
	if(R == 0)
		v = 0
	else
		v = -1*R*(deltaR*currV+deltaZ*currU)
	end
	return v
end

function calculateP(currP, xcord, ycord, prevX, prevY, currV, currU, deltaZ)
	#may need to fix assigment as to what is i and i-1
	#println("in calculate P")
	currR = sqrt(xcord^2+ycord^2)
	prevR = sqrt(prevX^2+prevY^2)
	deltaR = abs(currR-prevR)

	#should figure out a way to pass these so they don't need to be caculated again
	rho = 1.05 #g/cm^3, given by GENERALIZED APPROACH TO THE MODELING OF A R T E R I A L BLOOD FLOW
	gammaDot = calculateGammaDot(currU, currV, deltaZ, deltaR, currR)
	mu = calculateMu(gammaDot)

	tauRR = -2*mu*currV/deltaR
	tauZZ = -2*mu*currU/deltaZ
	tauRZ = -1*mu*(currU/deltaR + currV/deltaZ)

	P = currP +(currR-prevR)*(-1*(currV*deltaR*currV+currU*deltaZ*currV)-1*(1/currR*deltaR*currR*tauRR+deltaZ*tauRZ)-rho*deltaZ*currV)
	#println("got here")
	return P
end

function calculateRwall(A, B, Pwall)
	Rwall = A+B*Pwall
end

function main()
	close("all")
	#println("In main")
	numPoints = 25
	grid = generateGrid(1,1,numPoints)
	#println(grid)
	#readline(STDIN)
	#print(length(grid))
	deltat = .1;
	deltaX = grid[1,2][1]-grid[1,1][1]
	deltaY = grid[2,1][2]-grid[1,1][2]
	deltaZ = .1
	
	tFinal = 10;
	zEnd = .4

	u0 = 1.0
	v0 = .01
	p0 = 1
	R0 = 1 #initial radius of blood vessel
	Rwall = R0;

	t0 = 0.0
	tsim = t0
	zSim = 0.0
	P0 = 1.0 #inital pressure
	allData = Array[[ceil(tFinal/deltat)],[ceil(tFinal/deltat)]] 
	#fill velocity vectors with initial conditions
	u = fill(u0, (numPoints, numPoints))
	v = fill(v0, (numPoints, numPoints))
	P = fill(P0, (numPoints, numPoints))
	avgP = 0;

	
	numRuns = 1
	#for iterative pressure calculations
	prevX = grid[1,1][1]
	prevY = grid[1,1][2]	
	
	closeMargin = .1 #for calculating wall pressure
	#while tsim < tFinal
	while zSim < zEnd
		wallcounter = 0 #for counting the number of points on the wall
		Ptot = 0 #for running sum of wall pressures
		for coords in grid
				xcord = coords[1]
				ycord = coords[2]
				(xindex, yindex) = lookupIndex(grid, xcord, ycord)
				#print("At indices")
				#println(sub2ind(grid, coords))
				inVessel = checkInside(xcord, ycord, Rwall)
				#velocities at present coordinates
				currU = u[xindex, yindex]
				currV = v[xindex, yindex]
				currP = P[xindex, yindex]
				initials = [currU]# v[xindex, yindex]]
				if(inVessel == 1)
					#inside blood vessel, actually calculate velocity profile
					println("At cordinates $xcord, $ycord")
					p = [deltaX, deltaY, deltaZ, u[xindex, yindex], v[xindex, yindex], currP, xcord, ycord]
					wrappedU(t,w,wdot) = calculateU(t,w,wdot, p)
					tspan = [t0:deltat/2:t0+deltat]
					#println(typeof(tspan)) #they're floats, like they should be

					#calculated the u velocities
					res = Sundials.cvode(wrappedU, initials, tspan)
					#print("here")
					#vAll = float([ a[1] for a in res])
					#uAll = float([ a[2] for a in res])
					
					uAll = res[:,1]
					#println(uAll[length(uAll)])
					#vAll = res[:,2]
					#get last elements (the ones at tf)
					u[xindex,yindex]= uAll[length(uAll)]
					currU = u[xindex,yindex]
					println("u is $currU at $xcord, $ycord")
					
					v[xindex, yindex]=calculateV(currU, currV, xcord, ycord, deltaZ, deltaX, deltaY)
					currV = v[xindex, yindex]					

					#calculate pressures
					#println(string("x index is ", xindex))
					if(xindex > 1)
						P[xindex-1, yindex]= calculateP(currP, xcord, ycord, prevX, prevY, currV, currU, deltaZ)
					end

					#if on the inside and close to the wall, use this point to calculate the pressure at the wall
					if(abs(sqrt(xcord^2+ycord^2)-Rwall)<=closeMargin)
						Ptot = Ptot+currP
						wallcounter = wallcounter+1
					end
					
					

				
				elseif(inVessel ==0)
				#outside of blood vessel, set velocities to zero
					#println("skipped")
					u[xindex, yindex]= 0
					v[xindex, yindex] = 0
				end
		prevX = xcord
		prevY = ycord	

		Pwall = Ptot/wallcounter
		Rwall = calculateRwall(R0, .01, Pwall)
		end
		
		#println(u)
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

