using Distributions
using PyPlot
srand(1)
# generate 100 observations from correlated normal variates
n = 100
dist = MvNormal([0.0; 0.0], [1.0 0.5; 0.5 1.0])
r = rand(dist, n)'
# create 100 000 bootstrap replications
# and fetch time and memory used
@time bootcor = Float64[cor(r[sample(1:n, n),:])[1, 2] for i in 1:10^5]
# calculate kernel density estimator
kdeboot = kde(bootcor)
# plot results
plt.hist(bootcor, 50, normed = 1)
plot(kdeboot.x, kdeboot.density, color = "y", linewidth = 3.0)
axvline(0.5, color = "r", linewidth = 3.0)
savefig("corboot.pdf", format = "pdf")
# save results to pd
