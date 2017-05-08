abstract AbstractLotkaVolterra

#abstract
specificrate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = intrinsicrate(Z)+communitymatrix(Z)*x
rate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = x.*specificrate(Z)

jacobian(Z::AbstractLotkaVolterra,x::Vector{Float64}) = diagm(specificrate(Z,x))+ diagm(x)*ommunitymatrix(Z)
jacobian(Z::AbstractLotkaVolterra) = Diagonal(fixedpoint(Z))*communitymatrix(Z)
function jacobian(Z::AbstractLotkaVolterra,sector::Vector{Int64})
    diagterm = intrinsicrate(Z)
    diagterm[sector] = 0.
    squareterm = Diagonal(fixedpoint(Z,sector))*communitymatrix(Z)
    return Diagonal(diagterm) + squareterm
end

#sector check and generation functions
sectors(Z::AbstractLotkaVolterra,dim::Int64) = subsets([1:nspecies(Z)],dim)
sectors(Z::AbstractLotkaVolterra) = chain([sectors(Z,dim) for dim = 1:nspecies(Z)]...)
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

isfeasible(Z::AbstractLotkaVolterra,sector::Vector{Int64}) = allpositive(fixed_point(Z,sector)[sector])
isfeasible(Z::AbstractLotkaVolterra) = allpositive(fixed_point(Z))
feasibility(Z::AbstractLotkaVolterra) = isfeasible(Z)? 1 : 0

isstable(Z::AbstractLotkaVolterra,x_fp::Vector{Float64}) = real(eigmaxreal(jacobian(Z,x_fp))) < 0
stability(Z::AbstractLotkaVolterra,x_fp::Vector{Float64}) = isstable(Z,x_fp) < 0 ? 1 : 0

isviable(Z::AbstractLotkaVolterra) =
function viability(Z::AbstractLotkaVolterra)
    x = fixedpoint(Z)
    return allpositive(x) & isstable(Z,x) ? 1 : 0
end

function odeint(Z::AbstractLotkaVolterra,x0::Vector{Float64},times)
    f(t::Float64,x::Vector{Float64}) = rate(Z,x)
    return ode45(f,x0,times)
end
