type Taylor{T}
    coeffs :: Array{T,1}
    order :: Int
    # Constructor interno
    function Taylor(coeffs::Array{T,1}, order::Int)
        ll = length(coeffs)
        order = max(ll-1, order)
        v = zeros(T, order+1)
        # v[1:ll] = coeffs[1:ll]
        for i=1:ll
            v[i] = coeffs[i]
        end
        new(v, order)
    end
end

# Constructores externos
Taylor{T<:Number}(v::Array{T,1}, n::Int) = Taylor{T}(v,n)
Taylor{T<:Number}(v::Array{T,1}) = Taylor{T}(v,0)
Taylor{T<:Number}(c::T, n::Int) = Taylor{T}([c],n)
Taylor{T<:Number}(c::T) = Taylor{T}([c],0)
Taylor{T<:Number}(t::Taylor{T},n) = Taylor{T}(t.coeffs, n)
Taylor{T<:Number}(t::Taylor{T}) = Taylor{T}(t.coeffs, 0)

function +(f::Taylor,g::Taylor)
    l = max(f.order,g.order)
    f, g = Taylor(f,l), Taylor(g,l)
    Taylor(f.coeffs+g.coeffs, l)
end
+(f::Taylor) = f
function -(f::Taylor,g::Taylor)
    l = max(f.order,g.order)
    f, g = Taylor(f,l), Taylor(g,l)
    Taylor(f.coeffs-g.coeffs, l)
end
-(f::Taylor) = Taylor(-f.coeffs,f.order)

function *(f::Taylor,g::Taylor)
    ll = max(f.order,g.order)
    f, g = Taylor(f,ll), Taylor(g,ll)
    T = promote_type( eltype(f.coeffs), eltype(g.coeffs) )
    v = zeros(T,ll+1)
    for ord = 0:ll     ## orden del resultado
        suma = zero(T)
        for n = 0:ord  ## implementación \Sum
            suma += f.coeffs[n+1] * g.coeffs[ord-n+1]
        end
        v[ord+1] = suma
    end
    #
    Taylor(v, ll)
end