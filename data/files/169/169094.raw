#SA.jl contains the code required to execute the basic functions of Simulated 
#Annealing. 
#
#This implementation is designed to emulate the matlab implementation as found
#at http://www.mathworks.com/matlabcentral/fileexchange/10548-general-simulated
#-annealing-algorithm/content/anneal.m
#
#This module is designed in its most cut down form to require only 2 parameters
#the initial guess vector, and the cost function. This is all, however, this 
#code is also designed to allow for customization of the SA algorithm by 
#allowing for an options vector to hold the following settings:
#Verb: 0 Means silent run no output
#Verb: 1 Means just output cost value of best configuration and best 
#Configuration
#Verb: 2 Means Report Temperature Changes 
#Verb: 3 Means Write to file in the format T, Cost, stateVect 
#Default: 1
#
#outFile: If verb is set to 3 then an output file must be specified
#Default: "SAOutput.dat"
#MaxTries: A function that tells the max number of iterations before the 
#program automatically ceases execution.
#Default: 300
#
#MaxConsRej: A function that says how many times a change from current 
#configuration can be rejected before the solution is deemed frozen and 
#the minima located.
#Default: 1000
#
#MaxSuccess: A function that says how many times changes from the current 
#Temperature can occur before changing the temperature. This prevents high 
#temperatures from allowing infinite run time due to constant transitions.
#Default: 20
#
#StopTemp: A number which is designed to yield the stop conditions for temp
#Default: 1*10^-8
#
#Generator: A function used to generate a new state given the old one
#Default: Simply just changes one value of the state vector randomly
#
#CoolSched: A function that is used to change decrement temperature
#Default: Tnew=.9*T
#
#InitTemp: Given value that tells the system what temperature to 
#Start at
#
#StopVal: Given value at which the energy is low enough for acceptance.
#Default: -Inf
#
#ProbDist: This dicates the probability of a transition, for 
#for simulated annealing the value is given by default as the boltzmann 
#distribution.
#Default: exp(-dE/T)
#
#The parameters given are designed to give maximum flexibility to this 
#so that it might be used in many diverse scenarios.
#
#END INTRO COMMENTS
#BEGIN CODE COMMENTS

#This function is the default generator used by the Anneal function
#
function defaultGenerator(stateVec)
	println("NOT IMPLEMENTED YET")
	stateVec
end
#
#
function Anneal(InitState, Cost;Gen = defaultGenerator, verb=1,
MaxTries = x->300,MaxConsRej = T->1000, MaxSuccess = T->20, StopTemp = 10E-8, 
CoolSched= T->.9*T, InitTemp=1,ProbDist = (dE,T)->exp(-dE/T),StopVal=-Inf,
outFile="SAOutput.dat")
	total=0; #Number of iterations that the annealing while loop has 
	#executed
	success=0; #Number of sucessful consecutive successful transitions at 
	#given temperature T
	k=0; #Number of iterations
	consRej=0 #Number of times a transition failed to happen at a given T
	frozen=false #Checks to see if the state has either fallen below the 
	#minimum temperature or if the state can no longer transition from its 
	#current state due to being close to a global optimum
	currE=Cost(InitState)#initial energy of the given state
	report=verb #verbosity mode flag
	T=InitTemp #Temperature of the system, set to initial temp given
	bestSoln=InitState #Best found state in total time running
	currSoln=InitState #Current accepted state
	testSoln=InitState #Test solution, current transitions to it 
	#probabalistically
	testE=0 #The energy of the test solution
	bestE=currE #best energy, set to inital energy initially
	#fileOut=Array(Float32,3+length(bestSoln),1) #Array that stores the 
	fileOut=hcat([total,T,currE]',currSoln')
	file
	#values of the run before executing in format discussed above
	#println(currE)
	entry=0
	if(report==2)#If we want constant reports on energy and
		#temp then report
		println(string("T : ",T, " Cost: ", currE))	
	end

	while(!frozen) #While the system is still moving
		k+=1 #Increments run counter
		
		if(k>=MaxTries(T) || success>=MaxSuccess(T))
		#	println("stage1")
		#Checks, if in this Temperatures run the incrementor has 
		#Exceeded the maximum number of tries to get to the optimal or
		#if the system is transitioning too much then the temperature 
		#Needs to lower
		#if we drop below the minimum temperature or we are not longer
		#transitioning between states then we consider the system to be
		#frozen and exit the annealing loop.

			if(T<=StopTemp || consRej >= MaxConsRej(T))
				#println("Frozen")
				frozen=true
				total=total+k #
				break;
			
			else #if the system is not frozen 
				T=CoolSched(T)	#Go to the new temperature
				if(report==2)#If we want constant reports on energy and
				#temp then report
					println(string("T : ",T, " Cost: ", currE))	
				elseif(report==3) #This option loads an array for 
					#write to file at the end of the run.
					#println([total,T,currE]')
					#println(currSoln')
					#println(hcat([total,T,currE]', currSoln'))
					entry=hcat([total,T,currE]', currSoln')
					fileOut=vcat(fileOut,entry)
					#println(fileOut)
				end
				#Also increment the total number of runs by runs at the
				#old T.
				total+=k;		
				k=1; #reset T counter
				success=1; #Note the number of sucessful transitions at 
				#this temperature
			end	
		end
		if(currE<bestE) #if the currE is better than the best E then 
		#keep it as our best known optimal soln
			bestSoln=testSoln
			bestE=testE
		end

		testSoln=Gen(currSoln) #Generate a new test solution
		testE=Cost(testSoln) #Compute its energy
		#println(string("TESTE: ", testE, " OLDE :", currE))
		if(testE<=StopVal) #if the new energy is less than the stop 
		#we have achieved our goal report the testSoln as best output
			bestSoln=testSoln
			bestE=testE	
			break
		elseif(rand()<ProbDist((testE-currE),T)) #If not below stopval
		#Then make a probabalistic jump to the test soln 
			#println("jump")
			currSoln = testSoln #if jump then make the test soln
			#the current soln
			currE=testE #set currE as new energy
			success+=1 #increment jump success
			consRej=0 #reset consecutive rejection counter
		else
			consRej+=1 #if no transition increment consRej
		end	
	end	

	if(report>0) #Print output for all but silent modes
		println(string("Initial Temp: ", InitTemp))
		println(string("Final Temp: ", T))
		println(string("Consecutive Rejections: ", consRej))
		println(string("Total Iterations: ", total))
		println(string("Final Cost: ", bestE))
		#println(string("Final Solution: ", bestSoln))
	end
	
	if(report==3) #write the output to file
		writecsv(outFile,fileOut)
	end
	(bestE,bestSoln)
end


		
				
			
	


 
