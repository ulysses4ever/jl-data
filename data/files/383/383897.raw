using JuMP
using DataFrames

function makeSinitial()
	path_to_S = "network/Network.dat"
	dv =readtable(path_to_S)
	global S
	S =convert(Array, dv)
	return S
end

function makemodelinital(numReactions)
	S =makeSinitial()
	println(S)
	println(size(S))
	m = Model() #create the model
	global v
	@defVar(m, v[1:numReactions,1:1]>=0) #require fluxes to be non-negative
	R1 = v[1,1];
	R2a= v[2,1];
	R2b= v[3,1];
	R3= v[4,1];
	R3 = v[5,1];
	R4 = v[6,1];
	R5a = v[7,1];
	R6 = v[8,1];
	R7 = v[9,1];
	R8a = v[10,1];
	R8b = v[11,1];
	Rres = v[12,1];
	Tc1 = v[13,1];
	Tc2 = v[14,1];
	Tf = v[15,1];
	Td = v[16,1];
	Te = v[17,1];
	Th = v[18,1];
	TO2 = v[19,1];
	Growth = v[20,1]

	#volume_cell = v[20,1];
	
	println(size(v))
	
	#add constraints from paper
	@addConstraint(m,Tc1 <=10.5)
	@addConstraint(m,Tc2 <=10.5)
	@addConstraint(m,Td<=12.0)
	@addConstraint(m,Te<=12.0)
	@addConstraint(m,Tf<=5.0)
	@addConstraint(m,Th<=5.0)
	@addConstraint(m,TO2<=15.0)
	

	#see if this forces growth
	#@addConstraint(m, biomass_cell>=.01)

	#FBA constraint
	@addConstraint(m, S*v .<= 10)

	#create objective
	@setObjective(m, Max,Growth)
	
	return m
end

function makemodel(numReactions,S)
	m = Model() #create the model
	global v
	@defVar(m, v[1:numReactions,1:1]>=0) #require fluxes to be non-negative
	R1 = v[1,1];
	R2a= v[2,1];
	R2b= v[3,1];
	R3= v[4,1];
	R3 = v[5,1];
	R4 = v[6,1];
	R5a = v[7,1];
	R6 = v[8,1];
	R7 = v[9,1];
	R8a = v[10,1];
	R8b = v[11,1];
	Rres = v[12,1];
	Tc1 = v[13,1];
	Tc2 = v[14,1];
	Tf = v[15,1];
	Td = v[16,1];
	Te = v[17,1];
	Th = v[18,1];
	TO2 = v[19,1];
	Growth = v[20,1]

	#volume_cell = v[20,1];
	
	println(size(v))
	
	#add constraints from paper
	@addConstraint(m,Tc1 <=10.5)
	@addConstraint(m,Tc2 <=10.5)
	@addConstraint(m,Td<=12.0)
	@addConstraint(m,Te<=12.0)
	@addConstraint(m,Tf<=5.0)
	@addConstraint(m,Th<=5.0)
	@addConstraint(m,TO2<=15.0)
	

	#see if this forces growth
	#@addConstraint(m, biomass_cell>=.01)

	#FBA constraint
	@addConstraint(m, S*v .<= 10)

	#create objective
	@setObjective(m, Max,Growth)
	
	return m
end

function calculateNextIterate(stepsize, S, v, X,currIterate)
	nextIterate = stepsize*(S*v)*X+currIterate
	return nextIterate
end

function logic(S,v)
	RP02= false
	RPc1 = false
	RPh = false
	RPb = false
	if(contains(string(typeof(v)), "JuMP"))
		R1 =  getValue(v[1,1]);
		R2a=  getValue(v[2,1]);
		R2b=  getValue(v[3,1]);
		R3=   getValue(v[4,1]);
		R3 =   getValue(v[5,1]);
		R4 =   getValue(v[6,1]);
		R5a =   getValue(v[7,1]);
		R6 =   getValue(v[8,1]);
		R7 =   getValue(v[9,1]);
		R8a =   getValue(v[10,1]);
		R8b =   getValue(v[11,1]);
		Rres =   getValue(v[12,1]);
		Tc1 =   getValue(v[13,1]);
		Tc2 =   getValue(v[14,1]);
		Tf =   getValue(v[15,1]);
		Td =   getValue(v[16,1]);
		Te =   getValue(v[17,1]);
		Th =   getValue(v[18,1]);
		TO2 =  getValue(v[19,1]);
		Growth =   getValue(v[20,1])

	else	

		R1 = (v[1,1]);
		R2a= (v[2,1]);
		R2b= (v[3,1]);
		R3=  (v[4,1]);
		R3 =  (v[5,1]);
		R4 =  (v[6,1]);
		R5a =  (v[7,1]);
		R6 =  (v[8,1]);
		R7 =  (v[9,1]);
		R8a =  (v[10,1]);
		R8b =  (v[11,1]);
		Rres =  (v[12,1]);
		Tc1 =  (v[13,1]);
		Tc2 =  (v[14,1]);
		Tf =  (v[15,1]);
		Td =  (v[16,1]);
		Te =  (v[17,1]);
		Th =  (v[18,1]);
		TO2 = (v[19,1]);
		Growth =  (v[20,1])
	end
	#regulatory proteins
	if(TO2==0)
		RP02 = false;
	end

	if(Tc1>0)
		RPc1 = true;
	end

	if(Th>0)
		RPh = true;
	end

	if(R2b > 0)
		RPb = true;
	end
	#regulating reactions

	if(RPb)
		#set R2a to zero by setting column in S to zero
		S[:,3] = 0.0
		
	end

	if(RP02)
		#set R5a to zero 
		S[:,7] = 0.0
		#set Rres to zero
		S[:,12]=0.0
	end

	if(RPb)
		#set R7 to zero
		S[:,9] = 0.0
	end

	if(RPh)
		#set R8a to zero
		S[:,10]= 0.0
	end
	
	if(RPc1)
		#if carbon1 is present, prevent uptake of carbon2
		S[:,14] = 0.0
	end
	
	processedS = S
	return processedS
end

function simulateOverTime(numsteps, stepsize,S,v, initialCellMass, initialstate,numReactions)
	currIterate = initialstate
	q = v #for inital run
	allx = Array{Array}(19,1) #need to figure out better/actual way to store data
	for k = 1:numsteps
		#evalute logic on S
		S = logic(S,q)
		m = makemodel(numReactions,S)
		status = solve(m)
		q = getValue(v)
		Growth = getValue(v[20,1])
		X = initialCellMass*Growth
		x = calculateNextIterate(stepsize, S, q, X,currIterate)
		println(x)
		allx[k]= x
		x = currIterate
	end
	return allx
end

function main()
	m = Model()
	initialCellMass = 1.0
	numReactions = 20
	S = makeSinitial()
	m= makemodelinital(numReactions)
	status = solve(m)
	println(m)
	println("Objective value: ", getObjectiveValue(m))
	#want to plot biomass, C1, C2, D
	initalguess = (getValue(v))
	Growth = getValue(v[20,1])
	
	#cellMass = initalCellMass*Growth

	#time, in hours
	tstart = 0.0
	tend = 5.0 
	stepsize = .1
	numsteps = (tend-tstart)/stepsize

	initialstate = zeros(19,1) #starting with nothing, everywhere
	x = simulateOverTime(numsteps, stepsize,S,v,initialCellMass, initialstate,numReactions)	
end

main()
