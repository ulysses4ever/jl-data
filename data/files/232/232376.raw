using Distributions
using QuantEcon
type AR1
    a::Real
    b::Real
    sigma::Real
    phi::Distribution
end

function simulate(m::AR1, n::Integer, x0::Real)
    X = Array(Float64, n)
    X[1] = x0
    for t in 1:(n-1)
        X[t+1] = m.a * X[t] + m.b + rand(m.phi)
    end
    return X
end
m = AR1(0.9, 1, 1, Beta(5, 5))
X = simulate(m, 100, 0.0)
### Pkg.add("PyPlot")
### using PyPlot
using Gadfly
plot(x=1:100,y=X)

