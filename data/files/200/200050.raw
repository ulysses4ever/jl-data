srand(14578)

p = 6
ν = 10
L0 = makeLtri(rand(round(Int, p * (p + 1) / 2)))

#=
if Ψ = L ⋅ L^⊤, then tr(Ψ) = ∑_{ij} L_{ij}^2
thus tr(E[Ψ]) = tr(Ψ)/(ν - p - 1)
and ∂Ψ/∂L = 2L
=#
function f1(x)
    L = makeLtri(x[2:end])
    d = InverseWishart(x[1], L * L')
    trace(mean(d))
end
function f2(x)
    Ψ0 = L0 * L0'
    d = InverseWishart(x[1], Ψ0)
    trace(mean(d))
end
function f3(x)
    L = makeLtri(x)
    d = InverseWishart(ν, L * L')
    trace(mean(d))
end

gradL(n, x) = 2 * x / (n - p - 1)
function graddf(n, x)
    L = makeLtri(x)
    -trace(L * L')/(n - p - 1)^2
end

function grad1(x)
    vcat(graddf(x[1], x[2:end]), gradL(x[1], x[2:end]))
end
grad2(x) = graddf(x, L0)
grad3(x) = gradL(ν, x)

agrad1 = ForwardDiff.gradient(f1)
agrad2 = ForwardDiff.gradient(f2)
agrad3 = ForwardDiff.gradient(f3)

Ntests = 10
for _ in 1:Ntests
    df = rand() + p + 1
    l = rand(round(Int, p * (p + 1) / 2))
    @assert grad1(vcat(df, l)) ≈ agrad1(vcat(df, l))
    @assert grad2(df) ≈ agrad2([df])[1]
    @assert grad3(l) ≈ agrad3(l)
end
