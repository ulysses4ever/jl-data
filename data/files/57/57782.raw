#! /usr/bin/env julia

include("/home/steve/Software/julia/base/test.jl")
using Test

f() = 1
g() = 2

println(macroexpand(:(@test f() <= g() <=6 <=7)))
println(macroexpand(:(@test f() >= g() >= 6)))

@test f() <= g() <=6 <=7 
@test f() >= g() >= 6

