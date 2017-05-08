module Objects

export Objeto, Pared, Particula, ParedVertical, ParedHorizontal, Evento

abstract Objeto
abstract Pared <: Objeto

@doc doc"""Type with attributes position(r), velocity, radius, mass and label. Both position and velocity
are vectors. The label attribute corresponds to the cycle within the main loop in which the Disk suffered
its last collision (see simulacionanimada in *main.jl*) """->
type Particula{T<:Number} <: Objeto
  r::Array{T,1}
  v::Array{T,1}
  radio::T
  m::T
  etiqueta::Int
end

Particula(r,v,radio) = Particula(r,v,radio,1.0,0) #Fixed mass of 1.0 and label equal to 0 (by default)
Particula(r,v,radio, masa) = Particula(r,v,radio, masa ,0) #Label equal to 0 (by default)

@doc doc"""Type with attributes x and y. x corresponds to its horizontal position in a Cartesian Plane
(just a number) and y represents its initial and final height in the Plane (Array of length equal to 2)."""  ->
type ParedVertical{T<:Number} <:Pared
  x :: T
  y :: Array{T,1}
end

@doc doc"""Type with attributes x and y. x corresponds to its horizontal extension in a Cartesian plane
(initial and final position -Array of length equal to 2- and y corresponds to its vertical position
(a number).""" ->
type ParedHorizontal{T<:Number} <:Pared
  x :: Array{T,1}
  y :: T
end


@doc doc"""Type with attributes time, collider1, collider2 and label. The label makes reference to the cycle
within the main loop in which the event was predicted (see simulacionanimada in main.jl)."""->
type Evento
  tiempo :: Number
  p1::Particula
  Q ::Objeto
  etiqueta :: Int
end

end
