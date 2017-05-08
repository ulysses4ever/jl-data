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
encrypt!(key, data) = encrypt!(key, data, data)
encrypt(key, data) = encrypt!(key, data, zeros(Uint8, block_size(key)))

function decrypt!(key :: AES, data, out)
    AES_decrypt(data, out, key.de_key)
    out
end
decrypt!(key, data) = decrypt!(key, data, data)
decrypt(key, data) = decrypt!(key, data, zeros(Uint8, block_size(key)))


include("gen/des.h.jl")

immutable DES
    raw_key :: Array{Uint8}
    lib_key :: Array{Uint8}

    function DES(key :: Array{Uint8})
        bits = length(key) * 8
        @assert bits == 64 # but 8 of the bits are for parity

        lib_key = zeros(Uint8, 200)
        DES_set_key_unchecked(key, lib_key)

        new(key, lib_key)
    end
end

function generate_key(::Type{DES}, size)
    key = zeros(Uint8, 8)
    DES_random_key(key)
    DES(key)
end

block_size(k :: DES) = 8

function encrypt!(key :: DES, data, out)
    DES_ecb_encrypt(data, out, key.lib_key, 1)
    out
end

function decrypt!(key :: DES, data, out)
    DES_ecb_encrypt(data, out, key.lib_key, 0)
    out
end


immutable DES3
    k1 :: DES
    k2 :: DES
    k3 :: DES

    function DES3(key :: Array{Uint8})
        bits = length(key) * 8
        @assert bits == 64 * 3 # but 8 of the bits are for parity

        new(DES(key[1:8]), DES(key[9:16]), DES(key[17:24]))
    end
end

function generate_key(::Type{DES3}, size)
    final_key = zeros(Uint8, 24)

    key = zeros(Uint8, 8)
    DES_random_key(key)
    final_key[1:8] = key

    DES_random_key(key)
    final_key[9:16] = key

    DES_random_key(key)
    final_key[17:24] = key

    DES3(final_key)
end

block_size(k :: DES3) = 8

function encrypt!(key :: DES3, data, out)
    encrypt!(key.k1, data, out)
    encrypt!(key.k2, out, out)
    encrypt!(key.k3, out, out)
    out
end

function decrypt!(key :: DES3, data, out)
    decrypt!(key.k3, data, out)
    decrypt!(key.k2, out, out)
    decrypt!(key.k1, out, out)
    out
end

immutable DES3ede
    k1 :: DES
    k2 :: DES
    k3 :: DES

    function DES3ede(key :: Array{Uint8})
        bits = length(key) * 8
        @assert bits == 64 * 3 # but 8 of the bits are for parity

        new(DES(key[1:8]), DES(key[9:16]), DES(key[17:24]))
    end
end

function generate_key(::Type{DES3ede}, size)
    final_key = zeros(Uint8, 24)

    key = zeros(Uint8, 8)
    DES_random_key(key)
    final_key[1:8] = key

    DES_random_key(key)
    final_key[9:16] = key

    DES_random_key(key)
    final_key[17:24] = key

    DES3ede(final_key)
end

block_size(k :: DES3ede) = 8

function encrypt!(key :: DES3ede, data, out)
    encrypt!(key.k1, data, out)
    decrypt!(key.k2, out, out)
    encrypt!(key.k3, out, out)
    out
end

function decrypt!(key :: DES3ede, data, out)
    decrypt!(key.k3, data, out)
    encrypt!(key.k2, out, out)
    decrypt!(key.k1, out, out)
    out
end


export block_size, encrypt, encrypt!, decrypt, decrypt!,
    generate_key,
    AES, DES, DES3, DES3ede

end # module BlockCiphers