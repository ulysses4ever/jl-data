
using Base.Test
using StatefulIterators_
import StatefulIterators
import StatefulIterators_.reset!
import Base.read

reset!(x) = nothing
reset!(s::Union{StatefulIterators.ArrayIterator, StatefulIterators.IterIterator}) = (s.state = start(s.iter))

typealias TestTypes Union{Array, ASCIIString, Range}

read(x::TestTypes) = x[1]
read(x::TestTypes, n::Int) = x[1:n]
read(x::ASCIIString, n::Int) = collect(x[1:n]) # this must be specialized
read(x::TestTypes, dims::Int...) = reshape(read(x, prod(dims)), dims)
read{U}(x::TestTypes, ::Type{U}, dims...) = println("Not implemented!")
read{U}(x::StatefulIterators.IterIterator, ::Type{U}, dims...) = println("Not implemented!")
function read{U}(x::Array, ::Type{U}, dims...)
    M = prod(dims)
    N = cld(M * sizeof(U), sizeof(eltype(x)))
    return reshape(resize!(reinterpret(U, read(x, N)), M), dims)
end


N = 10^6; # size of iterable

function perf{T}(x::T, t::DataType)
    println(T)
    println("\tcollect")
    collect(x)
    reset!(x)
    @time collect(x)
    
    println("\tread single")
    reset!(x)
    read(x)
    reset!(x)
    @time (for _ in 1:N read(x); end)
    
    println("\tread chunk")
    reset!(x)
    read(x, N)
    reset!(x)
    @time read(x, N)
    
    println("\tread reinterpret")
    reset!(x)
    read(x, Int8, N)
    reset!(x)
    @time read(x, Int8, N)

    if eltype(t) <: Number
        println("\tsum")
        reset!(x)
        sum(x)
        reset!(x)
        @time sum(x)
    end
    println("\n")
end


# Performance tests
for A in (randn(N), 1:N, randstring(N))
    for T in (identity, StatefulIterator, StatefulIterators.StatefulIterator)
        perf(T(A), typeof(A))
    end
end


# Correctness tests
test_handler(r::Test.Success) = nothing
test_handler(r::Test.Failure) = println("Test failed: $(r.expr)")
test_handler(r::Test.Error)   = rethrow(r)

Test.with_handler(test_handler) do
    println("Correctness tests:")

    T = StatefulIterator

    s = T([1,2,3,4,5])
    @test collect(take(s, 3)) == [1,2,3]
    @test collect(take(s, 2)) == [4,5]

    @test collect(T([1,2,3,4,5])) == [1,2,3,4,5]

    r = 3:4:100
    s = T(r)
    @test collect(T(r)) == collect(r) == read(T(r), length(r)) == Int[read(s) for _ in 1:length(r)]

    @test read(T([0x1,0x2,0x3,0x4,0x5])) == 0x1
    @test read(T([0x1,0x2,0x3,0x4,0x5]), 2, 2) == [0x1 0x3; 0x2 0x4]
    
    @test read(T([0x1,0x2,0x3,0x4,0x5]), UInt16) == 0x0201
    @test read(T([0x1,0x2,0x3,0x4,0x5]), UInt16, 2) == [0x0201, 0x0403]
    @test read(T(UInt16[0x0201, 0x0403]), UInt8, 4) == [0x1,0x2,0x3,0x4]

    foo() = (for i in 1:4 produce(i); end)
    s = T(Task(foo))
    @test collect(T(Task(foo))) == collect(Task(foo)) == read(T(Task(foo)), 4) == [read(s) for _ in 1:4]

    str = randstring(100);
    s = T(str)
    @test collect(T(str)) == collect(str) == read(T(str), length(str)) == Char[read(s) for _ in 1:length(str)]
end
