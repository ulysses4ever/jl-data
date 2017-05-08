module HistogramPlot

using StatsBase, PyPlot, PyCall, HEP

#draws a familiar 1-D histogram with errors
#ax - PyPlot axes
#hh - Histogram
#kwords:
#do_error - default true, false to skip drawing errorbars
#scaling - multiply bar heights and errors ny this number

function barplot(ax::PyObject, hh, color::ASCIIString;kwargs...)
    kwargsd = [k=>v for (k, v) in kwargs]
    do_error = pop!(kwargsd, :do_error, true)
    scaling = pop!(kwargsd, :scaling, 1.0)
    empty_overflow = pop!(kwargsd, :empty_overflow, false)
    xs = zeros(2 * nbins(hh)[1]-2);
    ys = zeros(2 * nbins(hh)[1]-2);
    

#     edgs = deepcopy(edges(hh)[1])
#     edgs[1] = edgs[2] - diff(edgs)[2]
#     edgs[end] = edgs[end-1] + diff(edgs)[end-1]
    conts = deepcopy(contents(hh))

    if empty_overflow
        overflow = conts[end]
        conts[end] = 0
        underflow = conts[1]
        conts[1] = 0
        overflow>0 && println("overflow: $overflow")
        underflow>0 && println("underflow: $underflow")
    end
    if scaling == :normed
        scaling = 1.0 / sum(conts) 
    end

    for i=1:2*nbins(hh)[1]-2
        xs[i] = edges(hh)[1][1 + floor(i/2)]
        ys[i] = scaling * conts[1 + floor((i-1)/2)]
        #println(xs[i], " ", ys[i])
    end
    unshift!(xs, xs[1])
    unshift!(ys, 0)

    push!(xs, xs[end])
    push!(ys, 0)

    p = ax[:plot](xs, ys; color=color, kwargsd...)
    do_error && ax[:errorbar](
    midpoints(edges(hh)[1]), scaling * conts, scaling * errors(hh), fmt=nothing, ecolor=color
    )
    return p
end

function barplot{T<:Float64, N, E<:(Array{Float64,1},Array{Float64,1},)}(ax::PyObject, hh::ErrorHistogram{T,N,E}, color::ASCIIString;kwargs...)
    kwargsd = [k=>v for (k, v) in kwargs]
    do_error = pop!(kwargsd, :do_error, true)
    scaling = pop!(kwargsd, :scaling, 1.0)
    
    ws = deepcopy(hh.weights)
    p = ax[:matshow](
        hh.weights[2:end-1,2:end-1],
        interpolation="none",
        cmap=color,
        extent=[hh.edges[2][2],
        hh.edges[2][end-1],
        hh.edges[1][end-1],
        hh.edges[1][2]],
        aspect="auto"
    )
    #ax[:set_aspect](10)
    return p
end

export barplot
end # module
