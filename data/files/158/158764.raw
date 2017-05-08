include("Utils.jl")

# MODEL CLASS. Defines what problem we're solving.
type Model
  N::Int64
  params::Array{Float64, 1}
  scalars::Array{Float64, 1}
end

# Constructor that takes no input
function Model()
  Model(100, zeros(100), zeros(2))
end

# Initialise model parameters from the prior
function from_prior!(model)
  model.params = rand(model.N)
  compute_scalars!(model)
end

# Perturb model parameters
function perturb!(model)
  which = rand(1:model.N)
  model.params[which] += randh()
  model.params[which] = mod(model.params[which], 1.)
  compute_scalars!(model)
  return 0.
end

# Calculate the scalars
function compute_scalars!(model)
  model.scalars[1] = 0.
  model.scalars[2] = 0.
  for i in 1:model.N
    model.scalars[1] += -0.5*(model.params[i] - 0.5)^2
    model.scalars[2] += sin(4.*pi*model.params[i])^2
  end
end

