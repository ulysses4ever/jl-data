module SoItGoes

export
    slide,
    flatten,
    flatten_inner,
    tally,
    countmax,
    normalize

function slide{T}(seq::Matrix{T}, wstep::Int, wsize::Int)
    Matrix{T}[seq[:,t:t + wsize - 1] for t = 1:wstep:size(seq, 2) - wsize + 1]
end

flatten{T}(a::Array{T,1}) = any(map(x->isa(x, Array), a)) ? flatten(vcat(map(flatten, a)...)) : a
flatten{T}(a::Array{T}) = reshape(a, prod(size(a)))
flatten(a) = a

flatten_inner{T}(seq::Vector{T}) = map(flatten, seq)

function tally{I<:Integer}(x::Vector{I})
    counts = zeros(I, maximum(x))
    for i in x
        counts[i] += 1
    end
    counts
end

countmax{I<:Integer}(x::Vector{I}) = indmax(tally(x))

normalize(x, mu, sigma) = (x .-  mu) ./ sigma

function normalize(X::Matrix, dim::Int)
    mu = mean(X, dim)
    sigma = std(X, dim)
    normalize(X, mu, sigma)
end

normalize(sequences::Vector{Matrix}, mu, sigma) = map(x->normalize(x, mu, sigma), sequences)

function normalize(sequences::Vector{Matrix})
    X = hcat(sequences...)
    mu = mean(X, 2)
    sigma = std(X, 2)
    normalize(sequences, mu, sigma)
end



end # module MLTools