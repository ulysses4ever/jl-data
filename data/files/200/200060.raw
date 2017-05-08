import Distributions: meanlogdet
srand(14578)

p = 6
n = 10
L0 = makeLtri(rand(round(Int, p * (p + 1) / 2)))

#=
Each of these functions computes E[log |X|] for X ∼ Wishart:
$E[log |X|] = ψ_p(n/2) + p log 2 + log |V| with V the base
matrix.
We write the base matrix V in terms of its Cholesky: X = L ⋅ L^⊤$,
so that $∂E[logdet(V)] = tr(V^{-1}∂V) = 2 tr(L^{-1} ∂L)
=#
function f1(x)
    L = makeLtri(x[2:end])
    d = Wishart(x[1], L * L')
    meanlogdet(d)
end
function f2(x)
    Σ2 = L0 * L0'
    d = Wishart(x[1], Σ2)
    meanlogdet(d)
end
function f3(x)
    L = makeLtri(x)
    d = Wishart(n, L * L')
    meanlogdet(d)
end

function gradL(x)
    L = makeLtri(x)
    2 * getLtri(inv(L)')
end
function graddf(x)
    v = 0
    for i = 1:p
        v += polygamma(1, 0.5 * (x - (i - 1)))
    end
    v/2
end

function grad1(x)
    vcat(graddf(x[1]), gradL(x[2:end]))
end
grad2(x) = graddf(x)
grad3(x) = gradL(x)

agrad1 = ForwardDiff.gradient(f1)
agrad2 = ForwardDiff.gradient(f2)
agrad3 = ForwardDiff.gradient(f3)

Ntests = 10
for _ in 1:Ntests
    df = rand() + p - 1
    l = rand(round(Int, p * (p + 1) / 2))
    @assert grad1(vcat(df, l)) ≈ agrad1(vcat(df, l))
    @assert grad2(df) ≈ agrad2([df])[1]
    @assert grad3(l) ≈ agrad3(l)
end
