# Fabian R Lischka, 2015-08-06, Moers
# http://cryptopals.com/sets/1/challenges/11/

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

using AES
using Crypto101

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

for run = 1:50
    guess_method()
end
