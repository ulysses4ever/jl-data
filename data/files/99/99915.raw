using Base.Test
include("fib.jl")


list = Int[]

list = fib_next(list)

@test list[1] == 0
@test list[2] == 1

list = fib_next(list)
list = fib_next(list)

@test list[3] == 1
@test list[4] == 2

l = fib_up_to(8)

@test l[length(l)] <= 8

l = fib_up_to(1000)
@test l[length(l)] <= 1000
