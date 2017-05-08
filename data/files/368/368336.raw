##El modulo para trabajr con el modelo de Ising usando Metropolis-Hasting
module Ising

export configuracion, Configuracion, energia, energia!, δE, δE!, flip!, flip_matriz!

####  TIPOS  ####
type Configuracion
    ancho::Int64
    largo::Int64
    matriz::Array{Int64,2}
    interaccion::Float64
    magnetizacion::Int64
    temperatura::Float64
    energia::Float64
    posible_cambio::Array{Int64,1}
end
function configuracion(ancho::Int64,largo::Int64,temperatura::Float64)
    regreso=Configuracion(ancho,largo,int(rand(ancho,largo))-1,1,0,temperatura,0,[0,0])
    regreso.magnetizacion=sum(regreso.matriz)
    regreso
end

#### METODOS  #######

#Hacemos nuestro propio modulo para tener fronteras periodicas
function modulo(i::Int64,L::Int64)
    i = i>L ? 1 : i<1 ? L : i
end

#Magnetizacion
function magnetizacion(σ::Array{Int64,2})
    sum(σ)
end
function magnetizacion!(conf::Configuracion)
    conf.magnetizacion=magnetizacion(conf.matriz)
end

#Calculo de Energia
function energia(σ::Array{Int64,2},J::Float64=1)
    L1=size(σ)[1]
    L2=size(σ)[2]
    E=0
    for i in 1:L1
        for j in 1:L2
            E+=-σ[i,j]*(σ[modulo(i+1,L1),j]+σ[modulo(i-1,L1),j]+
                σ[i,modulo(j+1,L2)]+σ[i,modulo(j-1,L2)])*J
        end
    end
    E
end
function energia!(conf::Configuracion)
  conf.energia=energia(conf.arrreglo,conf.interaccion)
end

#Cambio de energia en un flip propuesto
function δE(σ::Array{Int64,2},i::Int64=0,j::Int64=0,J::Float64=1)
    if i==0 && j==0
        i,j=int((size(σ,1)-1)*rand())+1,int((size(σ,2)-1)*rand())+1
    end
    L1=size(σ)[1]
    L2=size(σ)[2]

    ΔE=2*J*σ[i,j]*(σ[modulo(i+1,L1),j]+σ[modulo(i-1,L1),j]+
    σ[i,modulo(j+1,L2)]+σ[i,modulo(j-1,L2)])/4,
    i,j
end
function δE!(conf::Configuracion)
    i,j=int((size(σ,1)-1)*rand())+1,int((size(σ,2)-1)*rand())+1
    conf.posible_cambio=[i,j]
    δE(conf.matriz,i,j,conf.interaccion)
end

#Flip a la configuracion si no se escoge la poscion esta sera aleatoria
function flip_matriz!(σ::Array{Int64,2},i::Int64=0,j::Int64=0)
    N=size(σ)[1]
    M=size(σ)[2]
    if i==0 && j==0
        i,j=int((N-1)*rand())+1,int((M-1)*rand())+1
    end
    σ[i,j]=-σ[i,j]
    σ
end
function flip!(conf::Configuracion,i::Int64=0,j::Int64=0)
    conf.matriz=flip_matriz!(conf.matriz,i,j)
end

##Termina modulo
end

###PRUEBAS
using Ising

