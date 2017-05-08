type Vehiculo
    velocidad::Int8
    posicion::Int64
    tipo::Int8
    cambio::Int8
    num::Int64
end

type Carretera1D
	cuenta::Int64
	N::Int64
	carretera::Vector{Vehiculo}
end

function Carretera1D(N::Int64)
    carretera = Vehiculo[]
    for i in 1:N
    # Aquí no es necesario poner la función Celda_Vacia
        celda = Vehiculo(round(Int8, -1), i, round(Int8, -1), zero(Int8), 0)
        push!(carretera, celda)
    end
    return Carretera1D(0, N, carretera)
end

type Carretera2D
  carriles::Int8
  carretera::Vector{Carretera1D}
end

function Carretera2D(carriles::Int64, N::Int64)
    C = Carretera1D[]
    if carriles > 1
        for i = 1:carriles
            push!(C, Carretera1D(N))
        end
        return Carretera2D(round(Int8,carriles), C)
    end
    if carriles == 1
        return Carretera1D(N)
    end
end