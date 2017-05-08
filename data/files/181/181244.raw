using PolynomialProbabilities
using Base.Test

# Create some simple pdfs
pp1 = PolynomialProbability(-Inf, Inf, 1)
pp2 = PolynomialProbability(-Inf, Inf, [1], [0])

@test pp1 == pp2

pp3 = PolynomialProbability(-Inf, 0, 0)
append!(pp3, 0, Inf, .5, [0, -.5])

@test length(pp3) == 2
@test pp3[0] == PolynomialProbability(-Inf, 0, 0)
