#! /usr/bin/julia

# Rosetta Code, Compound data type

type Point{T<:Real}
    x::T
    y::T
end

==(u::Point, v::Point) = (u.x == v.x) & (u.y == v.y)
-(u::Point) = Point(-u.x, -u.y)
+(u::Point, v::Point) = Point(u.x + v.x, u.y + v.y)
-(u::Point, v::Point) = Point(u.x - v.x, u.y - v.y)

a = Point(1, 2)
b = Point(3, 7)
c = Point(2, 4)

println("a = ", a)
println("b = ", b)
println("c = ", c)

println("a + b =     ", a+b)
println("-a + b =    ", -a+b)
println("a - b =     ", a-b)
println("a + b + c = ", a+b+c)
println("a == c      ", a == c)
println("a + a == c  ", a + a == c)




    


    
