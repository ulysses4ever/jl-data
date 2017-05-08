function f1(x)
    d = Poisson(x[1])
    skewness(d)
end

grad1(x) = [-1/(2x[1]^1.5)]

agrad1 = ForwardDiff.gradient(f1)

pts = Vector{Float64}[
    [1.],
    [1.15],
    [1.5],
    [1.588],
    [1.708]
]
for p in pts
    @assert grad1(p) ≈ agrad1(p)
end
