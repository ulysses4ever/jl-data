map(round, [1.2, 3.5, 1.7])
(1+2)::Int

function test(x::Number)
    return x*2
end

function test2(x)
    return x*2
end

test("aoeu")
test2("aoeu")

f(x::Float64, y::Float64) = 2x + y
f(2.0, 3.0)
f(2, 3.0)
methods(f)
f(x, y) = println("Whoa there, Nelly.")
f("foo", 1)
f(2.0, 3.0)


g(x::Float64, y) =  2x + y
g(x, y::Float64) = x + 2y

same_type{T}(x::T, y::T) = true
same_type(x,y) = false
methods(same_type)

myappend{T}(v::Vector{T}, x::T) = [v..., x]

mytypeof{T}(x::T) = T
mytypeof(1)
mytypeof(1.0)

(3.2+1)::Real

type Foo
    bar
    baz::Int
    qux::Float64
end

foo = Foo("Hello world", 3, 9.8)
typeof(foo)
names(foo)

x=10
eval(:x)

function testf(x)
    y = x
    println(typeof(y))
    println(y)
    println(eval(x)+1)
end

testf(:x)


using Compat
@compat d=Dict(:a => 0)
@compat d=Dict{ASCIIString, Int}("a" => 0, "B" => 9)
@compat Dict{Int,Int}( [ x => x*x for x in 1:10] )
[x => 2x for x in 1:10]
[2x for x in 1:10]

a = [1, 2, 3]
a[3]
b = [1 2 3]
b[1]
b[2]
b[3]
a2 = [1 2 3; 4 5 6]
a2[1]


a1 = [1, 2, 3]
a2 = ['a', 'b', 'c']
a3 = ["A", "B", "C"]
cat(2, a1, a2, a3)
[a1; a2; a3] # equals vcat (cat(1, ...))
b1 = [a1 a2 a3] # equals hcat (cat(2, ...))
b2 = [a3 a2 a1]
b1[3, 2]
c = cat(3, b1, b2)
c[2,3,2] # [row colmun z]
