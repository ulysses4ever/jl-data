module HardSphere

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
      dt = (V.x - (p.r[1] + p.sigma))/p.v[1]
    else
      return Inf
    end
  else
    if p.v[1] > 0
      dt = (V.x - (p.r[1] + p.sigma))/p.v[1]
    else
      return Inf
    end
  end
  return dt
end

#Hacer esto con metaprogramming

function dtcolision(p::Particula, H::ParedHorizontal)
  if p.r[2] > H.y
    if p.v[2] < 0
      dt = (H.y - (p.r[2] + p.sigma))/p.v[2]
    else
      return Inf
    end
  else
    if p.v[2] > 0
      dt = (H.y - (p.r[2] + p.sigma))/p.v[2]
    else
      return Inf
    end
  end
  return dt
end

function dtcolision(p1::Particula,p2::Particula)
  deltar = p1.r - p2.r
  deltav = p1.v - p2.v
  rdotv = dot(deltar, deltav)
  rcuadrado = dot(deltar,deltar)
  vcuadrado = dot(deltav, deltav)

  if rdotv >= 0
    return Inf
  end

  d = (rdotv)^2 -(vcuadrado)*(rcuadrado - (p1.sigma + p2.sigma)^2)

  if d < 0
    return Inf
  end

  dt = (-rdotv+ sqrt(d))/vcuadrado

  return dt
end

#Documentar esta función
function randuniform(a, b, c=1)
  a + rand(c)*(b - a)
end

function colision(p1::Particula, p2::Particula)
  deltar = p1.r - p2.r
  deltav = p1.v - p2.v
  rdotv = dot(deltar, deltav)
  J = 2*p1.m*p2.m*rdotv/((p1.sigma+p2.sigma)*(p1.m + p2.m))
  p1.v -= J/(p1.m)
  p2.v += J/(p2.m)
end

function colision(p1::Particula, V::ParedVertical )
  p1.v[1] = -p1.v[1]
end

function colision(p1::Particula, H::ParedHorizontal )
  p1.v[2] = -p1.v[2]
end

#Ver cómo especificar Q para que no sea tan amplia la definición
type Evento
  tiempo
  p1::Particula
  Q #puede ser pared o partícula
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
function colisionesfuturas(particulas::Array, paredes::Array, tinicial, tmax)
  pq = Collections.PriorityQueue()
  for i in 1:length(particulas)
    for j in 1:length(particulas)
      if j > i
        dt = dtcolision(particulas[i], particulas[j])
        if tinicial + dt < tmax
          #pq[dt] = Evento(tinicial+dt, particulas[i], particulas[j])
          Collections.enqueue!(pq,Evento(tinicial+dt, particulas[i], particulas[j]),tinicial+dt)
        end
      end
    end
    for pared in paredes
      dt = dtcolision(particulas[i], pared)
      if tinicial + dt < tmax
        #pq[dt] = Evento(tinicial+dt, particulas[i], pared)
        Collections.enqueue!(pq,Evento(tinicial+dt, particulas[i], pared),tinicial+dt)
      end
    end
  end
  pq
end




function colisionesfuturas2(particula, particulas, paredes, tinicial, tmax, pq )
    for p in particulas
        if particula != p
             dt = dtcolision(particula, p)
                if tinicial + dt < tmax
                    #pq[dt] = Evento(tinicial+dt, particulas[i], particulas[j])
                    Collections.enqueue!(pq,Evento(tinicial+dt, particula, p),tinicial+dt)
                end
            end
        end

        for pared in paredes
        dt = dtcolision(particula, pared)
            if tinicial + dt < tmax
                #pq[dt] = Evento(tinicial+dt, particulas[i], pared)
                Collections.enqueue!(pq,Evento(tinicial+dt, particula, pared),tinicial+dt)
            end
        end

    pq
end

#Hacer la comparación con partículas.
function simulacion(tinicial, tmax, N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
    particulas = crearparticulas(N,Lx1,Lx2,Ly1,Ly2,vmin,vmax)
    paredes = crearparedes(Lx1,Lx2,Ly1,Ly2)
    pq = colisionesfuturas(particulas,paredes,tinicial,tmax)
    evento = Collections.dequeue!(pq)
    #particula = evento.p1
    posicion = evento.p1.r[1]
    lista = [posicion]
    t = evento.tiempo
    tiempo = [evento.tiempo]
    #lista = [particula]
    while(!isempty(pq))
        evento = Collections.dequeue!(pq)
        posicion = evento.p1.r[1]
        if !in(posicion,lista) #Si está en la lista seguir con el siguiente
            push!(lista,posicion)
            for particula in particulas
                mover(particula,evento.tiempo - t)
            end
            t = evento.tiempo
            push!(tiempo,t)
            colision(evento.p1,evento.Q)
        end
        colisionesfuturas2(evento.p1, particulas, paredes, t, tmax, pq)
            if typeof(evento.Q) == Particula
            colisionesfuturas2(evento.Q, particulas, paredes, t, tmax, pq)
        end
    end
    lista, tiempo
end

#Fin del módulo
end
