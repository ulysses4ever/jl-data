using Distributions
using PyPlot

dist = Cauchy()
arr = [abs(rand(dist)) for i in 1:1000]
walk = cumsum(arr)
plt.plot(walk)
plt.savefig("cauchy_walk")
