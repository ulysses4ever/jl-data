#Pkg.add("DataStructures")
using DataStructures
using Base.Collections
include("archivos.jl")
include("export_kml.jl")
include("a_estrella.jl")


#PROCESAMIENTO DE ARCHIVOS

print("PROCESANDO ARCHIVOS... \n")

grafo = Grafo{Ciudad,Ruta}() #MAPA CON TODAS LAS RUTAS

procesar_ciudades(grafo, "ciudades.csv")


procesar_rutas(grafo, "rutas.csv")


#PRUEBAS

function prueba(texto::AbstractString, resultado::Bool)
	if resultado
		print("[OK]    ")
	else
		print("[ERROR] ")
	end
	print(texto,"\n")
end
function generar_grafo_final(grafo::Grafo)

	aristas_iter = obtener_obj_aristas(grafo)
	nodos = obtener_nodos(grafo)
	
	aristas = Array{Ruta}(0)
	for elm in aristas_iter
		append!(aristas,[elm])
	end
	grafo_final = Grafo{Ciudad,Ruta}()


	heap_aristas = BinaryHeap{Ruta,RutaCompScore}(RutaCompScore(),aristas)
	conj_disj_nodos = DisjointSets{AbstractString}(nodos)
	

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
	grafo_final
end
function generar_tendido_min(grafo_final::Grafo) 

	nodos = obtener_nodos(grafo_final)
	grafo_tendido = Grafo{Ciudad,Ruta}()

	aristas_iter = obtener_obj_aristas(grafo_final)
	aristas = Array{Ruta}(0)
	for elm in aristas_iter
		append!(aristas,[elm])
	end

	heap_aristas = BinaryHeap{Ruta,RutaCompDist}(RutaCompDist(),aristas)
	conj_disj_nodos = DisjointSets{AbstractString}(nodos)


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
	grafo_tendido
end


#SELECCION DE RUTAS

#cargarlas al heap. si se puede pasar directamente, así;
#si no, iterar sobre las llaves, agregarlas a un array y
#luego iniciar el heap

print("SELECCIONANDO RUTAS...\n")

#VARIACION DE KRUSKAL

grafo_final = generar_grafo_final(grafo)

#EXPORTO EL ARBOL CON RUTAS SELECCIONADAS

print("EXPORTANDO RUTAS...\n")
exportar_grafo_kml(grafo_final,"red.kml")


#ARBOL DE TENDIDO MINIMO

print("REALIZANDO ARBOL DE TENDIDO MINIMO...\n")

#KRUSKAL
grafo_tendido = generar_tendido_min(grafo_final)


#EXPORTO EL ARBOL DE TENDIDO MINIMO

print("EXPORTANDO TENDIDO ELECTRICO...\n")
exportar_grafo_kml(grafo_tendido,"tendido.kml")

#CAMINO MINIMO ENTRE CIUDADES SOLICITADAS

trazar_camino = true

while trazar_camino
	print("Ingrese el codigo de una de las ciudades...\n")
	ciudad_1 = strip(readline(STDIN))
	print("Ingrese el codigo de la otra ciudad...\n")
	ciudad_2 = strip(readline(STDIN))
	camino = Dict{AbstractString,AbstractString}
		
	try
		camino,costo = a_estrella(grafo_final,ciudad_1,ciudad_2)
	catch(KeyError)
		print("ID invalido\n")
		continue
	end
	
	objetivo = ciudad_2
	destino = objetivo
	origen = camino[destino]
	caminito = Grafo{Ciudad,Ruta}()
	
	while origen != Void
		nodo_origen = Nodo{Ciudad}(grafo_final.nodos[origen].propiedades,Dict())
		nodo_destino = Nodo{Ciudad}(grafo_final.nodos[destino].propiedades,Dict())
		id_tramo = grafo_final.nodos[origen].adyacentes[destino]
		tramo = grafo_final.aristas[id_tramo]
		agregar_nodo(caminito,origen,grafo_final.nodos[origen].propiedades)
		agregar_nodo(caminito,destino,grafo_final.nodos[destino].propiedades)
		agregar_arista(caminito,origen,destino,id_tramo,tramo)
		destino = origen
		origen = camino[destino]
	end

	print("EXPORTANDO CAMINO ENTRE CIUDADES...\n")
	exportar_grafo_kml(caminito,join(("ruta_",ciudad_1,"_",ciudad_2,".kml")))

	print("Desea trazar otro camino? (Y/N)")
	rta = strip(readline(STDIN))
	if (rta == "N") | (isspace(rta))
		trazar_camino = false
	end
end
