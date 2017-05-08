module IdealGas

import Base.isless

abstract Pared

type Particula
  r
  v
  sigma
  m
end
Particula(r,v,sigma) = Particula(r,v,sigma,1.0) #masa fija de 1.0

type ParedVertical <: Pared
  x
  y #intervalo
end

type ParedHorizontal <: Pared
  x #intervalo
  y
end

mover(p::Particula, dt::Real) = p.r += p.v * dt

function dtcolision(p::Particula, V::ParedVertical)
  if p.r[1] > V.x
    if p.v[1] < 0
      dt1 = (V.x - (p.r[1] + p.sigma))/p.v[1]
      dt2 = (V.x - (p.r[1] - p.sigma))/p.v[1]
      dt = min(dt1,dt2)

    else
      return Inf
    end
  elseif p.r[1] < V.x
    if p.v[1] > 0
      dt1 = (V.x - (p.r[1] + p.sigma))/p.v[1]
      dt2 = (V.x - (p.r[1] - p.sigma))/p.v[1]
      dt = min(dt1,dt2)

    else
      return Inf
    end

  else
    return Inf
  end
  return dt
end

#Hacer esto con metaprogramming

function dtcolision(p::Particula, H::ParedHorizontal)
  if p.r[2]> H.y
    if p.v[2] < 0
      dt1 = (H.y - (p.r[2] + p.sigma))/p.v[2]
      dt2 = (H.y - (p.r[2] - p.sigma))/p.v[2]
      dt = min(dt1,dt2)
    else
      return Inf
    end

  elseif p.r[2]< H.y

    if p.v[2] > 0
      dt1 = (H.y - (p.r[2] + p.sigma))/p.v[2]
      dt2 = (H.y - (p.r[2] - p.sigma))/p.v[2]
      dt = min(dt1,dt2)
    else
      return Inf
    end
  else
    return Inf

  end
  return dt
end

#Documentar esta función
function randuniform(a, b, c=1)
  a + rand(c)*(b - a)
end

function colision(p1::Particula, V::ParedVertical )
  p1.v = [-p1.v[1], p1.v[2]]
end

function colision(p1::Particula, H::ParedHorizontal )
  p1.v = [p1.v[1],-p1.v[2]]
end

#Ver cómo especificar Q para que no sea tan amplia la definición
type Evento
  tiempo
  p1::Particula
  Q #puede ser pared o partícula
  etiqueta
end

isless(e1::Evento, e2::Evento) = e1.tiempo < e2.tiempo

function solape(p1::Particula, p2::Particula)
  deltar = p1.r - p2.r
  rcuadrado = dot(deltar,deltar)
  return rcuadrado < (p1.sigma + p2.sigma)^2
end



function crearparticulas(N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
  radios = randuniform(0,1,N)
  masas =  randuniform(0,1,N)
  cotainfx = Lx1 + radios
  cotasupx = Lx2 - radios
  cotainfy = Ly1 + radios
  cotasupy = Ly2 - radios
  x = randuniform(cotainfx[1], cotasupx[1])
  y = randuniform(cotainfy[1], cotasupy[1])
  v = randuniform(vmin, vmax, 2)
  p  = Particula([x,y],v,radios[1], masas[1])
  particulas = [p]
  for i in 2:N
    overlap = true
    while(overlap)
      x = randuniform(cotainfx[i], cotasupx[i])
      y = randuniform(cotainfy[i], cotasupy[i])
      v = randuniform(vmin, vmax, 2)
      p  = Particula([x,y],v,radios[i], masas[i])
      for particula in particulas
        overlap = solape(particula, p)
      end
    end
    push!(particulas,p)
  end
  particulas
end



function crearparedes(Lx1,Lx2,Ly1,Ly2)
  arreglo = Array(Pared,4)
  arreglo[1] = ParedVertical(Lx1,[Ly1,Ly2])
  arreglo[2] = ParedVertical(Lx2,[Ly1,Ly2])
  arreglo[3] = ParedHorizontal([Lx1,Lx2],Ly1)
  arreglo[4] = ParedHorizontal([Lx1,Lx2],Ly2)
  arreglo
end





#Colocar t max como parámetro de tipo real
#Saber manejar la variable global tiempo (¿debe ser global?)
function colisionesfuturas(particulas::Array, paredes::Array, tinicial, tmax, pq)
  #  pq = Collections.PriorityQueue()

  for i in 1:length(particulas)
    tiempo = Float64[]
    for pared in paredes
      dt = dtcolision(particulas[i], pared)
      push!(tiempo,dt)
    end
    dt = minimum(tiempo)
    k = findin(tiempo,dt)
    if tinicial + dt < tmax
      #pq[dt] = Evento(tinicial+dt, particulas[i], paredes[k])
      Collections.enqueue!(pq,Evento(tinicial+dt, particulas[i], paredes[k],1),tinicial+dt)
    end
  end
  pq
end




function colisionesfuturas2(particula, particulas, paredes, tinicial, tmax, pq, etiqueta )
  tiempo = Float64[]
  for pared in paredes
    dt = dtcolision(particula, pared)
    push!(tiempo,dt)
  end
  dt = minimum(tiempo)
  k = findin(tiempo,dt)
  if tinicial + dt < tmax
    #pq[dt] = Evento(tinicial+dt, particulas[i], paredes[k])
    Collections.enqueue!(pq,Evento(tinicial+dt, particula, paredes[k], etiqueta),tinicial+dt)
  end

  pq
end

#Hacer la comparación con partículas.
function simulacion(tinicial, tmax, N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
  particulas = crearparticulas(N,Lx1,Lx2,Ly1,Ly2,vmin,vmax)
  #particulas = [Particula([0,0],[0.5,1.0],1.0,1.0)]
  paredes = crearparedes(Lx1,Lx2,Ly1,Ly2)
  pq = Collections.PriorityQueue()
  Collections.enqueue!(pq,Evento(0.0, Particula([0.,0.],[0.,0.],1.0),0., 0),0.)
  pq = colisionesfuturas(particulas,paredes,tinicial,tmax, pq)
  evento = Collections.dequeue!(pq)
  #particula = evento.p1
  t = evento.tiempo
  tiempo = [evento.tiempo]
  etiqueta = evento.etiqueta
  etiquetas = [etiqueta]
  #lista = [particula]
  while(!isempty(pq))
    evento = Collections.dequeue!(pq)
    label = evento.etiqueta
    if !in(label,etiquetas) #Si está en la lista seguir con el siguiente
      push!(etiquetas,label)
      for particula in particulas
        mover(particula,evento.tiempo - t)
      end
      t = evento.tiempo
      push!(tiempo,t)
      colision(evento.p1,evento.Q[1])
    end
    label += 1
    colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq, label)
    #     if typeof(evento.Q) == Particula
    #    colisionesfuturas2(evento.Q, particulas, paredes, t, tmax, pq)
    # end
  end
  etiquetas, tiempo
end


function simulacionanimada(tinicial, tmax, N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
  #Genera lista para las posiciones y las velocidades de todas las partículas, lo cual permite generar la animación
  #usando matplotlib (PyPlot)

  particulas = crearparticulas(N,Lx1,Lx2,Ly1,Ly2,vmin,vmax)
  posiciones = [particula.r for particula in particulas]
  velocidades = [particula.v for particula in particulas]

  paredes = crearparedes(Lx1,Lx2,Ly1,Ly2)
  pq = Collections.PriorityQueue()
  Collections.enqueue!(pq,Evento(0.0, Particula([0.,0.],[0.,0.],1.0),0., 0),0.)
  pq = colisionesfuturas(particulas,paredes,tinicial,tmax, pq)
  evento = Collections.dequeue!(pq)
  t = evento.tiempo
  tiempo = [evento.tiempo]
  etiqueta = evento.etiqueta
  etiquetas = [etiqueta]
  #lista = [particula]
  while(!isempty(pq))

    evento = Collections.dequeue!(pq)
    label = evento.etiqueta

    if !in(label,etiquetas) #Si está en la lista seguir con el siguiente
      push!(etiquetas,label)

      k = find(particulas .== evento.p1)



      for particula in particulas
        mover(particula,evento.tiempo - t)
      end

      t = evento.tiempo
      push!(tiempo,t)



      colision(evento.p1,evento.Q[1])

      for i in 1:N
        push!(posiciones, particulas[i].r)
        push!(velocidades, particulas[i].v)
      end

    end
    label += 1
    colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq, label)

  end

  push!(tiempo, tmax)

  posiciones, velocidades, tiempo, particulas
end

#Fin del modulo
end
