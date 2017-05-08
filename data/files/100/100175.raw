module HardSphere

import Base.isless


abstract Objeto
abstract Pared <: Objeto

type Particula{T<:Number} <: Objeto
  r::Array{T,1}
  v::Array{T,1}
  radio::T
  m::T
end

Particula(r,v,radio) = Particula(r,v,radio,1.0) #masa fija de 1.0

type ParedVertical{T<:Number} <:Pared
  x :: T
  y :: Array{T,1}
end

type ParedHorizontal{T<:Number} <:Pared
  x :: Array{T,1}
  y :: T
end


over(p::Particula, dt::Real) = p.r += p.v * dt

function dtcolision(p::Particula, V::ParedVertical)
  if p.r[1] > V.x
    if p.v[1] < 0
      dt1 = (V.x - (p.r[1] + p.radio))/p.v[1]
      dt2 = (V.x - (p.r[1] - p.radio))/p.v[1]
      dt = min(dt1,dt2)
    else
      return Inf
    end
  elseif p.r[1] < V.x
    if p.v[1] > 0
      dt1 = (V.x - (p.r[1] + p.radio))/p.v[1]
      dt2 = (V.x - (p.r[1] - p.radio))/p.v[1]
      dt = min(dt1,dt2)
    else
      return Inf
    end
  else
    return Inf
  end
  return dt
end

#Hacer esto con metaprogramming o con un macro!

function dtcolision(p::Particula, H::ParedHorizontal)
  if p.r[2]> H.y
    if p.v[2] < 0
      dt1 = (H.y - (p.r[2] + p.radio))/p.v[2]
      dt2 = (H.y - (p.r[2] - p.radio))/p.v[2]
      dt = min(dt1,dt2)
    else
      return Inf
    end

  elseif p.r[2]< H.y

    if p.v[2] > 0
      dt1 = (H.y - (p.r[2] + p.radio))/p.v[2]
      dt2 = (H.y - (p.r[2] - p.radio))/p.v[2]
      dt = min(dt1,dt2)
    else
      return Inf
    end
  else
    return Inf

  end
  return dt
end

function randuniform(a, b, c=1)
  """Esta función genera un arreglo de longitud c con números aleatorios escogidos
    uniformemente entre a y b"""
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
  tiempo :: Number
  p1::Particula
  Q #::Objeto -- Debe ser así, pero en este momento lleva a ciertos problemas
  etiqueta :: Int
end

isless(e1::Evento, e2::Evento) = e1.tiempo < e2.tiempo

#Revisar la función radio porque parece que tiene ciertos problemas en el caso del gas de esferas duras que es donde importa
function radio(p1::Particula, p2::Particula)
  deltar = p1.r - p2.r
  r = norm(deltar)
  return r < (p1.radio + p2.radio)
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
        overlap = radio(particula, p)
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








#############################################################################################
#Esferas duras.


function dtcolision(p1::Particula,p2::Particula)
  deltar = p1.r - p2.r
  deltav = p1.v - p2.v
  rdotv = dot(deltar, deltav)
  rcuadrado = dot(deltar,deltar)
  vcuadrado = dot(deltav, deltav)

  if rdotv >= 0
    return Inf
  end

  d = (rdotv)^2 -(vcuadrado)*(rcuadrado - (p1.radio + p2.radio)^2)

  if d < 0
    return Inf
  end

  dt = -(rdotv+ sqrt(d))/vcuadrado

  return dt
end


function colision(p1::Particula, p2::Particula)
  deltar = p1.r - p2.r
  deltav = p1.v - p2.v
  rdotv = dot(deltar, deltav)
  J = 2*p1.m*p2.m*rdotv/((p1.radio+p2.radio)*(p1.m + p2.m))
  p1.v -= J/(p1.m)
  p2.v += J/(p2.m)
end


function colisionesfuturas(particulas::Array, paredes::Array, tinicial::Number, tmax::Number, pq)
    """Esta función coloca en la estructura de datos los eventos siguientes que ocurren en un tiempo
    menor a tmax; la diferencia con colisionesfuturas2 es que pone la etiqueta del evento
    igual a 1 haciendo referencia al hecho de que es el cálculo inicial."""

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


        for j in i:length(particulas)
            dt = dtcolision(particulas[i], particulas[j])
                if tinicial + dt < tmax
          #pq[dt] = Evento(tinicial+dt, particulas[i], particulas[j])
                  Collections.enqueue!(pq,Evento(tinicial+dt, particulas[i], particulas[j],1),tinicial+dt)
                end
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






function simulacion(tinicial, tmax, N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
  particulas = crearparticulas(N,Lx1,Lx2,Ly1,Ly2,vmin,vmax)
  #particulas = [Particula([0,0],[0.5,1.0],1.0,1.0)]
  paredes = crearparedes(Lx1,Lx2,Ly1,Ly2)
  pq = Collections.PriorityQueue()
  Collections.enqueue!(pq,Evento(0.0, Particula([0.,0.],[0.,0.],1.0), Particula([0.,0.],[0.,0.],1.0), 0),0.)
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
      if typeof(evento.Q) == Particula{Float64}
      colision(evento.p1,evento.Q)
      else
      colision(evento.p1,evento.Q[1])
      end

    end

    label += 1

    if typeof(evento.Q) == Particula{Float64}
    colisionesfuturas2(evento.Q, particulas, paredes, t, tmax, pq,label)
    colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq,label)
    else
    colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq, label)
    end


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
  Collections.enqueue!(pq,Evento(0.0, Particula([0.,0.],[0.,0.],1.0),Particula([0.,0.],[0.,0.],1.0), 0),0.)
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
      for particula in particulas
        mover(particula,evento.tiempo - t)
      end
      t = evento.tiempo
      push!(tiempo,t)
      if typeof(evento.Q) == Particula{Float64}
      colision(evento.p1,evento.Q)
      else
      colision(evento.p1,evento.Q[1])
      end

      for i in 1:N
        push!(posiciones, particulas[i].r)
        push!(velocidades, particulas[i].v)
      end

    end

    label += 1

    if typeof(evento.Q) == Particula{Float64}
    colisionesfuturas2(evento.Q, particulas, paredes, t, tmax, pq,label)
    colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq,label)
    else
    colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq, label)
    end
  end
  push!(tiempo, tmax)
  posiciones, velocidades, tiempo, particulas
end



#Fin del módulo
end
