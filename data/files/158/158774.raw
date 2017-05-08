using PyCall
@pyimport matplotlib.pyplot as plt
include("Sampler0.jl")

srand(1)

sampler = Sampler(1)
initialise!(sampler)
update!(sampler)
(level, logX, good) = create_level(sampler)
println(logX)

for i in 1:size(sampler.keep_scalars)[1]
  color = "ro"
  if good[i]
    color = "go"
  end
  plt.plot(sampler.keep_scalars[i,1], sampler.keep_scalars[i,2],
           color, markersize=5)
end

plt.plot(level[1], level[2], "ko", markersize=20, alpha=0.2)
plt.show()

