module Hielo

export conf_i
export conf_random
export Single_cluster
export MultiCluster
export contador_segundos
export Single_cluster_E
export MultiCluster_E
export contadorespromedio_beta
export energiaspromedio_beta
export tiempo_sistema_S
export tiempos_S
export tiempo_sistema_M
export tiempos_M


function conf_i(n::Int,m::Int)
    out=zeros(n,n)
    out[1,1]=rand(0:2)
    for i in 1:n-1
        for j in 1:n-1
            out[i,j+1]=mod(out[i,j]+1,3)
        end
        out[i+1,:]=mod(out[i,:]+1,3)
    end

    #cuando n es 1 mod 3, hay problemas con las reglas de hielo
    if mod(n,3)==1
        out[:,n]=mod(out[:,1]+1,3)
        out[n,:]=mod(out[1,:]+1,3)
        out[n,n]=mod(out[1,1]+2,3)
    end
    out
end

function conf_random(L1::Int,L2::Int,pasos=30)
    old=conf_i(L1,L2)
    for t in 1:pasos
        new=MultiCluster(old)
        new,old=old,new
    end
    old
end

function indices_primeros(ij,i,j,L1,L2)
    if ij==1
        return mod1(i-1,L1),j
        elseif ij==2
        return i,mod1(j-1,L2)
        elseif ij==3
        return mod1(i+1,L1),j
        elseif ij==4
        return i,mod1(j+1,L2)
    end
end

function Single_cluster(arreglo::Array{Float64,2})
    L2=length(arreglo[1,:])
    L1=length(arreglo[:,1])
    red_bool=trues(L1,L2)
    #Se escoge un cuadrado al azar entre toda la red, y su número es escogido como 'colorA'
    i=rand(1:L1)
    j=rand(1:L2)
    colorA=arreglo[i,j]
    #Se escoge al azar un 'colorB' entre los restantes
    colorB=mod(rand(colorA+1:colorA+2),3)
    index_i=[i]
    index_j=[j]
    #Cambio el color de la celda inicial
    arreglo[i,j]=colorB
    red_bool[i,j]=false
    test=false
    t_limit=L1*2
    t=1
    while t<t_limit
        new_index_i=Int[]
        new_index_j=Int[]
        for n=1:length(index_i)
            #Primeros vecinos
            for ij=1:4
                inew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[1]
                jnew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[2]
                if red_bool[inew,jnew]==true
                    if arreglo[inew,jnew]==colorA
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorB
                        test=true
                    elseif arreglo[inew,jnew]==colorB
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorA
                        test=true
                    end
                end
            end
        end
        index_i=deepcopy(new_index_i)
        index_j=deepcopy(new_index_j)
        if test==false
            #println("there are no more squares to add")
            t=t_limit
        end
        test=false
    end
    return arreglo
end

function SingleCluster(arreglo::Array{Float64,2},red_bool,i,j,colorA, colorB)
    L2=length(arreglo[1,:])
    L1=length(arreglo[:,1])
    #red_bool=trues(L1,L2)
    arreglo_old=deepcopy(arreglo)
    if arreglo[i,j]==colorA
        arreglo[i,j]=colorB
    else
        arreglo[i,j]=colorA
    end
    index_i=[i]
    index_j=[j]
    red_bool[i,j]=false
    test=false
    t_limit=max(L1,L2)
    t=1
    while t<t_limit
        new_index_i=Int[]
        new_index_j=Int[]
        for n=1:length(index_i)
            #Primeros vecinos
            for ij=1:4
                inew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[1]
                jnew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[2]
                if red_bool[inew,jnew]==true
                    if arreglo[inew,jnew]==colorA
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorB
                        test=true
                    elseif arreglo[inew,jnew]==colorB
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorA
                        test=true
                    end
                end
            end
        end
        index_i=deepcopy(new_index_i)
        index_j=deepcopy(new_index_j)
        if test==false
            t=t_limit
        end
        test=false
    end
    #Se escoge con 50% si se cambian o no los colores de este nuevo cluster
    if rand()<0.5
        #println(":C")
        return arreglo_old,red_bool
    else
        return arreglo,red_bool
    end
end

function Update!(red_bool,red_bool_dummy)
    L2=length(red_bool[1,:])
    L1=length(red_bool[:,1])
    for i in 1:L1
        for j in 1:L2
            if red_bool_dummy[i,j]==false
                red_bool[i,j]=false
            end
        end
    end
    #return red_bool
end

function MultiCluster(arreglo)
    L2=length(arreglo[1,:])
    L1=length(arreglo[:,1])
    red_bool=trues(L1,L2)
    #hey=[]
    #Se escoge al azar dos colores
    colorA=rand(0:2)
    colorB=mod(rand(colorA+1:colorA+2),3)
    for i in 1:L1
        for j in 1:L2
            if red_bool[i,j]==true
                if arreglo[i,j]==colorA || arreglo[i,j]==colorB
                    arreglo,red_bool_dummy=SingleCluster(arreglo,red_bool,i,j,colorA,colorB)
                    Update!(red_bool,red_bool_dummy)
                end
            end
        end
    end
    return arreglo
end

function segundos_vecinos(arreglo::Array{Float64,2},i,j)
    L1=length(arreglo[:,1])
    L2=length(arreglo[1,:])
    arreglo[mod1(i-1,L1),mod1(j-1,L2)],arreglo[mod1(i-1,L1),mod1(j+1,L2)],arreglo[mod1(i+1,L1),mod1(j-1,L2)],arreglo[mod1(i+1,L1),mod1(j+1,L2)]
end

function indices_segundos(ij,i,j,L1,L2)
    if ij==1
        return mod1(i-1,L1),mod1(j-1,L2)
        elseif ij==2
        return mod1(i-1,L1),mod1(j+1,L2)
        elseif ij==3
        return mod1(i+1,L1),mod1(j-1,L2)
        elseif ij==4
        return mod1(i+1,L1),mod1(j+1,L2)
    end
end

function contador_segundos(arreglo::Array{Float64,2})
    L1=length(arreglo[:,1])
    L2=length(arreglo[1,:])
    contador=0
    for i in 1:L1
        for j in 1:L2
            segundo=segundos_vecinos(arreglo,i,j)
            for ij in 1:4
                if segundo[ij]==arreglo[i,j]
                    contador+=1
                end
            end
        end
    end
    contador/2
end

function Single_cluster_E(β,arreglo_or::Array{Float64,2},ϵ=1.0)
    arreglo=copy(arreglo_or)
    L2=length(arreglo[1,:])
    L1=length(arreglo[:,1])
    red_bool=trues(L1,L2)
    P_add=1-e^(-β*ϵ)
    #Se escoge un cuadrado al azar entre toda la red, y su número es escogido como 'colorA'
    i=rand(1:L1)
    j=rand(1:L2)
    colorA=arreglo[i,j]
    #Se escoge al azar un 'colorB' entre los restantes
    colorB=mod(rand(colorA+1:colorA+2),3)
    index_i=[i]
    index_j=[j]
    colorC=3-(colorA+colorB)
    #Cambio el color de la celda inicial
    arreglo[i,j]=colorB
    red_bool[i,j]=false
    test=false
    t_limit=L1*2
    t=1
    while t<t_limit
        new_index_i=Int[]
        new_index_j=Int[]
        for n=1:length(index_i)
            #Primeros vecinos
            for ij=1:4
                inew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[1]
                jnew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[2]
                if red_bool[inew,jnew]==true
                    if arreglo[inew,jnew]==colorA
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorB
                        test=true
                    elseif arreglo[inew,jnew]==colorB
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorA
                        test=true
                    end
                end
            end
            #Segundos vecinos
            segundo=segundos_vecinos(arreglo,index_i[n],index_j[n])
            for ij in 1:4
                ii_new=indices_segundos(ij,index_i[n],index_j[n],L1,L2)[1]
                jj_new=indices_segundos(ij,index_i[n],index_j[n],L1,L2)[2]
                if segundo[ij] !=arreglo[index_i[n],index_j[n]] && segundo[ij] !=colorC && red_bool[ii_new,jj_new]==true
                    if rand()<P_add
                        push!(new_index_i,ii_new)
                        push!(new_index_j,jj_new)
                        red_bool[ii_new,jj_new]=false
                        if arreglo[index_i[n],index_j[n]]==colorA
                                arreglo[ii_new,jj_new]=colorA
                        else
                                arreglo[ii_new,jj_new]=colorB
                        end
                        test=true
                    end
                end
            end
        end
        index_i=deepcopy(new_index_i)
        index_j=deepcopy(new_index_j)
        if test==false
            #println("there are no more squares to add")
            t=t_limit
        end
        test=false
    end
    return arreglo
end

function SingleCluster_E(β,arreglo::Array{Float64,2},red_bool,i,j,colorA,colorB,colorC,ϵ=1.0)
    L2=length(arreglo[1,:])
    L1=length(arreglo[:,1])
    P_add=1-e^(-β*ϵ)
    arreglo_old=copy(arreglo)
    if arreglo[i,j]==colorA
        arreglo[i,j]=colorB
    else
        arreglo[i,j]=colorA
    end
    index_i=[i]
    index_j=[j]
    red_bool[i,j]=false
    test=false
    t_limit=max(L1,L2)
    t=1
    while t<t_limit
        new_index_i=Int[]
        new_index_j=Int[]
        for n=1:length(index_i)
           #Primeros vecinos
            for ij=1:4
                inew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[1]
                jnew=indices_primeros(ij,index_i[n],index_j[n],L1,L2)[2]
                if red_bool[inew,jnew]==true
                    if arreglo[inew,jnew]==colorA
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorB
                        test=true
                    elseif arreglo[inew,jnew]==colorB
                        push!(new_index_i,inew)
                        push!(new_index_j,jnew)
                        red_bool[inew,jnew]=false
                        arreglo[inew,jnew]=colorA
                        test=true
                    end
                end
            end
            #Segundos vecinos
            segundo=segundos_vecinos(arreglo,index_i[n],index_j[n])
            for ij in 1:4
                ii_new=indices_segundos(ij,index_i[n],index_j[n],L1,L2)[1]
                jj_new=indices_segundos(ij,index_i[n],index_j[n],L1,L2)[2]
                if segundo[ij] !=arreglo[index_i[n],index_j[n]] && segundo[ij] !=colorC && red_bool[ii_new,jj_new]==true
                    if rand()<P_add
                    #println("aceptó")
                        push!(new_index_i,ii_new)
                        push!(new_index_j,jj_new)
                        red_bool[ii_new,jj_new]=false
                        if arreglo[index_i[n],index_j[n]]==colorA
                                arreglo[ii_new,jj_new]=colorA
                        else
                                arreglo[ii_new,jj_new]=colorB
                        end
                        test=true
                    end
                end
            end
        end
        index_i=deepcopy(new_index_i)
        index_j=deepcopy(new_index_j)
        if test==false
            t=t_limit
        end
        test=false
    end
    if rand()<0.5
        #println(":C")
        return arreglo_old,red_bool
    else
        return arreglo,red_bool
    end
end

function MultiCluster_E(β,arreglo_or,ϵ=1.0)
    arreglo=copy(arreglo_or)
    L2=length(arreglo[1,:])
    L1=length(arreglo[:,1])
    red_bool=trues(L1,L2)
    #Se escoge al azar dos colores
    colorA=rand(0:2)
    colorB=mod(rand(colorA+1:colorA+2),3)
    colorC=3-(colorA+colorB)
    for i in 1:L1
        for j in 1:L2
            if red_bool[i,j]==true
                if arreglo[i,j]==colorA || arreglo[i,j]==colorB
                    arreglo,red_bool_dummy=SingleCluster_E(β,arreglo,red_bool,i,j,colorA,colorB,colorC)
                    Update!(red_bool,red_bool_dummy)
                end
            end
        end
    end
    return arreglo
end

function contadorespromedio_beta(configuracion_inicial::Array{Float64,2},β_max=5.0,t_max=50,intervalos=20)
    betas=[0:β_max/intervalos:β_max]
    maximo=length(betas)
    out=zeros(maximo)
    for i in 1:maximo
        old=copy(configuracion_inicial)
        for t in 1:t_max
            new=Single_cluster_E(betas[i],old)
            out[i]+=contador_segundos(new)
            new,old=old,new
        end
        out[i]=out[i]/t_max
    end
    out
end

function energiaspromedio_beta(configuracion_inicial::Array{Float64,2},β_max=5.0,t_max=50,intervalos=20)
    L1=length(configuracion_inicial[:,1])
    L2=length(configuracion_inicial[1,:])
    1-contadorespromedio_beta(configuracion_inicial::Array{Float64,2},β_max,t_max,intervalos)/(L1*L2)
end

function tiempo_sistema_S(β,original::Array{Float64,2},t_max=1000)
    old=copy(original)
    t=0
    tic()
    while t<t_max
        new=Single_cluster_E(β,old)
        if abs(contador_segundos(new)-contador_segundos(old))<1.0
            return toq()
        end
        new,old=old,new
        t+=1
    end
end

function tiempos_S(β,L_max,paso,t_promedio=10)
    tamaños=[10:paso:L_max]
    maximo=length(tamaños)
    out=zeros(maximo)
    for L in 1:maximo
        old=conf_random(tamaños[L],tamaños[L],15)
        for t in 1:t_promedio
            out[L]+=tiempo_sistema_S(β,old)
        end
    end
    out./t_promedio
end

function tiempo_sistema_M(β,original::Array{Float64,2},t_max=1000)
    old=copy(original)
    t=0
    tic()
    while t<t_max
        new=MultiCluster_E(β,old)
        if abs(contador_segundos(new)-contador_segundos(old))<1.0
            return toq()
        end
        new,old=old,new
        t+=1
    end
end

function tiempos_M(β,L_max,paso,t_promedio=10)
    tamaños=[10:paso:L_max]
    maximo=length(tamaños)
    out=zeros(maximo)
    for L in 1:maximo
        old=conf_random(tamaños[L],tamaños[L],15)
        for t in 1:t_promedio
            out[L]+=tiempo_sistema_M(β,old)
        end
    end
    out./t_promedio
end

end
