module ModelsGenerators

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
