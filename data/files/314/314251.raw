include("../helpers.jl")

using Gadfly
using Color

L(R) = x -> R * x * (1 - x)

k = 60
Rs = linspace(0.1, 4.0, 10) # [0.1, 0.533, 0.967, 1.4, ...]
xs = map(R -> iterate(L(R), 0.2, k), Rs)

fps = map(x -> fixedpoint(x, ϵ = 1e-3), xs) # [4, 8, 26, 10, ...]

# Values of R ∈ [3.0, 4.0] have very interesting properties.
# See Wikipedia or explore them yourself.
# Doing a Fourier Transform of the sequence will help illuminate these interesting
# properties
