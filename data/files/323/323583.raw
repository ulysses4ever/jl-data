module ChargedParticle_Base

export ChargedParticle

const elemCharge = 1.6e-19;

type ChargedParticle
  mass::Float64
  charge::Float64
  mobility::Float64
  location::Array{Float64,1}
  active::Bool
end

ChargedParticle(location::Array{Float64,1},charge::Float64) = ChargedParticle(
  1.0,
  charge*elemCharge,
  2e-4,
  location,
  true
  )

ChargedParticle(location::Array{Float64,1}) = ChargedParticle(location,1.0)

end
