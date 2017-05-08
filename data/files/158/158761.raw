include("Model.jl")

# Sampler class
type Sampler
  num_particles::Int64		# Number of NS particles
  particles::Array{Model, 1}	# The particles themselves
  steps::Int64
  skip::Int64
  keep::Array{Float64, 2}
end

# Constructor
function Sampler(num_particles::Int64)
  # Make the particles
  particles = Model[]
  for i in 1:num_particles
    push!(particles, Model())
  end

  return Sampler(num_particles, particles, 10000, 10, zeros(1000, 2))
end

# Initialise function
# Generates particles from prior
function initialise!(sampler::Sampler)
  for i in 1:sampler.num_particles
    from_prior!(sampler.particles[i])
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
      sampler.keep[i/sampler.skip, :] = sampler.particles[which].scalars
    end
  end
end

# Calculate logX of a point
function calculate_logx(sampler::Sampler, scalars::Array{Float64, 1})
  above = 0
  for i in 1:size(sampler.keep)[1]
    if all(vec(sampler.keep[i, :]) .>= scalars)
      above += 1
    end
  end
  return log(above/size(sampler.keep)[1])
end

