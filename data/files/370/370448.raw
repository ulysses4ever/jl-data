abstract AbstractLotkaVolterra

#abstract
"""The per capita growth rate of each speicies in the ecosystem"""
specificrate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = intrinsicrate(Z)+communitymatrix(Z)*x
"""The total growth rate of each species in the ecosystem"""
rate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = x.*specificrate(Z,x)

"""The Jacobian matrix of the rate function at the specified density x"""
jacobian(Z::AbstractLotkaVolterra,x::Vector{Float64}) = diagm(specificrate(Z,x))+ diagm(x)*communitymatrix(Z)
"""The Jacobian matrix of the rate function at the interior fixed point"""
jacobian(Z::AbstractLotkaVolterra) = Diagonal(fixedpoint(Z))*communitymatrix(Z)
"""The jacobian matrix of the rate function at the fixed point of the specified sector"""
function jacobian(Z::AbstractLotkaVolterra,sector::Vector{Int64})
    x = fixedpoint(Z,sector)
    diagterm = specificrate(Z,copy(x))
    diagterm[sector] = 0.
    squareterm = Diagonal(x)*communitymatrix(Z)
    return Diagonal(diagterm) + squareterm
end

#sector check and generation functions
"""The set of all sector vectors in the ecosystem with a specified number of species (dim)"""
sectors(Z::AbstractLotkaVolterra,dim::Int64) = subsets(collect(1:nspecies(Z)),dim)
"""The set of all sector vectors in the ecosystem"""
sectors(Z::AbstractLotkaVolterra) = chain(Any[Int64[]],[sectors(Z,dim) for dim = 1:nspecies(Z)]...)
"""The set of all sector vectors of a given kind.
The supported kinds include: :feasible,:infeasible,:stable,:unstable,:viable,:unviable  """
function sectors(Z::AbstractLotkaVolterra,kind::Symbol)
  allsectors = filter(sector->isfixedpoint(Z,sector),sectors(Z))#this needs to be pulled out, just here for now
  @match kind begin
    :feasible => filter(sector->isfeasible(Z,sector),allsectors)
    :infeasible => filter(sector->!isfeasible(Z,sector),allsectors)
    :stable => filter(sector->isstable(Z,sector),allsectors)
    :unstable => filter(sector->!isstable(Z,sector),allsectors)
    :viable => filter(sector->isviable(Z,sector),allsectors)
    :unviable => filter(sector->!isviable(Z,sector),allsectors)
    _ => error("not a valid sector filter kind")
  end
end
"""Tests whether a given vector is a valid sector for the ecosystem"""
function issector(Z::AbstractLotkaVolterra,sector::Vector{Int64})
  N = length(sector)
  usector = unique(sector)
  return length(usector) == N && all(0.< usector .<= nspecies(Z))
end

#fixed point checks and generation
"""Checks for the existence of a fixed point in the interior sector of an ecosystem.
The test may fail due to numerical illposedness of the community matrix"""
function isfixedpoint(Z::AbstractLotkaVolterra)
  try
    fixedpoint(Z)
    return true
  catch
    return false
  end
end
"""Checks for the existence of a fixed point in the specified sector of an ecosystem.
The test may fail due to numerical illposedness of the community matrix"""
function isfixedpoint(Z::AbstractLotkaVolterra,sector::Vector{Int64})
  try
    fixedpoint(Z,sector)
    return true
  catch
    return false
  end
end
"""Returns the interior fixed point of the ecosystem or throws an error if it does nto exist"""
fixedpoint(Z::AbstractLotkaVolterra) = -communitymatrix(Z)\intrinsicrate(Z)
"""Returns the fixed point of the ecosystem in the specified sector or throws an error if it does to exist"""
function fixedpoint(Z::AbstractLotkaVolterra,sector::Vector{Int64})
    A = communitymatrix(Z)[sector,sector]
    r = intrinsicrate(Z)[sector]
    x = zeros(nspecies(Z))
    x[sector] = -A\r
    return x
end
"""Returns all the fixed points of an ecosystem"""
fixedpoints(Z::AbstractLotkaVolterra) = imap(sector->fixedpoint(Z,sector),filter(sector->isfixedpoint(Z,sector),sectors(Z)))
"""Returns all the fixed points of an ecosystem of a specified kind"""
function fixedpoints(Z::AbstractLotkaVolterra,kind::Symbol)
  return imap(sector->fixedpoint(Z,sector),filter(sector->isfixedpoint(Z,sector),sectors(Z,kind)))
end

isfeasible(Z::AbstractLotkaVolterra,sector::Vector{Int64}) = length(sector)>0 && all(fixedpoint(Z,sector)[sector] .> 0.)
isfeasible(Z::AbstractLotkaVolterra) = all(fixedpoint(Z) .> 0.)

isstable(Z::AbstractLotkaVolterra) = real(eigmaxreal(jacobian(Z))) < 0.
isstable(Z::AbstractLotkaVolterra,sector::Vector{Int64}) = real(eigmaxreal(jacobian(Z,sector))) < 0.

isviable(Z::AbstractLotkaVolterra) = isfeasible(Z) & isstable(Z)
isviable(Z::AbstractLotkaVolterra,sector::Vector{Int64}) = isfeasible(Z,sector) & isstable(Z,sector)

feasibility(Z::AbstractLotkaVolterra) = isfeasible(Z)? 1 : 0
stability(Z::AbstractLotkaVolterra) = isstable(Z) < 0 ? 1 : 0
viability(Z::AbstractLotkaVolterra) = isviable(Z) ? 1 : 0

"""Solve the initial value problem for the ecosystem desnity of the ecosystem ODE. API subject to change."""
function odeint(Z::AbstractLotkaVolterra,x0::Vector{Float64},times)
    f(t::Float64,x::Vector{Float64}) = rate(Z,x)
    return ode45(f,x0,times)
end
