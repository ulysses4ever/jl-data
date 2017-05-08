using PyPlot
function loglog_scatter(x; opt=".r")
    n = length(x)
    X = collect(0:1:maximum(x))
    Y = zeros(length(X))
    for i = 1 : length(X)
        Y[i] = sum(x.==X[i])
    end
    loglog(X, Y, opt)
end
