using QuantumComputing

psi = Ket(0,0,0,0)
n = length(psi)

println("input:")
println(psi)

psi = Hadamard(n,4)*GCNot(n,1,2,3)*Not(n,3)*Not(n,2)*psi

println("output:")
println(psi)
