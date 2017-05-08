#include("./objects.jl")

module Rules

importall Objects

export mover, dtcolision, colision

@doc doc"""Update the position of the Disk through moving it as a free particle with velocity Disk.v
during a time interval dt"""->
mover(p::Particula, dt::Real) = p.r += p.v * dt

@doc doc"""Calculates the time of collision between the Disk and a VerticalWall"""->
function dtcolision(p::Particula, V::ParedVertical)
    #La pared siempre va a estar acotada por números positivos
    dt = Inf
    if p.v[1] > 0
        if p.r[1] < V.x
            dt = (V.x - (p.r[1] + p.radio))/p.v[1]
        end
    elseif p.v[1] < 0
        if p.r[1] > V.x
            dt = ((p.r[1] - p.radio) - V.x)/-p.v[1]
        end
    end
    dt
end


#Hacer esto con metaprogramming o con un macro!

@doc doc"""Calculates the time of collision between the Disk and a HorizontallWall"""->
function dtcolision(p::Particula, H::ParedHorizontal)
    dt = Inf
    if p.v[2] > 0
        if p.r[2] < H.y
            dt = (H.y - (p.r[2] + p.radio))/p.v[2]
        end
    elseif p.v[2] < 0
        if p.r[2] > H.y
            dt = ((p.r[2] - p.radio) - H.y)/-p.v[2]
        end
    end
    dt
end

@doc doc"""Calculates the time of collision between two Disks."""->
function dtcolision(p1::Particula,p2::Particula)
    deltar = p1.r - p2.r
    deltav = p1.v - p2.v
    rdotv = dot(deltar, deltav)
    rcuadrado = dot(deltar,deltar)
    vcuadrado = dot(deltav, deltav)
    if rdotv >= 0
        return Inf
    end
    d = (rdotv)^2 -(vcuadrado)*(rcuadrado - (p1.radio + p2.radio)^2)
    if d < 0
        return Inf
    end
    #dt = min((-rdotv+ sqrt(d))/vcuadrado, (-rdotv - sqrt(d))/vcuadrado)
    dt = (rcuadrado - (p1.radio + p2.radio)^2)/(-rdotv + sqrt(d))
    return dt
end

@doc doc"""Update the velocity vector of a disk (Disk.v) after it collides with a VerticalWall."""->
function colision(p1::Particula, V::ParedVertical )
    p1.v = [-p1.v[1], p1.v[2]]
end

@doc doc"""Update the velocity vector of a disk (Disk.v) after it collides with a HorizontallWall."""->
function colision(p1::Particula, H::ParedHorizontal )
    p1.v = [p1.v[1],-p1.v[2]]
end

@doc doc"""Update the velocity vector of two Disks after they collides."""->
function colision(p1::Particula, p2::Particula)
    deltar = p1.r - p2.r
    deltav = p1.v - p2.v
    h = dot(deltar,deltav)
    sigma = p1.radio+p2.radio
    J = 2*p1.m*p2.m*h/(sigma*(p1.m + p2.m))
    p1.v -= J*deltar/(sigma*p1.m)
    p2.v += J*deltar/(sigma*p2.m)
end

end
