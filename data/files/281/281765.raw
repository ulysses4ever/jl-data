module Histeresis

export MicroEstado, edo_inicial, magnetizacion_aumenta_H, magnetizacion_disminuye_H, microEstados_aumenta_H

type MicroEstado
    σ::Array{Int,2}
    h::Array{Float64,2}
    #Vamos a suponer que todas las configuraciones son cuadradas
    L::Int
end

import Base.show

show(io::IO, m::MicroEstado) = print(io, m.σ)

function edo_inicial(L::Int)
    σ = -ones(Int, (L,L))

    h = Array(Float64, (L,L))
    for i in 1:L^2
        # Temporal, hay que cambiar la distribución
        h[i] = randn()
    end

    MicroEstado(σ, h, L)
end


function energia_espin(m::MicroEstado, i::Int, j::Int)
    σ = m.σ ; L = m.L

    #Tal vez deberíamos de cambiar el signo de la energía
    σ[i,j]*( σ[mod1(i-1, L),j] + σ[mod1(i+1, L),j] + σ[i,mod1(j-1, L)] + σ[i,mod1(j+1, L)] ) +
    m.h[i,j]
end

function voltea_espin_abajo!(m::MicroEstado, i::Int, j::Int)
    if m.σ[i,j] == -1
        m.σ[i,j] *= -1
    end
end

function voltea_espin_arriba!(m::MicroEstado, i::Int, j::Int)
    if m.σ[i,j] == 1
        m.σ[i,j] *= -1
    end
end

function max_energia_abajo(m::MicroEstado,min_energia)
    energias = Array(Float64,(m.L,m.L))

    for i = 1:m.L, j = 1:m.L
        if m.σ[i,j] == -1
            energias[i,j] = energia_espin(m,i,j)
        else
            energias[i,j] = min_energia
        end
    end

    #Si cambiamos signo de la energía sería findmin
    f = findmax(energias) # Da el máximo y el índice lineal del máximo
    i = mod1(f[2], m.L)
    j = int(ceil(f[2]/m.L))

    -f[1], i, j
end

function min_energia_arriba(m::MicroEstado,max_energia)
    energias = Array(Float64,(m.L,m.L))

    for i = 1:m.L, j = 1:m.L
        if m.σ[i,j] == 1
            energias[i,j] = energia_espin(m,i,j)
        else
            energias[i,j] = max_energia
        end
    end

    f = findmin(energias) # Da el máximo y el índice lineal del máximo
    i = mod1(f[2], m.L)
    j = int(ceil(f[2]/m.L))

    f[1], i, j
end

function espines_vecinos_abajo(m::MicroEstado,i::Int,j::Int)
    vecinos = [ (mod1(i-1,m.L),j), (mod1(i+1,m.L),j), (i,mod1(j-1,m.L)), (i,mod1(j+1,m.L)) ]
    vecinos_abajo = (Int,Int)[]

    for k in vecinos
        if m.σ[k...] == -1
            push!(vecinos_abajo, k)
        end
    end

    vecinos_abajo
end

function espines_vecinos_arriba(m::MicroEstado,i::Int,j::Int)
    vecinos = [ (mod1(i-1,m.L),j), (mod1(i+1,m.L),j), (i,mod1(j-1,m.L)), (i,mod1(j+1,m.L)) ]
    vecinos_arriba = (Int,Int)[]

    for k in vecinos
        if m.σ[k...] == 1
            push!(vecinos_arriba, k)
        end
    end

    vecinos_arriba
end

function avalancha_abajo(m::MicroEstado, i::Int, j::Int, H::Float64)
    voltea_espin_abajo!(m,i,j)
    #puede haber un problema, si se escoje de entrada un espín que ya está volteado
    espines_volteados = [(i,j)]

    candidatos = espines_vecinos_abajo(m,i,j)

    while length(candidatos) > 0
        nuevos_candidatos = (Int,Int)[]

        for k in candidatos
            if energia_espin(m,k...) < H # H es negativo en un principio
                voltea_espin_abajo!(m,k...)
                push!(espines_volteados,k)
                nuevos_candidatos = vcat(nuevos_candidatos, espines_vecinos_abajo(m,k...))
            end
        end

        candidatos = nuevos_candidatos
    end

    m, espines_volteados
end

function avalancha_arriba(m::MicroEstado, i::Int, j::Int, H::Float64)
    voltea_espin_arriba!(m,i,j)
    #puede haber un problema, si se escoje de entrada un espín que ya está volteado
    espines_volteados = [(i,j)]

    candidatos = espines_vecinos_arriba(m,i,j)

    while length(candidatos) > 0
        nuevos_candidatos = (Int,Int)[]

        for k in candidatos
            if energia_espin(m,k...) > H # H es positivo en un principio
                voltea_espin_arriba!(m,k...)
                push!(espines_volteados,k)
                nuevos_candidatos = vcat(nuevos_candidatos, espines_vecinos_abajo(m,k...))
            end
        end

        candidatos = nuevos_candidatos
    end

    m, espines_volteados
end

magnetizacion(m::MicroEstado) = sum(m.σ)

function magnetizacion_aumenta_H(m::MicroEstado)
    energia_minima = minimum(m.h)-5
    N = m.L^2
    mag = [magnetizacion(m)]
    hs = [0.]

    while mag[end] < N
        H,i,j = max_energia_abajo(m,energia_minima)
        push!(hs, H)
        m, volteados = avalancha_abajo(m,i,j,H)
        ΔM = 2*length(volteados)
        #Ojo: esto sólo sirve porque volteamos espines hacia arriba
        push!(mag, mag[end] + ΔM)
    end

    mag, hs
end

function magnetizacion_disminuye_H(m::MicroEstado)
    max_energia = maximum(m.h)+5
    N = m.L^2
    mag = [magnetizacion(m)]
    hs = [0.]

    while mag[end] > -N
        H,i,j = min_energia_arriba(m,max_energia)
        push!(hs, H)
        m, volteados = avalancha_arriba(m,i,j,H)
        ΔM = -2*length(volteados)
        #Ojo: esto sólo sirve porque volteamos espines hacia abajo
        push!(mag, mag[end] + ΔM)
    end

    mag, hs
end

function microEstados_aumenta_H(m::MicroEstado, num_pasos::Int)
    energia_minima = minimum(m.h)-5
    edos = Array{Int,2}[copy(m.σ)] #Si no se hace ésto, nada más se copia el apuntador
    sizehint(edos, num_pasos)

    for i in 1:num_pasos-1
        H,i,j = max_energia_abajo(m,energia_minima)
        avalancha_abajo(m,i,j,H)
        push!(edos, copy(m.σ))
    end

    edos
end

end
