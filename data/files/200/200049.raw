function f1(x)
    d = Dirichlet(x)
    mean(d)[1]
end
function f2(x)
    n = 10
    d = Dirichlet(n, x[1])
    mean(d)[1]
end

function grad1(x)
    n = length(x)
    num = zeros(n)
    num[1] = one(eltype(x))
    num./sum(x) - (x[1] ./ sum(x)^2)
end
grad2(x) = [0.]

agrad1 = ForwardDiff.gradient(f1)
agrad2 = ForwardDiff.gradient(f2)

pts = Vector{Float64}[
    [1., 2.],
    [1.15, 0.75],
    [1.5, 3.75],
    [1.588, 1.082, 1.598, 1.081, 1.202],
    [1.708, 1.688, 1.503]
]
for p in pts
    @assert grad1(p) ≈ agrad1(p)
    @assert isapprox(grad2(p[1]), agrad2([p[1]]), atol=1e-16)
end
