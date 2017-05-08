function pharm(n::Int)
    np = nprocs()-1

    if n%np != 0
        error("n must be a multiple of ", np)
    end
    
    chunk = round(Int,n/np)
        
    result = @parallel (+) for k=1:np
        range_harm((k-1)*chunk+1, k*chunk)
    end
    return result
end

function range_harm(a::Int, b::Int)
    result = 0.0
    for k=a:b
        result += 1/k
    end
    return result
end

function sharm(n::Int)
    return range_harm(1,n)
end

