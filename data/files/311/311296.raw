##El modulo para trabajr con el modelo de Ising usando Metropolis-Hasting
module Ising

export configuracion, Configuracion, configuracion, energia, energia!, δE, δE!, flip!, flip_matriz!, magnetizacion, magnetizacion!,
        simulacion_con_E_y_M, simulacion_con_E_y_M_arreglo, promedio_propiedad, energia_magnetizacion_vs_temperatura

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
    regreso=Configuracion(ancho,largo,int(rand(ancho,largo))-1,1.,0,temperatura,0,[0,0])
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
function energia(σ::Array{Int64,2},J::Float64=1.)
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
function δE(σ::Array{Int64,2},i::Int64=0,j::Int64=0,J::Float64=1.)
    if i==0 && j==0
        i,j=int((size(σ,1)-1)*rand())+1,int((size(σ,2)-1)*rand())+1
    end
    L1=size(σ)[1]
    L2=size(σ)[2]

    float( 2*σ[i,j]*(σ[modulo(i+1,L1),j]+σ[modulo(i-1,L1),j]+
    σ[i,modulo(j+1,L2)]+σ[i,modulo(j-1,L2)]) ),
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

#Proceso estocastico con algoritmo Metropolis-Hastings
function metropolis!(σ::Array{Int64,2},T::Float64)
    ΔE,i,j=δE(σ)
    ΔM=0
    α=exp(-1/T*ΔE)
    r=rand()
    cambio=false
    if r<α
        σ[i,j]=-σ[i,j]
        cambio=true
        ΔM=σ[i,j]<0?-2:2
    else
        cambio=false
    end
    return cambio,ΔE,ΔM
end

######Evolucion de una cadena#######
function simulacion_con_E_y_M_arreglo(espines::Array{Int64,2},iteraciones::Int64,T::Float64=1.0)
    Es::Array{Float64}=Array(Float64, iteraciones)
    Ms::Array{Float64}=Array(Float64, iteraciones)
    cambios::Array{Bool}=Array(Bool, iteraciones)
    E=energia(espines)
    M=magnetizacion(espines)

    for i in 1:iteraciones
        cambio,ΔE,ΔM=metropolis!(espines,T)
        cambios[i]=cambio
        if cambio
            E+=ΔE
            M+=ΔM
        end
        Es[i]=E
        Ms[i]=M
    end

    return Es,Ms,cambios
end
function simulacion_con_E_y_M(conf::Configuracion,iteraciones::Int64)
    espines=conf.matriz
    T=conf.temperatura
    simulacion_con_E_y_M_arreglo(espines,iteraciones,T)
end

#Funcion para sacar el promedio de una propiedad que depende de la matriz de estabilidad de nuestro metod
function promedio_propiedad(propiedad::Array{Float64,1},estados::Int64,funcion_tamano_sampleo::Function=sqrt)
    sumProp::Float64=0
    medidas::Int64=0
    for i in 1:int(funcion_tamano_sampleo(estados)):length(propiedad)
        medidas+=1
        sumProp+=propiedad[i]
    end
    sumProp/medidas
end

#Funcion que regresa un arreglo de la propiedad promediada en el intervalo de temperaturas deseadas
function energia_magnetizacion_vs_temperatura(conf::Configuracion,iteraciones::Int64,
                                              Ts::Array{Float64,1}=[0.1:0.3:6.],funcion_tamano_sampleo::Function=sqrt)
    #Unos contendores
    ts_num=length(Ts)
    E_proms=Array(Float64,ts_num)
    M_proms=Array(Float64,ts_num)
    estados=conf.ancho*conf.largo

    #Sacamos el promedio
    for i in 1:ts_num
        conf.temperatura=Ts[i]
        Es,Ms,cambios=simulacion_con_E_y_M(conf,iteraciones)
        E_proms[i] = promedio_propiedad(Es,estados,funcion_tamano_sampleo)
        M_proms[i] = promedio_propiedad(Ms,estados,funcion_tamano_sampleo)
    end

    return Ts,E_proms,M_proms
end
function propiedad_vs_beta(propiedad::Array{Float64,1},estados::Int64,funcion_tamano_sampleo::Function=sqrt,Ts::Array{Float64,1}=[0.1:0.3:6.])

    f_proms=propiedad_vs_temperatura(propiedad,estados,funcion_tamano_sampleo,Ts)[2]

    betas=similar(Ts)
    for i in 1:length(Ts)
        betas[i]=1/Ts[i]
    end

    return betas,f_proms
end
##Termina modulo
end


