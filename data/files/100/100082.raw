include("./objects.jl")
include("./timesandrules.jl")
include("./creatingobjects.jl")

module HardDisksSimulation

importall Objects
importall Rules
importall Init
import Base.isless
export simulacionanimada, energia

#This allow to use the PriorityQueue providing a criterion to select the priority of an Event.
isless(e1::Evento, e2::Evento) = e1.tiempo < e2.tiempo

@doc doc"""Calculates the initial feasible Events and push them into the PriorityQueue with label
equal to 0"""->
function colisionesfuturas(particulas::Array, paredes::Array, tinicial::Number, tmax::Number, pq)
#Puts the initial label of the
    for i in 1:length(particulas)
        tiempo = Float64[]
        for pared in paredes
            dt = dtcolision(particulas[i], pared)
            push!(tiempo,dt)
        end
        dt = minimum(tiempo)
        k = findin(tiempo,dt)
        if tinicial + dt < tmax
            Collections.enqueue!(pq,Evento(tinicial+dt, particulas[i], paredes[k[1]],0),tinicial+dt)
        end
        for j in i+1:length(particulas) #Numero de pares sin repetición N(N-1)/2
            dt = dtcolision(particulas[i], particulas[j])
            if tinicial + dt < tmax
                Collections.enqueue!(pq,Evento(tinicial+dt, particulas[i], particulas[j],0),tinicial+dt)
            end
        end
    end
    pq
end


@doc doc"""Updates the PriorityQueue pushing into it all the feasible Events that can occur after the collision
of a Disk with a Wall"""->
function colisionesfuturas2(particula, particulas, paredes, tinicial, tmax, pq, etiqueta )
    tiempo = Float64[]
    for pared in paredes
        dt = dtcolision(particula, pared)
        push!(tiempo,dt)
    end
    dt = minimum(tiempo)
    k = findin(tiempo,dt)
    if tinicial + dt < tmax
        Collections.enqueue!(pq,Evento(tinicial+dt, particula, paredes[k[1]], etiqueta),tinicial+dt)
    end

    tiempo = Float64[]
    for p in particulas
        if particula != p
            dt = dtcolision(particula, p)
            if tinicial + dt < tmax
                Collections.enqueue!(pq,Evento(tinicial+dt, particula, p, etiqueta),tinicial+dt)
            end
        end
    end
    pq
end

@doc doc"""Updates the PriorityQueue pushing into it all the possible Events that can occur after the collision
of two Disks."""->
function colisionesfuturas2(particula1, particula2, particulas, paredes, tinicial, tmax, pq, etiqueta)

    tiempo = Float64[]
    for pared in paredes
        dt = dtcolision(particula1, pared)
        push!(tiempo,dt)
    end
    dt = minimum(tiempo)
    k = findin(tiempo,dt)
    if tinicial + dt < tmax
        Collections.enqueue!(pq,Evento(tinicial+dt, particula1, paredes[k[1]], etiqueta),tinicial+dt)
    end

    tiempo = Float64[]
    for pared in paredes
        dt = dtcolision(particula2, pared)
        push!(tiempo,dt)
    end
    dt = minimum(tiempo)
    k = findin(tiempo,dt)
    if tinicial + dt < tmax
        Collections.enqueue!(pq,Evento(tinicial+dt, particula2, paredes[k[1]], etiqueta),tinicial+dt)
    end

    #Voy a considerar que no hay recolisión entre las partículas que acaban de chocar, por consiguiente ajusto el tiempo de colisión entre p1 y p2 igual a infinito.
    tiempo = Float64[]
    for p in particulas
        if (particula1 != p) & (particula2 != p)
            dt = dtcolision(particula1, p)
            if tinicial + dt < tmax
                Collections.enqueue!(pq,Evento(tinicial+dt, particula1, p, etiqueta),tinicial+dt)
            end
        end
    end

    tiempo = Float64[]
    for p in particulas
        if (particula1 != p) & (particula2 != p)
            dt = dtcolision(particula2, p)
            if tinicial + dt < tmax
                Collections.enqueue!(pq,Evento(tinicial+dt, particula2, p, etiqueta),tinicial+dt)
            end
        end
    end
    pq
end

@doc doc"""Calculates the total energy (kinetic) of the system."""
function energia(masas,velocidades)
    e = 0.
    for i in 1:length(masas)
        e += masas[i]*norm(velocidades[i])^2/2.
    end
    e
end


@doc doc"""Contains the main loop of the project. The PriorityQueue is filled at each step with Events associated
to the collider Disk(s); and at the same time the element with the highest physical priority (lowest time) is removed
from the Queue and ignored if it is physically meaningless. The loop goes until the last Event is removed
from the DAta Structure, which is delimited by the maximum time(tmax)."""->
function simulacionanimada(tinicial, tmax, N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
    #Genera lista para las posiciones y las velocidades de todas las partículas, lo cual permite generar la animación
    #usando matplotlib (PyPlot)
    #radios = randuniform(0,1,N)
    #masas = randuniform(0,1,N)
    #p = Particula([1.,2.],[1.5,1.5],1.0,1.0)
    #particulas = [p]
    #p = Particula([4.,5.],[0.4,0.4],1.0,1.0)
    #push!(particulas,p)
    particulas = crearparticulas(N,Lx1,Lx2,Ly1,Ly2,vmin,vmax)
    posiciones = [particula.r for particula in particulas]
    velocidades = [particula.v for particula in particulas]
    masas = [particula.m for particula in particulas]
    paredes = crearparedes(Lx1,Lx2,Ly1,Ly2)
    pq = Collections.PriorityQueue()
    Collections.enqueue!(pq,Evento(0.0, Particula([0.,0.],[0.,0.],1.0),Particula([0.,0.],[0.,0.],1.0), 0),0.)
    pq = colisionesfuturas(particulas,paredes,tinicial,tmax, pq)
    evento = Collections.dequeue!(pq)
    t = evento.tiempo
    tiempo = [evento.tiempo]
    #Label hace referencia a la etiqueta que asocio a los eventos que calculo, que para colisiones futuras está en 1.
    label = 0
    while(!isempty(pq))
        label += 1
        evento = Collections.dequeue!(pq)
        if (evento.etiqueta >= evento.p1.etiqueta)
            if typeof(evento.Q) == Particula{Float64}
                if (evento.etiqueta >= evento.Q.etiqueta)
                    evento.Q.etiqueta = label
                    evento.p1.etiqueta = label
                    for particula in particulas
                        mover(particula,evento.tiempo - t)
                    end
                    t = evento.tiempo
                    push!(tiempo,t)
                    colision(evento.p1,evento.Q)
                    for i in 1:N
                        push!(posiciones, particulas[i].r)
                        push!(velocidades, particulas[i].v)
                    end
                    colisionesfuturas2(evento.p1, evento.Q, particulas, paredes, t, tmax, pq,label)
                end
            else
                evento.p1.etiqueta = label
                for particula in particulas
                    mover(particula,evento.tiempo - t)
                end
                t = evento.tiempo
                push!(tiempo,t)
                colision(evento.p1,evento.Q)
                for i in 1:N
                    push!(posiciones, particulas[i].r)
                    push!(velocidades, particulas[i].v)
                end
                colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq, label)
            end
        end
    end
    push!(tiempo, tmax)
    posiciones, velocidades, tiempo, particulas, masas
end

#Fin del módulo
end
