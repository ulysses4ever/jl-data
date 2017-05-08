# En este modulo construimos las simulaciones mostradas en el capítulo 3
# de la tesis en el que se estudian las transiciones de fase
# del libramiento de Cuernavaca

module Modelos

using carretera1D2
using PyPlot

export Modelo_NaSch, Modelo_Anticipacion

##########################################################################################
########################### Simulación NaSch sin anticipación ############################
##########################################################################################

########################### Funciones Autómatas Celulares ################################

function AcelerarRuido_NaSch(carretera, R::Float64, vmax::Array{Int8, 1} = Int8[3, 5], frontera_izq::Int64 = 5)

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


function DesacelerarMover_NaSch(C, alfa::Float64, frontera_izq = 5)

    i = Pos_izq(C.carretera)
    i_1 = ( i > 1 ? Pos_izq(C.carretera[1:i-1]) : 0 )

    # Este while es para los pasos siguientes
    while (i > 0)

        if i_1 != 0
          distancia = i - i_1 - 1

          # Desaceleramos el automovil i-1 a partir del automovil i
          velocidad_estimada = floor( C.carretera[i].velocidad * (1.0 - alfa) + 0.5 )
          Cambiar_Vehiculo!(C.carretera[i_1], min( (velocidad_estimada+distancia), C.carretera[i_1].velocidad),
                              C.carretera[i_1].posicion, C.carretera[i_1].tipo, C.carretera[i_1].cambio, C.carretera[i_1].num)
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
end

##################################### Auxiliares ###################################

function agregar_sencillo_NaSch!(array_velocidad, array_flujo, array_densidad, i, t, T)

    v = ( array_densidad[i, t] != 0 ? array_flujo[i, t]/array_densidad[i, t] : 0 )
    array_velocidad[i, t] += v/T
end

function agregar_NaSch!(i, j, t, x_seccion, v, array, T)

    if v.velocidad > 0
        if j-v.velocidad < x_seccion
            array[i, t] += 1/T
        end
    end
end

#################################### Mediciones ######################################

function Medir_NaSch(C, t, Secciones, T, flujo_local, densidad_local, velocidad_local_promedio)

    for (i, x_seccion) in enumerate(Secciones)

        # Medicion del flujo local
        for j = x_seccion+4:-1:x_seccion
            agregar_NaSch!(i, j, t, x_seccion, C.carretera[j], flujo_local, T)
        end

        # Medicion de la densidad local
        for j = x_seccion+4:-1:x_seccion
            agregar_NaSch!(i, j, t, x_seccion, C.carretera[j], densidad_local, T*C.carretera[j].velocidad)
        end

        # Medicion de la velocidad promedio espacial

        agregar_sencillo_NaSch!( velocidad_local_promedio, flujo_local, densidad_local, i, t, T )

    end
end

function Espacio_Tiempo!(X, carretera, t)

    for v in carretera
        if v.tipo == 1 || v.tipo == 2
            X[v.num, t] = v.posicion
        end
    end
end


function Modelo_NaSch( R::Float64, N::Int64, Tf::Int64 ; xlim=(0,Tf), ylim=(0,N))

  C = Carretera1D(N)
  #Secciones = [1:div(N,20)+1:N]
  #S = length(Secciones)
  #A = fld(Tf-N, T)+1
  X = zeros(Tf, Tf+1)
  #flujo_local = zeros(S, A)
  #densidad_local = zeros(S, A)
  #velocidad_local_promedio = zeros(S, A)

  for t = 0:Tf-1

    #if t > N
      Espacio_Tiempo!(X, C.carretera, t+1)
    #end

    Insertar_Carro!(C.carretera, 0., t+1)

    AcelerarRuido_NaSch(C.carretera, R)
    DesacelerarMover_NaSch(C, 1.0)

    #if t > N
    #    Medir_NaSch(C, cld(t+1, T), Secciones, Int8(T), flujo_local, densidad_local, velocidad_local_promedio)
    #end
  end
  #return Tf, X, densidad_local, flujo_local

  #PyPlot.plot(densidad_local(s,:), flujo_local(s, :))
  #PyPlot.plot(Tf, X)

  for v = 2:size(X)[1]
      PyPlot.plot([1:Tf], [x for x in X[v, 1:end-1]])
  end
  PyPlot.xlim(xlim[1], xlim[2])
  PyPlot.ylim(ylim[1], ylim[2])
  PyPlot.xlabel("tiempo [segundos]")
  PyPlot.ylabel("X [celdas]")
end

##########################################################################################
########################### Simulación NaSch con anticipación ############################
##########################################################################################

function Modelo_Anticipacion( R::Float64, alpha::Float64, N::Int64, Tf::Int64 ; xlim=(0,Tf), ylim=(0,N))

  C = Carretera1D(N)
  #Secciones = [1:div(N,20)+1:N]
  #S = length(Secciones)
  #A = fld(Tf-N, T)+1
  X = zeros(Tf, Tf+1)
  #flujo_local = zeros(S, A)
  #densidad_local = zeros(S, A)
  #velocidad_local_promedio = zeros(S, A)

  for t = 0:Tf-1

    #if t > N
      Espacio_Tiempo!(X, C.carretera, t+1)
    #end

    Insertar_Carro!(C.carretera, 0., t+1)

    AcelerarRuido_NaSch(C.carretera, R)
    DesacelerarMover_NaSch(C, alpha)

    #if t > N
    #    Medir_NaSch(C, cld(t+1, T), Secciones, Int8(T), flujo_local, densidad_local, velocidad_local_promedio)
    #end
  end
  #return Tf, X, densidad_local, flujo_local

  #PyPlot.plot(densidad_local(s,:), flujo_local(s, :))
  #PyPlot.plot(Tf, X)

  for v = 2:size(X)[1]
      PyPlot.plot([1:Tf], [x for x in X[v, 1:end-1]])
  end
  PyPlot.xlim(xlim[1], xlim[2])
  PyPlot.ylim(ylim[1], ylim[2])
  PyPlot.xlabel("tiempo [segundos]")
  PyPlot.ylabel("X [celdas]")
end


end
