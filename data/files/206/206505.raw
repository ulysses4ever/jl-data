module CipherModes

import Base
importall BlockCiphers
importall Padding
importall Iteration

# --- ecb mode
# warning -- exposed for amusement purposes only, DO NOT USE
function ecb_encrypt!(padding, key, in :: Array{Uint8})
    for block = slicerator(in, block_size(key))
        encrypt!(key, block)
    end
    in
end
function ecb_encrypt(padding, key, in :: Array{Uint8})
    out = zeros(Uint8, padded_size(block_size(key), in))
    out[1:length(in)] = in
    pad!(padding, block_size(key), out, length(in))

    ecb_encrypt!(padding, key, out)
end

function ecb_decrypt!(padding, key, in :: Array{Uint8})
    for block = slicerator(in, block_size(key))
        decrypt!(key, block)
    end
    in
end
function ecb_decrypt(padding, key, in :: Array{Uint8})
    out = zeros(Uint8, padded_size(in, block_size(key)))
    out[1:length(in)] = in
    pad!(padding, out, length(in))
    ecb_decrypt!(padding, key, copy(in))
end


# --- cbc mode
function cbc_encrypt!(padding, key, data :: Array{Uint8})
    tmp = zeros(Uint8, block_size(key))
    previous = cryptographic_rand(block_size(key))
    for block = BlockIterator(in, block_size(key), padding)
        tmp[1:block_size(key)] = block
        block[1:block_size(key)] = encrypt!(key, block $ previous)
        previous = tmp
    end
    prepend!(in, iv)
end
cbc_encrypt(padding, key, data) = cbc_encrypt!(padding, key, copy(data))

function cbc_decrypt!(key, in :: Array{Uint8})
    iv = data[1:block_size(key)]
    for i=1:block_size(key)
        shift!(data)
    end

    previous = iv
    for block = BlockIterator(in, block_size(key), padding)
        decrypt!(key, block)
        block $= previous
        previous[1:block_size(key)] = block
    end
    in
end
cbc_decrypt(padding, key, data) = cbc_decrypt!(padding, key, copy(data))


# --- pcb mode
function pcbc_encrypt!(padding, key, data :: Array{Uint8})
    iv = cryptographic_rand(block_size(key))
    tmp = copy(iv)
    unencrypted = zeros(Uint8, block_size(key))

    for block = BlockIterator(in, block_size(key), padding)
        unencrypted[1:block_size(key)] = block
        block $= tmp
        encrypt!(key, block)
        tmp[1:block_size(key)] = unencrypted $ block
    end
    prepend!(in, iv)
end
pcbc_encrypt(padding, key, data) = pcbc_encrypt!(padding, key, copy(data))

function pcbc_decrypt!(key, in :: Array{Uint8})
    iv = data[1:block_size(key)]
    for i=1:block_size(key)
        shift!(data)
    end

    encrypted = zeros(Uint8, block_size(key))
    tmp = copy(iv)
    for block = BlockIterator(in, block_size(key), padding)
        encrypted[1:block_size(key)] = block
        decrypt!(key, block)

        block $= tmp

        tmp[1:block_size(key)] = block $ encrypted
    end
    in
end
pcbc_decrypt(padding, key, data) = pcbc_decrypt!(padding, key, copy(data))


# --- ctr mode
function ctr_encrypt!(key, nonce :: Uint64, data :: Array{Uint8})
    seed = zeros(Uint8, 16)
    seed[9:16] = [unit8(noonce << (offset * 8)) for offset=0:7]

    tmp = copy(seed)
    ctr = uint64(0)

    for block = BlockIterator(in, block_size(key), padding)
        tmp[1:16] = seed
        tmp[1:8] = [unit8(ctr << (offset * 8)) for offset=0:7]
        encrypt!(key, tmp)
        block $= tmp
    end
    in
end
ctr_encrypt(key, nonce :: Uint64, data :: Array{Uint8}) = ctr_encrypt!(key, nonce, copy(data))

ctr_decrypt!(key, nonce :: Uint64, data :: Array{Uint8}) = ctr_encrypt!(key, nonce, data)
ctr_decrypt(key, nonce :: Uint64, data :: Array{Uint8}) = ctr_encrypt(key, nonce, data)


# --- cfb mode
function cfb_encrypt!(padding, key, data :: Array{Uint8})
    iv = cryptographic_rand(block_size(key))
    tmp = copy(iv)

    for block = BlockIterator(in, block_size(key), padding)
        encrypt!(key, tmp)
        block $= tmp
        tmp[1:block_size(key)] = block
    end
    prepend!(in, iv)
end
cfb_encrypt(padding, key, data) = cfb_encrypt!(padding, key, copy(data))

function cfb_decrypt!(key, in :: Array{Uint8})
    iv = data[1:block_size(key)]
    for i=1:block_size(key)
        shift!(data)
    end

    previous = iv
    for block = BlockIterator(in, block_size(key), padding)
        decrypt!(key, previous)
        block $= previous
        previous[1:block_size(key)] = block
    end
    in
end
cfb_decrypt(padding, key, data) = cfb_decrypt!(padding, key, copy(data))


# --- ofb mode
function ofb_encrypt!(padding, key, data :: Array{Uint8})
    iv = cryptographic_rand(block_size(key))
    tmp = copy(iv)

    for block = BlockIterator(in, block_size(key), padding)
        encrypt!(key, tmp)
        block $= tmp
    end
    prepend!(in, iv)
end
ofb_encrypt(padding, key, data) = ofb_encrypt!(padding, key, copy(data))

function ofb_decrypt!(key, in :: Array{Uint8})
    previous = data[1:block_size(key)]
    for i=1:block_size(key)
        shift!(data)
    end

    for block = BlockIterator(in, block_size(key), padding)
        decrypt!(key, previous)
        block $= previous
    end
    in
end
ofb_decrypt(padding, key, data) = ofb_decrypt!(padding, key, copy(data))

export ecb_encrypt!, ecb_encrypt, ecb_decrypt!, ecb_decrypt

end # module CipherModes