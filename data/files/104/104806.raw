#Pkg.add("DataStructures")
using DataStructures
#include("datastructures/heaps/binary_heap.jl")
#include("datastructures/disjoint_set.jl")
include("archivos.jl")

grafo = Grafo{Ciudad,Ruta}()


procesar_ciudades(grafo, "ciudades.csv")

#print(grafo.tamanio)

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

#elegimos las rutas a considerar


#cargarlas al heap. si se puede pasasr directamente, así;
#si no, iterar sobre las llaves, agregarlas a un array y
#luego iniciar el heap


aristas = obtener_obj_aristas(grafo)
nodos = obtener_nodos(grafo)

grafo_final = Grafo{Ciudad,Ruta}()


heap_aristas = BinaryHeap{Ruta}(comparar_rutas,aristas)
conj_disj_nodos = DisjointSets{AbstractString}(nodos)

threshold = 15

while num_groups(conj_disj_nodos) < length(conj_disj_nodos)
	arista_actual = pop!(heap_aristas)
	cdad1 = arista_actual.id_ciudad1
	cdad2 = arista_actual.id_ciudad2
	if !in_same_set(conj_disj_nodos, cdad1, cdad2) || arista_actual.score > threshold
		union!(conj_disj_nodos, cdad1, cdad2)
		if(!pertenece(grafo_final,cdad1))
			agregar_nodo(grafo_final,cdad1,prop::Any)
		end
		if(!pertenece(grafo_final,cdad2))
			agregar_nodo(grafo_final,cdad2,prop::Any)
		end
		agregar_arista(grafo_final,cdad1,cdad2,string(arista_actual.id_ruta),arista_actual)
	end
end
#ahora esta todo en grafo_final
#hay que imprimirlo..
