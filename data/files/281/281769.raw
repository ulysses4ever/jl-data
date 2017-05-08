module Histeresis

export MicroEstado, edo_inicial, edo_aleatorio, magnetizacion_aumenta_H!, microEstados_aumenta_H!

#######################################   NOTA   #####################################

# Los nombres de las funciones que siguen son heredados de la 1er versión que se realizó,
# en donde al comenzar todos los espines apuntaban hacia abajo y el campo externo H se
# incrementaba. De ahí que los nombres sean max_abajo, espines_vecinos_abajo, avalancha_abajo!
# etc. Se agregó el parámetro espin, igual a -1,+1, y que decide hacia donde los espines
# originalmente, y en que sentido evoluciona el campo H. Si espin=-1, apuntan hacia abajo y H
# aumenta, si espin=+1 apuntan hacia arriba y H disminuye.

######################################################################################


# El tipo que define a los objetos que vamos a utilizar. σ es un arreglo que contiene espines,
# h es es campo aleatorio
type MicroEstado
    σ::Array{Int,2}
    h::Array{Float64,2}
    L::Int # La longitud del cuadrado de espines
	N::Int # El númeto total de espines
end

import Base.show

show(io::IO, m::MicroEstado) = print(io, m.σ)

# Un par de funciones para generar un estado inicial
# La primera genera un edo con todos los espines apuntando en una sóla dirección, dada por espin
function edo_inicial(L::Int, R, espin::Int)
    σ = espin*ones(Int, (L,L))

    h = Array(Float64, (L,L))
    for i in 1:L^2
        h[i] = R*randn()
    end

    MicroEstado(σ, h, L, L^2)
end

# Esta segunda función genera un estado con espines apuntando aleatoriamente arriba o abajo.
function edo_aleatorio(L::Int, R)
    σ = rand(0:1, (L,L))*2 - 1

    h = Array(Float64, (L,L))
    for i in 1:L^2
        h[i] = R*randn()
    end

    MicroEstado(σ, h, L, L^2)
end

# Esta función es importante para decidir cuándo se voltea un espín. Nos da una parte de la
# enegía de un espín, si quitamos el valor mismo del espín. El valor que regresa esta función se
# suma con el campo externo H y compara con cero.
function criterio_espin(m::MicroEstado, i::Int, j::Int)
    σ = m.σ ; L = m.L

    σ[mod1(i-1, L),j] + σ[mod1(i+1, L),j] + σ[i,mod1(j-1, L)] + σ[i,mod1(j+1, L)] + m.h[i,j]
end

# El nombre es bastante indicativo...
function voltea_espin!(m::MicroEstado, i::Int, j::Int)
    m.σ[i,j] *= -1
end

# Encuentra el espín con máxima o mínima energía, y con el que se va a desatar una avalancha
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

# Encuentra a los vecinos de un espín dado, que no han sido volteados aún
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

# A partir de un espín inicial, propaga una avalancha
function avalancha_abajo!(m::MicroEstado, i::Int, j::Int, H::Float64, espin::Int)
    voltea_espin!(m,i,j)
    num_volteados = 1

    candidatos = espines_vecinos_abajo(m,i,j,espin)

    while length(candidatos) > 0
        nuevos_candidatos = (Int,Int)[]

        for k in candidatos
            if m.σ[k...] == espin
                if  -espin*(criterio_espin(m,k...) + H) > 0
                    voltea_espin!(m,k...)
                    num_volteados += 1
                    nuevos_candidatos = vcat(nuevos_candidatos, espines_vecinos_abajo(m,k...,espin))
                end
            end
        end

        candidatos = nuevos_candidatos
    end

    m, num_volteados
end

# La magnetización total de un MicroEstado
magnetizacion(m::MicroEstado) = sum(m.σ)

# La función que calcula la evolución de la magnetización al cambiar H. Si espin=-1, los
# espines apuntan en un pirncipio hacia abajo y el campo aumenta para voltearlos. Si espin=+1
# ocurre lo contrario
function magnetizacion_aumenta_H!(m::MicroEstado, H_set, espin::Int)
    valor_min = -(maximum(abs(m.h)))-5
    mag = [magnetizacion(m)]

    H,i,j = max_abajo(m, valor_min, espin)
    hs = [H]

	volteados = Int[]

    while -espin*(hs[end] - H_set) < 0 && mag[end] != -espin*m.N
        push!(hs, H)
        m, num_volteados = avalancha_abajo!(m,i,j,H, espin)
        ΔM = -2espin*num_volteados
        push!(mag, mag[end] + ΔM)
		push!(volteados, num_volteados)
        H,i,j = max_abajo(m, valor_min, espin)
    end

    mag, hs, volteados
end

# Esta funcón regresa las matrices σ al cambiar el campo (incrementar o disminuir H, según el
# valor de espin).
function microEstados_aumenta_H!(m::MicroEstado, H_set, espin::Int)
    valor_min = -(maximum(abs(m.h)))-5
	mag = [magnetizacion(m)]

	H,i,j = max_abajo(m, valor_min, espin)
	hs = [H]

	edos = Array{Int,2}[copy(m.σ)] #Si no se hace ésto, nada más se copia el apuntador

    while -espin*(hs[end] - H_set) < 0 && mag[end] != -espin*m.N
        push!(hs, H)
        m, num_volteados = avalancha_abajo!(m,i,j,H, espin)
        ΔM = -2espin*num_volteados
        push!(mag, mag[end] + ΔM)
        push!(edos, copy(m.σ))
		H,i,j = max_abajo(m, valor_min, espin)
    end

    edos
end

end
