# Matasano Crypto Challenge. Solutions in Julia. Fabian R Lischka
# Set 2, http://cryptopals.com/sets/2/

using AES
using Crypto101
using Base.Collections, Base.Order



# Challenge 9
# http://cryptopals.com/sets/2/challenges/9/
# Fabian R Lischka, 2015-05-10, TG 921 (Airbus A380) FRA-BKK -CGK (Jakarta)

# Implement PKCS#7 padding
# A block cipher transforms a fixed-sized block (usually 8 or 16 bytes) of plaintext into ciphertext.
# But we almost never want to transform a single block; we encrypt irregularly-sized messages.

# One way we account for irregularly-sized messages is by padding, creating a plaintext that is an even
# multiple of the blocksize. The most popular padding scheme is called PKCS#7.

# So: pad any block to a specific block length, by appending the number of bytes of padding to the end of the block. For instance,
# "YELLOW SUBMARINE"
# ... padded to 20 bytes would be:
# "YELLOW SUBMARINE\x04\x04\x04\x04"

function m09()
    unpaddedText = b"YELLOW SUBMARINE"

    p20 = PadderPKCS7(20)
    println("Challenge 9:")

    println( pad(p20, unpaddedText) == b"YELLOW SUBMARINE\x04\x04\x04\x04")
    println( unpad(p20, pad(p20, unpaddedText)) == unpaddedText )
end


# Challenge 10
# http://cryptopals.com/sets/2/challenges/10/
# Fabian R Lischka, 2015-07-09, Moers

# Implement CBC mode
# CBC mode is a block cipher mode that allows us to encrypt irregularly-sized messages,
# despite the fact that a block cipher natively only transforms individual blocks.
# In CBC mode, each ciphertext block is added to the next plaintext block before the next call to the cipher core.

# The first plaintext block, which has no associated previous ciphertext block,
# is added to a "fake 0th ciphertext block" called the initialization vector, or IV.

# Implement CBC mode by hand by taking the ECB function you wrote earlier, making it encrypt instead of decrypt
# (verify this by decrypting whatever you encrypt to test), and using your XOR function from the previous exercise to combine them.

# The file here is intelligible (somewhat) when CBC decrypted against "YELLOW SUBMARINE" with an IV of all ASCII 0 (\x00\x00\x00 &c)


function getciphertext(fn)
    Array{UInt8}(base64decode(chomp(readall(fn))))
end

function m10()
    key = b"YELLOW SUBMARINE"
    blockcipher = AES.AESBlock(key)
    blockmode = AES.Blockmode_CBC(zeros(UInt8, 16)) # IV
    padder = Crypto101.PadderPKCS7( AES.blocklength_bytes(blockcipher) )
    c = AES.Cipher( blockcipher, blockmode, padder)

    ciphertext = getciphertext("10.txt")

    plaintext = decipher(c, ciphertext)
    println("Challenge 10:")
    println(ascii(plaintext))
end



# Challenge 11
# http://cryptopals.com/sets/2/challenges/11/
# Fabian R Lischka, 2015-08-06, Moers

# An ECB/CBC detection oracle
# Now that you have ECB and CBC working:
# Write a function to generate a random AES key; that's just 16 random bytes.
# Write a function that encrypts data under an unknown key --- that is, a function that generates a random key and encrypts under it.
# The function should look like:
# encryption_oracle(your-input)
# => [MEANINGLESS JIBBER JABBER]
# Under the hood, have the function append 5-10 bytes (count chosen randomly) before the plaintext and 5-10 bytes after the plaintext.
# Now, have the function choose to encrypt under ECB 1/2 the time, and under CBC the other half (just use random IVs each time for CBC).
# Use rand(2) to decide which to use.
# Detect the block cipher mode the function is using each time. You should end up with a piece of code that, pointed at a block box that might be encrypting ECB or CBC, tells you which one is happening.


# ENCRYPTION_ORACLE takes a plaintext, encrypts it with a random password, using either ECB or CBC.
# it also prepends 5 to 10 random bytes to the plaintext, and appends 5 to 10 random bytes to the plaintext.
function encryption_oracle(plaintext)
    keylength_bytes = 16
    extended_plaintext = vcat( randompass( 5 + mod(rand(Int),6)), plaintext, randompass( 5 + mod(rand(Int),6)) )
    key = randompass(keylength_bytes)
    blockcipher = AES.AESBlock(key)
    if rand() > 0.5
        blockmode = AES.Blockmode_ECB()
    else
        blockmode = AES.Blockmode_CBC(randompass(keylength_bytes)) # IV
    end
    padder = Crypto101.PadderPKCS7( AES.blocklength_bytes(blockcipher) )
    c = AES.Cipher( blockcipher, blockmode, padder)
    ciphertext = AES.encipher(c, extended_plaintext)
    (blockmode, ciphertext)
end


function guess_method()
    plaintext = zeros(UInt8, 200)
    blockmode, ciphertext = encryption_oracle(plaintext)
    cs = zeros(Int,13)
    for offset in 1:13
        cs[offset] = countsameblocks(ciphertext[offset:end])

    end
    c = sum(cs)
    print("c = $c, guess = ")
    if c > 0
        print("ECB")
    else
        print("CBC")
    end
    println(", truth =", blockmode)
end

function m11()
    println("Challenge 10:")

    for run = 1:50
        guess_method()
    end

end

# Challenge 12
# http://cryptopals.com/sets/1/challenges/12/
# Fabian R Lischka, 2015-08-06, Moers

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

const secret_plaintext_base64 = "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK"
const secret_plaintext = base64decode(secret_plaintext_base64)

# computes AES-128-ECB( plaintext || secret_plaintext, key)
function encryption_oracle_deterministic(plaintext, key)
    extended_plaintext = vcat( plaintext, secret_plaintext )
    blockcipher = AES.AESBlock(key)
    blockmode = AES.Blockmode_ECB()
    padder = Crypto101.PadderPKCS7( AES.blocklength_bytes(blockcipher) )
    c = AES.Cipher( blockcipher, blockmode, padder)
    ciphertext = AES.encipher(c, extended_plaintext)
    ciphertext
end

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

function m12()
    println("Challenge 12:")
    byte_at_a_time()
end

m09()
m10()
m11()
m12()