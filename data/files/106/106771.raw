using MDP
using Base.Test

println("Running SimpleMDP tests")

println(repeat("=", 50))
println("Finite Horizon")
println(repeat("=", 50))

I = [1,1,2,3,4]
J = [1,2,2,2,1]
R = sparse(I, J, Float64[2,2,2,2,3])
P = sparse(I,J,[.75,.25,1.00,1.00,1.00])
indvec = [2,4]
V0 = Float64[-1; 1]
β=0.5

mdp = SimpleMDP(R, P, indvec, β, IClock())

sol1 = valueiteration(mdp; Vstart=V0)
sol2 = policyiteration(mdp; Pstart=[1, 3])
soltrue = ([4.666667, 5.333333], [2,4])

println("Simple Solution")
println("  Value Iteration")
@test_approx_eq_eps sol1[1] soltrue[1] 1e-3
@test sol1[2] == soltrue[2]

println("  Policy Iteration")
@test_approx_eq_eps sol2[1] soltrue[1] 1e-3
@test sol2[2] == soltrue[2]

simulate(mdp, 10, 1)
