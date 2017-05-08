using QuantumComputing

# Quantum circuit of Deutsch-Jozsa algorithm
#
#      +---+  +---+  +---+  +---+
# |0⟩ -+ X +--+ H +--+   +--+ H +--
#      +---+  +---+  |   |  +---+
#                    | U |
#             +---+  |   |
# |0⟩ --------+ H +--+   +---------
#             +---+  +---+
#                          

psi = Ket(0,0,0,0,0)
n = length(psi)

Uf = reduce(*,[Hadamard(n,i) for i=1:n])

G1 = Not(n,5)
G2 = reduce(*,[Hadamard(n,i) for i=1:n])
G3 = reduce(*,[Hadamard(n,i) for i=1:n-1])

psi = G3*Uf*G2*G1*psi

println(psi)
println(extract(psi,5))

