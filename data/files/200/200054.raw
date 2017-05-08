function f1(x)
    d = Normal(x[1], x[2])
    mean(d) / std(d)
end
function f2(x)
    d = Normal(x[1], 3.5)
    mean(d) / std(d)
end
function f3(x)
    d = Normal(1.1, x[1])
    mean(d) / std(d)
end

grad1(x) = [1/x[2], -x[1]/x[2]^2]
grad2(x) = [1/3.5]
grad3(x) = [-1.1/x^2]

agrad1 = ForwardDiff.gradient(f1)
agrad2 = ForwardDiff.gradient(f2)
agrad3 = ForwardDiff.gradient(f3)

pts = Vector{Float64}[
    [1., 2.],
    [1.15, 0.75],
    [0.5, 3.75]
]
for p in pts
    @assert grad1(p) ≈ agrad1(p)
    @assert grad2(p[1]) ≈ agrad2([p[1]])
    @assert grad3(p[2]) ≈ agrad3([p[2]])
end
