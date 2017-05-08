abstract AbstractLotkaVolterra

#abstract
specificrate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = intrinsicrate(Z)+communitymatrix(Z)*x
rate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = x.*specificrate(Z)

jacobian(Z::AbstractLotkaVolterra,x::Vector{Float64}) = diagm(specificrate(Z,x))+ diagm(x)*ommunitymatrix(Z)
jacobian(Z::AbstractLotkaVolterra) = Diagonal(fixedpoint(Z))*communitymatrix(Z)
function jacobian(Z::AbstractLotkaVolterra,sector::Vector{Int64})
    diagterm = copy(intrinsicrate(Z))
    diagterm[sector] = 0.
    squareterm = Diagonal(fixedpoint(Z,sector))*communitymatrix(Z)
    return Diagonal(diagterm) + squareterm
end

#sector check and generation functions
sectors(Z::AbstractLotkaVolterra,dim::Int64) = subsets([1:nspecies(Z)],dim)
sectors(Z::AbstractLotkaVolterra) = chain(Any[Int64[]],[sectors(Z,dim) for dim = 1:nspecies(Z)]...)
function sectors(Z::AbstractLotkaVolterra,kind::Symbol)
  allsectors = sectors(Z)
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
function issector(Z::AbstractLotkaVolterra,sector::Vector{Int64})
  N = length(sector)
  usector = unique(sector)
  return length(usector) == N && all(0.< usector .<= nspecies(Z))
end

#fixed point checks and generation
function isfixedpoint(Z::AbstractLotkaVolterra)
  try
    fixedpoint(Z)
    return true
  catch
    return false
  end
end
function isfixedpoint(Z::AbstractLotkaVolterra,sector::Vector{Int64})
  try
    fixedpoint(Z,sector)
    return true
  catch
    return false
  end
end
fixedpoint(Z::AbstractLotkaVolterra) = -communitymatrix(Z)\intrinsicrate(Z)
function fixedpoint(Z::AbstractLotkaVolterra,sector::Vector{Int64})
    A = communitymatrix(Z)[sector,sector]
    r = intrinsicrate(Z)[sector]
    x = zeros(nspecies(Z))
    x[sector] = -A\r
    return x
end
fixedpoints(Z::AbstractLotkaVolterra) = imap(sector->fixedpoint(Z,sector),sectors(Z))
fixedpoints(Z::AbstractLotkaVolterra,kind::Symbol) = imap(sector->fixedpoint(Z,sector),sectors(Z,kind))

isfeasible(Z::AbstractLotkaVolterra,sector::Vector{Int64}) = length(sector)>0 && all(fixedpoint(Z,sector)[sector] .> 0.)
isfeasible(Z::AbstractLotkaVolterra) = all(fixedpoint(Z) .> 0.)

isstable(Z::AbstractLotkaVolterra) = real(eigmaxreal(jacobian(Z))) < 0.
isstable(Z::AbstractLotkaVolterra,sector::Vector{Int64}) = real(eigmaxreal(jacobian(Z,sector))) < 0.

isviable(Z::AbstractLotkaVolterra) = isfeasible(Z) & isstable(Z)
isviable(Z::AbstractLotkaVolterra,sector::Vector{Int64}) = isfeasible(Z,sector) & isstable(Z,sector)

feasibility(Z::AbstractLotkaVolterra) = isfeasible(Z)? 1 : 0
stability(Z::AbstractLotkaVolterra) = isstable(Z) < 0 ? 1 : 0
viability(Z::AbstractLotkaVolterra) = isviable(Z) ? 1 : 0

function odeint(Z::AbstractLotkaVolterra,x0::Vector{Float64},times)
    f(t::Float64,x::Vector{Float64}) = rate(Z,x)
    return ode45(f,x0,times)
end
