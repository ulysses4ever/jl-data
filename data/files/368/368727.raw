# Carretera 1D mejorado

module carretera1D2

export Vehiculo, Carretera1D
export Celda_Vacia!, Cambiar_Vehiculo!, Insertar_Carro!, Pos_izq
export agregar!, agregar_sencillo!
export AcelerarRuido, DesacelerarMover, Medir

type Vehiculo
    velocidad::Int64
    posicion::Int64
    tipo::Int64
    cambio::Int64
    num::Int64
end


type Carretera1D
	cuenta::Int64
	N::Int64
	carretera::Vector{Vehiculo}
end

function Carretera1D(N)
    carretera = Vehiculo[]
    for i in 1:N
    # Aquí no es necesario poner la función Celda_Vacia
        celda = Vehiculo(-1, i, -1, 0, 0)
        push!(carretera, celda)
    end
    return Carretera1D(0, N, carretera)
end

function Celda_Vacia!(v)
    v.velocidad = -1
    v.tipo = -1
    v.cambio = 0
    v.num = 0
end

function Cambiar_Vehiculo!(V, vel, pos, tipo, cambio, num)
    V.velocidad = vel
    V.posicion = pos
    V.tipo = tipo
    V.cambio = cambio
    V.num = num
end

function Insertar_Carro!(carretera, p::Float64, num::Int64)
    frontera_izq = 5
    vmax = [3, 5]

    lim = frontera_izq+1
    while carretera[lim].tipo == -1 && lim < (frontera_izq+vmax[2])
        lim += 1
    end
    v_nueva = ( rand() <= p ? vmax[1] : vmax[2] )
    pos_nueva = min( lim - vmax[2], v_nueva)
    tipo = (v_nueva == vmax[1] ? 1 : 2 )
    Cambiar_Vehiculo!(carretera[pos_nueva], v_nueva, pos_nueva, tipo, 1, num)

    lim = 0; v_nueva = 0; pos_nueva = 0; tipo = 0;
end

function AcelerarRuido(carretera)

    frontera_izq = 5
    vmax = [3, 5]
    R = 0.2
    for v in carretera[frontera_izq+1:end]
        if v.tipo == 1 || v.tipo == 2

            #Acelerar
            if v.velocidad != -1
                Cambiar_Vehiculo!(v, min(v.velocidad+1, vmax[v.tipo]), v.posicion, v.tipo, v.cambio, v.num)
            end

            #Ruido
            if v.velocidad > 0
                if rand() <= R
                    Cambiar_Vehiculo!(v, max(v.velocidad-1, 0), v.posicion, v.tipo, v.cambio, v.num)
                end
            end
        end
    end
end


function Pos_izq(carretera)

    gap = carretera[end].posicion

    while gap >= 1 && carretera[gap].tipo == -1
        gap -= 1
    end
    gap
end


function DesacelerarMover(C)
    alfa = 0.75
    frontera_izq = 5
    i = Pos_izq(C.carretera)
    if i != 0
      i_1 = Pos_izq(C.carretera[1:i-1])
  elseif i == 0
      i_1 = 0
  end

    # Este if es para el primer paso en el que solo hay un coche. Este no se desacelera y unicamente se mueve
    if i_1 == 0
        pos_sig = C.carretera[i].velocidad + C.carretera[i].posicion
        if C.carretera[i].posicion != pos_sig

            if pos_sig <= C.N
                Cambiar_Vehiculo!(C.carretera[pos_sig], C.carretera[i].velocidad, pos_sig, C.carretera[i].tipo, 0, C.carretera[i].num)

                if C.carretera[i].posicion <= frontera_izq && pos_sig > frontera_izq
                    C.cuenta += 1
                end
            else
                C.cuenta -= 1
            end

            Celda_Vacia!(C.carretera[i])
        end
    end

    # Este while es para los pasos siguientes
    while (i_1 >= 1)
        distancia = i - i_1 - 1

        # Desaceleramos el automovil i-1 a partir del automovil i
        velocidad_estimada = int( floor( C.carretera[i].velocidad * (1.0 - alfa) + 0.5 ) )
        Cambiar_Vehiculo!(C.carretera[i_1], min( (velocidad_estimada+distancia), C.carretera[i_1].velocidad),
                            C.carretera[i_1].posicion, C.carretera[i_1].tipo, C.carretera[i_1].cambio, C.carretera[i_1].num)

        # Movemos el automovil i

        pos_sig = C.carretera[i].velocidad + C.carretera[i].posicion
        if C.carretera[i].posicion != pos_sig

            if pos_sig <= C.N
                Cambiar_Vehiculo!(C.carretera[pos_sig], C.carretera[i].velocidad, pos_sig, C.carretera[i].tipo, 0, C.carretera[i].num)

                if C.carretera[i].posicion <= frontera_izq && pos_sig > frontera_izq
                    C.cuenta += 1
                end
            else
                C.cuenta -= 1
            end

            Celda_Vacia!(C.carretera[i])
        end

        # Reindexamos el automovil i-1 como el automovil i

        i = i_1
        i_1 = Pos_izq(C.carretera[1:i-1])
    end
end


  # El codigo que sigue es para hacer las mediciones de densidad, flujo y velocidad

  # Las dos funciones siguientes son solo auxiliares

function agregar_sencillo!(array_velocidad, array_flujo, array_densidad, i, t)

    v = ( array_densidad[i, t] != 0 ? array_flujo[i, t]/array_densidad[i, t] : 0 )
    array_velocidad[i, t] += v
end

function agregar!(i, j, t, x_seccion, v, array, array1, array2, T)

    if v.velocidad > 0
        if j-v.velocidad < x_seccion
            array[i, t] += 1/T

            if v.tipo == 1
                array1[i, t] += 1/T
            end
            if v.tipo == 2
                array2[i, t] += 1/T
            end
        end
    end
end

  # Y luego la funcion donde se mide

function Medir(C, t, Secciones, flujo_local, densidad_local ,
               velocidad_local_promedio, flujo_local1, densidad_local1 ,velocidad_local_promedio1,
               flujo_local2, densidad_local2 , velocidad_local_promedio2)


    T = 1. # T es el periodo de tiempo por el cual se mide

    for (i, x_seccion) in enumerate(Secciones)

        # Medicion del flujo local
        for j = x_seccion+4:-1:x_seccion
            agregar!(i, j, t, x_seccion, C.carretera[j], flujo_local, flujo_local1, flujo_local2, T)
        end


        # Medicion de la densidad local
        for j = x_seccion+4:-1:x_seccion
            agregar!(i, j, t, x_seccion, C.carretera[j], densidad_local, densidad_local1, densidad_local2,
                    T*C.carretera[j].velocidad)
        end

        # Medicion de la velocidad promedio espacial

        agregar_sencillo!( velocidad_local_promedio, flujo_local, densidad_local, i, t )
        agregar_sencillo!( velocidad_local_promedio1, flujo_local1, densidad_local1, i, t )
        agregar_sencillo!( velocidad_local_promedio2, flujo_local2, densidad_local2, i, t )
    end
end

end
