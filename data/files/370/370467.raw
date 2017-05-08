#systems parameterized in the standard "generalized" form
type PredatorPrey <: AbstractLotkaVolterra
    α::Float64
    β::Float64
    δ::Float64
    γ::Float64
    function PredatorPrey(α::Float64,β::Float64,δ::Float64,γ::Float64)
        all([α,β,δ,γ] .> 0.) ? new(α,β,δ,γ) : error("all arguments must be positive")
    end
end

nspecies(Z::PredatorPrey ) = 2
communitymatrix(Z::PredatorPrey ) = [0. -Z.β; Z.δ 0.]
intrinsicrate(Z::PredatorPrey) = [Z.α, -Z.β]

somecycle(Z::PredatorPrey) = true
somecycle(Z::PredatorPrey,sector::Vector{Int64}) = sector==[1,2]

function incycle(Z::PredatorPrey,x::Vector{Float64})
  return (length(x) == 2) && all(x .> 0.) && (x != fixedpoint(Z))
end

cycle(Z::PredatorPrey,x::Vector{Float64}) = "returns a cycle (whatever that is) corresponding to point"
cycles(Z::PredatorPrey) = "returns a family of cycles... somehow"
