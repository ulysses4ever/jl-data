using Base.Test
include("../derivative.jl")

fnc = (x) -> x^2 + 2x + 3
d = derivative(fnc)

@test d(0) == 2.0
@test d(1) == 4.0
@test d(2) == 6.0
