module HistogramPlot

using StatsBase, PyPlot

nbins(h::Histogram) = size(h.edges[1])
edges(h::Histogram) = h.edges
contents(h::Histogram) = h.weights
errors(h::Histogram) = sqrt(h.weights)
integral(h::Histogram) = sum(h.weights)

#draws a familiar 1-D histogram with errors
#ax - PyPlot axes
#hh - Histogram
#kwords:
#do_error - default true, false to skip drawing errorbars
#scaling - multiply bar heights and errors ny this number
function barplot{T<:Real}(ax::PyObject, hh::Histogram{T, 1, (Array{Float64,1},)}, color::ASCIIString;kwargs...)
    kwargsd = [k=>v for (k, v) in kwargs]
    do_error = pop!(kwargsd, :do_error, true)
    scaling = pop!(kwargsd, :scaling, 1.0)
    xs = zeros(2 * nbins(hh)[1]-2);
    ys = zeros(2 * nbins(hh)[1]-2);

    for i=1:2*nbins(hh)[1]-2
        xs[i] = edges(hh)[1][1 + floor(i/2)]
        ys[i] = scaling * contents(hh)[1 + floor((i-1)/2)]
        #println(xs[i], " ", ys[i])
    end
    
    p = ax[:plot](xs, ys; color=color, kwargsd...)
    do_error && ax[:errorbar](
    midpoints(edges(hh)[1]), scaling * contents(hh), scaling * errors(hh), fmt=nothing, ecolor=color
    )
    return p
end

end # module
