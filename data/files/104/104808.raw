#Pkg.add("DataStructures")
using DataStructures
using Base.Collections
include("archivos.jl")
include("export_kml.jl")
include("a_estrella.jl")

#include("datastructures/heaps/binary_heap.jl")
#include("datastructures/disjoint_set.jl")
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

#elegimos las rutas a considerar


#cargarlas al heap. si se puede pasasr directamente, así;
#si no, iterar sobre las llaves, agregarlas a un array y
#luego iniciar el heap

aristas_iter = obtener_obj_aristas(grafo)
nodos = obtener_nodos(grafo)

aristas = Array{Ruta}(0)
for elm in aristas_iter
	#print(elm.score,"\n")
	append!(aristas,[elm])
end
#for elm in aristas_iter
#append!(aristas,[elm])
#end

grafo_final = Grafo{Ciudad,Ruta}()


heap_aristas = BinaryHeap{Ruta,RutaCompScore}(RutaCompScore(),aristas)
conj_disj_nodos = DisjointSets{AbstractString}(nodos)


print("num groups:",num_groups(conj_disj_nodos))
print(" length: ",length(nodos))

while num_groups(conj_disj_nodos) > 1
	arista_actual = pop!(heap_aristas)
	cdad1 = string(arista_actual.id_ciudad_1)
	cdad2 = string(arista_actual.id_ciudad_2)
	
	if !in_same_set(conj_disj_nodos, cdad1, cdad2) || arista_actual.score > 16000 # es el cuartil mas alto
		union!(conj_disj_nodos, cdad1, cdad2)
		if(!pertenece(grafo_final,cdad1))
			agregar_nodo(grafo_final,cdad1, nodo_obtener(grafo,cdad1))
		end
		
		if(!pertenece(grafo_final,cdad2))
			agregar_nodo(grafo_final,cdad2, nodo_obtener(grafo,cdad2))
		end
		#print("Agregamos arista\n")
		agregar_arista(grafo_final,cdad1,cdad2,string(arista_actual.id_ruta),arista_actual)
	end
end

print("Antes:",cantidad_aristas(grafo)," Despues: ",cantidad_aristas(grafo_final)," \n")
exportar_grafo_kml(grafo_final,"grafo_final.kml")

#ahora lo mismo, pero para el tendido minimo

grafo_tendido = Grafo{Ciudad,Ruta}()

aristas_iter = obtener_obj_aristas(grafo_final)
aristas = Array{Ruta}(0)
for elm in aristas_iter
	append!(aristas,[elm])
end

heap_aristas = BinaryHeap{Ruta,RutaCompDist}(RutaCompDist(),aristas)
conj_disj_nodos = DisjointSets{AbstractString}(nodos)


print("num groups:",num_groups(conj_disj_nodos))
print(" length: ",length(nodos))

while num_groups(conj_disj_nodos) > 1
	arista_actual = pop!(heap_aristas)
	cdad1 = string(arista_actual.id_ciudad_1)
	cdad2 = string(arista_actual.id_ciudad_2)
	
	if !in_same_set(conj_disj_nodos, cdad1, cdad2)
		union!(conj_disj_nodos, cdad1, cdad2)
		if(!pertenece(grafo_tendido,cdad1))
			agregar_nodo(grafo_tendido,cdad1, nodo_obtener(grafo,cdad1))
		end
		
		if(!pertenece(grafo_tendido,cdad2))
			agregar_nodo(grafo_tendido,cdad2, nodo_obtener(grafo,cdad2))
		end
		#print("Agregamos arista\n")
		agregar_arista(grafo_tendido,cdad1,cdad2,string(arista_actual.id_ruta),arista_actual)
	end
end

print("Antes:",cantidad_aristas(grafo_final)," Despues: ",cantidad_aristas(grafo_tendido)," \n")
exportar_grafo_kml(grafo_tendido,"grafo_tendido_minimo.kml")

#Camino minimo entre ciudad 1 y ciudad 2
camino,costo = a_estrella(grafo,"1","2")

caminito = Grafo{Ciudad,Ruta}()
for (destino,origen) in camino
	if (origen == Void)
		continue
	end
	nodo_origen = Nodo{Ciudad}(grafo.nodos[origen].propiedades,Dict())

	nodo_destino = Nodo{Ciudad}(grafo.nodos[destino].propiedades,Dict())

	id_tramo = grafo.nodos[origen].adyacentes[destino]
	tramo = grafo.aristas[id_tramo]
	agregar_nodo(caminito,origen,grafo.nodos[origen].propiedades)
	agregar_nodo(caminito,destino,grafo.nodos[origen].propiedades)
	agregar_arista(caminito,origen,destino,id_tramo,tramo)
end


exportar_grafo_kml(caminito,"caminito.kml")
exportar_grafo_kml(grafo,"grafo_prueba.kml")
