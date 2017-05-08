module Histograms

using StatsBase

import Base.ndims
import Base.push!, Base.+

nbins(h::AbstractHistogram) = map(x->size(x, 1) - 1, edges(h))
nbins(h::AbstractHistogram, i::Int) = size(edges(h)[i], 1)
edges(h::AbstractHistogram) = h.edges

contents(h::Histogram) = h.weights
integral(h::Histogram) = sum(h.weights)
entries(h::Histogram) = contents(h)

integral{T<:Real, N, E}(h::AbstractHistogram{T, N, E}, ndims=1:N) =
    first(sum(contents(h), ndims))

import Base.mean

function mean{T<:Real, N, E}(h::AbstractHistogram{T, N, E}, ndims=1:N)
    ret = Array(Float64, length(ndims))
    for (ind, ndim) in enumerate(ndims)
        mids = Base.midpoints(edges(h)[ndim])
        tot = 0
        otherdims = collect(1:N)
        deleteat!(otherdims, ndim)
        
        for (midp, w) in zip(mids, sum(contents(h), otherdims))
            tot += midp * w
        end
        ret[ind] = tot
    end
    return ret / integral(h)
end

type ErrorHistogram{T<:Real, N, E} <: AbstractHistogram{T, N, E}
    edges::E
    weights::Array{T,N}
    weights_sq::Array{T,N}
    closed::Symbol
    function ErrorHistogram(
        edges::NTuple{N,AbstractArray},
        weights::Array{T,N},
        weights_sq::Array{T,N},
        closed::Symbol)
        for edg in edges
            issorted(edg) || error("edges must be sorted: $edg")
        end
        closed == :right || closed == :left || error("closed must :left or :right")
        map(x -> length(x)-1,edges) == size(weights) || error("Histogram edge vectors must be 1 longer than corresponding weight dimensions")
        new(edges, weights, weights_sq, closed)
    end 
end

Hist1D = ErrorHistogram{Float64, 1, Tuple{Vector{Float64}, }}
Hist2D = ErrorHistogram{Float64, 2, Tuple{Vector{Float64}, Vector{Float64}} }
Hist3D = ErrorHistogram{Float64, 2, Tuple{Vector{Float64}, Vector{Float64}, Vector{Float64}}}

function ErrorHistogram(edges...)
    T = Float64
    N = length(edges)
    E = typeof(edges)

    return ErrorHistogram{T, N, E}(
        edges,
        zeros(T, map(x->size(x, 1) - 1, edges)...),
        zeros(T, map(x->size(x, 1) - 1, edges)...),
        :left
    )
end



function push!{T, N, E, X <: Real, W <: Real}(
    h::ErrorHistogram{T,N,E},
    xs::NTuple{N,X},
    w::W
    )
    idxs = if h.closed == :right
        map((edge, x) -> searchsortedfirst(edge,x) - 1, h.edges, xs)
    else
        map(searchsortedlast, h.edges, xs)
    end

    try
        h.weights[idxs...] += w
        h.weights_sq[idxs...] += w^2
    catch e
        isa(e,BoundsError) || rethrow(e)
    end
    h
end

function push!{T, E, X <: Real, W <: Real}(
    h::ErrorHistogram{T,1,E}, x::X, w::W
    )
    i = if h.closed == :right 
        searchsortedfirst(edges(h)[1], x) - 1 
    else
        searchsortedlast(edges(h)[1], x)
    end

    if 1 <= i <= length(h.weights)
        @inbounds h.weights[i] += w
        @inbounds h.weights_sq[i] += w^2
    end
    h
end

nbins(h::ErrorHistogram) = map(x->size(x, 1) - 1, edges(h))
ndims{T, N, E}(h::ErrorHistogram{T, N, E}) = N

errors(h::ErrorHistogram) =  sqrt(h.weights_sq)
errorssq(h::ErrorHistogram) =  h.weights_sq
contents(h::ErrorHistogram) = h.weights
edges(h::ErrorHistogram) = h.edges
entries(h::ErrorHistogram) = sum(contents(h))^2 / sum(errorssq(h))

normalize(h::Histogram) = Histogram(h.edges, h.weights/sum(h.weights))
function normalize{T<:Real, N, E}(h::ErrorHistogram{T, N, E})
    sw = sum(h.weights)
    ErrorHistogram{T, N, E}(h.edges, h.weights/sw, h.weights_sq, h.closed)
end

function +{T1<:Real, T2<:Real, N, E}(h1::ErrorHistogram{T1, N, E}, h2::ErrorHistogram{T2, N, E})
    @assert ndims(h1) == ndims(h2)
    @assert nbins(h1) == nbins(h2)
    @assert h1.closed == h2.closed

    for i=1:ndims(h1)
        @assert all(edges(h1)[i] .== edges(h2)[i])
    end

    return ErrorHistogram{T1, N, E}(
        edges(h1),
        contents(h1) .+ contents(h2),
        h1.weights_sq .+ h2.weights_sq,
        h1.closed
    )
end

integralerror{T<:Real, N, E}(h::ErrorHistogram{T, N, E}, ndims=1:N) =
    first(sqrt(sum(errorssq(h), ndims)))

import Base.mean
function mean(h::Hist1D)
    l = 0.0
    mids = midpoints(h.edges[1][2:end-1])
    for i=2:nbins(h)[1]-1
        l += mids[i-1] * h.weights[i]
    end
    return l / sum(h.weights)
end

import Base.std
function std(h::Hist1D)
    l = 0.0
    mids = midpoints(h.edges[1][2:end-1])
    m = mean(h)
    for i=2:nbins(h)[1]-1
        l += (mids[i-1] - m)^2 * h.weights[i] 
    end
    return sqrt(l / sum(h.weights))
end

export nbins, edges, contents, errors, integral
export normalize, entries
export ErrorHistogram, Hist1D, Hist2D, Hist3D
export +
end
