using Plotly

print_with_color(:green,"\nThis is a simulation of a [Quantum] Multi-Slit Experiment \nperformed with Quantum Particlese.g., Photos.\n\n")

print_with_color(:red, "############# ASSUMPTIONS ###############\n")
print_with_color(:blue, "1) Given the number of slits (n), the number of targets (t) is given by\n")
print_with_color(:green, "\t t = 2n + 1.\n")
print_with_color(:red, "##########################################\n\n")

print_with_color(:blue, "The user is asked for the probability amplitudes of the photon from each \nslit to 3 targets behind it.\n")
print_with_color(:blue, "Next, the user enters the time clicks.\n")
print_with_color(:blue, "The program then calculates, the state of the system after given time clicks.\n")
print_with_color(:red, "The program is yet to find the INTERFERENCE POINTS - TODO.\n\n")

################################################################

function plot(λ::Array, i::Int64)
  println("\nPlotting for ", i)
  println("Data: ", λ[:])

  Plotly.signin("YOUR_PLOTLY_USERNAME", "KEY")

  trace1 = [
    "x" => [1:dims],
    "y" => λ[:],
    "fill" => "tozeroy",
    "type" => "scatter"
  ]

  data = [trace1]
  response = Plotly.plot(data, ["filename" => "single_quantum_prob_"*string(i), "fileopt" => "overwrite"])
  plot_url = response["url"]

  println("DONE. Plot@ ", plot_url)
end



# 3 cases for a given number: integer, floating-point, or rational
function parseNumber(Δ::String)
  if contains(Δ, "/") && contains(Δ, ".")
    parsed_Δ = parseRational(Δ)
    Δ = round(parsed_Δ[1] / parsed_Δ[2], 3)
  elseif contains(Δ, ".")
    Δ = float64(Δ)
  elseif contains(Δ, "/")
    a,b = int64(split(Δ, "/"))
    Δ = rationalize(a/b)
  else
    Δ = int(Δ)
  end
  Δ
end

# Parse rational
function parseRational(Δ)
  p, q = float64(split(Δ, "/"))
end

# parse the imputs to form a complex number
function parseInputs(α::String, β::String)
  ℜ_ℑ = parseNumber(α) + parseNumber(β)*im
end

# Get the number of slits.
function getSlits()
  println("Enter total number of slits:")
  n = int(chomp(readline(STDIN)))
end

slits = getSlits()
dims = 3slits + 2 # Dimensions of the Dynamics matrix

# Create a Dynamics matrix Ξ of (dims x dims)
# filled with 0+0im
Ξ = zeros(Complex, dims, dims)

# Get the probability amplitudes
function input(λ::Int64, ξ::Int64)
  println("Enter the probability amplitude (α,β) from slit $(λ) to target $(ξ)")
  α, β = split(chomp(readline(STDIN)), ",")
  ℜ_ℑ = parseInputs(chomp(α), chomp(β))
  Ξ[ξ,λ] = ℜ_ℑ
  Ξ[ξ,ξ] = 1+0im
end

# Create a state vector of dimensions (dims x 1)

# Generate initial State vector
function generateStateVector(dims::Int64)
  θ = zeros(Complex, dims, 1)
  θ[1] = 1+im
  θ
end

# Photo source to slit probabilty
# rounded to nearest 3 decimal places
print_with_color(:blue, "\nCalculating probability amplitudes from Photon source to the slits...")
μ_slit = 1 / sqrt(slits)
print_with_color(:blue, "DONE\n\n")
print_with_color(:green, "PHOTON SOURCE TO SLIT PROBABILITIY = $(μ_slit)\n\n")

# Fill Ξ with μ_slit
i = 2
while(i <= slits + 1)
  Ξ[i, 1] = μ_slit
  i += 1
end

# Fill rest of the Ξ
j = slits + 2
for i = 2:slits+1
  for k = 1:3
    input(i, j)
    j += 1
  end
  j -= 1
end

# Generate the Initial State Vector
print_with_color(:blue, "Generating State vector...")
θ = generateStateVector(dims)
print_with_color(:blue, "DONE\n\n")

# Prompt for number of time clicks
println("Enter the total number of time clicks:")
time_clicks = int64(chomp(readline(STDIN))) #for example 8


println("Running for a total of $(time_clicks) time clicks: ")
for i=1:time_clicks
  η = Ξ ^ i
  ψ = η * θ
  abs_ψ = abs2(ψ)
  plot(abs_ψ, i)
end


println("\nCalculating the Interference points:")
k = slits * 3
for i=1:slits-1
  println(k)
  k -= 2
end
println("DONE")

