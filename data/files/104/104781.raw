using Base.Collections

haversine(lat1,lon1,lat2,lon2) = 2 * 6372.8 * asin(sqrt(sind((lat2-lat1)/2)^2 + cosd(lat1) * cosd(lat2) * sind((lon2 - lon1)/2)^2))

function heuristica(nodo1::Nodo_Ciudad,nodo2::Nodo_Ciudad)
	return haversine(nodo1.propiedades.latitud,nodo1.propiedades.longitud,nodo2.propiedades.latitud,nodo2.propiedades.longitud)
end

function a_estrella(mapa::Grafo, id_comienzo::AbstractString, id_objetivo::AbstractString)
	cola = PriorityQueue()
	enqueue!(cola,id_comienzo,0)
	origen = Dict()
	costo = Dict()
	origen[id_comienzo] = Void
	costo[id_comienzo] = 0
	objetivo = mapa.nodos[id_objetivo]
	while !(isempty(cola))
		id_actual = dequeue!(cola)
		if id_actual == id_objetivo
			break
		end
		for (id_siguiente,id_ruta) in mapa.nodos[id_actual].adyacentes
			nuevo_costo = costo[id_actual] + mapa.aristas[id_ruta].distancia

			#ESTA ASQUEROSO ESTO, CODEARLO MAS LINDO
			
			nuevo_costo_es_menor = false
			if (id_siguiente in keys(costo))
				if nuevo_costo<costo[id_siguiente]
					nuevo_costo_es_menor = true
				end
			end
			if !(id_siguiente in keys(costo))|nuevo_costo_es_menor
				siguiente = mapa.nodos[id_siguiente]
				costo[id_siguiente] = nuevo_costo
				prioridad = nuevo_costo + heuristica(objetivo,siguiente)
				enqueue!(cola,id_siguiente,prioridad)
				origen[id_siguiente] = id_actual
			end
		end
	end
	return (origen,costo)
end
