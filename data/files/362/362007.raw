# Ill-Conditioning Matrix Number #

include("util.jl")

A = [1.0 2.0 4.0; 1.0 2.00001 4.0; 0.0 3.0 2.0]
b = [2.0, 2.0, 3]

C = improve(A,b,2)

solve(A,b)

solve(C[1],C[2])

cond(C[1])
cond(A)
