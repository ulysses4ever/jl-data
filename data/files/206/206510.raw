module CipherModes

import Base
importall BlockCiphers
importall Padding
importall Iteration
importall Rand

function make_output_array(padding, extra, key, in)
    out = zeros(Uint8, extra + padded_size(block_size(key), in))
    out[(1 + extra):(length(in) + extra)] = in
    pad!(padding, block_size(key), out, length(in) + extra)
    out
end

# --- ecb mode
# warning -- exposed for amusement purposes only, DO NOT USE
function ecb_encrypt!(padding, key, in :: Array{Uint8})
    for block = slicerator(in, block_size(key))
        encrypt!(key, block)
    end
    in
end
ecb_encrypt(padding, key, in :: Array{Uint8}) = ecb_encrypt!(padding, key, make_output_array(padding, 0, key, in))

function ecb_decrypt!(padding, key, in :: Array{Uint8})
    for block = slicerator(in, block_size(key))
        decrypt!(key, block)
    end
    unpad!(padding, in)
    in
end
ecb_decrypt(padding, key, in :: Array{Uint8}) = ecb_decrypt!(padding, key, copy(in))

function xor!(a, b)
    for i=1:length(a)
        a[i] $= b[i]
    end
    a
end

# --- cbc mode
function cbc_encrypt!(padding, key, in :: Array{Uint8})
    in[1:block_size(key)] = cryptographic_rand(block_size(key))

    previous = in[1:block_size(key)]
    for in_block = offset(1, slicerator(in, block_size(key)))
        xor!(in_block, previous)
        encrypt!(key, in_block)
        previous[1:block_size(key)] = in_block[1:block_size(key)]
    end
    in
end
cbc_encrypt(padding, key, in) = cbc_encrypt!(padding, key, make_output_array(padding, block_size(key), key, in))

function cbc_decrypt!(padding, key, in :: Array{Uint8})
    iv = in[1:block_size(key)]
    for i=1:block_size(key)
        shift!(in)
    end

    tmp = zeros(Uint8, block_size(key))
    previous = iv
    for block = slicerator(in, block_size(key))
        tmp[1:block_size(key)] = block
        decrypt!(key, block, block)
        xor!(block, previous)
        previous[1:block_size(key)] = tmp
    end
    unpad!(padding, in)
    in
end
cbc_decrypt(padding, key, in) = cbc_decrypt!(padding, key, copy(in))


# --- pcb mode
function pcbc_encrypt!(padding, key, in :: Array{Uint8})
    in[1:block_size(key)] = cryptographic_rand(block_size(key))

    unencrypted = zeros(Uint8, block_size(key))
    tmp = in[1:block_size(key)]
    for block = offset(1, slicerator(in, block_size(key)))
        unencrypted[1:block_size(key)] = block
        xor!(block, tmp)
        encrypt!(key, block)
        tmp[1:block_size(key)] = unencrypted $ block
    end
    in
end
pcbc_encrypt(padding, key, in) = pcbc_encrypt!(padding, key, make_output_array(padding, block_size(key), key, in))

function pcbc_decrypt!(padding, key, in :: Array{Uint8})
    iv = in[1:block_size(key)]
    for i=1:block_size(key)
        shift!(in)
    end

    encrypted = zeros(Uint8, block_size(key))
    tmp = copy(iv)
    for block = slicerator(in, block_size(key))
        encrypted[1:block_size(key)] = block
        decrypt!(key, block)
        xor!(block, tmp)
        tmp[1:block_size(key)] = block $ encrypted
    end
    unpad!(padding, in)
    in
end
pcbc_decrypt(padding, key, in) = pcbc_decrypt!(padding, key, copy(in))


# --- ctr mode
function ctr_encrypt64!(key, nonce :: Int64, in :: Array{Uint8})
    seed = zeros(Uint8, block_size(key))
    seed[5:8] = [uint8(nonce << (offset * 8)) for offset=0:3]

    tmp = zeros(Uint8, block_size(key))
    for ctr = 0:int32(ceil(length(in) / block_size(key)))
        tmp[1:8] = seed
        tmp[1:4] = [uint8(ctr << (offset * 8)) for offset=0:3]

        encrypt!(key, tmp)
        xor!(slice(in, ((ctr * block_size(key)) + 1) : min(length(in), ((ctr + 1) * block_size(key)))), tmp)
    end
    in
end

function ctr_encrypt128!(key, nonce :: Int64, in :: Array{Uint8})
    seed = zeros(Uint8, block_size(key))
    seed[9:16] = [uint8(nonce << (offset * 8)) for offset=0:7]

    tmp = zeros(Uint8, block_size(key))
    for ctr = 0:int64(ceil(length(in) / block_size(key)))
        tmp[1:16] = seed
        tmp[1:8] = [uint8(ctr << (offset * 8)) for offset=0:7]

        encrypt!(key, tmp)
        xor!(slice(in, ((ctr * block_size(key)) + 1) : min(length(in), ((ctr + 1) * block_size(key)))), tmp)
    end
    in
end
ctr_encrypt!(key :: DES, nonce :: Int64, in :: Array{Uint8}) = ctr_encrypt64!(key, nonce, copy(in))
ctr_encrypt!(key, nonce :: Int64, in :: Array{Uint8}) = ctr_encrypt128!(key, nonce, copy(in))
ctr_encrypt(key, nonce :: Int64, in :: Array{Uint8}) = ctr_encrypt!(key, nonce, copy(in))

ctr_decrypt!(key, nonce :: Int64, in :: Array{Uint8}) = ctr_encrypt!(key, nonce, in)
ctr_decrypt(key, nonce :: Int64, in :: Array{Uint8}) = ctr_encrypt(key, nonce, in)


# --- cfb mode
function cfb_encrypt!(key, in :: Array{Uint8})
    in[1:block_size(key)] = cryptographic_rand(block_size(key))

    tmp = in[1:block_size(key)]
    for idx = 1:int64(floor(length(in) / block_size(key)))
        encrypt!(key, tmp)
        xor!(slice(in, ((idx * block_size(key)) + 1) : min(length(in), ((idx + 1) * block_size(key)))), tmp)
        tmp = slice(in, ((idx * block_size(key)) + 1) : min(length(in), ((idx + 1) * block_size(key))))
    end
    in
end
function cfb_encrypt(key, in)
    out = zeros(Uint8, length(in) + block_size(key))
    cfb_encrypt!(key, out)
end

function cfb_decrypt!(key, in :: Array{Uint8})
    iv = in[1:block_size(key)]
    for i=1:block_size(key)
        shift!(in)
    end

    tmp = iv
    for idx = 0:int64(floor(length(in) / block_size(key)))
        encrypt!(key, tmp)
        tmp = copy(slice(in, ((idx * block_size(key)) + 1) : min(length(in), ((idx + 1) * block_size(key)))))
        xor!(slice(in, ((idx * block_size(key)) + 1) : min(length(in), ((idx + 1) * block_size(key)))), tmp)
    end
    in
end
cfb_decrypt(key, in) = cfb_decrypt!(key, copy(in))


# --- ofb mode
function ofb_encrypt!(key, in :: Array{Uint8})
    in[1:block_size(key)] = cryptographic_rand(block_size(key))

    tmp = in[1:block_size(key)]
    for idx = 1:int64(floor(length(in) / block_size(key)))
        encrypt!(key, tmp)
        xor!(slice(in, ((idx * block_size(key)) + 1) : min(length(in), ((idx + 1) * block_size(key)))), tmp)
    end
    in
end
function ofb_encrypt(key, in)
    out = zeros(Uint8, length(in) + block_size(key))
    ofb_encrypt!(key, out)
end

function ofb_decrypt!(key, in :: Array{Uint8})
    iv = in[1:block_size(key)]
    for i=1:block_size(key)
        shift!(in)
    end

    tmp = iv
    for idx = 0:int64(floor(length(in) / block_size(key)))
        encrypt!(key, tmp)
        xor!(slice(in, ((idx * block_size(key)) + 1) : min(length(in), ((idx + 1) * block_size(key)))), tmp)
    end
    in
end
ofb_decrypt(key, in) = ofb_decrypt!(key, copy(in))


export ecb_encrypt!, ecb_encrypt, ecb_decrypt!, ecb_decrypt,
       cbc_encrypt, cbc_decrypt,
       pcbc_encrypt, pcbc_decrypt,
       ctr_encrypt, ctr_decrypt,
       cfb_encrypt, cfb_decrypt,
       ofb_encrypt, ofb_decrypt

end # module CipherModes