using DataStructures

type Ciudad
	nombre :: AbstractString
	longitud :: Float64
	latitud :: Float64
	provincia :: Int64
	habitantes :: Int64
end

typealias Nodo_Ciudad Nodo{Ciudad}

type Ruta
	id_ruta :: Int32
	id_ciudad_1 :: Int32
	id_ciudad_2 :: Int32
	puntaje :: Float64
	distancia :: Float64 
	score :: Float64
end

function armar_score(distancia::Float64,puntaje::Float64,poblacion::Int64)
	return (poblacion *4pi*10.0^(-7) * puntaje)/sqrt(distancia)
end

#sera un heap de maximo asi?
function comparar_rutas(ruta1::Ruta,ruta2::Ruta)
	if ruta1.score < ruta2.score
		return -1
	elseif ruta1.score > ruta2.score
		return 1
	else
		return 0
	end
end

function comparar_dist(ruta1::Ruta,ruta2::Ruta)
	if ruta1.distancia < ruta2.distancia
		return -1
	elseif ruta1.distancia > ruta2.distancia
		return 1
	else
		return 0
	end
end

immutable RutaCompScore
end

immutable RutaCompDist
end

DataStructures.compare(c::RutaCompScore,r1::Ruta,r2::Ruta) = comparar_rutas(r1,r2) > 0 # heap de max
DataStructures.compare(c::RutaCompDist, r1::Ruta,r2::Ruta) = comparar_dist(r1,r2)  < 0 # heap de min
