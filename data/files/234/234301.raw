# one-liner
[int(string(s)) for s in string(BigInt(1) << 1000)] |> sum |> println

# multi-liner
function two_sum(n::Int)
    n = BigInt(1) << n
    s = 0
    for c in string(n)
        s += int(string(c))
    end
    s
end

