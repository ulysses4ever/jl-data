using QuantumComputing
using Base.Test

# write your own tests here
a = Ket(0,1,0,1,0)
b = Ket(1,0,1,0,1)

n = length(a)
@test n==5
@test a == a
@test a != b

c = Swap(n,1,1)*a
@test c == a
c = Swap(n,1,2)*a
@test c == Ket(1,0,0,1,0)
c = Swap(n,1,n)*a
@test c == a

c = Swap(2,2,2)
for i=0:1, j=0:1
@test c*Ket(i,j)==Ket(i,j) 
end

c = Not(5,1)
@test c*Ket(0,0,0,0,0)==Ket(1,0,0,0,0)
c = Not(n,n)
@test c*Ket(1,1,1,1,1)==Ket(1,1,1,1,0)

a = Ket(1,1)
c = CNot(2,1,2)*a
println(c)
@test c == Ket(0,1)

c = GCNot(2,2,1)
for i=0:1, j=0:1
@test c*Ket(i,j) == GGate(CNOT)*Ket(i,j)
end

