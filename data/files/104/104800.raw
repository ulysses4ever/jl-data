type Nodo{Propiedades}
	propiedades :: Propiedades
	#El diccionario almacena (clave,valor) == (destino, indice)
	#donde "indice" es la referencia a la arista, que esta en el grafo
	adyacentes :: Dict{AbstractString,AbstractString} #Clave: String Valor:String
end

type Grafo{PropiedadesNodo,PropiedadesArista}
	tamanio::Int
	nodos::Dict{AbstractString,Nodo{PropiedadesNodo}}
	aristas::Dict{AbstractString, PropiedadesArista}
	#Constructor
	#No tiene parametros; siempre se inicia en 0
	#y las claves de los diccionarios deben ser AbstractString
	function Grafo()
		new(0,Dict{AbstractString,PropiedadesNodo}(),Dict{AbstractString,PropiedadesArista}())
	end
end

function agregar_nodo(grafo::Grafo,clave::AbstractString,prop::Any)
	if !haskey(grafo.nodos,clave)
		nodo = Nodo(prop,Dict{AbstractString,AbstractString}())
		grafo.nodos[clave]=nodo
		grafo.tamanio += 1
	end
end
#void agregar_arista(Grafo grafo, String origen, String destino, String id, Void* Objeto)
function agregar_arista(grafo::Grafo,clave_origen::AbstractString,clave_destino::AbstractString, id_arista::AbstractString, prop_arista::Any)
	if haskey(grafo.nodos,clave_origen) && haskey(grafo.nodos,clave_destino)
		grafo.aristas[id_arista] = prop_arista
		grafo.nodos[clave_origen].adyacentes[clave_destino] = id_arista
		grafo.nodos[clave_destino].adyacentes[clave_origen] = id_arista
	end
end

function ver_adyacentes(grafo::Grafo, clave::AbstractString)
	if haskey(grafo.nodos,clave)
		return keys(grafo.nodos[clave].adyacentes)
	end
end

function pertenece(grafo::Grafo, clave::AbstractString)
	return haskey(grafo.nodos,clave)
end

function arista_existe(grafo::Grafo, origen::AbstractString, destino::AbstractString) 
	return pertenece(grafo,origen) && pertenece(grafo,destino) && haskey(grafo.nodos[origen].adyacentes,destino)
end

function arista_existe_id(grafo::Grafo, id_arista::AbstractString)
	return haskey(grafo.aristas,id_arista)
end

function nodo_obtener(grafo::Grafo, clave::AbstractString)
	pertenece(grafo,clave) && return grafo.nodos[clave].propiedades
	return false # en caso de que no exista
end
function arista_obtener(grafo::Grafo, origen::AbstractString, destino::AbstractString)
	arista_existe(grafo,origen,destino) && return grafo.aristas[grafo.nodos[origen].adyacentes[destino]]
	return false # en caso de que no exista
end

#esto no va a funcionar(se puede corregir despues, no es necesario por ahora..)
function borrar_nodo(grafo::Grafo,clave::AbstractString)
	if haskey(grafo.nodos,clave)
		for nodo in values(grafo.nodos)
			delete!(nodo.adyacentes,clave)
		end
		delete!(nodo,clave)
	end
end

function borrar_arista(grafo::Grafo,clave_origen::AbstractString,clave_destino::AbstractString)
	if haskey(grafo.nodos,clave_origen) && haskey(grafo.nodos,clave_destino)
		delete!(grafo.nodos[clave_origen].adyacentes,clave_destino)
	end
end

function obtener_nodos(grafo::Grafo)
	return keys(grafo.nodos)
end
function obtener_aristas(grafo::Grafo)
	return keys(grafo.aristas)
end
function obtener_obj_aristas(grafo::Grafo)
	return values(grafo.aristas)
end