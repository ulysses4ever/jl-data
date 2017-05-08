#!/usr/bin/julia

Σ = 0
i0 = 1
i1 = 1

while i1 < 4000000
    i = i0 + i1
    Σ += i%2 == 0 ? i : 0
    i0 = i1
    i1 = i
end

println(Σ)