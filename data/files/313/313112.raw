abstract AbstractLotkaVolterra

#abstract
specificrate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = intrinsicrate(Z)+communitymatrix(Z)*x
rate(Z::AbstractLotkaVolterra,x::Vector{Float64}) = x.*specificrate(Z)

jacobian(Z::AbstractLotkaVolterra,x::Vector{Float64}) = diagm(specificrate(Z,x))+ diagm(x)*ommunitymatrix(Z)

#sector check function
sectors(Z::AbstractLotkaVolterra) = subsets(1:nspecies(Z))
function issector(Z::AbstractLotkaVolterra,sector::Vector{Int64})
  N = length(sector)
  usector = unique(sector)
  return length(usector) == N && all(0.< usector .<= nspecies(Z))
end

#sector based fixed points should be defined as well
hasfixedpoint(Z::AbstractLotkaVolterra) = "checks for well conditioend linear solver problem"
fixedpoint(Z::AbstractLotkaVolterra) = -communitymatrix(Z)\intrinsicrate(Z)

isfeasible(Z::AbstractLotkaVolterra) = allpositive(fixed_point(Z))
feasibility(Z::AbstractLotkaVolterra) = isfeasible(Z)? 1 : 0


isstable(Z::AbstractLotkaVolterra,x_fp::Vector{Float64}) = real(eigmaxreal(jacobian(Z,x_fp))) < 0
stability(Z::AbstractLotkaVolterra,x_fp::Vector{Float64}) = isstable(Z,x_fp) < 0 ? 1 : 0

function viability(Z::AbstractLotkaVolterra)
    x = fixedpoint(Z)
    return allpositive(x) & isstable(Z,x) ? 1 : 0
end

function odeint(Z::AbstractLotkaVolterra,x0::Vector{Float64},times)
    f(t::Float64,x::Vector{Float64}) = rate(Z,x)
    return ode45(f,x0,times)
end
