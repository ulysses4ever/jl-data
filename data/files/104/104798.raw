type Nodo{Propiedades}
	propiedades :: Propiedades
	adyacentes :: Dict{AbstractString,Int} #Clave: String Valor:Int
end

type Grafo
	tamanio::Int
	nodos::Dict{AbstractString,Nodo{Any}}
end


function agregar_nodo(grafo::Grafo,clave::AbstractString,nodo::Nodo)
	if !(clave in keys(grafo.nodos))
		grafo.nodos[clave]=Nodo
		grafo.tamanio += 1
	end
end

function agregar_arista(grafo::Grafo,clave_origen::AbstractString,clave_destino::AbstractString,peso::Int)
	if (clave_origen in keys(grafo.nodos)) & (clave_destino in keys(grafo.nodos))
		grafo.nodos[clave_origen].adyacentes[clave_destino] = peso
	end
end

function ver_adyacentes(grafo::Grafo, clave::AbstractString)
	if (clave in keys(grafo.nodos))
		return grafo.nodos[clave].adyacentes
	end
end

function pertenece(grafo::Grafo, clave::AbstractString)
	if (clave in keys(grafo.nodos))
		return True
	end
	return False
end

function borrar_nodo(grafo::Grafo,clave::AbstractString)
	if (clave in keys(grafo.nodos))
		for nodo in values(grafo.nodos)
			delete!(nodo.adyacentes,clave)
		end
		delete!(nodo,clave)
	end
end

function borrar_arista(grafo::Grafo,clave_origen::AbstractString,clave_destino::AbstractString)
	if (clave_origen in keys(grafo.nodos)) & (clave_destino in keys(grafo.nodos))
		delete!(grafo.nodos[clave_origen].adyacentes,clave_destino)
	end
end
