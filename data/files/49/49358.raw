module TestCountMin

using FactCheck
using CountMin

facts("getprimes") do
    a = getprimesabove(2, 1)
    @fact a --> [3,]
    @fact length(a) --> 1
    @fact all(map(isprime, a)) --> true

    a = getprimesabove(200, 2)
    @fact a --> [211, 223]
    @fact length(a) --> 2
    @fact all(map(isprime, a)) --> true

    b = getprimesbelow(10, 1)
    @fact b --> [7, ]
    @fact length(b) --> 1
    @fact all(map(isprime, b)) --> true

    b = getprimesbelow(200, 2)
    @fact b --> [199, 197]
    @fact length(b) --> 2
    @fact all(map(isprime, b)) --> true
end

facts("CountMinSketch empty constructor") do
    cms = CountMinSketch{UInt16}()
    @fact eltype(cms.sketch) --> UInt16
    @fact cms.sketch --> zeros(UInt16, 0, 0)
    @fact cms.moduli --> zeros(UInt64, 0)

    cms = CountMinSketch{UInt8}()
    @fact eltype(cms.sketch) --> UInt8
    @fact cms.sketch --> zeros(UInt8, 0, 0)
    @fact cms.moduli --> zeros(UInt64, 0)
end

facts("CountMinSketch normal constructor") do
    cms = CountMinSketch{UInt16}(4, 100)
    @fact eltype(cms.sketch) --> UInt16
    @fact size(cms.sketch) --> (4, 100)
    @fact cms.moduli --> UInt64[97, 89, 83, 79]

    # table too small
    @fact_throws CountMinSketch{UInt8}(4,0)
    # too few tables
    @fact_throws CountMinSketch{UInt8}(0,100)
end

facts("CountMinSketch properties") do
    cms = CountMinSketch{UInt16}(4, 100)
    @fact eltype(cms) --> UInt16
    @fact size(cms) --> (4, 100)
end

facts("CountMinSketch push/pop/add") do
    cms = CountMinSketch{UInt16}(4, 100)
    @fact cms[hash(1)] --> UInt16(0)
    push!(cms, hash(1))
    @fact cms[hash(1)] --> UInt16(1)
    push!(cms, hash(1))
    @fact cms[hash(1)] --> UInt16(2)
    pop!(cms, hash(1))
    @fact cms[hash(1)] --> UInt16(1)
    add!(cms, hash(1), 100)
    @fact cms[hash(1)] --> UInt16(101)
    add!(cms, hash(1), -10)
    @fact cms[hash(1)] --> UInt16(91)
end

facts("CountMinSketch getindex") do
    cms = CountMinSketch{UInt16}(4, 100)
    @fact cms[hash(1)] --> UInt16(0)
    push!(cms, hash(1))
    @fact cms[hash(1)] --> UInt16(1)
    push!(cms, hash(1))
    @fact cms[hash(1)] --> UInt16(2)
    pop!(cms, hash(1))
    @fact cms[hash(1)] --> UInt16(1)
    add!(cms, hash(1), 100)
    @fact cms[hash(1)] --> UInt16(101)
    add!(cms, hash(1), -10)
    @fact cms[hash(1)] --> UInt16(91)
end

end # module TestCountMinSketch
