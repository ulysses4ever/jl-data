include("Model.jl")

# Sampler class
type Sampler
  num_particles::Int64		# Number of NS particles
  particles::Array{Model, 1}	# The particles themselves
  steps::Int64
  skip::Int64
  keep::Array{Model, 1}
  keep_scalars::Array{Float64, 2}
end

# Constructor
function Sampler(num_particles::Int64)
  # Make the particles
  particles = Model[]
  for i in 1:num_particles
    push!(particles, Model())
  end

  return Sampler(num_particles, particles, 10000, 100, Model[], zeros(100, 2))
end

# Initialise function
# Generates particles from prior
function initialise!(sampler::Sampler)
  for i in 1:sampler.num_particles
    from_prior!(sampler.particles[i])
  end
  for i in 1:div(sampler.steps, sampler.skip)
    push!(sampler.keep, Model())
  end
end

# Update function
function update!(sampler::Sampler)
  for i in 1:sampler.steps
    which = rand(1:sampler.num_particles)
    proposal = deepcopy(sampler.particles[which])
    logH = perturb!(proposal)

    if rand() <= exp(logH)
      sampler.particles[which] = proposal
    end

    if rem(i, sampler.skip) == 0
      sampler.keep_scalars[i/sampler.skip, :] = sampler.particles[which].scalars
      sampler.keep[i/sampler.skip] = deepcopy(sampler.particles[which])
    end
  end
end

# Calculate logX of a point
function calculate_logx(sampler::Sampler, scalars::Array{Float64, 1})
  above = 0
  for i in 1:size(sampler.keep_scalars)[1]
    if all(vec(sampler.keep_scalars[i, :]) .>= scalars)
      above += 1
    end
  end
  return log(above/size(sampler.keep_scalars)[1])
end

function create_level(sampler::Sampler)
  scalars = zeros(2)
  scalars[1] = median(sampler.keep_scalars[:,1])
  scalars[2] = median(sampler.keep_scalars[:,2])

  logX_level = calculate_logx(sampler, scalars)

  good = zeros(Bool, div(sampler.steps, sampler.skip))
  for i in 1:div(sampler.steps, sampler.skip)
    logX = calculate_logx(sampler, vec(sampler.keep_scalars[i, :]))
    good[i] = logX >= logX_level
  end

  return (scalars, logX_level, good)
end

