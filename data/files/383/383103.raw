function dynamicTimeWarping(s::Array{Float64,2},t::Array{Float64,2})
    
    function distance(x,y)
        return norm(x-y)
    end
    
    n=size(s)[2]
    m=size(t)[2]
    dtw=Array(Float64,n,m)
    for i in 1:n
        dtw[i,1]=Inf
    end
    for i in 1:m
        dtw[1,i]=Inf
    end
    
    dtw[1,1]=0
    
    for i in 2:n
        for j in 2:m            
           dtw[i,j]= distance(s[:,i],t[:,j]) + minimum([dtw[i-1,j],dtw[i,j-1],dtw[i-1,j-1]])    
        end
    end
    
    tx=Array(Int64,0)
    ty=Array(Int64,0)
    
    optI=n
    optJ=m
    unshift!(tx,optI)
    unshift!(tY,optJ)
    while(optI>1 && optJ>1)
        i=argmin(dtw[optI-1,optJ],dtw[optI,optJ-1],dtw[optI-1,optJ-1])
        if i==1
            optI-=1
        elseif i==2
            optJ-=1
        else
            optJ-=1
            optI-=1
        end
        unshift!(tx,optI)
        unshift!(tY,optJ)      
    end    
    return (dtw[n,m],tx,ty)
end


