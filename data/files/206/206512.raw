include("../src/Padding.jl")
include("../src/Iteration.jl")
include("../src/BlockCiphers.jl")
include("../src/CipherModes.jl")
include("testing.jl")

importall Padding
importall CipherModes
importall BlockCiphers

println("testing AES \n")

plain = zeros(Uint8, 10)
key = AES(zeros(Uint8, int32(128/8)))

out = ecb_encrypt(Pkcs7, key, plain)
println("encrypted: ", length(out), ", ")
show(out)
println()
@assert_equal(16, length(out))
