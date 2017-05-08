require("../src/openssl_common.jl")
require("../src/rand.h.jl")

d = zeros(Uint8, 100)

if 1 != RAND_bytes(d, 100)
    println("ERROR")
else
    println("PASS")
end
