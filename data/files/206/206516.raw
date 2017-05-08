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

for plain = {zeros(Uint8, 20), zeros(Uint8, 0), zeros(Uint8, 1)}
    key = AES(zeros(Uint8, int32(128/8)))

    base_len = length(plain)
    padded_len = block_size(key) * int64(ceil(length(plain) / block_size(key)))
    if(length(plain) % block_size(key) == 0)
        padded_len += block_size(key)
    end
    iv_len = block_size(key)

    out = ecb_encrypt(Pkcs7, key, plain)
    @assert_equal(padded_len + 0, length(out))
    @assert_not_equal(plain, out)
    @assert_equal(plain, ecb_decrypt(Pkcs7, key, out))

    out = cbc_encrypt(Pkcs7, key, plain)
    @assert_equal(padded_len + iv_len, length(out))
    @assert_not_equal(plain, out)
    @assert_equal(plain, cbc_decrypt(Pkcs7, key, out))

    out = pcbc_encrypt(Pkcs7, key, plain)
    @assert_equal(padded_len + iv_len, length(out))
    @assert_not_equal(plain, out)
    @assert_equal(plain, pcbc_decrypt(Pkcs7, key, out))

    out = ctr_encrypt(key, 31337, plain)
    @assert_equal(base_len, length(out)) # no padding :D
    if(length(plain) != 0)
        @assert_not_equal(plain, out)
    end
    @assert_equal(plain, ctr_decrypt(key, 31337, out))

    out = cfb_encrypt(key, plain)
    @assert_equal(base_len + iv_len, length(out)) # no padding + iv though :D
    @assert_not_equal(plain, out)
    @assert_equal(plain, cfb_decrypt(key, out))

    out = ofb_encrypt(key, plain)
    @assert_equal(base_len + iv_len, length(out)) # no padding + iv though :D
    @assert_not_equal(plain, out)
    @assert_equal(plain, ofb_decrypt(key, out))
end

println()