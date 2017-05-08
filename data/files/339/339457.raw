using StatsBase
using PyPlot

function linreg2(x, y, w::WeightVec)
    size(x) == size(y) || throw(DimensionMismatch("x and y must be the same size"))
    my = mean(y, w)
    mx, vx = mean(x, w)
    # don't need to worry about the scaling (n vs n - 1) since they cancel in the ratio
    b = cov(x, y)/vx
    a = my - b*mx
    return (a, b)
end

x = collect(linspace(0, 10, 20))
y = randn(20)
w = WeightVec(ones(20))
cov(x, y, w)
linreg(x, y)
linreg(x, y, ones(20))

linreg2(x, y, w)
