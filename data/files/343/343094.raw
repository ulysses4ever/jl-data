module Histeresis

export MicroEstado, edo_inicial, edo_aleatorio, magnetizacion_aumenta_H!

type MicroEstado
    σ::Array{Int,2}
    h::Array{Float64,2}
    #Vamos a suponer que todas las configuraciones son cuadradas
    L::Int
end

import Base.show

show(io::IO, m::MicroEstado) = print(io, m.σ)

function edo_inicial(L::Int, R, espin::Int)
    σ = espin*ones(Int, (L,L))

    h = Array(Float64, (L,L))
    for i in 1:L^2
        h[i] = R*randn()
    end

    MicroEstado(σ, h, L)
end

function edo_aleatorio(L::Int, R)
    σ = rand(0:1, (L,L))*2 - 1

    h = Array(Float64, (L,L))
    for i in 1:L^2
        h[i] = R*randn()
    end

    MicroEstado(σ, h, L)
end

function criterio_espin(m::MicroEstado, i::Int, j::Int)
    σ = m.σ ; L = m.L

    σ[mod1(i-1, L),j] + σ[mod1(i+1, L),j] + σ[i,mod1(j-1, L)] + σ[i,mod1(j+1, L)] + m.h[i,j]
end

function voltea_espin!(m::MicroEstado, i::Int, j::Int)
    m.σ[i,j] *= -1
end

function max_abajo(m::MicroEstado, valor_min, espin::Int)
    tmp = Array(Float64,(m.L,m.L))

    for i = 1:m.L, j = 1:m.L
        if m.σ[i,j] == espin
            tmp[i,j] = -espin*criterio_espin(m,i,j)
        else
            tmp[i,j] = valor_min
        end
    end

    f = findmax(tmp) # Da el máximo y el índice lineal del máximo
	# Traducimos el índice lineal a dos índices matriciales
    i = mod1(f[2], m.L)
    j = int(ceil(f[2]/m.L))

    espin*f[1], i, j
end

function espines_vecinos_abajo(m::MicroEstado, i::Int, j::Int, espin::Int)
    vecinos = [ (mod1(i-1,m.L),j), (mod1(i+1,m.L),j), (i,mod1(j-1,m.L)), (i,mod1(j+1,m.L)) ]
    vecinos_abajo = (Int,Int)[]

    for k in vecinos
        if m.σ[k...] == espin
            push!(vecinos_abajo, k)
        end
    end

    vecinos_abajo
end

function avalancha_abajo!(m::MicroEstado, i::Int, j::Int, H::Float64, espin::Int)
    voltea_espin!(m,i,j)
    espines_volteados = [(i,j)]

    candidatos = espines_vecinos_abajo(m,i,j,espin)

    while length(candidatos) > 0
        nuevos_candidatos = (Int,Int)[]

        for k in candidatos
            if m.σ[k...] == espin
                if  -espin*(criterio_espin(m,k...) + H) > 0
                    voltea_espin!(m,k...)
                    push!(espines_volteados,k)
                    nuevos_candidatos = vcat(nuevos_candidatos, espines_vecinos_abajo(m,k...,espin))
                end
            end
        end

        candidatos = nuevos_candidatos
    end

    m, espines_volteados
end

magnetizacion(m::MicroEstado) = sum(m.σ)

function magnetizacion_aumenta_H!(m::MicroEstado, H_set, espin::Int)
    valor_min = -(maximum(abs(m.h)))-5
    N = m.L^2
    mag = [magnetizacion(m)]

    H,i,j = max_abajo(m, valor_min, espin)
    hs = [H]

    while -espin*(hs[end] - H_set) < 0 && mag[end] != -espin*N
        push!(hs, H)
        m, volteados = avalancha_abajo!(m,i,j,H, espin)
        ΔM = -2espin*length(volteados)
        push!(mag, mag[end] + ΔM)
        H,i,j = max_abajo(m, valor_min, espin)
    end

    mag, hs
end

# function microEstados_aumenta_H(m::MicroEstado, num_pasos::Int)
#     energia_minima = minimum(m.h)-5
#     edos = Array{Int,2}[copy(m.σ)] #Si no se hace ésto, nada más se copia el apuntador
#     sizehint(edos, num_pasos)

#     for i in 1:num_pasos-1
#         H,i,j = max_energia_abajo(m,energia_minima)
#         avalancha_abajo(m,i,j,H)
#         push!(edos, copy(m.σ))
#     end

#     edos
# end

end
