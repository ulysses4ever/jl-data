# Fabian R Lischka, 2015-08-06, Moers
# http://cryptopals.com/sets/1/challenges/12/

# Byte-at-a-time ECB decryption (Simple)
# Copy your oracle function to a new function that encrypts buffers under ECB mode using a consistent but unknown key
# (for instance, assign a single random key, once, to a global variable).

# Now take that same function and have it append to the plaintext, BEFORE ENCRYPTING, the following string:
# ...
# Base64 decode the string before appending it. Do not base64 decode the string by hand; make your code do it. The point is that you don't know its contents.

# What you have now is a function that produces:

# AES-128-ECB(your-string || unknown-string, random-key)
# It turns out: you can decrypt "unknown-string" with repeated calls to the oracle function!

# Here's roughly how:

# Feed identical bytes of your-string to the function 1 at a time --- start with 1 byte ("A"), then "AA", then "AAA" and so on. Discover the block size of the cipher. You know it, but do this step anyway.
# Detect that the function is using ECB. You already know, but do this step anyways.
# Knowing the block size, craft an input block that is exactly 1 byte short (for instance, if the block size is 8 bytes, make "AAAAAAA"). Think about what the oracle function is going to put in that last byte position.
# Make a dictionary of every possible last byte by feeding different strings to the oracle; for instance, "AAAAAAAA", "AAAAAAAB", "AAAAAAAC", remembering the first block of each invocation.
# Match the output of the one-byte-short input to one of the entries in your dictionary. You've now discovered the first byte of unknown-string.
# Repeat for the next byte.

# my notes: if you have a black box that encrypts something secret using ECB,
# but you can insert an arbitrary plaintext before the secret (repeatedly with the same key)
# then you can easily deduce the secret (from the ciphertext)


using AES
using Crypto101

# computes AES-128-ECB( plaintext || secret_plaintext, key),
function encryption_oracle_deterministic(plaintext, key)
    extended_plaintext = vcat( plaintext, secret_plaintext )
    blockcipher = AES.AESBlock(key)
    blockmode = AES.Blockmode_ECB()
    padder = Crypto101.PadderPKCS7( AES.blocklength_bytes(blockcipher) )
    c = AES.Cipher( blockcipher, blockmode, padder)
    ciphertext = AES.encipher(c, extended_plaintext)
    ciphertext
end

secret_plaintext_base64 = "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK"
secret_plaintext = base64decode(secret_plaintext_base64)

# GUESS_BLOCKLENGTH guesses the blocklength of an oracle that encrypts a plaintext,
# by incrementing the plaintext length and observing the jump in the size of the ciphertext
# It returns the guessed block length, and the length of the plaintext one has to provide
# to see the first jump in ciphertext length
function guess_blocklength( oracle )
    b_max = 600
    plaintext = zeros(UInt8,b_max)
    base_length = length(oracle(plaintext[1:1]))
    for i = 2:b_max
        l = length(oracle(plaintext[1:i]))
        if l > base_length
            return (l - base_length, i)
        end
    end
    error("couldn't guess blocklength of oracle")
end

function guess_mode(oracle)
    plaintext = zeros(UInt8, 200)
    ciphertext = oracle(plaintext)
    cs = zeros(Int,13)
    for offset in 1:13
        cs[offset] = countsameblocks(ciphertext[offset:end])

    end
    c = sum(cs)
    println("Guessing block mode, number of identical blocks = $c")
    if c > 0
        return("ECB")
    else
        return("CBC")
    end
end

function byte_at_a_time()
    key = randompass(16)
    oracle = pt -> encryption_oracle_deterministic(pt, key)
    blocklength, plaintext_to_jump = guess_blocklength( oracle )
    blockmode_string = guess_mode( oracle )
    println("blocklength: $blocklength, mode: $blockmode_string")

    lo, hi = 0x01, 0xFF
    known = zeros(UInt8, 0)
    border = 0
    maxlen = length( oracle( zeros(UInt8,0) ) )
    while length(known) < maxlen
        filler = zeros(UInt8, blocklength)

        while length(filler) > 0
            pop!(filler)
            target = oracle(filler)[(border+1):(border+blocklength)]
#              println("pt :   ", filler, " target: ", target)
            guessed_char = 0x3f # '?'
            template = vcat(filler, known, [0x00])
            for i::UInt8 in Crypto101.charsbyfrequency # 0x00:0xFF in optimized order
                template[end] = i
                res = oracle(template)[(border+1):(border+blocklength)]
#                  println("guess: ", template, "   res : ", res)
                if res == target
                    guessed_char = i
                    break
                end
            end
            push!(known, guessed_char)
            print(ascii([guessed_char]))
        end

        border += blocklength
    end
end
