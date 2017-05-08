include("archivos.jl")
include("export_kml.jl")
include("a_estrella.jl")

grafo = Grafo{Ciudad,Ruta}()

procesar_ciudades(grafo, "ciudades.csv")

print(grafo.tamanio)

procesar_rutas(grafo, "rutas.csv")


##pruebas!
function prueba(texto::AbstractString, resultado::Bool)
	if resultado
		print("[OK]    ")
	else
		print("[ERROR] ")
	end
	print(texto,"\n")
end

print("hacemos pruebas\n")
prueba("Ciudad existe", pertenece(grafo,"1"))
prueba("Ciudad existe", pertenece(grafo,"37"))
prueba("Ciudad no existe", !pertenece(grafo,"40"))

prueba("Arista existe", arista_existe(grafo,"1","2"))
prueba("Arista existe (simetria)", arista_existe(grafo,"2","1"))
prueba("Arista no existe", !arista_existe(grafo,"6","2"))

prueba("Obtener arista no es falso", arista_obtener(grafo,"1","2") != false)
prueba("Obtener arista es falso", arista_obtener(grafo,"6","2") == false)

prueba("Obtener valor da bien",arista_obtener(grafo,"1","2").puntaje == 1526342)


#Camino minimo entre ciudad 1 y ciudad 2
camino,costo = a_estrella(grafo,"1","2")

caminito = Grafo{Ciudad,Ruta}()
for (destino,origen) in camino
	if (origen == Void)
		continue
	end
	nodo_origen = Nodo_Ciudad(grafo.nodos[origen].propiedades,Dict())

	nodo_destino = Nodo_Ciudad(grafo.nodos[destino].propiedades,Dict())

	id_tramo = grafo.nodos[origen].adyacentes[destino]
	tramo = grafo.aristas[id_tramo]
	agregar_nodo(caminito,origen,nodo_origen)
	agregar_nodo(caminito,destino,nodo_destino)
	agregar_arista(caminito,origen,destino,id_tramo,tramo)
end


exportar_grafo_kml(caminito,"caminito.kml")
exportar_grafo_kml(grafo,"grafo_prueba.kml")
