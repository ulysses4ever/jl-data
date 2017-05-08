function agregar_lugares_de_interes(ciudades::Dict{AbstractString,Nodo_Ciudad},arch::IOStream)
	for ciudad in values(ciudades)
		write(arch,("\t\t<Placemark>\n"))
		write(arch,join(("\t\t\t<name>",ciudad.propiedades.nombre,"</name>\n")))
		write(arch,"\t\t\t<Point>\n")
		write(arch,join(("\t\t\t\t<coordinates>",ciudad.propiedades.longitud,", ",ciudad.propiedades.latitud,"</coordinates>\n")))
		write(arch,"\t\t\t</Point>\n")
		write(arch,("\t\t</Placemark>\n\n"))
	end
end

function agregar_rutas(ciudades::Dict{AbstractString,Nodo_Ciudad},rutas::Dict{AbstractString,Ruta},arch::IOStream) #¿HAY UNA FORMA MAS LINA DE DEFINIR TODO ESTO?, PODRIAMOS HACER UN TIPO MAPA
	for ruta in values(rutas)
		write(arch,("\t\t<Placemark>\n"))
		write(arch,"\t\t\t<LineString>\n")
		ciudad_1 = ciudades[string(ruta.id_ciudad_1)]
		ciudad_2 = ciudades[string(ruta.id_ciudad_2)]
		write(arch,join(("\t\t\t\t<coordinates>",ciudad_1.propiedades.longitud,", ",ciudad_1.propiedades.latitud," ",ciudad_2.propiedades.longitud,", ",ciudad_2.propiedades.latitud, "</coordinates>\n")))
		write(arch,"\t\t\t</LineString>\n")
		write(arch,("\t\t</Placemark>\n\n"))
	end
end	

function exportar_grafo_kml(mapa::Grafo,nombre_archivo::AbstractString)
	arch = open(nombre_archivo,"w")
	write(arch,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
	write(arch,"<kml xmlns=\"http://earth.google.com/kml/2.1\">\n")
	write(arch,"\t<Document>\n")
	write(arch,join(("\t\t<name>",nombre_archivo,"</name>\n\n")))

	agregar_lugares_de_interes(mapa.nodos,arch)
	agregar_rutas(mapa.nodos,mapa.aristas,arch)

	write(arch,"\t</Document>\n")
	write(arch,"</kml>\n")
	close(arch)
end
