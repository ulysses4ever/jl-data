include("../src/Rand.jl")
include("testing.jl")

print("checking rand interface ")

bytes = Rand.cryptographic_rand(10)
@assert_equal(10, length(bytes))

c = copy(bytes)
@assert_equal(bytes, c)
Rand.cryptographic_rand(c)
@assert_not_equal(bytes, c)
println()