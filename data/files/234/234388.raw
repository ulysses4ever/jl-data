const ϕ = (1 + √5) / 2
const ψ = (1 - √5) / 2

function fib(n::Integer)
    int((ϕ^n - ψ^n) / √5)
end


f = 0
s = 0
i = 1
while f < 4e6
    f = fib(i)
    if iseven(f)
        s += f
    end
    i += 1
end
println(s)
