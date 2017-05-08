using PyCall
@pyimport matplotlib.pyplot as plt
include("Sampler0.jl")

srand(0)

sampler = Sampler(1)
initialise!(sampler)
update!(sampler)

plt.plot(sampler.keep[:,1], sampler.keep[:,2], "bo", markersize=3, alpha=0.2)
plt.show()

N = 101
s1 = linspace(-6, -3, N)
s2 = linspace(35, 65, N)
logX = zeros(N, N)

for j in 1:N
  for i in 1:N
    logX[i, j] = calculate_logx(sampler, [s1[j], s2[N-i+1]])
  end
  println(j)
end

plt.imshow(logX, extent=[-6, -3, 35, 65], interpolation="nearest", aspect="auto")
plt.show()

