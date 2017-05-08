##### Vectors, Arrays and Matrices

a=Array(Int64,1)
b=zeros(10)
c=ones(10)


##### exercise

##### 1.3.1

## Pkg.add("QuantEcon")
## Pkg.add("PyPlot")


using QuantEcon

function compute_asymptotic_var(A, Sigma, tolerance=1e-6)
    V = Sigma * Sigma'
    S = V
    err = tolerance + 1
    while err > tolerance
        next_S = A * S * A' + V
        err = norm(S - next_S)
        S = next_S
    end
    return S
end

A =     [0.8 -0.2;
        -0.1 0.7]
Sigma = [0.5 0.4;
         0.4 0.6]

eigmax(A)

compute_asymptotic_var(A, Sigma)

### using QuantEcon

solve_discrete_lyapunov(A, Sigma * Sigma')
