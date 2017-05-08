using PyPlot, PyCall

# scatter plot 2d data
function scatter2d (X::Matrix{Float64})
    if size(X)[1] != 2
        println("Only 2d data supported.\n")
    else
        scatter(X[1,:], X[2,:], 50)
    end
end

# scatter plot 2d data with labels
function scatter2d (X::Matrix{Float64}, labels)
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
