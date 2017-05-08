
include("gato.jl")
using .Gato
using Gtk.ShortNames

t = nvo_juego()

button_clicked(widget) = button_clicked(widget, t)

function button_clicked(widget, t::Tablero)
	pos = getproperty(widget, :label, AbstractString)
    pos = Int(pos[1]) - 48

	if !tiro_valido(t,pos)
		return
	end

	if turno(t, pos)
		Gtk.gtk_quit()
	end
	println(t)

    if t.cuenta_turnos < 8
		t.cuenta_turnos +=1
    else
		Gtk.gtk_quit()
        println("Empate")
	end

# 	setproperty!(widget, :label, "ON")
end

include("gui.jl")
