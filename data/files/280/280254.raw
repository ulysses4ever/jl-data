module ising
function distribucion(N::Int,M::Int)
    dist=zeros(Int,N,M)
    for i=1:N
        for j=1:M
            dist[i,j]+=rand(-1:2:1)
        end
    end
    dist
end
function azar(dist_inicial,M::Int,N::Int)
    cambio=copy(dist_inicial)
    columna=rand(1:M);
    renglon=rand(1:N);
    cambio[renglon,columna]+=-2*cambio[renglon,columna]
    cambio
end

function energiasperiodicas(espines,tamaniox,tamanioy)
    energia=0;
    for i=1:tamanioy
        for j=1:tamaniox
            energia+=-espines[i,j]*(espines[mod1(i+1,tamanioy),j]+espines[i,mod1(j+1,tamaniox)]+
            espines[mod1(i-1,tamanioy),j]+espines[i,mod1(j-1,tamaniox)])
        end
    end
    energia
end

function aceptar(σ,N,M,T)
    #Cantidades iniciales
    β=1/T;
    τ=azar(σ,N,M)
    energia_σ=energiasperiodicas(σ,N,M)
    energia_τ=energiasperiodicas(τ,N,M)
    α=min(1,exp(β*(energia_σ-energia_τ)))
    a=rand()


    if a<=α
        σ=copy(τ) 
    end
    σ
end

function evolucionisingenergia(tiempo,N::Int,M::Int,T)
    σ=distribucion(N,M)
    energia=zeros(tiempo+1);
    energia[1]=energiasperiodicas(σ,N,M);
    for i=1:tiempo
        σ=aceptar(σ,N,M,T)
        energia[i+1]=energiasperiodicas(σ,N,M);
        
    end
    energia
end

function evolucionisingmagnetizacion(tiempo,N::Int,M::Int,T)
    σ=distribucion(N,M)
    magnetizaciones=zeros(tiempo+1);
    magnetizaciones[1]=magnetizacion(σ);
    for i=1:tiempo
        σ=aceptar(σ,N,M,T)
        magnetizaciones[i+1]=magnetizacion(σ);
        
    end
    magnetizaciones
end

function evolucionisingmagnetizacion(tiempo,N::Int,M::Int,T)
    σ=distribucion(N,M)
    magnetizaciones=zeros(tiempo+1);
    magnetizaciones[1]=magnetizacion(σ);
    for i=1:tiempo
        σ=aceptar(σ,N,M,T)
        magnetizaciones[i+1]=magnetizacion(σ);
        
    end
    magnetizaciones
end

function promagnetizacion(tiempo,N::Int,M::Int,TS)
    TamaT=length(TS)
    promedio=zeros(TamaT)
    for T in 1:TamaT
        σ=distribucion(N,M)
        magnetizaciones=magnetizacion(σ);
        for i=1:tiempo
            σ=aceptar(σ,N,M,T)
            magnetizaciones+=magnetizacion(σ);

        end
        promedio[T]=magnetizaciones/(tiempo+1)
     end
    promedio
end
end
