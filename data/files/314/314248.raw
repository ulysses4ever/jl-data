include("../helpers.jl")

f(x) = cos(x)

k = 20
x = iterate(f, 1.0, k) # converges around ≈ 0.73

fp = fixedpoint(x, ϵ = 1e-3) # n = 17
