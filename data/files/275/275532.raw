# Fabian R Lischka, 2015-04-10, Indonesia, Bali, Onion Collective
# http://cryptopals.com/sets/1/challenges/6/

# Here's a text. It's been base64'd after being encrypted with repeating-key XOR.
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

using Crypto101

function getciphertext()
    fn = "6.txt"
    base64decode(readall(fn))
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

ct_b = str2bytes(getciphertext())
dist, keysize, z = guesskeysize(ct_b,20,40)[1]
println("Trying keysize $keysize with average bit distance of $dist and z-score of $z...")
# slice
key = guessslices(ct_b, keysize)
println("Guessed key: $(ascii(key))")
println("Message:")
println(ascii(encryptxor(ct_b,key)))
