using Gtk.ShortNames

g = @Grid()
win = @Window(g, "Gato", 300, 300, false, true)

b1 = @Button("1")
b2 = @Button("2")
b3 = @Button("3")
b4 = @Button("4")
b5 = @Button("5")
b6 = @Button("6")
b7 = @Button("7")
b8 = @Button("8")
b9 = @Button("9")

g[1, 1] = b1
g[1, 2] = b2
g[1, 3] = b3
g[2, 1] = b4
g[2, 2] = b5
g[2, 3] = b6
g[3, 1] = b7
g[3, 2] = b8
g[3, 3] = b9

setproperty!(g, :column_homogeneous, true)
setproperty!(g, :column_spacing, 15)
setproperty!(g, :row_homogeneous, true)
setproperty!(g, :row_spacing, 15)
showall(win)

function button_clicked(widget)
	pos = getproperty(widget, :label, AbstractString)
	pos = Int(pos[1]) - 48
	println(pos)
# 	println(getproperty(widget, :label, AbstractString))
# 	setproperty!(widget, :label, "ON")
end

signal_connect(button_clicked, b1, :clicked)
signal_connect(button_clicked, b2, :clicked)
signal_connect(button_clicked, b3, :clicked)
signal_connect(button_clicked, b4, :clicked)
signal_connect(button_clicked, b5, :clicked)
signal_connect(button_clicked, b6, :clicked)
signal_connect(button_clicked, b7, :clicked)
signal_connect(button_clicked, b8, :clicked)
signal_connect(button_clicked, b9, :clicked)

signal_connect(win, :destroy) do widget
    Gtk.gtk_quit()
end
Gtk.gtk_main()
