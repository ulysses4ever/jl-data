# Fabian R Lischka, 2015-05-17, Indonesia, Bali, Ubud, OnionCo
# http://cryptopals.com/sets/1/challenges/8

# In this file are a bunch of hex-encoded ciphertexts.
# One of them has been encrypted with ECB.
# Detect it.
# Remember that the problem with ECB is that it is stateless and deterministic;
# the same 16 byte plaintext block will always produce the same 16 byte ciphertext.

fn = "8.txt"

function countsameblocks(ct_b, block_size = 16) # n^2 algo
    c = 0
    r = 2
    while r*block_size <= length(ct_b)
        l = 1
        while l < r
            if ct_b[((r-1)*block_size+1):(r*block_size)] == ct_b[((l-1)*block_size+1):(l*block_size)]
                c += 1
            end
            l += 1
        end
        r += 1
    end
    c
end

for ln in open(readlines,fn)
    ct_b = hex2bytes(chomp(ln))
    c = countsameblocks(ct_b)
    if c > 0
        println(ln)
        println(ct_b)
    end
end


