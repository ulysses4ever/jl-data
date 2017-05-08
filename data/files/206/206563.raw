module Rand

export cryptographic_rand

include("gen/libcrypto_common.jl")
include("gen/rand.h.jl")

cryptographic_rand(len :: Int) = cryptographic_rand(zeros(Uint8, len))
function cryptographic_rand(a :: Array{Uint8})
    RAND_bytes(a, length(a))
    a
end

end # module Rand