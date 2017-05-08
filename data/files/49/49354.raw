module TestCountMin

using FactCheck
using CountMin

facts("getprimes") do
    a = getprimesabove(2, 1)
    @fact a => [3,]
    @fact length(a) => 1
    @fact all(map(isprime, a)) => true

    a = getprimesabove(200, 2)
    @fact a => [211, 223]
    @fact length(a) => 2
    @fact all(map(isprime, a)) => true

    b = getprimesbelow(10, 1)
    @fact b => [7, ]
    @fact length(b) => 1
    @fact all(map(isprime, b)) => true

    b = getprimesbelow(200, 2)
    @fact b => [199, 197]
    @fact length(b) => 2
    @fact all(map(isprime, b)) => true
end

facts("CountMinSketch empty constructor") do
    cms = CountMinSketch{Uint16}()
    @fact cms.tables => 0
    @fact cms.tablesize => 0
    @fact eltype(cms.sketch) => Uint16
    @fact cms.sketch => zeros(Uint16, 0, 0)
    @fact cms.moduli => zeros(Uint64, 0)

    cms = CountMinSketch{Uint8}()
    @fact cms.tables => 0
    @fact cms.tablesize => 0
    @fact eltype(cms.sketch) => Uint8
    @fact cms.sketch => zeros(Uint8, 0, 0)
    @fact cms.moduli => zeros(Uint64, 0)

end

end # module TestCountMinSketch
