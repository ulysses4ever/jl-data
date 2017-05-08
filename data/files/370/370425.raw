type LogisticGrowth <: AbstractLotkaVolterra
  r::Real
  K::Real
  LogisticGrowth(r,K) = K > 0 ? new(r,K) : error("must have positive carrying capacity")
end
LogisticGrowth() = LogisticGrowth(1.,1.)

#LogisticGrowth specific data
nspecies(Z::LogisticGrowth) = 1

#values here are scalar, as opposed to vector
specificrate(Z::LogisticGrowth,x::Real) = Z.r*(1-x/Z.k)
rate(Z::LogisticGrowth,x::Real) = x*specificrate(Z)

#existence and evaluation of fixed points
somefixedpoint(Z::LogisticGrowth) = true
hasfixedpoint(Z::LogisticGrowth) = true
hasfixedpoint(Z::LogisticGrowth,sector::Vector{Int64}) = issector(Z,sector)
function fixedpoint(Z::LogisticGrowth,sector::Vector{Int64})
  if !issector(Z,sector)
    error("Not a valid sector for LogististiGrowth fixed point")
  else
    return sector == [] ? 0. : Z.K
  end
end

#feasibility, stability
isfeasible(Z::LogisticGrowth) =
function isfeasible(Z::LogisticGrowth,sector::Vector{Int64})
  if !issector(Z,sector)
    error("Not a valid sector for LogististiGrowth fixed point")
  else
    return sector == [1]
  end
end
isstable(Z::LogisticGrowth) = isstable(Z,[1])
function isstable(Z::LogisticGrowth,sector::Vector{Int64})
  if !issector(Z,sector)
    error("Not a valid sector for LogististiGrowth fixed point")
  else
    return sector == [] $ Z.r > 0
  end
end

function odeint(Z::LogisticGrowth,x0::Real,times)
  K,r = Z.K,Z.r
  ρ = x0/K
  expterm = [exp(-r*t)for t in times]
  return K*ρ./((1-ρ)*expterm + ρ)
end
