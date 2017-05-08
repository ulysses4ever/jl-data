include("../src/Rand.jl")
include("../src/Padding.jl")
include("../src/Iteration.jl")
include("../src/BlockCiphers.jl")
include("../src/CipherModes.jl")
include("testing.jl")

importall Padding
importall CipherModes
importall BlockCiphers

print("testing encryption modes with AES ")

plain = zeros(Uint8, 20)
key = AES(zeros(Uint8, int32(128/8)))

out = ecb_encrypt(Pkcs7, key, plain)
@assert_equal(32 + 0, length(out))
@assert_not_equal(plain, out)
@assert_equal(plain, ecb_decrypt(Pkcs7, key, out))

out = cbc_encrypt(Pkcs7, key, plain)
@assert_equal(32 + 16, length(out))
@assert_not_equal(plain, out)
@assert_equal(plain, cbc_decrypt(Pkcs7, key, out))

out = pcbc_encrypt(Pkcs7, key, plain)
@assert_equal(32 + 16, length(out))
@assert_not_equal(plain, out)
@assert_equal(plain, pcbc_decrypt(Pkcs7, key, out))

out = ctr_encrypt(key, 31337, plain)
@assert_equal(20, length(out)) # no padding :D
@assert_not_equal(plain, out)
@assert_equal(plain, ctr_decrypt(key, 31337, out))

out = cfb_encrypt(key, plain)
@assert_equal(20 + 16, length(out)) # no padding + iv though :D
@assert_equal(plain, cfb_decrypt(key, out))

out = ofb_encrypt(key, plain)
@assert_equal(20 + 16, length(out)) # no padding + iv though :D
@assert_equal(plain, ofb_decrypt(key, out))

println()