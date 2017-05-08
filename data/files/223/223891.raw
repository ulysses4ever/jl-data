module Teste

type Kernel{T<:FloatingPoint}
    coef::Array{T,1}
    m::Int
    
end
Kernel{T}(c::Array{T,1}) = Kernel(c, length(c))



function daniell_kernel{T<:FloatingPoint}(m, ::Type{T})
    one(T)/(2*m+1) * ones(T, m+1)
end
daniell_kernel(m) = daniell_kernel(m, Float64)

function modified_daniell_kernel{T<:FloatingPoint}(m, ::Type{T})
    cc = ones(T, m+1) / (2*m)
    cc[m+1] /= 2
    return cc
end
modified_daniell_kernel(m) = modified_daniell_kernel(m, Float64)

function fejer_kernel{T<:FloatingPoint}(m, r, ::Type{T})

    
    o1 = one(T)
    n = 2*m + 1
    wn = zeros(T, m+1)
    
    wj = 2*o1*pi*linspace(o1, m*o1, m)/n
    for i = 1:m
        wn[i+1] = sin(r*o1*wj[i]/2)^2 / sin(wj[i]/2)^2 / r
    end
    wn[1] = r
    return wn / (wn[1] + 2*sum(wn[2:end]))

    return wn
end
fejer_kernel(m, r) = fejer_kernel(m, r, Float64)



end

    