#!/usr/bin/julia

prods = Set([ a * b for a in 1:999, b in 1:999 ])
filter!(x -> string(x) == reverse(string(x)) , prods)
println(maximum(prods))