using PyCall
@pyimport matplotlib.pyplot as plt
include("Sampler0.jl")

srand(0)

sampler = Sampler(1)
initialise!(sampler)
update!(sampler)

plt.plot(sampler.keep[:,1], sampler.keep[:,2], "bo", markersize=5, alpha=0.3)
plt.show()

