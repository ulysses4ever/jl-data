module SoItGoes

export
    chunk,
    flatten,
    flatten_inner,
    tally,
    countmax,
    normalize

function chunk{T}(a::Matrix{T}, w::Int, s::Int=1)
    Matrix{T}[a[:,t:t + w - 1] for t = 1:s:size(a, 2) - w + 1]
end

function chunk{T}(a::Vector{T}, w::Int, s::Int=1) 
    Vector{T}[a[t:t + w - 1] for t = 1:s:length(a) - w + 1]
end

flatten{T}(a::Array{T,1}) = any(map(x->isa(x, Array), a)) ? flatten(vcat(map(flatten, a)...)) : a
flatten{T}(a::Array{T}) = reshape(a, prod(size(a)))
flatten(a) = a

function tally{I<:Integer}(a::Array{I})
    counts = zeros(I, maximum(a))
    for i in a
        counts[i] += 1
    end
    counts
end

countmax{I<:Integer}(x::Array{I}) = indmax(tally(x))

normalize(data, mu, sigma) = (data .-  mu) ./ sigma

function normalize(data::Matrix, dim::Int=2)
    mu = mean(data, dim)
    sigma = std(data, dim)
    normalize(data, mu, sigma)
end

normalize(data::Vector{Matrix}, mu, sigma) = map(x->normalize(x, mu, sigma), data)

function normalize(data::Vector{Matrix})
    X = hcat(data...)
    mu = mean(X, 2)
    sigma = std(X, 2)
    normalize(data, mu, sigma)
end



end # module SoItGoes