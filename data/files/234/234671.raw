abstract ParameterType
abstract MetropolisParameter <: ParameterType
# would be nice to have more flexibility in acceptance and rejections
# currently parameter support must be the same for all rvs in a parameter
# would be nice to have non-normal candidates

# originally had MetropolisScalar, but am going to use MetropolisVector
# where it's a vector of length 1. This will allow us to iterate over
# the elements using one set of updates for scalar and vectors
type MetropolisVector <: MetropolisParameter
  can::Vector      # candidate value
  canstar::Vector  # transformed candidate value
  cur::Vector      # current value
  curstar::Vector  # transformed current value
  ll::Array        # tells which log likelihood values are impacted
  support::Vector  # parameter support
  length::Integer

  canddist::Normal     # candidate distribution
  prior::Distribution  # prior distribution
  usestar::Bool        # should we use the transformed parameter to eval prior
  transform::Function  # should there be a transformation
  impacts::Array       # array of everything the update impacts
  seq::Bool            # update sequentially (vs block)

  acc::Vector  # number of acceptances
  att::Vector  # number of attempts
  mh::Vector   # current metropolis standard deviation

  updating::Bool

  MetropolisVector() = new()
end

type MetropolisMatrix <: MetropolisParameter
  can::Matrix      # candidate value
  canstar::Matrix  # transformed candidate value
  cur::Matrix      # current value
  curstar::Matrix  # transformed current value
  ll::Array        # tells which log likelihood values are impacted
  support::Vector  # parameter support
  nrows::Integer
  ncols::Integer

  canddist::Normal     # candidate distribution
  prior::Distribution  # prior distribution
  usestar::Bool        # should we use the transformed parameter to eval prior
  transform::Function  # should there be a transformation
  impacts::Array       # array of everything the update impacts
  seq::Bool            # update sequentially (vs block)

  acc::Matrix  # number of acceptances
  att::Matrix  # number of attempts
  mh::Matrix   # current metropolis standard deviation

  updating::Bool

  MetropolisMatrix() = new()
end

function fillcan!(obj::MetropolisParameter, fill_with::Real)
  fill!(obj.can, fill_with)
end

function fillcur!(obj::MetropolisParameter, fill_with::Real)
  fill!(obj.cur, fill_with)
end

# create a metropolis parameter that's a scalar or vector
# to simplify the update, we treat scalars as arrays of length 1
function createmetropolis(length::Integer; initial::Real=0.0,
                          prior::Distribution=Distributions.Normal(),
                          support::Vector=[-Inf, Inf],
                          transform::Function=transident,
                          impacts::Array=[], ll::Array=[],
                          usestar::Bool=false, seq::Bool=true,
                          tune::Real=1.0)

  this = MetropolisVector()
  this.can = fill(convert(FloatingPoint, initial), length)
  this.cur = fill(convert(FloatingPoint, initial), length)
  this.canstar = copy(this.can)  # create initial object in memory
  this.curstar = copy(this.can)  # create initial object in memory

  if transform != transident
    for i = 1:length
      this.canstar[i] = transform(this.can[i], support, false)
      this.curstar[i] = transform(this.cur[i], support, false)
    end
  end

  this.ll         = ll
  this.support    = support
  this.length     = length
  this.canddist   = Distributions.Normal()
  this.prior      = prior
  this.usestar    = usestar
  this.transform  = transform
  this.impacts    = impacts
  this.seq        = seq
  this.acc        = fill(0, length)
  this.att        = fill(0, length)
  this.mh         = fill(tune, length)
  this.updating   = false

  return this
end

# create a metropolis parameter that's a matrix
function createmetropolis(nrows::Integer, ncols::Integer; initial::Real=0.0,
                          prior::Distribution=Distributions.Normal(),
                          support::Vector=[-Inf, Inf],
                          transform::Function=transident,
                          impacts::Array=[], ll::Array=[],
                          usestar::Bool=false, seq::Bool=true,
                          tune::Real=1.0)
  this = MetropolisMatrix()
  this.can = fill(convert(FloatingPoint, initial), nrows, ncols)
  this.cur = fill(convert(FloatingPoint, initial), nrows, ncols)

  if transform == transident
    this.canstar = copy(this.can)
    this.curstar = copy(this.cur)
  else
    for j = 1:ncols, i = 1:nrows
      this.canstar[i, j] = transform(this.can[i, j], support, false)
      this.curstar[i, j] = transform(this.cur[i, j], support, false)
    end
  end

  this.ll         = ll
  this.support    = support
  this.nrows      = nrows
  this.ncols      = ncols
  this.canddist   = Distributions.Normal()
  this.prior      = prior
  this.usestar    = usestar
  this.transform  = transform
  this.impacts    = impacts
  this.seq        = seq
  this.acc        = fill(0, nrows, ncols)
  this.att        = fill(0, nrows, ncols)
  this.mh         = fill(tune, nrows, ncols)
  this.updating   = false

  return this
end
