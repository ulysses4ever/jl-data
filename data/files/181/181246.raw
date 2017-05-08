using PolynomialProbabilities
using Base.Test

# Create some simple pdfs
pp1 = PolynomialProbability();
append!(pp1, -Inf, Inf, 1.);
pp2 = PolynomialProbability(1. * eye(1), [0.]);

@test pp1 == pp2

pp3 = PolynomialProbability();
append!(pp3, -Inf, 0., 0.);
append!(pp3, 0., Inf, [[.5 0]; [.5 .5]], [0, -.5]);

@test length(pp3) == 2
@test pp3[1] == PolynomialProbabilityPiece(-Inf, 0., 0.);

# Test some simplifications

# Test dropping of blank values
ppbefore = PolynomialProbability([[1. 1 0]; [0 0 0]], [1., 2.]);
ppafter = ppsimple(ppbefore)

@test ppafter[1].t0 == -Inf
@test ppafter[1].t1 == Inf
@test ppafter[1].polys == [[1. 1]]
@test ppafter[1].exp == [1]

# Test combining polys
ppbefore = PolynomialProbability()
append!(ppbefore, -Inf, 0., [[1. 1]], [1.])
append!(ppbefore, 0., Inf, [[1. 1]; [3 3]; [1 1]], [1., 3, 1])
ppafter = ppsimple(ppbefore)

@test ppafter[1].t0 == -Inf
@test ppafter[1].t1 == 0
@test ppafter[1].polys == [[1. 1]]
@test ppafter[1].exp == [1.]

@test ppafter[2].t0 == 0
@test ppafter[2].t1 == Inf
@test ppafter[2].polys == [[3. 3]; [2 2]]
@test ppafter[2].exp == [3., 1]
