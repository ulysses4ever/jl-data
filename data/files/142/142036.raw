using Base.Test
using Distributions
import Delta: IndependentBelief, Dirac, SampleableBelief

a = IndependentBelief(Normal(0,1), Normal(0,3))
@test isa(rand(a),(Float64, Float64))
b = Dirac{Float64,SampleableBelief}(10,10)
@test rand(b) == (10,10)
