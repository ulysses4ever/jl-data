
## Esta función da la distancia de seguridad que debe de haber entre dos vehículos
function distancia_seguridad(i, Carretera1, N, delta, alfa::Float32 = 0.75f0)

    pvfo = Vehiculo_Adelante(i, Carretera1, N)
    d_ifo = (pvfo < N ? (pvfo-i-1) : delta*5 ) # 5 = vmax[2]
    dfo = d_ifo + int8( floor( (1.-alfa) * Carretera1[pvfo].velocidad + 0.5) )
    alfa = 0; pvfo = 0; d_ifo = 0
    return dfo
end


## Esta función hace que un vehículo cambie de carril
function Cambiar_Carril!(v0::Vehiculo, Cuenta0, C1::Carretera1D)

    i = v0.posicion
    if C1.carretera[i].tipo == -1

        pvbo = Vehiculo_Atras(i, C1.carretera, C1.N)
        ############################ cambio ###################################
        d_bo = (pvbo < (C1.N) ? (i-pvbo-1) : 5 ) # 5 = vmax[2] (i-pvbo-longitud)
        vb = C1.carretera[pvbo].velocidad
        if vb <= d_bo

            Cambiar_Vehiculo!( C1.carretera[i], v0.velocidad, v0.posicion, v0.tipo, 1, v0.num)
            Celda_Vacia!( v0 )
            Cuenta0 -= 1
            C1.cuenta += 1
        end
    end
end

## Esta función hace los cambios de carril desde un carril izquierdo hacia uno derecho
function CambioIzq_Der!(Ck, Ckmenos1, k)

    for v in Ck.carretera[end:-1:9]
        if (v.tipo == 1 || v.tipo == 2) && v.cambio == 0

            delta = v.tipo == 2 ? int8(3) : int8(1)
            l = v.velocidad
            dfo = distancia_seguridad(v.posicion, Ckmenos1.carretera, Ckmenos1.N, delta)
            dfs = distancia_seguridad(v.posicion, Ck.carretera, Ck.N, delta)

            if v.tipo == 2 && dfo >= l*delta && (dfs  >= delta*l || l > dfs)
                Cambiar_Carril!(v, Ck.cuenta, Ckmenos1)
            end

            if v.tipo == 1 && dfo >= l*delta #(dfs  >= delta*l || l > dfs)
                Cambiar_Carril!(v, Ck.cuenta, Ckmenos1)
            end
            l = dfo = dfs = delta = 0
        end
    end
end

## Esta función hace los cambios de carril desde un carril derecho hacia uno izquierdo
function CambioDer_Izq!(Ck, Ckmas1, k)

    for v in Ck.carretera[end:-1:9]
        #if (v.tipo == 2 || (v.tipo == 1 && k < 2)) && v.cambio == 0
        if v.tipo == 2 && v.cambio == 0
            l = v.velocidad
            dfs = distancia_seguridad(v.posicion, Ck.carretera, Ck.N, int8(1))

            if dfs < l
                if Ckmas1.carretera[v.posicion].tipo == -1
                    dfo = distancia_seguridad(v.posicion, Ckmas1.carretera, Ckmas1.N, int8(1))
                    if dfo >= l
                        Cambiar_Carril!(Ck.carretera[v.posicion], Ck.cuenta, Ckmas1)
                    end
                end
            end
            dfs = l = dfo = 0
        end
    end
end

## Esta función simula una rampa de entrada (tipo == 1) o de salida (tipo == 0)
function Rampa!( tipo, x0, lramp, pin, p, Ck, num, vmax::Array{Int8, 1} = Int8[3, 5])
    #vmax = [3, 5]

    # Rampa de salida, tipo == 0
    if tipo == 0
    ############################ cambio ###################################
        x = Pos_der(Ck.carretera[x0:x0+lramp])  # if longitud > 1 Ck.carretera[xi] && ... && Ck.carretera[xi+londitud] esten vacia 
        if x <= x0+lramp && rand() < pin
            if Ck.cuenta > 0
                Ck.cuenta -= 1
            end
            Celda_Vacia!(Ck.carretera[x])
        end

    # Rampa de entrada, tipo == 1
    elseif tipo == 1
    ############################ cambio ###################################
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
