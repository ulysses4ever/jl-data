using DataFrames

function sim_trivial(N)
    A = randn(N)
    B = 0.2*A .+ 0.05*randn(N)
    C = -0.8*B + 0.05*randn(N)
    DataFrame(A=A, B=B, C=C)
end

function sim_basic(N)
    A = randn(N)
    B = A .+ 0.1*randn(N)
    C = 0.6*A .+ 0.1*randn(N)
    D = B .- 0.3*C .+ 0.1*randn(N)
    E = D .+ 0.1*randn(N)
    F = E .+ 0.1*randn(N)
    G = F .+ 0.1*randn(N)
    DataFrame(A=A, B=B, C=C, D=D, E=E, F=F, G=G)
end

function sim_redundant(N)
    A = randn(N)
    Ac = A + 0.01*randn(N)
    B = 0.2*A .+ 0.05*randn(N)
    Bc = B + 0.01*randn(N)
    C = -0.8*B + 0.05*randn(N)
    Cc = C + 0.01*randn(N)
    DataFrame(A=A, Ac=Ac, B=B, Bc=Bc, C=C, Cc=Cc)
end