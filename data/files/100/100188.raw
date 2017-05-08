module HardSphere
import Base.isless
export Evento, Particula


abstract Objeto
abstract Pared <: Objeto
type Particula{T<:Number} <: Objeto
  r::Array{T,1}
  v::Array{T,1}
  radio::T
  m::T
  etiqueta::Int
end
Particula(r,v,radio) = Particula(r,v,radio,1.0,0) #masa fija de 1.0 y etiqueta igual a 1
Particula(r,v,radio, masa) = Particula(r,v,radio, masa ,0) #masa fija de 1.0 y etiqueta igual a 0
type ParedVertical{T<:Number} <:Pared
  x :: T
  y :: Array{T,1}
end
type ParedHorizontal{T<:Number} <:Pared
  x :: Array{T,1}
  y :: T
end
mover(p::Particula, dt::Real) = p.r += p.v * dt
function dtcolision(p::Particula, V::ParedVertical)
  #La pared siempre va a estar acotada por números positivos
  dt = Inf
  if p.v[1] > 0
    if p.r[1] < V.x
      dt = (V.x - (p.r[1] + p.radio))/p.v[1]
    end
  elseif p.v[1] < 0
    if p.r[1] > V.x
      dt = ((p.r[1] - p.radio) - V.x)/-p.v[1]
    end
  end
  dt
end
#Hacer esto con metaprogramming o con un macro!
function dtcolision(p::Particula, H::ParedHorizontal)
  dt = Inf
  if p.v[2] > 0
    if p.r[2] < H.y
      dt = (H.y - (p.r[2] + p.radio))/p.v[2]
    end
  elseif p.v[2] < 0
    if p.r[2] > H.y
      dt = ((p.r[2] - p.radio) - H.y)/-p.v[2]
    end
  end
  dt
end
function randuniform(a, b, c=1)
  """Esta función genera un arreglo de longitud c con números aleatorios escogidos
uniformemente entreusing HardSphere a y b"""
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
  Q ::Objeto
  etiqueta :: Int
end
isless(e1::Evento, e2::Evento) = e1.tiempo < e2.tiempo
#Revisar la función radio porque parece que tiene ciertos problemas en el caso del gas de esferas duras que es donde importa
function solape(p1::Particula, p2::Particula)
  deltar = p1.r - p2.r
  r = norm(deltar)
  return r < (p1.radio + p2.radio)
end
function crearparticula(Lx1, Lx2, Ly1, Ly2, vmin, vmax)
  radios = randuniform(0.5,1.0)[1]
  masas = randuniform(0.5,1.0)[1]
  #radios = 1.0
  #masas = 1.0
  cotainfx = Lx1 + radios
  cotasupx = Lx2 - radios
  cotainfy = Ly1 + radios
  cotasupy = Ly2 - radios
  x = randuniform(cotainfx, cotasupx)
  y = randuniform(cotainfy, cotasupy)
  v = randuniform(vmin, vmax, 2)
  p = Particula([x,y],v,radios, masas)
  p
end
function crearparticulas(N, Lx1, Lx2, Ly1, Ly2, vmin, vmax)
  p = crearparticula(Lx1, Lx2, Ly1, Ly2, vmin, vmax)
  particulas = [p]
  for i in 2:N
    overlap = true
    while(overlap)
      p = crearparticula(Lx1, Lx2, Ly1, Ly2, vmin, vmax)
      arreglo = [false]
      for particula in particulas
        test = solape(particula, p)
        push!(arreglo,test)
      end
      k = findin(arreglo,true)
      if k == []
        overlap = false
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
  #dt = min((-rdotv+ sqrt(d))/vcuadrado, (-rdotv - sqrt(d))/vcuadrado)
  dt = (rcuadrado - (p1.radio + p2.radio)^2)/(-rdotv + sqrt(d))
  return dt
end


function colision(p1::Particula, p2::Particula)
  deltar = p1.r - p2.r
  deltav = p1.v - p2.v
  h = dot(deltar,deltav)
  sigma = p1.radio+p2.radio
  J = 2*p1.m*p2.m*h/(sigma*(p1.m + p2.m))
  p1.v -= J*deltar/(sigma*p1.m)
  p2.v += J*deltar/(sigma*p2.m)
end


#   deltar = -p1.r + p2.r
#   deltap = p1.m*p1.v - p2.m*p2.v
#   omega = deltar/norm(deltar)
#   h = dot(omega, deltap)
#   if h > 0
#     p1.v -= h*omega/p1.m
#     p2.v += h*omega/p2.m
#   end
# end

function colisionesfuturas(particulas::Array, paredes::Array, tinicial::Number, tmax::Number, pq)
  """Esta función coloca en la estructura de datos los primeros eventos que ocurren en un tiempo
menor a tmax; la diferencia con colisionesfuturas2 es que pone la etiqueta del evento
igual a 1 haciendo referencia al hecho de que es el cálculo inicial."""
  for i in 1:length(particulas)
    tiempo = Float64[]
    for pared in paredes
      dt = dtcolision(particulas[i], pared)
      push!(tiempo,dt)
    end
    dt = minimum(tiempo)
    k = findin(tiempo,dt)
    if tinicial + dt < tmax
      Collections.enqueue!(pq,Evento(tinicial+dt, particulas[i], paredes[k[1]],1),tinicial+dt)
    end
    for j in i+1:length(particulas) #Numero de pares sin repetición N(N-1)/2
      dt = dtcolision(particulas[i], particulas[j])
      if tinicial + dt < tmax
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
  posiciones, velocidades, tiempo, particulas
end

#Fin del módulo
end
