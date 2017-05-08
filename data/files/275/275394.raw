# Matasano Crypto Challenge. Solutions in Julia. Fabian R Lischka
# Set 1, http://cryptopals.com/sets/1/

using AES
using Crypto101
using Base.Collections, Base.Order


# 1. Convert hex to base64 and back.
# The string:
#  49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
# should produce:
#  SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective

function m01()
    h = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    b_ref = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
    b = base64encode(hex2bytes(h))
    println("Challenge 1:")
    println(b == b_ref)
end

# 2. Fixed XOR
# Write a function that takes two equal-length buffers and produces
# their XOR sum.
# The string:
# 1c0111001f010100061a024b53535009181c
# ... after hex decoding, when xor'd against:
# 686974207468652062756c6c277320657965
# ... should produce:
# 746865206b696420646f6e277420706c6179

# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective

function m02()
    s1 = "1c0111001f010100061a024b53535009181c"
    s2 = "686974207468652062756c6c277320657965"
    s_ref = "746865206b696420646f6e277420706c6179"
    b1 = hex2bytes(s1)
    b2 = hex2bytes(s2)
    br = b1 $ b2
    s = bytes2hex(br)
    println("Challenge 2:")
    println(s == s_ref)
end


# 3. Single-byte XOR cipher
# The hex encoded string:
# 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
# ... has been XOR'd against a single character. Find the key, decrypt the message.
# You can do this by hand. But don't: write code to do it for you.
# How? Devise some method for "scoring" a piece of English plaintext. Character frequency is a good metric. Evaluate each output and choose the one with the best score.
# ETAOIN SHRDLU

# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective

function m03()
    cthex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
    ctb = hex2bytes(cthex)

    s,b,pt = collectNBestXor(ctb)[1]
    println("Challenge 3:")
    println("xor with $b (\"$(Char(b))\"), score of $s, plaintext:\n",ascii(pt))
    # xor with 88 ("X"), score of 1.2357727124823528, plaintext:
    # Cooking MC's like a pound of bacon
end



# 4. One of the 60-character strings in this file has been encrypted by single-character XOR.
# Find it.

# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective

function m04()
    fn = "4.txt"

    ln = 1
    candidate_heap = fill((Inf,zero(UInt8),UInt8[],ln), 1)
    for l in open(readlines,fn)
        ciphertext_b = hex2bytes(chomp(l))
        s,b,pt = collectNBestXor(ciphertext_b)[1]
        heappushpop!(candidate_heap,(s,b,pt,ln), Reverse)
        ln += 1
    end

    sm,bm,ptbm,ln = heappeek(candidate_heap)
    println("Challenge 4:")
    println("Line $ln, xor with $bm (\"$(Char(bm))\"), score of $sm, plaintext:\n",ascii(ptbm))
    # Line 171, xor with 53 ("5"), score of -1.4441432527780258, plaintext:
    # Now that the party is jumping
end



# 5. Implement repeating-key XOR
# Here is the opening stanza of an important work of the English language:
# Burning 'em, if you ain't quick and nimble
# I go crazy when I hear a cymbal
# Encrypt it, under the key "ICE", using repeating-key XOR.

# In repeating-key XOR, you'll sequentially apply each byte of the key; the first byte of plaintext will be XOR'd against I, the next C, the next E, then I again for the 4th byte, and so on.

# It should come out to:
# 0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272
# a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
# Encrypt a bunch of stuff using your repeating-key XOR function. Encrypt your mail. Encrypt your password file. Your .sig file.
# Get a feel for it. I promise, we aren't wasting your time with this.

# Fabian R Lischka, 2015-04-10, Indonesia, Bali, Onion Collective

# note: b"hello" creates an array of bytes (UInt8), UTF-8 encoded (thus coinciding with ASCII on lower 127)

function m05()
    key_b = b"ICE"
    pt_b = b"Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
    ct_hex_ref = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"

    ct_hex = bytes2hex(encryptxor(pt_b, key_b))
    println("Challenge 5:")
    println(ct_hex == ct_hex_ref)
end


# 6. Here's a text. It's been base64'd after being encrypted with repeating-key XOR.
# Decrypt it.
# Here's how:
# Let KEYSIZE be the guessed length of the key; try values from 2 to (say) 40.
# Write a function to compute the edit distance/Hamming distance between two strings. The Hamming distance is just the number of differing bits. The distance between:
# this is a test
# and
# wokka wokka!!!
# is 37. Make sure your code agrees before you proceed.
# For each KEYSIZE, take the first KEYSIZE worth of bytes, and the second KEYSIZE worth of bytes, and find the edit distance between them. Normalize this result by dividing by KEYSIZE.
# The KEYSIZE with the smallest normalized edit distance is probably the key. You could proceed perhaps with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE blocks instead of 2 and average the distances.
# Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
# Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
# Solve each block as if it was single-character XOR. You already have code to do this.
# For each block, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte for that block. Put them together and you have the key.

# Fabian R Lischka, 2015-04-17, Indonesia, Bali, Lembongan, Bunga Bungalow

function getciphertext(fn)
    Array{UInt8}(base64decode(chomp(readall(fn))))
end

function guesskeysize(ct_b, numBlocks = 2, maxkeysize = 40)
    # dist_keysize_heap = fill((Inf, 0), collectBestN) # Inf is the worst distance
    distances = zeros(maxkeysize-1)
    for keysize = 2:maxkeysize
        d = 0.0
        for k = 1:keysize
            db = 0.0
            for n = 1:(numBlocks-1)
                for j = 0:(n-1)
                    db += hammingdistance(ct_b[k+n*keysize], ct_b[k+j*keysize])
                end
            end
            db /= numBlocks*(numBlocks-1)/2
            d += db
        end
        d /= keysize
        # we heapify reverse, to keep the worst (largest) distance in front to toss it out
        #         heappushpop!(dist_keysize_heap, (d, keysize), Reverse)
        distances[keysize-1] = d
    end
    # heapify!(dist_keysize_heap) # now we heapify forward, so that we can pop from best to worst
    m, s = mean(distances), std(distances)
    return sort!([(d,i+1,(m-d)/s) for (i,d) in enumerate(distances)])
end

function guessslices{T<:Unsigned}(ct_b::Array{T,1}, keysize)
    b = Array(T,keysize)
    for k = 1:keysize
        ct_tranchek = ct_b[k:keysize:end]
        _,b[k],_ = collectNBestXor(ct_tranchek)[1]
    end
    b
end

function m06()
    ct_b = getciphertext("6.txt")
    dist, keysize, z = guesskeysize(ct_b,20,40)[1]
    println("Trying keysize $keysize with average bit distance of $dist and z-score of $z...")
    # slice
    key = guessslices(ct_b, keysize)
    println("Challenge 6:")

    println("Guessed key: $(ascii(key))")
    println("Message:")
    println(ascii(encryptxor(ct_b,key)))
end


# 7. The Base64-encoded content in this file has been encrypted via AES-128 in ECB mode under the key
# "YELLOW SUBMARINE".
# (case-sensitive, without the quotes; exactly 16 characters; I like "YELLOW SUBMARINE" because it's exactly 16 bytes long, and now you do too).
# Decrypt it. You know the key, after all.
# Easiest way: use OpenSSL::Cipher and give it AES-128-ECB as the cipher.

# Fabian R Lischka, 2015-04-17, Indonesia, Bali, Nusa Lembongan, Bunga Bungalow
# finished own decryption: 2015-06-13, Philippines, Cebu, Bantayan, Santa Fe, Balikpayan Resto

# one way: put this on command line
# openssl aes-128-ecb -d -in "7.data" -K 59454c4c4f57205355424d4152494e45

function m07()
    key = b"YELLOW SUBMARINE"

    blockcipher = AES.AESBlock(key)
    blockmode = AES.Blockmode_ECB()
    padder = Crypto101.PadderPKCS7( AES.blocklength_bytes(blockcipher) )

    c = AES.Cipher( blockcipher, blockmode, padder)

    ciphertext = getciphertext("7.txt")
    plaintext = AES.decipher(c, ciphertext)
    println("Challenge 7:")

    println("length: ", length(ciphertext))
    println(ascii(plaintext))
end


# 8. In this file are a bunch of hex-encoded ciphertexts.
# One of them has been encrypted with ECB.
# Detect it.
# Remember that the problem with ECB is that it is stateless and deterministic;
# the same 16 byte plaintext block will always produce the same 16 byte ciphertext.

# Fabian R Lischka, 2015-05-17, Indonesia, Bali, Ubud, OnionCo

function m08()
    fn = "8.txt"
    println("Challenge 8:")

    for ln in open(readlines,fn)
        ct_b = hex2bytes(chomp(ln))
        c = countsameblocks(ct_b)
        if c > 0
            println(ln)
            println(ct_b)
        end
    end
end

m01()
m02()
m03()
m04()
m05()
m06()
m07()
m08()