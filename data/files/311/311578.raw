# Carretera 2D

module carretera2D

export Vehiculo, Carretera1D, Carretera2D
export Celda_Vacia!, Obstaculo!, Cambiar_Vehiculo!, Cambiar_Carril!, Insertar_Carro!, Rampa!, CambioIzq_Der!, CambioDer_Izq!
export Vehiculo_Atras, Vehiculo_Adelante, Pos_siguiente, Pos_der, Pos_izq, Pos_izq9, distancia_seguridad
export agregar!, agregar_sencillo!
export AcelerarRuido, DesacelerarMover, Medir, Espacio_Tiempo!, Tiempo_Promedio_Entrada!, Tiempo_Promedio_Salida!

#################### Tipos #####################

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


############################ Funciones Auxiliares ####################################

function Celda_Vacia!(v::Vehiculo)
    v.velocidad = Int8(-1)
    v.tipo = Int8(-1)
    v.cambio = Int8(0)
    v.num = 0
end

function Obstaculo!(v::Vehiculo)
    v.velocidad = Int8(-1)
    v.tipo = Int8(-2)
    v.cambio = Int8(0)
    v.num = Int8(0)
end

function Cambiar_Vehiculo!(v, vel, pos, tipo, cambio, num)
    v.velocidad = Int8(vel)
    v.posicion = pos
    v.tipo = Int8(tipo)
    v.cambio = Int8(cambio)
    v.num = num
end

## Hay que tener cuidado con Insertar_Carro! para solo llamarla en celdas vacias

function Insertar_Carro!(carretera, num::Int64, p::Float64, vmax::Array{Int8, 1} = Int8[3, 5], frontera_izq::Int8 = Int8(5) )
    #frontera_izq = 5
    #vmax = [3, 5]

    lim = frontera_izq + Int8(1)
    while carretera[lim].tipo == -1 && lim < (frontera_izq+vmax[2])
        lim += Int8(1)
    end
    v_nueva = ( rand() <= p ? vmax[1] : vmax[2] )
    pos_nueva = min( lim - vmax[2], v_nueva)
    tipo = (v_nueva == vmax[1] ? 1 : 2 )
    Cambiar_Vehiculo!(carretera[pos_nueva], v_nueva, pos_nueva, tipo, 1, num)

    lim = 0; v_nueva = 0; pos_nueva = 0; tipo = 0;
    frontera_izq = 0; vmax = 0
end

function Cambiar_Carril!(v0::Vehiculo, Cuenta0, C1::Carretera1D)

    i = v0.posicion
    if C1.carretera[i].tipo == -1

        pvbo = Vehiculo_Atras(i, C1.carretera, C1.N)
        d_bo = (pvbo < (C1.N) ? (i-pvbo-1) : 5 ) # 5 = vmax[2]
        vb = C1.carretera[pvbo].velocidad
        if vb <= d_bo

            Cambiar_Vehiculo!( C1.carretera[i], v0.velocidad, v0.posicion, v0.tipo, 1, v0.num)
            Celda_Vacia!( v0 )
            Cuenta0 -= 1
            C1.cuenta += 1
        end
    end
end

function Vehiculo_Adelante( posicion, Carretera, N)
    i = posicion
    while i < N && Carretera[i].tipo == -1
        i += 1
    end
    i
end

function Vehiculo_Atras( posicion, Carretera, N, frontera_izq::Int8 = Int8(5) )
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

function distancia_seguridad(i, Carretera1, N, delta, alfa::Float32 = 0.75f0)

    pvfo = Vehiculo_Adelante(i, Carretera1, N)
    d_ifo = (pvfo < N ? (pvfo-i-1) : delta*5 ) # 5 = vmax[2]
    dfo = d_ifo + Int8( floor( (1.-alfa) * Carretera1[pvfo].velocidad + 0.5) )
    alfa = 0; pvfo = 0; d_ifo = 0
    return dfo
end

function Rampa!( tipo, x0, lramp, pin, p, Ck, num, vmax::Array{Int8, 1} = Int8[3, 5])
    #vmax = [3, 5]

    if tipo == 0
        x = Pos_der(Ck.carretera[x0:x0+lramp])
        if x <= x0+lramp && rand() < pin
            if Ck.cuenta > 0
                Ck.cuenta -= 1
            end
            Celda_Vacia!(Ck.carretera[x])
        end

    elseif tipo == 1
        x = Pos_siguiente(Ck.carretera[x0:x0+lramp])
        if x <= x0+lramp && rand() < pin
          Ck.cuenta += 1
          v_nueva = (rand() <= p ? vmax[1] : vmax[2])
          tipo_nuevo = (v_nueva == vmax[1] ? 1 : 2)
          Cambiar_Vehiculo!( Ck.carretera[x], v_nueva, x, tipo_nuevo, 1, num)
        end
        v_nueva = 0; tipo_nuevo = 0
    end
    x = 0
end

function CambioIzq_Der!(Ck, Ckmenos1, k)

    for v in Ck.carretera[end:-1:9]
        if (v.tipo == 1 || v.tipo == 2) && v.cambio == 0

            delta = v.tipo == 2 ? Int8(3) : Int8(1)
            l = v.velocidad
            dfo = distancia_seguridad(v.posicion, Ckmenos1.carretera, Ckmenos1.N, delta)
            dfs = distancia_seguridad(v.posicion, Ck.carretera, Ck.N, delta)

            if v.tipo == 2 && dfo >= l*delta && (dfs  >= delta*l || l > dfs)
                Cambiar_Carril!(v, Ck.cuenta, Ckmenos1)
            end

            if v.tipo == 1 && (dfs  >= delta*l || l > dfs)
                Cambiar_Carril!(v, Ck.cuenta, Ckmenos1)
            end
            l = dfo = dfs = delta = 0
        end
    end
end

function CambioDer_Izq!(Ck, Ckmas1, k)

    for v in Ck.carretera[end:-1:9]
        #if (v.tipo == 2 || (v.tipo == 1 && k < 2)) && v.cambio == 0
        if v.tipo == 2 && v.cambio == 0
            l = v.velocidad
            dfs = distancia_seguridad(v.posicion, Ck.carretera, Ck.N, Int8(1))

            if dfs < l
                if Ckmas1.carretera[v.posicion].tipo == -1
                    dfo = distancia_seguridad(v.posicion, Ckmas1.carretera, Ckmas1.N, Int8(1))
                    if dfo >= l
                        Cambiar_Carril!(Ck.carretera[v.posicion], Ck.cuenta, Ckmas1)
                    end
                end
            end
            dfs = l = dfo = 0
        end
    end
end

##################################### Funciones AC ########################################


function AcelerarRuido(carretera, vmax::Array{Int8, 1} = Int8[3, 5], R::Float32 = 0.2f0, frontera_izq::Int64 = 5)

    #frontera_izq = 5
    #vmax = [3, 5]
    #R = 0.2
    for v in carretera[frontera_izq+1:end]
        if v.tipo == 1 || v.tipo == 2

            #Acelerar
            if v.velocidad != -1
                #if (i > 349) && ( i < 620 && i > 663) # Zona de Curvas
                #    Cambiar_Vehiculo!(v, min(v.velocidad+1, vmax[v.tipo]), v.posicion, v.tipo, v.cambio, v.num)
                #else
                    Cambiar_Vehiculo!(v, min(v.velocidad+1, vmax[v.tipo]), v.posicion, v.tipo, v.cambio, v.num)
                #end
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

function DesacelerarMover(C, alfa::Float32 = 0.75f0, frontera_izq::Int8 = Int8(5))
    #alfa = 0.75::Float64
    #frontera_izq = 5::Int64
    i = Pos_izq(C.carretera)
    i_1 = ( i > 1 ? Pos_izq(C.carretera[1:i-1]) : 0 )

    # Este if es para el primer paso en el que solo hay un coche. Este no se desacelera y unicamente se mueve
    #if i_1 == 0 && i > 0
    #    pos_sig = C.carretera[i].velocidad + C.carretera[i].posicion
    #    if C.carretera[i].posicion != pos_sig

    #        if pos_sig <= C.N
    #            Cambiar_Vehiculo!(C.carretera[pos_sig], C.carretera[i].velocidad, pos_sig, C.carretera[i].tipo, 0, C.carretera[i].num)

    #            if C.carretera[i].posicion <= frontera_izq && pos_sig > frontera_izq
    #                C.cuenta += 1
    #            end
    #        else
    #            C.cuenta -= 1
    #        end

    #        Celda_Vacia!(C.carretera[i])
    #    end
    #end

    # Este while es para los pasos siguientes
    while (i > 0)
        #if (C.carretera[i] == 1 || C.carretera[i] == 2) && (C.carretera[i_1] == 1 ||C.carretera[i_1] == 2 )
        if i_1 != 0
          distancia = i - i_1 - 1

          # Desaceleramos el automovil i-1 a partir del automovil i
          velocidad_estimada = round(Int8, floor( C.carretera[i].velocidad * (1.0 - alfa) + 0.5 ) )
          Cambiar_Vehiculo!(C.carretera[i_1], min( (velocidad_estimada+distancia), C.carretera[i_1].velocidad),
                              C.carretera[i_1].posicion, C.carretera[i_1].tipo, C.carretera[i_1].cambio, C.carretera[i_1].num)
        end
        # Movemos el automovil i

        pos_sig = C.carretera[i].velocidad + C.carretera[i].posicion
        if C.carretera[i].posicion != pos_sig && C.carretera[pos_sig].tipo == -1

            if pos_sig <= C.N
                Cambiar_Vehiculo!(C.carretera[pos_sig], C.carretera[i].velocidad, pos_sig, C.carretera[i].tipo, 0, C.carretera[i].num)

                if C.carretera[i].posicion <= frontera_izq && pos_sig > frontera_izq
                    C.cuenta += 1
                end
            else
                C.cuenta -= 1
            end

            Celda_Vacia!(C.carretera[i])
        elseif C.carretera[pos_sig].tipo == -2
           while C.carretera[pos_sig].tipo == -2
               pos_sig -= 1
           end
           Cambiar_Vehiculo!(C.carretera[pos_sig], C.carretera[i].velocidad, pos_sig, C.carretera[i].tipo, 0, C.carretera[i].num)
           Celda_Vacia!(C.carretera[i])
       end

        # Reindexamos el automovil i-1 como el automovil i
        #end
        i = i_1
        i_1 = ( i > 1 ? Pos_izq(C.carretera[1:i-1]) : 0 )
    end
end


###################################### Funciones de Medicion ######################################

  # El codigo que sigue es para hacer las mediciones de densidad, flujo y velocidad

##################################### Auxiliares ###################################

function agregar_sencillo!(array_velocidad, array_flujo, array_densidad, i, t, T)

    v = ( array_densidad[i, t] != 0 ? array_flujo[i, t]/array_densidad[i, t] : 0 )
    array_velocidad[i, t] += v/T
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

#################################### Mediciones ######################################

function Medir(C, t, Secciones, T, flujo_local, densidad_local ,
               velocidad_local_promedio, flujo_local1, densidad_local1 ,velocidad_local_promedio1,
               flujo_local2, densidad_local2 , velocidad_local_promedio2)


    #T = 1.  T es el periodo de tiempo por el cual se mide

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

        agregar_sencillo!( velocidad_local_promedio, flujo_local, densidad_local, i, t, T )
        agregar_sencillo!( velocidad_local_promedio1, flujo_local1, densidad_local1, i, t, T )
        agregar_sencillo!( velocidad_local_promedio2, flujo_local2, densidad_local2, i, t, T )
    end
end

function Espacio_Tiempo!(X, carretera, t)

    for v in carretera
        if v.tipo == 1 || v.tipo == 2
            X[v.num, t] = v.posicion
        end
    end
end

function Tiempo_Promedio_Entrada!(tipo::Int, carretera, tiempos_entrada, t;
                                        frontera_izq::Int64 = 5, vmax::Array{Int, 1} = [2, 5])

    x1 = frontera_izq+1; x2 = frontera_izq+vmax[tipo]
    for v in carretera[x2:-1:x1]
        if v.tipo == tipo
            tiempos_entrada[v.num] = t
        end
    end
    x1 = x2 = 0
end

function Tiempo_Promedio_Salida!(tipo::Int, carretera, tiempos_salida, t; vmax::Array{Int, 1} = [2, 5])
    i = vmax[tipo]-1
    for v in carretera[end:-1:end-i]
        if v.tipo == tipo
            #tiempos_promedio[v.num] = t+1-tiempos_promedio[v.num]
            tiempos_salida[v.num] = t+1
        end
    end
    i = 0
end


end
