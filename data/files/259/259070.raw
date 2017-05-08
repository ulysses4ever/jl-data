function Celda_Vacia!(v::Vehiculo)
    v.velocidad = int8(-1)
    v.tipo = int8(-1)
    v.cambio = int8(0)
    v.num = 0
end

function Obstaculo!(v::Vehiculo)
    v.velocidad = int8(-1)
    v.tipo = int8(-2)
    v.cambio = int8(0)
    v.num = int8(0)
end

function Cambiar_Vehiculo!(v, vel, pos, tipo, cambio, num)
    v.velocidad = int8(vel)
    v.posicion = int64(pos)
    v.tipo = int8(tipo)
    v.cambio = int8(cambio)
    v.num = num
end

## Hay que tener cuidado con Insertar_Carro! para solo llamarla en celdas vacias

function Insertar_Carro!(carretera, num::Int64, p::Float64, vmax::Array{Int8, 1} = Int8[3, 5], frontera_izq::Int8 = int8(5) )
    #frontera_izq = 5
    #vmax = [3, 5]

    lim = frontera_izq + int8(1)
    while carretera[lim].tipo == -1 && lim < (frontera_izq+vmax[2])
        lim += int8(1)
    end
    v_nueva = ( rand() <= p ? vmax[1] : vmax[2] )
    pos_nueva = min( lim - vmax[2], v_nueva)
    tipo = (v_nueva == vmax[1] ? 1 : 2 )
    Cambiar_Vehiculo!(carretera[pos_nueva], v_nueva, pos_nueva, tipo, 1, num)

    lim = 0; v_nueva = 0; pos_nueva = 0; tipo = 0;
    frontera_izq = 0; vmax = 0
end



############## La funcion Vehiculo_Adelante cuenta a los obstáculos

function Vehiculo_Adelante( posicion, Carretera, N)
    i = posicion
    while i < N && Carretera[i].tipo == -1
        i += 1
    end
    i
end

############ La funcion Vehiculo_Atras NO cuenta los obstáculos

function Vehiculo_Atras( posicion, Carretera, N, frontera_izq::Int8 = int8(5) )
    #frontera_izq = 5

    i = posicion - 1
    while i > frontera_izq && (Carretera[i].tipo == -1 || Carretera[i].tipo == -2)
        i -= 1
    end

    if i > frontera_izq
        return i
    else
        return N
    end
end

function Pos_izq(carretera)

    gap = carretera[end].posicion

    while gap >= 1 && (carretera[gap].tipo == -1 || carretera[gap].tipo == -2)
        gap -= 1
    end
    gap
end

function Pos_izq9(carretera)

    gap = carretera[end].posicion

    while gap >= 9 && (carretera[gap].tipo == -1 || carretera[gap].tipo == -2)
        gap -= 1
    end
    gap
end

function Pos_der(carretera)
    x = carretera[1].posicion
    i = 1
    while x < carretera[end].posicion && (carretera[i].tipo == -1 ||carretera[i].tipo == -2)
        x += 1
        i += 1
    end
    x
end

function Pos_siguiente(carretera)
    x = carretera[end].posicion
    i = length(carretera)
    while x > carretera[1].posicion && (carretera[i].tipo == 1 || carretera[i].tipo == 2)
        x -= 1
        i -= 1
    end
    x
end


