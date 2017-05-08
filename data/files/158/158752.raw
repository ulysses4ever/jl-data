include("Model.jl")

# Sampler class
type Sampler
  num_particles::Int64		# How many particles to use
  particles::Array{Model, 1}	# The particles themselves
end

# Constructor
function Sampler(num_particles::Int64)
  particles = Model[]
  for i in 1:num_particles
    push!(particles, Model())
  end
  return Sampler(num_particles, particles)
end

# Generate all particles from prior
function initialise!(sampler::Sampler)
  for i in 1:sampler.num_particles
    from_prior!(sampler.particles[i])
  end
end

# Explore the prior
function explore!(sampler::Sampler, steps::Int64=10000, thin::Int64=10)
  keep = zeros((div(steps, thin), 2))

  for i in 1:steps
    which = rand(1:sampler.num_particles)
    proposal = deepcopy(sampler.particles[which])
    logH = perturb!(proposal)
    if rand() <= exp(logH)
      sampler.particles[which] = proposal
    end

    if rem(i, thin) == 0
      keep[div(i, thin), :] = sampler.particles[which].scalars
    end
  end
  return keep
end

