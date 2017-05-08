module utils

using Distributions
using NPZ
import PyPlot.plt

cov = npzread("PHOENIX_covariance_matrix.npy")
#cov = npzread("kurucz_covariance_matrix.npy")

# either create our own d = MvNormal(full(mat))

# or load a numpy file and convert to Julia format

d = MvNormal(cov)

out = rand(d,200)

for i in 1:size(out, 2)
    plt.plot(out[:,i], "k")
end

plt.savefig("out.png")
npzwrite("PHOENIX_draws.npy", out)


end
