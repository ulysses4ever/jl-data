using PyCall
@pyimport matplotlib.pyplot as plt
include("Utils.jl")

# Seed rng
srand(0)

# Sample from three distributions
x = rand(1000)
x = append!(x, 0.5*rand(1000))
x = append!(x, 0.25*rand(1000))
n = [1000, 1000, 1000]	# Number of points from each distribution
f = n/sum(n)		# Fraction of points from each distribution
num_distributions = 3

# True upper limits of the distributions
limits = [1., 0.5, 0.25]

# Initial guesses of normalising constants
logZ = [0., 0., 0.]

# Function to do one iteration of logZ[k]
# Using Equation 8 of Cameron et al
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

# Evaluate the mixture
function logp_mix(logZ::Array{Float64, 1}, x::Float64)
  terms = zeros(num_distributions)
  for i in 1:num_distributions
    terms[i] = log(f[i]) - logZ[i]
    if x > limits[i]
      terms[i] = -1E300
    end
  end
  return logsumexp(terms)
end

# Do the iteration procedure and plot the logZs as we go
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
plt.ioff()

# Evaluate the mixture at all the points
logp = zeros(length(x))
for i in 1:length(x)
  logp[i] = logp_mix(logZ, x[i])
  println(i)
end

# Histogram of the raw data, and a representation of U(0, 1) by dividing
# out the mixture density
plt.hist(x, 100, normed=true, alpha=0.2)
plt.hold(true)
plt.hist(x, 100, weights=exp(-logp), normed=true, alpha=0.2, color=[1., 0., 0.])
plt.show()

