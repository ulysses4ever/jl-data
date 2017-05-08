## función para generar configuraciones aleatorias de espines.

function configal(L)
    out=zeros(Int,L,L)
    for i in 1:L
        for j in 1:L
            out[i,j]=rand(-1:2:1)
        end 
    end
    return out
end

## fucnión que calcula el aumento de energía al cambiar un espín.

function aumentoe(x,y,L,configinicial::Array{Int64,2})
    out=0
    out=-configinicial[y,x]*configinicial[mod1(y+1,L),x]-configinicial[y,x]*configinicial[mod1(y-1,L),x]-configinicial[y,x]*configinicial[y,mod1(x+1,L)]-configinicial[y,x]*configinicial[y,mod1(x-1,L)]

    return -out*2
end


## función que simula el modelo de ising y regresa un arreglo depsues de un tiempo t.

function mcmcising(t,T,L,configinicial::Array{Int64,2})
    sigma=0
    out=configinicial
    w=0
    for i in 1:t
        w+=i
        x=rand(1:L)
        y=rand(1:L)
        z=rand()
        m=aumentoe(x,y,L,out)
        alfa=min(1,e^(-m/T))
            if z<alfa
                out[y,x]=out[y,x]*-1
            end
    end
    return out
end

## función que calucla la energía de un arreglo de espines.

function energia(config::Array{Int64,2},L)
    out=0
    m=ones(L*L)
    s=1
    for x in 1:L
        for y in 1:L
            m[s]=aumentoe(x,y,L,config)/2
            s+=1
        end
    end
    return -sum(m)
end

## función que calcula la magnetización de un arreglo de espines.



## fucnion que calcula la energía y la magnetización en cada tiempo de un arregle de espines al ir cambiando con Markov Chain Monte Carlo. [1] da energía y [2] da magnetización. 

function mcmcisingen(t,T,L,configinicial::Array{Int64,2})
    sigma=0
    out=configinicial
    en=zeros(t)
    mag=zeros(t)
    for i in 1:t
        x=rand(1:L)
        y=rand(1:L)
        z=rand()
        m=aumentoe(x,y,L,out)
        alfa=min(1,e^(-m/T))
            if z<alfa
                out[y,x]=out[y,x]*-1
            end
        en[i]=energia(out,L)
        mag[i]=magnetizacion(out,L)
    end
    return en,mag
end

