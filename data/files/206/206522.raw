module BlockCiphers

include("Rand.jl")

import Base

include("gen/libcrypto_common.jl")
include("gen/aes.h.jl")

immutable AES
    raw_key :: Array{Uint8}
    enc_key :: Array{Uint8}
    de_key :: Array{Uint8}

    function AES(key :: Array{Uint8})
        bits = length(key) * 8
        @assert (bits == 128 || bits == 192 || bits == 256)

        enc_key = zeros(Uint8, 1000)
        AES_set_encrypt_key(key, length(key) * 8, enc_key)

        de_key = zeros(Uint8, 1000)
        AES_set_decrypt_key(key, length(key) * 8, de_key)

        new(key, enc_key, de_key)
    end
end

generate_key(::Type{AES}, size) = AES(Rand.create_block_cipher_key(uint64(size / 8)))

function block_size(k :: AES)
    16
end

function encrypt!(key :: AES, data, out)
    AES_encrypt(data, out, key.enc_key)
    out
end
encrypt!(key :: AES, data) = encrypt!(key, data, data)
encrypt(key :: AES, data) = encrypt!(key, data, zeros(Uint8, 16))

function decrypt!(key :: AES, data, out)
    AES_decrypt(data, out, key.de_key)
    out
end
decrypt!(key :: AES, data) = decrypt!(key, data, data)
decrypt(key :: AES, data) = decrypt!(key, data, zeros(Uint8, 16))

export block_size, encrypt, encrypt!, decrypt, decrypt!,
    generate_key,
    AES

end # module BlockCiphers