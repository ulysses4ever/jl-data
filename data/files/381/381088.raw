
# Incluimos el módulo que escribimos con el juego, y la biblioteca para trabajar con ventanas Gtk
include("gato.jl")
using .Gato
using Gtk.ShortNames


# Comienza un juego

t = nvo_juego()


# Esta función es la que hace que el juego y la interfaz se hablen. Se llama con la señal de un click sobre un botón.

button_clicked_cb(widget) = button_clicked_cb(widget, t)

function button_clicked_cb(widget, t::Tablero)
	# Pedimos la posicíon del click, que es el nombre del botón
	pos = getproperty(widget, :label, AbstractString)
	pos = Int(pos[1]) - 48 # Lo convertimos a un entero entre 1 y 9

	# Si el botón ya había sido escogido, no hace nada
	if !tiro_valido(t,pos)
		return
	end

	# Mandamos la posición del click a la función que actualiza el tiro. Regresa true si hubo un ganador.
	termina, ganador = turno(t, pos)

	# Si hay ganador:
	if termina
# 		info_dialog("Gana "*ganador*"!")
		Gtk.gtk_quit()
		println("Gana ", ganador, "!")
	end

	println(t)

	# Si no hubo ganador, incrementa el número de turnos, para terminar el juego si hubo empate.
	if t.cuenta_turnos < 8
		t.cuenta_turnos +=1
	else
# 		info_dialog("Empate!")
		Gtk.gtk_quit()
		println("Empate!")
	end

# 	caracter = t.representacion[pos]
# 	setproperty!(widget, :label, caracter)
end

include("gui.jl")
