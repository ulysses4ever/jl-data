include("graph.jl")

type Ciudad{}
	nombre :: AbstractString
	longitud :: Int64
	latitud :: Int64
	provincia :: Int32
	habitantes :: Int32
end

typealias Nodo_Ciudad Nodo{Ciudad}

type Ruta{}
	id_ciudad_1 :: Int32
	id_ciudad_2 :: Int32
	puntaje :: Int32
	distancia :: Int32 
end


#Recibe un mapa (grafo) y agrega las ciudades
function procesar_ciudades(mapa::Grafo, nombre_archivo::AbstractString)
	arch_ciudades = readdlm(nombre_archivo,'\t',header=true) 
		#Crea una tupla, primer elemento una matriz con datos, segundo un array del header
	ciudades = arch_ciudades[1]
	cant_filas = size(ciudades)[1] 
	mapa = Grafo(0,Dict()) #Creo grafo vacio
	for i in 1:cant_filas
		id = ciudades[i,:][1]
		nombre = ciudades[i,:][2]
		longitud = ciudades[i,:][3]
		latitutd = ciudades[i,:][4]
		provincia = ciudades[i,:][5]
		habitantes = ciudades[i,:][6]
		ciudad = Ciudad(nombre,longitud,latitud,provincia,habitantes)
		nodo_ciudad = Nodo_Ciudad(ciudad,Dict())
		agregar_nodo(mapa,id,nodo_ciudad)
    end
 end


#Recibe un mapa (grafo) y agrega las rutas, devuelve un diccionario con todas las rutas
function procesar_rutas(mapa::Grafo, nombre_archivo::AbstractString)
	arch_rutas = readdlm(nombre_archivo,'\t',header=true) 
	rutas = arch_rutas[1]
	cant_filas = size(rutas)[1] 
	rutas = Dict{AbstractString,Ruta}
	for i in 1:cant_filas
		id = rutas[i,:][1]
		id_ciudad_1 = rutas[i,:][2]
		id_ciudad_2 = rutas[i,:][3]
		puntaje = rutas[i,:][4]
		distancia = distancia[i,:][5]
		ruta = Ruta(id_ciudad_1,id_ciudad_2,puntaje,distancia)
		agregar_arista(mapa,id)
		rutas[id] = ruta
    end
    return rutas
end

 