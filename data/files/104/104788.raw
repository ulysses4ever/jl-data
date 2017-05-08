function agregar_lugares_de_interes(ciudades::Dict{Int64,Nodo_Ciudad},arch::IOStream)
	write(arch,("<Placemark>"))
	for ciudad in values(ciudades)
		write(arch,join(("\t<name>",ciudad.nombre,"</name>")))
		write(arch,"\t<Point>")
		write(arch,join(("\t\t<coordinates>",ciudad.longitud,", ",ciudad.latitud,"</coordinates>")))
		write(arch,"\t</Point>")
	end
	write(arch,("</Placemark>"))
end

function agregar_rutas(ciudades::Dict{Int64,Nodo_Ciudad},rutas::Dict{Int64,Ruta},arch::IOStream) #¿HAY UNA FORMA MAS LINA DE DEFINIR TODO ESTO?, PODRIAMOS HACER UN TIPO MAPA
	write(arch,("<Placemark>"))
	for ruta in values(rutas)
		write(arch,"\t<LineString>")
		ciudad_1 = ciudades[ruta.id_ciudad_1]
		ciudad_2 = ciudades [ruta.id_ciudad_2]
		write(arch,join(("\t\t<coordinates>",ciudad_1.longitud,", ",ciudad_1.latitud," ",ciudad_2.longitud,", ",ciudad_2.latitud, "</coordinates>")))
		write(arch,"\t</LineString>")
	end
	write(arch,("</Placemark>"))
end	

function exportar_grafo_kml(mapa::Grafo,nombre_archivo::AbstractString)
	arch = open(nombre_archivo,"w")
	write(arch,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
	write(arch,"<kml xmlns=\"http://earth.google.com/kml/2.1\">\n")
	write(arch,"\t<Document>\n")
	write(arch,join(("<name>",nombre_archivo,"</name>\n")))
	
	agregar_lugares_de_interes(mapa.nodos,arch)
	agregar_rutas(mapa.aristas,arch)

	write(arch,"\t</Document>\n")
	write(arch,"</kml>\n")
	close(arch)
end
