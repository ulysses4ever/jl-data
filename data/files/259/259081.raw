function AcelerarRuido(carretera; vmax::Array{Int8, 1} = Int8[3, 5], R::Float32 = 0.2f0, frontera_izq::Int64 = 5)

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



function DesacelerarMover(C::Carretera1D)

    alfa = 0.75f0
    frontera_izq = int8(5)

    i = Pos_izq(C.carretera)
    i_1 = ( i > 1 ? Pos_izq(C.carretera[1:i-1]) : 0 )

    # Este while es para los pasos siguientes
    while (i > 0)

        if i_1 != 0
        ############################ cambio ###################################
          distancia = i - i_1 - 1 # distancia = i - i_1 - C.carretera[i_1].longitud

          # Desaceleramos el automovil i-1 a partir del automovil i
          velocidad_estimada = round(Int8, floor( C.carretera[i].velocidad * (1.0 - alfa) + 0.5 ) )
          Cambiar_Vehiculo!(C.carretera[i_1], min( (velocidad_estimada+distancia), C.carretera[i_1].velocidad),
                              C.carretera[i_1].posicion, C.carretera[i_1].tipo, C.carretera[i_1].cambio,
                                C.carretera[i_1].num)
        end

        # Movemos el automovil i

        pos_sig = C.carretera[i].velocidad + C.carretera[i].posicion
        if C.carretera[i].posicion != pos_sig #&& C.carretera[pos_sig].tipo == -1

            if pos_sig > C.N
                Celda_Vacia!(C.carretera[i])
                C.cuenta -= 1
            end

            if pos_sig <= C.N && C.carretera[pos_sig].tipo == -1

                if C.carretera[i].posicion <= frontera_izq && pos_sig > frontera_izq
                    C.cuenta += 1
                end

                Cambiar_Vehiculo!(C.carretera[pos_sig], C.carretera[i].velocidad, pos_sig, C.carretera[i].tipo, 0
                                    , C.carretera[i].num)

                Celda_Vacia!(C.carretera[i])
            elseif pos_sig <= C.N && C.carretera[pos_sig].tipo == -2
                while C.carretera[pos_sig].tipo == -2
                   pos_sig -= 1
                end
               Cambiar_Vehiculo!(C.carretera[pos_sig], C.carretera[i].velocidad, pos_sig, C.carretera[i].tipo, 0,
                                C.carretera[i].num)
               Celda_Vacia!(C.carretera[i])
            end
        end
        # Reindexamos el automovil i-1 como el automovil i

        i = i_1
        i_1 = ( i > 1 ? Pos_izq(C.carretera[1:i-1]) : 0 )
    end

    alfa = frontera_izq = i = i_1 = 0
end


################################## Funciones especiales para las simulaciones en la zona de curvas ############################

######### Sentido 1 ###########

function AcelerarRuidoS1(carretera, vmax::Array{Int8, 1} = Int8[3, 5], R::Float32 = 0.2f0, frontera_izq::Int64 = 5)

    for v in carretera[frontera_izq+1:end]
        if v.tipo == 1 || v.tipo == 2

            #Acelerar
            if v.velocidad != -1
                if (v.posicion < 349) || ( v.posicion > 620 && v.posicion < 663) # Zona de Curvas
                    vmax[2] = int8(4)
                end
                Cambiar_Vehiculo!(v, min(v.velocidad+1, vmax[v.tipo]), v.posicion, v.tipo, v.cambio, v.num)

            end

            #Ruido
            if v.velocidad > 0
                if rand() <= R
                    Cambiar_Vehiculo!(v, max(v.velocidad-1, 0), v.posicion, v.tipo, v.cambio, v.num)
                end
            end
            vmax[2] = int8(5)
        end
    end
  vmax = 0
end


##### Sentido 2 #######

function AcelerarRuidoS2(carretera, vmax::Array{Int8, 1} = Int8[3, 5], R::Float32 = 0.2f0, frontera_izq::Int64 = 5)

    for v in carretera[frontera_izq+1:end]
        if v.tipo == 1 || v.tipo == 2

            #Acelerar
            if v.velocidad != -1
                if (v.posicion > 3518) || ( v.posicion < 3408 && v.posicion > 3265) # Zona de Curvas
                    vmax[2] = int8(4)
                end

                if (v.posicion > 2500) && v.tipo == 1 # Pendiente
                    vmax[1] = int8(2)
                end
                Cambiar_Vehiculo!(v, min(v.velocidad+1, vmax[v.tipo]), v.posicion, v.tipo, v.cambio, v.num)
            end

            #Ruido
            if v.velocidad > 0
                if rand() <= R
                    Cambiar_Vehiculo!(v, max(v.velocidad-1, 0), v.posicion, v.tipo, v.cambio, v.num)
                end
            end
        vmax = Int8[3, 5]
        end
    end
  vmax = 0
end
