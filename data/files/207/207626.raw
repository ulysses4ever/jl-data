println("\nThis program is a simulation of Classical Probabilistic System.")
println("The program asks for the Dynamics matrix (3x3 matrix) and the initial state of the system (1x3 vector).")
println("The state is represented by a row vector.")
println("It also asks for the number of time clicks.")
println("After that, it calculates the state of system before the specified time clicks.\n\n")

##############################################################


function getInitialState()
	X = Array(Real, 1, 3)
	@printf "\nEnter the Initial state vector of the system\n\n"
	for i=1:3
		X[i] = parseStateEntry(readline(STDIN)) # CHANGE TO REAL --> TODO
	end
	X
end

function getTimeClicks()
	@printf "\nEnter the time clicks\n"
	time_clicks = int64(readline(STDIN))
end

function f_getDynamicsMatrix()
	print("\nReading the Dynamics Matrix from a local file...")
	M = Array(Real, 3, 3)
	count = 1
	open("dmat2.txt") do f
		while !eof(f)
			entry = chomp(readline(f))
			if entry != "+"
				M[count] = parseDynamicEntry(entry)
				count += 1
			end
		end
	end
	println("...DONE\n")
	M
end

function parseDynamicEntry(entry)
	m = match(r"([0-9]+)(//)([0-9]+)", entry)
	rationalize(m == nothing ? int64(entry)/1 : int64(m.captures[1])/int64(m.captures[3]))
end

function parseStateEntry(entry)
	m = match(r"([0-9]+)(/)([0-9]+)", entry)
	rationalize(m == nothing ? int64(entry)/1 : int64(m.captures[1])/int64(m.captures[3]))
end

################################################

M = f_getDynamicsMatrix()
println("The transposed Dynamics matrix is \n")
println(transpose(M))

X = getInitialState()

time_clicks =  getTimeClicks()

Y = transpose(M^time_clicks) * transpose(X)

println("\n GOING BACK IN TIME. Before $(time_clicks) time clicks, the state of the system was\n")

println(Y)
