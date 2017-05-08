srand(13457)

import Distributions: mvtdist

p = 7
df = 5
L2 = makeLtri(rand(round(Int, p * (p + 1) / 2)))
μ3 = rand(p)
function f1(x)
    L = makeLtri(x[p+1:end])
    d = mvtdist(df, x[1:p], L * L')
    sqmahal(d, zeros(p))
end
function f2(x)
    Σ2 = L2 * L2'
    d = mvtdist(df, x, Σ2)
    sqmahal(d, zeros(p))
end
function f3(x)
    L = makeLtri(x)
    d = mvtdist(df, μ3, L * L')
    sqmahal(d, zeros(p))
end

function gradμ(μ, l)
    L = makeLtri(l)
    Σ = L * L'
    inv(Σ) * 2μ
end
function gradΣ(μ, l)
    L = makeLtri(l)
    Σ = L * L'
    X = μ * μ'
    getLtri(-2 * inv(Σ) * X * inv(L'))
end

function grad1(x)
    μ = x[1:p]
    l = x[p+1:end]
    vcat(gradμ(μ, l), gradΣ(μ, l))
end
grad2(x) = gradμ(x, getLtri(L2))
grad3(x) = gradΣ(μ3, x)

agrad1 = ForwardDiff.gradient(f1)
agrad2 = ForwardDiff.gradient(f2)
agrad3 = ForwardDiff.gradient(f3)

Ntests = 10
for _ in 1:Ntests
    m = rand(p)
    l = rand(round(Int, p * (p + 1) / 2))
    @assert grad1(vcat(m, l)) ≈ agrad1(vcat(m, l))
    @assert grad2(m) ≈ agrad2(m)
    @assert grad3(l) ≈ agrad3(l)
end
