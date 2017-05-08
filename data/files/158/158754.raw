using PyCall
@pyimport matplotlib.pyplot as plt
include("Utils.jl")

# Seed rng
srand(0)

x = rand(10000)
x = append!(x, 0.5*rand(10000))
x = append!(x, 0.25*rand(10000))

limits = [1., 0.5, 0.25]

# Using Equation 8 of Cameron et al
# Initial guesses of normalising constants
logZ = [0., 0., 0.]

# Function to do one iteration of logZ[k]
function update!(logZ::Array{Float64, 1}, k::Int64)
  terms = zeros(length(x))
  for i in 1:length(x)
    if x[i] > limits[k]
      terms[i] = -1E300
    end
    terms[i] -= logp_mix(logZ, x[i])
  end
  logZ[k] = logsumexp(terms) - log(length(x))
end

function logp_mix(logZ::Array{Float64, 1}, x::Float64)
  terms = zeros(3)
  for i in 1:3
    terms[i] = log(1./3) - logZ[i]
    if x > limits[i]
      terms[i] = -1E300
    end
  end
  return logsumexp(terms)
end

plt.ion()
plt.hold(false)
for i in 1:100
  for j in 2:3
    update!(logZ, j)
  end
  plt.plot(logZ, "bo-")
  plt.title(i)
  plt.draw()
  println(exp(logZ))
end

