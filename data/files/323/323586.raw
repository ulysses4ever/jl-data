module ChargedParticle_Base

import Base.(+)
import Base.(/)
import Base.(-)
import Base.(*)
import Base.(norm)

export ChargedParticle,Vector3d,+,/,-,norm


const elemCharge = 1.0#1.6e-19;

type Vector3d
  x::Float64
  y::Float64
  z::Float64
end

function +(a::Vector3d,b::Vector3d)
  Vector3d(a.x+b.x,a.y+b.y,a.z+b.z)
end

function -(a::Vector3d,b::Vector3d)
  Vector3d(a.x-b.x,a.y-b.y,a.z-b.z)
end

function *(a::Float64,b::Vector3d)
  Vector3d(a*b.x,a*b.y,a*b.z)
end


function /(a::Float64,b::Vector3d)
  Vector3d(a/b.x,a/b.y,a/b.z)
end

function /(a::Vector3d,b::Float64)
  Vector3d(a.x/b,a.y/b,a.z/b)
end

function norm(v::Vector3d)
  sqrt(v.x^2+v.y^2+v.z^2)
end

type ChargedParticle
  mass::Float64
  charge::Float64
  mobility::Float64
  location::Vector3d
  active::Bool
end

ChargedParticle(location::Vector3d,charge::Float64) = ChargedParticle(
  1.0,
  charge*elemCharge,
  2e-4,
  location,
  true
  )

ChargedParticle(location::Vector3d) = ChargedParticle(location,1.0)

end
