
# El tipo Gato guarda la configuración de un juego

type Gato
    juego_A::Array{Int}
    juego_B::Array{Int}
    representacion::Array{ASCIIString}
    turno::Bool
    cuenta_turnos::Int
end

import Base.show

function show(io::IO, g::Gato)
    rep  = g.representacion
    for reng in 1:3
        print(io, rep[reng,1], "\t", rep[reng,2], "\t", rep[reng,3], "\n")
    end
end



# Las funciones


# Crea un juego vacío

function nvo_juego()
    turno = true
    A = zeros(Int, 3, 3)
    B = zeros(Int, 3, 3)

    repr = Array(ASCIIString, (3, 3))
    fill!(repr, ".")

    Gato(A, B, repr, turno)
end


# Prueba si el arreglo que se le da como argumento es una configuración ganadora

function prueba_ganador(M::Array{Int})
    v = sum(M, 1)
    h = sum(M, 2)
    diagonal = diag(M)
    otra_diag = [M[1, 3], M[2, 2], M[3, 1]]

    if diagonal == [1, 1, 1] || otra_diag == [1, 1, 1]
        return true
    else
        for i in 1:3
            if v[i] == 3 || h[i] == 3
                return true
            end
        end
    end

    false
end


# Hace efectiva la tirada de un jugador

function tirada(g::Gato, pos::Int)
    if g.turno
        g.juego_A[pos] = 1
        g.representacion[pos] = "X"
    else
        g.juego_B[pos] = 1
        g.representacion[pos] = "O"
    end
end


# Verifica que la posción que se escoge es una casilla vacía

function tiro_valido(g::Gato, pos::Int)
    if g.juego_A[pos] == 0 && g.juego_B[pos] == 0
        true
    else
        false
    end
end


# Un turno del juego

function turno(g::Gato)
    pos_valida = false

    while !pos_valida
        pos = readline(STDIN)
        pos = Int(pos[1]) - 48

        if tiro_valido(g, pos) # Si la tirada es válida...

            tirada(g, pos)

            if g.turno # ... y es el turno del primer jugador
                ganador = prueba_ganador(g.juego_A) # Evalúa true o false
            else
                ganador = prueba_ganador(g.juego_B)
            end

            if ganador
                return true
            else
                # Si no hay un ganador, es el turno del siguiente jugador
                g.turno = !g.turno
                return false
            end
        else
            println("Sitio ocupado")
        end
    end
end


# El juego completo: crea un juego vacío y después llama a la función turno mientras no haya un ganador,
# y siempre y cuando no pasemos de 9 turnos

function juego_gato()
    g = nvo_juego()

    while g.cuenta_turnos < 9
        continua = turno(g)
        println(g)

        if continua
            break
        end

        g.cuenta_turnos += 1
    end

    println("Empate")
end