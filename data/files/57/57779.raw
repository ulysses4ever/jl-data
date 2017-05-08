#! /usr/bin/env julia

include("/home/steve/Software/julia/base/test.jl")
using Test

f() = 1

println(macroexpand(:(@test f() != 1)))
println(macroexpand(:(@test f() == 1)))

@test f() == 1
@test f() != 1

