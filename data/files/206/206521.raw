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
        enc_key = zeros(Uint8, 1000)
        AES_set_encrypt_key(key, length(key) * 8, enc_key)

        de_key = zeros(Uint8, 1000)
        AES_set_decrypt_key(key, length(key) * 8, de_key)

        new(key, enc_key, de_key)
    end
end

generate_key(::Type{AES}, size) = AES(Rand.create_block_cipher_key(uint64(size / 8)))

block_size(k :: AES) = 16

function encrypt!(key :: AES, data :: Array{Uint8}, out :: Array{Uint8})
    AES_encrypt(data, out, key.enc_key)
    out
end
encrypt(key :: AES, data :: Array{Uint8}) = encrypt!(key, data, zeros(Uint8, 16))

function decrypt!(key :: AES, data :: Array{Uint8}, out :: Array{Uint8})
    AES_decrypt(data, out, key.de_key)
    out
end
decrypt(key :: AES, data :: Array{Uint8}) = decrypt!(key, data, zeros(Uint8, 16))

export block_size, encrypt, encrypt!, decrypt, decrypt!,
    generate_key,
    AES

end # module BlockCiphers