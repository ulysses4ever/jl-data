module Rand

export cryptographic_rand, create_block_cipher_key

include("gen/libcrypto_common.jl")
include("gen/rand.h.jl")

cryptographic_rand(len) = cryptographic_rand(zeros(Uint8, len))
function cryptographic_rand(a :: Array{Uint8})
    RAND_bytes(a, length(a))
    a
end

create_block_cipher_key(size) = cryptographic_rand(size)

end # module Rand