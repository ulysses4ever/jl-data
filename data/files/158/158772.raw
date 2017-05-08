using PyCall
@pyimport matplotlib.pyplot as plt
include("Sampler0.jl")

srand(0)

sampler = Sampler(1)
initialise!(sampler)
update!(sampler)

plt.plot(sampler.keep[:,1], sampler.keep[:,2], "bo", markersize=3, alpha=0.2)
plt.plot(-4, 50, "r*", markersize=10)
println(calculate_logx(sampler, [-4., 50.]))
plt.show()

