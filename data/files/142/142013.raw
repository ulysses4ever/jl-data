abstract DistributionType

type SampleProcess   <: DistributionType end
# type FunctionalBelief <: BeliefType end # Will be a Sigma RandomVariable

# A belief is a distribution over value X and activation A
abstract Belief{D <: DistributionType}
typealias SampleableBelief Belief{SampleProcess}

# When a socket is cleared, it contains NO_BELIEF
immutable NoBelief <: Belief end
const NO_BELIEF = NoBelief()

## INDEPENDENT BELIEFS
## ===================

# When X and A are independent
immutable IndependentBelief <: SampleableBelief
  X::Distribution
  A::Distribution
end

rand(b::IndependentBelief) = (rand(b.X), rand(b.A))
rand(b::IndependentBelief, n::Int64) = [rand(b) for i = 1:n]


## DEPENDENT BELIEFS
## ===================

# When X and A are not nececssarily independent
immutable DependentBelief <: SampleableBelief
  sampler::Function
end

rand(b::DependentBelief) = b.sampler()
rand(b::DependentBelief, n::Int64) = [rand(b) for i = 1:n]

## DIRAC BELIEFS
## =============

# When X and A are just values
immutable Dirac{S,B} <: Belief{B}
  x::S
  A::Float64
end

# Sampling from a delta just returns a value
rand{T}(b::Dirac{T,SampleProcess}) = (b.x, b.A)
rand{T}(b::Dirac{T,SampleProcess}, n::Int64) = [rand(b) for i = 1:n]

## MIXED BELIEFS
## =============

# When a belief is a result of mixing
immutable MixedBelief <: SampleableBelief
  components::Vector{Belief}
end

function rand(b::MixedBelief)
  weights::Vector{Float64} = [rand(c)[2] for c in b.components]
  weights = [1/(1+exp(-w)) for w in weights] #Sigmoid it so +ve
  pnormalize!(weights)
  c = Categorical(weights, Distributions.NoArgCheck())
  rand(b.components[rand(c)])
end

# ======
# Mixing

# At each time step a basin accumulates the evidence incident upon it
# There's more than one way to accumulate and it depends upon the
function mix{B<:SampleableBelief}(beliefs::Vector{B})
  if length(beliefs) == 1
    beliefs[1]
  else
    MixedBelief(beliefs)
  end
end
