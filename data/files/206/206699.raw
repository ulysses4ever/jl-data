module ModelsGenerators

export
  randiv

# package code goes here
function randiv(n::Int64        = 100;
                m::Int64        = 5,
                k::Int64        = 1,
                theta0::Float64 = 0.0,
                rho::Float64    = 0.9,
                CP::Int64       = 10)

    ## Generate IV Model with CP
    
    tau     = fill(sqrt(CP/(m*n)), m)
    z       = randn(n, m)
    vi      = randn(n, 1)
    eta     = randn(n, 1)
    epsilon = rho*eta+sqrt(1-rho^2)*vi
    x       = z*tau + eta
    if k>1
        x_ex = randn(n, k-1)
        x = [x  x_ex]
        z = [z  x_ex]
    end
    y       = x[:,1]*theta0 + epsilon
    return y, x, z
end

end # module


## function typed_fad_hessian{T<:Real}(f::Function, ::Type{T})
##   g(x::Vector{T}) = hessian(f(FADHessian(x)))
##   return g
## end

## function ForwardDiff.hessian{T<:Real, n}(x::Array{FADHessian{T, n},1})

##     y = Array(T, n, n, length(x))
##     k = 1

##     for s = 1:length(x)
##         for i in 1:n
##             for j in 1:i
##                 y[i, j, s] = x[s].h[k]
##                 k += 1
##             end
##         end
##         for i in 1:n
##             for j in (i+1):n
##                 y[i, j, s] = y[j, i, s]
##             end
##         end
##         k = 1
##     end
    
##     y
## end

## y,x,z = randiv(k=2)
## h(theta) = (z'*(y-x*theta))[:]
## h([.1,.1])

## g = forwarddiff_jacobian(h, Float64, fadtype=:typed)
## g([.1,.1])

## fad =  hessian(f(FADHessian([.1, .1])))



## f(x) = [x[1]^2+x[2], 3*x[1], x[1]^2*x[2]^3]

## ss = forwarddiff_hessian(f, Float64, fadtype=:typed)
## ss([.1, .1])

## ss = forwarddiff_hessian(f, Float64, fadtype=:typed)
## ss([.1, .1])
