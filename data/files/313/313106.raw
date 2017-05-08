abstract AbstractLotkaVolterraSystem

#abstract
specificrate(Z::AbstractLotkaVolterraSystem,x::Vector{Float64}) = intrinsicrate(Z)+communitymatrix(Z)*x
rate(Z::AbstractLotkaVolterraSystem,x::Vector{Float64}) = x.*specificrate(Z)

jacobian(Z::AbstractLotkaVolterraSystem,x::Vector{Float64}) = diagm(specificrate(Z,x))+ diagm(x)*ommunitymatrix(Z)

#sector based fixed points should be defined as well
fixedpoint(Z::AbstractLotkaVolterraSystem) = -communitymatrix(Z)\intrinsicrate(Z)

isfeasible(Z::AbstractLotkaVolterraSystem) = allpositive(fixed_point(Z))
feasibility(Z::AbstractLotkaVolterraSystem) = isfeasible(Z)? 1 : 0


isstable(Z::AbstractLotkaVolterraSystem,x_fp::Vector{Float64}) = real(eigmaxreal(jacobian(Z,x_fp))) < 0
stability(Z::AbstractLotkaVolterraSystem,x_fp::Vector{Float64}) = isstable(Z,x_fp) < 0 ? 1 : 0

function viability(Z::AbstractLotkaVolterraSystem)
    x = fixedpoint(Z)
    return allpositive(x) & isstable(Z,x) ? 1 : 0
end

function odeint(Z::AbstractLotkaVolterraSystem,x0::Vector{Float64},times)
    f(t::Float64,x::Vector{Float64}) = rate(Z,x)
    return ode45(f,x0,times)
end
