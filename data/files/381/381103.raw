
module Gato

export Tablero, nvo_juego, tiro_valido, turno
import Base.show


# El tipo Tablero guarda la configuración de un juego

type Tablero
	juego_A::Array{Int}
	juego_B::Array{Int}
	representacion::Array{ASCIIString}
	turno::Bool
	cuenta_turnos::Int
end

function show(io::IO, t::Tablero)
	rep  = t.representacion
	for reng in 1:3
		print(io, rep[reng,1], "\t", rep[reng,2], "\t", rep[reng,3], "\n")
	end
end



# Las funciones


# Crea un juego vacío

function nvo_juego()
	turno = true
	cuenta_turnos = 0
	A = zeros(Int, 3, 3)
	B = zeros(Int, 3, 3)

	repr = Array(ASCIIString, (3, 3))
	fill!(repr, ".")

	Tablero(A, B, repr, turno, cuenta_turnos)
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


# Verifica que la posción que se escoge es una casilla vacía

function tiro_valido(t::Tablero, pos::Int)
	if t.juego_A[pos] == 0 && t.juego_B[pos] == 0
		true
	else
		false
	end
end


# Hace efectiva la tirada de un jugador

function tirada(t::Tablero, pos::Int)
	if t.turno
		t.juego_A[pos] = 1
		t.representacion[pos] = "X"
	else
		t.juego_B[pos] = 1
		t.representacion[pos] = "O"
	end
end


# Un turno del juego

function turno(t::Tablero, pos::Int)
	tirada(t, pos)

	if t.turno
		termina = prueba_ganador(t.juego_A)
		ganador = "X"
	else
		termina = prueba_ganador(t.juego_B)
		ganador = "O"
	end

	if termina
		return true, ganador
	else
		# Si no hay un ganador, es el turno del siguiente jugador
		t.turno = !t.turno
		return false, ""
	end
end


end # Termina módulo Gato
