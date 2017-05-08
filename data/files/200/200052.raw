srand(12347)

# each of these functions computes
# x' ⋅ Λ^-1 x = ||L'^-1 x||^2
p = 5
L2 = makeLtri(rand(round(Int, p * (p + 1) / 2)))
μ3 = rand(p)
function f1(x)
    L = makeLtri(x[p+1:end])
    μ = x[1:p]
    Λ = L * L'
    d = MvNormalCanon(Λ * μ, Λ)
    sqmahal(d, zeros(p))
end
function f2(x)
    Λ2 = L2 * L2'
    d = MvNormalCanon(Λ2 * x, Λ2)
    sqmahal(d, zeros(p))
end
function f3(x)
    L = makeLtri(x)
    Λ = L * L'
    d = MvNormalCanon(Λ * μ3, Λ)
    sqmahal(d, zeros(p))
end

function gradμ(μ, l)
    L = makeLtri(l)
    Λ = L * L'
    Λ * 2μ
end
function gradΛ(μ, l)
    L = makeLtri(l)
    X = μ * μ'
    2 * getLtri(X * L)
end

function grad1(x)
    μ = x[1:p]
    l = x[p+1:end]
    vcat(gradμ(μ, l), gradΛ(μ, l))
end
grad2(x) = gradμ(x, getLtri(L2))
grad3(x) = gradΛ(μ3, x)

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
