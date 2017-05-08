# Fabian R Lischka, 2015-05-17, Indonesia, Bali, Ubud, OnionCo
# http://cryptopals.com/sets/1/challenges/8

# In this file are a bunch of hex-encoded ciphertexts.
# One of them has been encrypted with ECB.
# Detect it.
# Remember that the problem with ECB is that it is stateless and deterministic;
# the same 16 byte plaintext block will always produce the same 16 byte ciphertext.

using Crypto101

fn = "8.txt"

for ln in open(readlines,fn)
    ct_b = hex2bytes(chomp(ln))
    c = countsameblocks(ct_b)
    if c > 0
        println(ln)
        println(ct_b)
    end
end


