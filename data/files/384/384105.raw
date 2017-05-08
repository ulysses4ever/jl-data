using ODE
using PyPlot


function generateGrid(xmax, ymax, numPoints)
	x = linspace(-xmax, xmax, numPoints)
	y = linspace(-ymax, ymax, numPoints)
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
	gammaDot = sqrt((v/deltaR)^2 +(v/r)^2 + (u/deltaZ)^2 + (u/deltaZ+u/deltaR)^2)
	return gammaDot
end

function calculateMu(gammaDot)
	#using Carreau model 
	#from http://www.ncbi.nlm.nih.gov/pmc/articles/PMC1552100/

	mu0 = .56 #dyne/cm^2 s #.056 #Pa s
	muInf = .035 #dyne/cm^2 s #0.0035 #Pa s
	lambda = 3.313 # s
	n = .2568
	
	mu = mu0+(mu0-muInf)*(1+(lambda*gammaDot)^2)^(n-1)/2
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
	if sqrt(x^2+y^2) < R
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

function calculateU(t, w, p)
	#getting negative inifities for u, leads to Nans. Why?
	#p is for passing in parameters
	deltaX = p[1]
	deltaY = p[2]
	deltaZ = p[3]
	currU = p[4]
	currV = p[5]
	currP = p[6]
	currX = p[7]
	currY = p[8]
	#deltaR = sqrt(deltaX^2 + deltaY^2)
	deltaR = .1
	R = sqrt(currX^2+currY^2)


	rho = 1.05 #g/cm^3, given by GENERALIZED APPROACH TO THE MODELING OF A R T E R I A L BLOOD FLOW
	gammaDot = calculateGammaDot(currU, currV, deltaZ, deltaR, R)
	mu = calculateMu(gammaDot)

	tauRR =- 2*mu*currV/deltaR
	tauZZ = -2*mu*currU/deltaZ
	tauRZ = -1*mu*(currU/deltaR + currV/deltaZ)

	#println(string("delta X is", deltaX, "delta Y is", deltaY, "delta Z is ", deltaZ, "currU is ", currU, "currP is", currP, " currX is ", currX, "currY is", currY))
	#as given in paper
	#dudt = -1*(currV*deltaR*currU+currU*deltaZ*currU) -1/rho*deltaZ*currP -1/rho*(1/R*deltaR*(R*tauRZ)*deltaZ*tauZZ)
	#slightly modified to remove division by R, equivalent algebraically
	#dudt = -1*(currV*deltaR*currU+currU*deltaZ*currU) -1/rho*deltaZ*currP -1/rho*(deltaR*(tauRZ)*deltaZ*tauZZ)
	#println(string("dudt is", dudt))
	#as I think it should be written
	if(R == 0)
	#to prevent division by zero
		dudt = 0
	else
		#dudt = -1*(currV*1/deltaR*currU+currU*1/deltaZ*currU) -1/rho*1/deltaZ*currP +1/rho*(1/R*(R*tauRZ)/deltaR*1/deltaZ*tauZZ)
		dudt = -1*(currV*deltaR*currU+currU*deltaZ*currU) -1/rho*deltaZ*currP -1/rho*(1/R*deltaR*(R*tauRZ)*deltaZ*tauZZ)
	end

	if(dudt > 100)
		dudt = 100.0
	elseif(dudt< -100)
		dudt = -100.0
	end

	if(isnan(dudt) || isinf(dudt))
		println("dudt is Nan or inf")
		println(string("delta X is", deltaX, "delta Y is", deltaY, "delta Z is ", deltaZ, "currU is ", currU, "currP is", currP, " currX is ", currX, "currY is", currY))
		println(string("tauRR is", tauRR, "tauZZ is ", tauZZ, "tarRZ is ", tauRZ))
	elseif(dudt>1000)
		println(string("dudt is ", dudt))
		println(string("mu is", mu))
		println(string("delta X is", deltaX, "delta Y is", deltaY, "delta Z is ", deltaZ, "currU is ", currU, "currP is", currP, " currX is ", currX, "currY is", currY))
		println(string("tauRR is ", tauRR, " tauZZ is ", tauZZ, " tarRZ is ", tauRZ))
		println(string("-1*(currV*1/deltaR*currU+currU*1/deltaZ*currU) is ", -1*(currV*1/deltaR*currU+currU*1/deltaZ*currU)))	
		println(string("-1/rho*1/deltaZ*currP is ", -1/rho*1/deltaZ*currP ))
		println(string("1/rho*(1/R*(R*tauRZ)/deltaR*1/deltaZ*tauZZ) is "), 1/rho*(1/R*(tauRZ+R*tauRZ/deltaR)*1/deltaZ*tauZZ))
	
	end

	wdot = [dudt]
	println(string("dudt is ", dudt))

	return wdot
end

function calculateV(currU, currV, currX, currY, deltaZ, deltaX, deltaY)
	#println("In calculateV")	
	R = sqrt(currX^2+currY^2)
	#println(R)
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
#	if(currR == 0)
#		currR = .00001 #prevent division by zero
#	end

	prevR = sqrt(prevX^2+prevY^2)
	deltaR = abs(currR-prevR)
	if (deltaR == 0)
		deltaR = .000001 #prevent divison by zero
	end

	#should figure out a way to pass these so they don't need to be caculated again
	rho = 1.05 #g/cm^3, given by GENERALIZED APPROACH TO THE MODELING OF A R T E R I A L BLOOD FLOW
	gammaDot = calculateGammaDot(currU, currV, deltaZ, deltaR, currR)
	mu = calculateMu(gammaDot)

	tauRR = -2*mu*currV/deltaR
	tauZZ = -2*mu*currU/deltaZ
	tauRZ = -1*mu*(currU/deltaR + currV/deltaZ)

	#P = currP +(currR-prevR)*(-1*(currV*1/deltaR*currV+currU*1/deltaZ*currV)-1*(1/currR*1/deltaR*currR*tauRR+1/deltaZ*tauRZ)-rho*1/deltaZ*currV)
	P = currP +(currR-prevR)*(-1*(currV*1/deltaR*currV+currU*1/deltaZ*currV)-1*(tauRR+currR*tauRR/deltaR+1/deltaZ*tauRZ)-rho*1/deltaZ*currV)
	#absolute value may or may not be correct
	#P = (currP +(currR-prevR)*(-1*(currV*deltaR*currV+currU*deltaZ*currV)-1*(1/currR*deltaR*currR*tauRR+deltaZ*tauRZ)-rho*deltaZ*currV))
	#println("got here")

	if(isnan(P))
		println("In calculate P")
		println(string("delta Z is ", deltaZ, "currU is ", currU, "currP is", currP, " currX is ", xcord, "currY is", ycord))
		println(string("tauRR is ", tauRR, " tauZZ is ", tauZZ, " tarRZ is ", tauRZ))
		quit()
		
	end
	#force pressures to be positive
	if(P < 0)
		P = 0
	end

	return P
end

function calculateRwall(A, B, Pwall)
	Rwall = A+B*Pwall
	if(isnan(Rwall))
		
		println(string("R wall is a Nan A = ", A, " P wall = ", Pwall))
	end
	return Rwall
end

function drawBorder(Rwall, x)
	y = zeros(length(x))
	z = zeros(length(x))
	for(k = 1:length(x))
		y[k] = sqrt(abs(Rwall^2-x[k]^2))
		z[k] =-1*sqrt(abs(Rwall^2-x[k]^2))
	end
	PyPlot.hold(true)
	plot(x, y, "k")
	plot(x,z,"k")
end

function plotConstantX(historicData, zMax, deltaZ, yMax, deltaY, xMax, deltaX, deltat, path)
	zcords = [0:deltaZ:zMax;]
	ycords = [-yMax:deltaY:yMax;]
	xcords = [-xMax:deltaX:xMax;]
	t0 = 0.0
	t = 0.0
#	println("zcords")
#	println(size(zcords))
#	println("ycords")
#	println(size(ycords))

	uYZ = fill(-1.0, length(ycords), length(zcords))	
	vYZ = fill(-1.0,length(ycords), length(zcords))
	allU = Array{Array}(length(xcords),1)
	allV = Array{Array}(length(xcords),1)

	#println(string("uYZ is size", size(uYZ)))

	zcounter = 1
	timecounter = 1
	for timepoint in historicData
		#println("time point is")
		println(size(timepoint))
		#println("time counter is", timecounter)
		#zindex = 1
		for j = 1:length(zcords)-1
			zindex = j
			println(string("j is ", j))
			udata = timepoint[j,1] 
			vdata = timepoint[j,2]
			#println(string("size of u data is", size(udata)))
			for k = 1:size(udata,1)-1
				#for each slice of constant x
				desiredIndex = k 
				for n = 1:size(udata, 1)-1
					yindex = 1
					for m = 1:size(udata,2)-1
						#store the data at selected x
						if(n == desiredIndex)
							#println(string("at x index = ", desiredIndex, "at y index ", yindex, "at zindex", zindex))
							uYZ[yindex, zindex] = udata[k,m]
							vYZ[yindex, zindex] = vdata[k,m]
							yindex = yindex +1
							#println("uYZ is")
							#println(uYZ)
						end
					end
					allU[k] = uYZ
					allV[k]= vYZ
				end
				
			end
			
		end
			println(string("length of allU is", length(allU)))
			for q = 1:length(allU)
				println(string("q = ", q))
				currU = allU[q]
				currV = allV[q]
				figure()
				pcolormesh(zcords, ycords, currU)
				PyPlot.pcolor(zcords, ycords,currU, vmin = -1, vmax = 1)
				xlabel("Z")
				ylabel("Y")
				usefulString = string("Z velocity at t = ", t, "x = ", xcords[q])
				colorbar()
				title(usefulString)
				saveStringZ = (string("Z velocity at t = ", t, "x = ", xcords[q], ".png"))
				savefig(joinpath(path, saveStringZ))

				figure()
				pcolormesh(zcords, ycords, currV)
				PyPlot.pcolor(zcords, ycords,currV, vmin = -1, vmax = 1)
				xlabel("Z")
				ylabel("Y")
				usefulString2 = string("R velocity at t = ", t, "x = ", xcords[q])
				colorbar()
				title(usefulString2)
				saveStringR= (string("R velocity at t = ", t, "x = ", xcords[q], ".png"))
				savefig(joinpath(path, saveStringR))
				close("all")
			end
		t = t0+deltat
		timecounter = timecounter +1
	end
end

function plotPressure(x,y,P,Rwall,zSim, tsim, path)
	figure()
	PyPlot.hold(true)
	pcolormesh(x,y,P)
	#PyPlot.pcolor(x,y,P, vmin = 0, vmax = 3)
	colorbar()
	drawBorder(Rwall, x)
	title(string("Pressure at z= ", zSim, " t = ", tsim ))
	savestringP = string("Pressureatz=", zSim, "t", tsim, ".png")
	savefig(joinpath(path, savestringP))
end

function findCenter(R)
	xcord = R/2.0
	ycord =R/2.0
	centercords = [xcenter, ycenter]
	return centercords
end

function plotRvsT(zcords, radii, tsim, path)
	figure()
	plot(zcords, radii)
	xlabel("Z displacement")
	ylabel("Radius")
	title(string("Radius as a function of z at t = ", tsim))
	saveStringRvsT=(string("RadiiWRTZat t = ", tsim, ".png"))
	savefig(joinpath(path, saveStringRvsT))
end

function createSaveDir(dirName)
	mkdir(dirName)
end

function main()
	close("all")
	presentTime = string(now())
	mkdir(presentTime) #create directory with datetime
	path = joinpath("/home/rachel/Documents/RachelLeCover_Repository/", presentTime)
	#println("In main")
	numPoints =50
	xmax = 1
	ymax = 1
	grid = generateGrid(xmax,ymax,numPoints)
	#println(grid)
	#readline(STDIN)
	#print(length(grid))
	deltat = .1;
	deltaX = grid[2,1][1]-grid[1,1][1]
	deltaY = grid[1,2][2]-grid[1,1][2]
	deltaZ = .1
	
	tFinal = .5;
	zEnd = .7
	
	#actual blood velocities between 66-12 cm/sec, depending on location in body
	#from http://circ.ahajournals.org/content/40/5/603
	u0 = Float64(50.0) #from Methods in the analysis of the effects of gravity..., flow rate is .5m/s, through aeorta,  now divided by number of vessels
	v0 = Float64(.01)
	
	R0 = 1.0 #initial radius of blood vessel, in cm
	Rwall = R0;

	t0 = 0.0
	tsim = t0
	zSim = 0.0
	#according to wolfram alpha, average systolic blood pressure is 90-171 mmHg and diastolic is 40-95 mmHg, corresponding to 133322 barnes = dyne/cm^2
	#P0 = 133322.0 #inital pressure, in dyne/cm^2
	#run into problems when pressure greater than 1000 dyne/cm^2
	P0 = Float64(1000.0)
	maxP = 2*P0

	#fill velocity vectors with initial conditions
	u = fill(u0, (numPoints, numPoints))
	v = fill(v0, (numPoints, numPoints))
	P = fill(P0, (numPoints, numPoints))
	avgP = 0;

	
	numRuns = 1
	#for iterative pressure calculations
	prevX = grid[1,1][1]
	prevY = grid[1,1][2]	

	#for storing velocity data
	velocityData = Array{Array}(Integer(ceil(zEnd/deltaZ)),2)
	#maybe plus one?
	
	#for storing data with respect to time
	historicData = Array{Array}(1, Integer(ceil(tFinal/deltat)))
	closeMargin = .01 #for calculating wall pressure
	centerMargin = .01

	#for plotting
	x = linspace(-xmax, xmax, numPoints)
	y = linspace(-ymax, ymax, numPoints)
	z = linspace(0, zEnd, Integer(ceil(zEnd/deltaZ)))

	#centerCoords = findCenter(R0)
	xcenter = R0/2
	ycenter = R0/2

	#from Relation Between Pressure and Diameter in the Ascending Aorta of Man
	#b = 1.82E-3 #in cm/cm H20
	#b = 1.82E-3/980.665 # in cm/(dyne cm^2)
	#b = 1E-6
	b = 1.214E-6 #cm^3/dyne from http://stroke.ahajournals.org/content/25/1/11.full.pdf	

	#for storing radii as move through Z
	radii = fill(R0, Integer(ceil(zEnd/deltaZ)), 1)
	#for storing radii with respect to time
	historicRadii = Array{Array}(1, Integer(ceil(tFinal/deltat))) 
	
	while tsim < tFinal
		println(string("Tsim is ", tsim))
		#readline(STDIN)
		zSlice = 1
		zSim = 0.0

		if(numRuns > 1)
			#we can use historical data
			prevVelocityData=historicData[numRuns-1]
			prevRadii = historicRadii[numRuns-1]
			#for  radius calculations, to prevent pressure from being zero
			A = R0 -.0001
		else
			prevRadii = fill(R0, 1, Integer(ceil(zEnd/deltaZ)))
			A = R0
		end
		
		while zSim < zEnd
			Rwall = prevRadii[zSlice]
			wallcounter = 0 #for counting the number of points on the wall
			Ptot = 0 #for running sum of wall pressures
			vRtot = 0
			if(numRuns > 1)			
				prevU = prevVelocityData[zSlice,1]
				prevV = prevVelocityData[zSlice,1]
			else
				prevU = u
				prevV = v
			end
			for coords in grid
					xcord = coords[1]
					ycord = coords[2]
					(xindex, yindex) = lookupIndex(grid, xcord, ycord)
					#print("At indices")
					#println(sub2ind(grid, coords))
					inVessel = checkInside(xcord, ycord, Rwall)
					#velocities at present coordinates, from historical data
					currU = prevU[xindex, yindex]
					currV = prevV[xindex, yindex]
					currP = P[xindex, yindex]
					initials = [currU]# v[xindex, yindex]]
					if(inVessel == 1)
						#inside blood vessel, actually calculate velocity profile
						#println("At cordinates $xcord, $ycord")
						p = [deltaX, deltaY, deltaZ, currU, currV, currP, xcord, ycord]
					
						#for Sundials
						#wrappedU(t,w,wdot) = calculateU(t,w,wdot, p)

						#for ODE
						wrappedU(t,w) = calculateU(t,w, p)
						tspan = [t0:deltat/10:t0+deltat;]
						#println(typeof(tspan)) #they're floats, like they should be

						#calculated the u velocities
						tout,res = ODE.ode23(wrappedU, initials, tspan)
						#res = Sundials.cvode(wrappedU, initials, tspan)
						#println(res)
						#print("here")
						#vAll = float([ a[1] for a in res])
						uAll = float16([ a[1] for a in res])
					
						
					
						#println(uAll[length(uAll)])
						#vAll = res[:,2]
						#get last elements (the ones at tf)
						#force z velocity to be non-negative
						udesired = uAll[length(uAll)]
						if(udesired < 0)
							u[xindex, yindex] = abs(udesired)
						else
							u[xindex,yindex]= udesired
						end
					
						currU = u[xindex,yindex]
						#println("u is $currU at $xcord, $ycord")
						#if at center of pipe, set R velocity to zero
						xcenter = Rwall/2
						ycenter = Rwall/2
						
						if(xcenter-centerMargin<=xcord && xcord<=xcenter+centerMargin && ycenter-centerMargin<=ycord && ycord<=ycenter+centerMargin)						v[xindex, yindex] = 0.0
									println(string("set r velocity at ", xcord, ", ", ycord, " to zero"))
						else
							v[xindex, yindex]=calculateV(currU, currV, xcord, ycord, deltaZ, deltaX, deltaY)
						end
						
						currV = v[xindex, yindex]					

						#calculate pressures
						#println(string("x index is ", xindex))

						#if on the inside and close to the wall, use this point to calculate the pressure at the wall
						#should actually use Rwall
						#println(string("Rwall-(sqrt(xcord^2+ycord^2))", Rwall-(sqrt(xcord^2+ycord^2))))
						#println(string("Rwall-sqrt(xcord^2+ycord^2)", Rwall-sqrt(xcord^2+ycord^2)))
						
						if(isnan(Rwall))
							println("Rwall is a NaN")
							println(string("at cordinates ", xcord, ", ", ycord, " z slice ", zSim, "t = ", tsim))
							#readline(STDIN)
						end
						if(isnan(Ptot))
							println("Ptot is a NaN")
							println(string("at cordinates ", xcord, ", ", ycord, " z slice ", zSim, "t = ", tsim))
							#readline(STDIN)
						end
						if(Rwall-(sqrt(xcord^2+ycord^2))<closeMargin && Rwall-sqrt(xcord^2+ycord^2)> 0)
							#println(string("Ptot is ", Ptot, " and vRtot is ", vRtot, " and wall counter is ", wallcounter))
							calcP = (Rwall-A)/b
							if(calcP < 0)
								P[xindex, yindex] = 0
							else
								P[xindex, yindex] = calcP
							end
							#putting bounds on pressures
							if(P[xindex, yindex] > maxP)
								P = maxP
							end
							
							currP = P[xindex, yindex]
							Ptot = Ptot + P[xindex, yindex]
							wallcounter = wallcounter +1
							vRtot = vRtot+currV

						else
							P[xindex, yindex]= calculateP(currP, xcord, ycord, prevX, prevY, currV, currU, deltaZ)

						end
					
					

				
					elseif(inVessel ==0)
					#outside of blood vessel, set velocities to zero, pressure to zero
						#println("skipped")
						u[xindex, yindex]= 0
						v[xindex, yindex] = 0
						P[xindex, yindex] = 0
					end
			prevX = xcord
			prevY = ycord	

			
			end
			#	
		figure()
		PyPlot.hold(true)
		#plt.hold(True)
		pcolormesh(x,y,u)
		#PyPlot.pcolor(x,y,u, vmin = -1, vmax = 1)
		colorbar()
		drawBorder(Rwall, x)
		title(string("z velocity at z= ", zSim, "t = ", tsim))
		savestringZ = string( "Zvelocityatz", zSim, "t", tsim, ".png")
		PyPlot.axis([-xmax, xmax, -ymax, ymax])
		savefig(joinpath(path, savestringZ))

		figure()
		PyPlot.hold(true)
		pcolormesh(x,y,v)
		#PyPlot.pcolor(x,y,v, vmin = -1, vmax = 1)
		colorbar()
		drawBorder(Rwall, x)
		title(string("R velocity at z= ", zSim, " t = ", tsim ))
		savestringR = string("Rvelocityatz", zSim, "t", tsim, ".png")
		PyPlot.axis([-xmax, xmax, -ymax, ymax])
		savefig(joinpath(path, savestringR))

		plotPressure(x,y,P,Rwall,zSim, tsim, path)
		Pwall = Ptot/wallcounter
		vRwallAvg = vRtot/wallcounter
		newRwall = Rwall + vRwallAvg*deltat
		radii[zSlice] = newRwall
		println(string("R wall is ", Rwall))	
		

		velocityData[zSlice, 1] = u
		velocityData[zSlice,2] = v
		

		zSim = zSim+deltaZ
		zSlice = zSlice+1
		end
		plotRvsT(z, radii, tsim, path)
		historicData[numRuns]= velocityData
		historicRadii[numRuns]=radii
		tsim = tsim+deltat
		numRuns = numRuns +1
	end
	close("all")
	#plotConstantX(historicData, zEnd, deltaZ, ymax, deltaY, xmax, deltaX, deltat, path)
	
end

main()
