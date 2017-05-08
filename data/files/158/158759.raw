include("Model.jl")

# The original sampler idea (same as TwinPeaks)
# Sampler class
type Sampler
  num_particles::Int64		# Number of NS particles
  particles::Array{Model, 1}	# The particles themselves
  direction::Array{Float64, 1}	# Probabilities for selecting each scalar
  threshold::Array{Float64, 1}	# Current thresholds
end

# Constructor
function Sampler(num_particles::Int64)
  # Make the particles
  particles = Model[]
  for i in 1:num_particles
    push!(particles, Model())
  end

  # Generate a direction
  direction = exp(5*rand()*randn(size(particles[1].scalars)))
  direction = direction/sum(direction)

  # Set initial thresholds to -infinity
  threshold = 1E-300*ones(size(direction))
  return Sampler(num_particles, particles, direction, threshold)
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
  # Choose a scalar to use as a threshold (use rejection sampling to choose
  # using the probabilities defined by 'direction')
  which = 0
  while true
    which = rand(1:size(sampler.direction)[1])
    if rand() <= sampler.direction[which]/maximum(sampler.direction)
      break
    end
  end

  # Find the worst particle with respect to the chosen scalar
  index = 1
  worst = sampler.particles[1].scalars[which]
  for i in 2:sampler.num_particles
    if sampler.particles[i].scalars[which] < worst
      worst = sampler.particles[i].scalars[which]
      index = i
    end
  end

  # Update the threshold
  sampler.threshold[which] = worst

  println(sampler.threshold)
end

