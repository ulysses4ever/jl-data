include("Model.jl")

# The original sampler idea (same as TwinPeaks)
# Sampler class
type Sampler
  num_particles::Int64		# Number of NS particles
  particles::Array{Model, 1}	# The particles themselves
  direction::Array{Float64, 1}	# Probabilities for selecting each scalar
end

# Constructor
function Sampler(num_particles)
  # Make the particles
  particles = Model[]
  for i in 1:num_particles
    push!(particles, Model())
  end

  # Generate a direction
  direction = exp(5*rand()*randn(size(particles[1].scalars)))
  direction = direction/sum(direction)
  return Sampler(num_particles, particles, direction)
end


