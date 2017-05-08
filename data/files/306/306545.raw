# Getting started with julia
# map, filter, list comprehensions

map(x -> x * 10, [2, 4, 5]) 

map([-3:3]) do x
     if x == 0 return 0
     elseif iseven(x) return 2
     elseif isodd(x) return 1
     end
end

filter( n -> iseven(n), [1:10])

#list comprehensions 

# constraining the type 
arr = Float64[x^2 for x in 1:4]
arr

cubes = [x^3 for x in [1:5]]

mat1 = [x + y for x in 1:2, y in 1:3]

table10 = [x * y for x = 1:10, y = 1:10]

arrany = Any[i * 2 for i in 1:5]

# multiple dispatch examples
# this is an insanely cool idea
f(n, m) = "base case"
f(n::Number, m::Number) = "n and m are both numbers"
f(n::Number, m) = "n is a number"
f(n, m::Number) = "m is a number"
f(n::Integer, m::Integer) = "n and m are both integers"

f(1.5, 2)
methods(f) # take a look at the methods for the function


#mastering julia
x = 7; y = 5; x/y

# interesting operator
y\x #reverse division

x = 0xbb31; y = 0xaa5f; x$y
# ~ NOT, | OR, & AND, $ XOR

# booleans
p = (2 < 3)
typeof(p)

#Arrays
# enumerate the vales stored in the array
A = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377];
A

A2 = [1:10]; B = [1:3:15]; C = [1:0.5:5];
A2
B
C # this returns floats instead of ints






