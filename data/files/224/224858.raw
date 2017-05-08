# example taken from http://mathworks.com/help/stats/slicesample.html

include("slice_sample.jl")
function f(x::Float64)
    exp(-.5*x^2) * (1 + sin(3*x)^2) * (1 + cos(5*x)^2)
end
function log_f(x::Float64)
    -.5*x^2 + log(1 + sin(3*x)^2) + log(1 + cos(5*x)^2)
end

nsamples = 2000
x = zeros(nsamples)
x[1] = slice_sample(log_f, 1.0)
for i = 2 : nsamples
    x[i] = slice_sample(log_f, x[i-1])
end

using PyPlot;
nbins = 50
(n, bins, patches) = plt.hist(x, nbins)
ngrids = 1000
xgrid = linspace(minimum(x), maximum(x), ngrids)
binwidth = bins[2] - bins[1]
area = quadgk(f, xgrid[1], xgrid[end])[1]
y = zeros(ngrids)
for i = 1 : ngrids
    y[i] = f(xgrid[i])
end
y *= (nsamples*binwidth/area)
plot(xgrid, y, "r", linewidth=2)
