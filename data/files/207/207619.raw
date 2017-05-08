using Plotly

print_with_color(:green,"\nThis is a simulation of a [Classical] Multi-Slit Experiment \nperformed with Classical Particles.\n\n")

print_with_color(:red, "############# ASSUMPTIONS ###############\n")
print_with_color(:blue, "1) Given the number of slits (n), the number of targets (t) is given by\n")
print_with_color(:green, "\t t = 2n + 1.\n")
print_with_color(:blue, "2) Unlike Quantum particles, a classical particle passed from a slit can \nhit only 3 of the targets directly behind it.\n")
print_with_color(:red, "##########################################\n\n")

print_with_color(:blue, "The user is asked for the transition probabilities of the particle from each \nslit to 3 targets behind it.\n")
print_with_color(:blue, "Next, the user enters the time clicks.\n")
print_with_color(:blue, "The program then calculates, the state of the system after given time clicks.\n")

################################################################

function generateInitialState(n)
	X = Array(Real, n, 1)
	X[1] = 1
	for i=2:n
		X[i] = 0
	end
	X
end

print_with_color(:blue, "\nEnter the number of slits\n");
n =  int64(readline(STDIN))

dims = n + 2 * n + 2

B = zeros(Real, dims, dims)

print_with_color(:blue, "\nCalculating transition probabilities from particle source to the slits...")
source_slits_prob = 1//n
print_with_color(:blue, "DONE\n\n")
print_with_color(:green, "SOURCE TO SLIT PROBABILITIY = $(source_slits_prob)\n\n")

print_with_color(:blue, "Generating State vector...")
X = generateInitialState(dims)
print_with_color(:blue, "DONE\n\n")

# fill with slit probabilities
i = 2
while(i <= n + 1)
	B[i,1] = source_slits_prob
	i += 1
end

function input(i, j)
	println("Enter transition probability between slit $(i) and target $(j)")
	prob =  chomp(readline(STDIN)) # for example; "1/3"
	m = match(r"([0-9])+(/)([0-9])+", prob)
	real_prob = rationalize(m == nothing ? int64(prob)/1 : int64(m.captures[1])/int64(m.captures[3]))
	B[j,i] = real_prob
	B[j, j] = 1 # particle stays once it reaches a target => prob = 1
end

j = n + 2
for i=2:n+1
	for k = 1:3
		input(i, j)
		j += 1
	end
	j -= 1
end


###############################

function plot(λ::Array, i::Int64)
  println("\nPlotting for ", i)
  println("Data: ", λ[:])
  Plotly.signin("YOUR_PLOTLY_USERNAME", "YOUR_KEY")

  trace1 = [
    "x" => [1:dims],
    "y" => λ[:],
    "fill" => "tozeroy",
    "type" => "scatter"
  ]

  data = [trace1]
  response = Plotly.plot(data, ["filename" => "single_classical_prob_"*string(i), "fileopt" => "overwrite"])
  plot_url = response["url"]

  println("DONE. Plot@ ", plot_url)
end

#############################


time_clicks = int64(readline(STDIN))
print_with_color(:blue, "Running for a total of $(time_clicks) time clicks...")

for i=1:time_clicks
  Y = B ^ i * X
  Y += 0.0
  plot(Y[:], i)
end
