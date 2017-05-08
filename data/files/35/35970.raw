"Normalize by subtracting mean and dividing by standard deviation"
immutable Normalizer
    mu::Vector{Float64}
    sigma::Vector{Float64}
    Normalizer(mu, sigma, sigma_min=1e-6) = new(mu, max(sigma, sigma_min))
end

function Normalizer(data::Matrix)
    mu = vec(mean(data, 2))
    sigma = vec(std(data, 2))
    return Normalizer(mu, sigma)
end

function Normalizer{T}(data::Vector{Matrix{T}})
    X = hcat(data...)
    mu = vec(mean(X, 2))
    sigma = vec(std(X, 2))
    return Normalizer(mu, sigma)
end

Base.length(params::Normalizer) = length(params.mu)

call{T}(params::Normalizer, data::Matrix{T}) = (data .-  params.mu) ./ params.sigma

call{T}(params::Normalizer, data::Vector{Matrix{T}}) = map(x->params(x), data)


"Linearly scale data between low and high"
immutable LinearScaler
    old_min::Vector{Float64}
    old_max::Vector{Float64}
    new_min::Vector{Float64}
    new_max::Vector{Float64}
end

function LinearScaler(data::Matrix, new_min::Vector{Float64}, new_max::Vector{Float64})
    size(data, 1) == length(new_min) || throw(DimensionMismatch("size of new_min does not match size of data"))
    size(data, 1) == length(new_max) || throw(DimensionMismatch("size of new_max does not match size of data"))
    old_min = vec(minimum(data, 2))
    old_max = vec(maximum(data, 2))
    return LinearScaler(old_min, old_max, new_min, new_max)
end

function LinearScaler(data::Matrix, new_min::Float64=0.0, new_max::Float64=1.0)
    n = size(data, 1)
    return LinearScaler(data, fill(new_min, n), fill(new_max, n))
end

LinearScaler{T}(data::Vector{Matrix{T}}, new_min=0.0, new_max=1.0) = LinearScaler(hcat(data...), new_min, new_max)

Base.length(params::LinearScaler) = length(params.old_min)

function call{T}(params::LinearScaler, data::Matrix{T})
    old_range = params.old_max .- params.old_min
    new_range = params.new_max .- params.new_min
    new_data = (((data .- params.old_min) .* new_range) ./ old_range) .+ params.new_min
    return new_data
end

call{T}(params::LinearScaler, data::Vector{Matrix{T}}) = map(x -> params(x), data)

