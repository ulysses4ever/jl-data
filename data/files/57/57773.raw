#! /usr/bin/env julia

using BoundingBoxes

@boundingbox Bounds2, "x", "y"

a = Bounds2(Float64)

# warmup rand
rand()

# dummy 

#update with random values
loop1() =  for i = 1:10000
    a.x_min = rand()
    a.y_min = rand()
    a.x_max = rand()
    a.y_max = rand()
end

@time loop1()
@time loop1()

#now make immutable
immutable Bounds2I{T}
    x_min::T
    y_min::T
    x_max::T
    y_max::T
end

b = Bounds2I{Float64}(Inf,Inf,-Inf,-Inf)
#update with random values
loop2() = for i = 1:10000
    b = Bounds2I{Float64}(rand(),rand(),rand(),rand())
end

@time loop2()
@time loop2()

