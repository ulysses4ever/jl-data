module RandomFerns

using Distributions
using StatsBase

export Ensemble, kfoldCV_fern, kfoldCV_fernEnsemble, build_fern, apply_fern, build_ensemble, apply_ensemble

if VERSION.minor >= 4
  typealias Range1{Int} Range{Int}
  _int(x) = round(Int, x)
else
  _int(x) = int(x)
end

include("utils.jl")

immutable Part
  dist::MvNormal
  mean::Any
end

immutable Fern
  parts::Array{Part}
  proj_matrix::Matrix
  cuts::Vector
end

immutable Ensemble
  ferns::Array{Fern}
end

function random_projection_matrix(method::Symbol, n_features::Int, n_components::Int)

  P = zeros(n_components, n_features)

  if method == :gaussian
    dist = Normal(0, (1/sqrt(n_components)))
    rand!(dist, P)

  elseif method == :sparse

    # todo

  end

  return P

end

function _get_index{T<:FloatingPoint}(x::Matrix{T}, cuts::Vector{T}, n::Int)
  idx = @parallel (+) for i=1:n
    c = x[:,i] .< cuts[i]
    b = c .* 2^i
  end

  idx = idx + 1
  return idx
end

### regression model ###

function apply_fern{T<:FloatingPoint}(model::Fern, features::Matrix{T})

  yhat = zeros(size(features)[1])
  w = zeros(size(features)[1])

  # project unseen data
  x = features * model.proj_matrix'

  # get indices
  idx = _get_index(x, model.cuts, size(model.proj_matrix)[1])

  # we only need to consider those parts
  uidx = unique(idx)
  for i = 1:size(uidx)[1]
    j = uidx[i]
    s = idx .== j

    if model.parts[j].mean == 0.0
      yhat[s] = 0.0
      w[s] = 0.0
    else
      yhat[s] = model.parts[j].mean
      w[s] = pdf(model.parts[j].dist, x[s,:]') ./ pdf(model.parts[j].dist, mean(model.parts[j].dist))
    end
  end

  return yhat, w
end

function apply_ensemble{T<:FloatingPoint}(model::Ensemble, features::Matrix{T})

  n = size(model.ferns)[2]

  yhat = zeros(size(features)[1])
  wsum = zeros(size(features)[1])

  for i=1:n
    yy, w = apply_fern(model.ferns[i], features)
    yhat = yhat + (yy .* w)
    wsum = wsum + w
  end

  r = yhat ./ wsum

  b = isnan(r)
  r[b] = 0

  return r

end

function build_fern{T<:FloatingPoint, U<:Real}(labels::Vector{T}, features::Matrix{U}, n_components=5)

  # sanity check
  if size(labels)[1] != size(features)[1]
    println("number of instances in features and labels matrix not equal!")
    return None
  end

  # get random projection and project features
  p = random_projection_matrix(:gaussian, size(features)[2], n_components)
  x = features * p'

  # get cutting values
  min_x = minimum(x, 1)
  max_x = maximum(x, 1)

  cuts = zeros(n_components)

  for i = 1:n_components
    d = Uniform(min_x[i], max_x[i])
    cuts[i] = rand(d)
  end

  # estimate index
  idx = _get_index(x, cuts, n_components)

  max_idx = 2^(n_components+1)
  # fill all parts with Distributions
  parts = Array(Part, 1, max_idx)
  for i = 1:max_idx
    s = idx .== i

    if (sum(s) == 0)
      x_cov = eye(n_components)
      x_mean = zeros(n_components)
      y_mean = 0
    else
      c = mean_and_cov(x[s,:])
      x_cov = c[2] .* eye(n_components)
      x_mean = vec(c[1])
      y_mean = mean(labels[s])

      # do something if covariance matrix is not positive definite
      if (det(x_cov) <= 0.0)
        x_cov = eye(n_components) # todo: this is probably a bad idea
        y_mean = 0.0
      end

    end

    dist = MvNormal(x_mean, x_cov)
    parts[i] = Part(dist, y_mean)
  end

  return Fern(parts, p, cuts)
end

function build_ensemble{T<:FloatingPoint, U<:Real}(labels::Vector{T}, features::Matrix{U}, n_components=5, n_ferns=10)

  # sanity check
  if size(labels)[1] != size(features)[1]
    println("number of instances in features and labels matrix not equal!")
    return None
  end

  ferns = Array(Fern, 1, n_ferns)

  for i=1:n_ferns
    ferns[i] = build_fern(labels, features, n_components)
  end

  return Ensemble(ferns)
end

end # module
