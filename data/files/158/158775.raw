using PyCall
@pyimport matplotlib.pyplot as plt

include("Sampler.jl")
include("Results.jl")

# Create sampler and results object
sampler = Sampler(10)
initialise!(sampler)
results = Results()

# Explore and accumulate results
keep = explore!(sampler)
add!(results, keep)

println(logX([-5., 50.], results))
plt.plot(keep[:,1], keep[:,2], "b.")
plt.show()

