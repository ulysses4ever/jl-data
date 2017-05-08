using PyPlot, PyCall

function scatter2d(X::Matrix{Float64}, labels = [])
    if isempty(labels)
        if size(X)[1] != 2
            println("Only 2d data supported.\n")
        else
            scatter(X[1,:], X[2,:], 50)
        end
    else
        if size(X)[1] != 2
            println("Only 2d data supported.\n")
        else
            ulabels = unique(labels)
            cc = pycall(get_cmap("jet").o, PyAny, linspace(0, 1.0, length(ulabels)))
            for i = 1 : length(ulabels)
                ind = find(labels .== ulabels[i])
                scatter(X[1,ind], X[2,ind], s=50, color=cc[i,:], edgecolor="black")
            end
        end
    end
end

function plot_powerlaw(cnt::Vector{Int}, opt=".r")
    x = collect(0:1:maximum(cnt))
    y = zeros(length(x))
    for i = 1 : length(x)
        y[i] = sum(cnt.==x[i])
    end
    loglog(x, y, opt)
end
