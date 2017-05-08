include("graph.jl")
include("estructuras.jl")


#Recibe un mapa (grafo) y agrega las ciudades
function procesar_ciudades(mapa::Grafo, nombre_archivo::AbstractString)
	#Crea una tupla, primer elemento una matriz con datos, segundo un array del header
	arch_ciudades = readdlm(nombre_archivo,'\t',header=true) 
	#Dejamos en "ciudades" la matriz
	ciudades = arch_ciudades[1]
	cant_filas = size(ciudades)[1] 
	for i in 1:cant_filas
		id = ciudades[i,:][1] #Int64
		nombre = ciudades[i,:][2] #SubString
		longitud = ciudades[i,:][3] #Float64
		latitud = ciudades[i,:][4] #Float64
		provincia = ciudades[i,:][5] #Int64
		habitantes = ciudades[i,:][6] #Int64
		ciudad = Ciudad(nombre,longitud,latitud,provincia,habitantes)
		agregar_nodo(mapa,string(id),ciudad)
    end
 end


#Recibe un mapa (grafo) y agrega las rutas(aristas)
function procesar_rutas(mapa::Grafo, nombre_archivo::AbstractString)
	arch_rutas = readdlm(nombre_archivo,'\t',header=true) 
	rutas = arch_rutas[1]
	cant_filas = size(rutas)[1] 
	for i in 1:cant_filas
		id = convert(Int64,rutas[i,:][1])
		id_ciudad_1 = convert(Int64,rutas[i,:][2]) #viene como Float64
		id_ciudad_2 = convert(Int64,rutas[i,:][3]) #idem
		puntaje = rutas[i,:][4]
		distancia = rutas[i,:][5]
		suma_poblacion = nodo_obtener(mapa,string(id_ciudad_1)).habitantes + nodo_obtener(mapa,string(id_ciudad_2)).habitantes

		score = armar_score(distancia,puntaje,suma_poblacion)
		
		ruta = Ruta(id,id_ciudad_1,id_ciudad_2,puntaje,distancia,score)
		#void agregar_arista(Grafo grafo, String origen, String destino, String id, Void* Objeto)

		agregar_arista(mapa,string(id_ciudad_1),string(id_ciudad_2),string(id),ruta)

		
    end
end

 
