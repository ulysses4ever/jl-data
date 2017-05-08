module Objects

export Objeto, Pared, Particula, ParedVertical, ParedHorizontal, Evento

abstract Objeto
abstract Pared <: Objeto

type Particula{T<:Number} <: Objeto
    r::Array{T,1}
    v::Array{T,1}
    radio::T
    m::T
    etiqueta::Int
end

Particula(r,v,radio) = Particula(r,v,radio,1.0,0) #masa fija de 1.0 y etiqueta igual a 1
Particula(r,v,radio, masa) = Particula(r,v,radio, masa ,0) #masa fija de 1.0 y etiqueta igual a 0

type ParedVertical{T<:Number} <:Pared
    x :: T
    y :: Array{T,1}
end

type ParedHorizontal{T<:Number} <:Pared
    x :: Array{T,1}
    y :: T
end

type Evento
    tiempo :: Number
    p1::Particula
    Q ::Objeto
    etiqueta :: Int
end

end
