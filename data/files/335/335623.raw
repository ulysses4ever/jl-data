# Fabian R Lischka, 2015-07-09, Moers
# http://cryptopals.com/sets/1/challenges/10/

# Implement CBC mode
# CBC mode is a block cipher mode that allows us to encrypt irregularly-sized messages,
# despite the fact that a block cipher natively only transforms individual blocks.
# In CBC mode, each ciphertext block is added to the next plaintext block before the next call to the cipher core.

# The first plaintext block, which has no associated previous ciphertext block,
# is added to a "fake 0th ciphertext block" called the initialization vector, or IV.

# Implement CBC mode by hand by taking the ECB function you wrote earlier, making it encrypt instead of decrypt
# (verify this by decrypting whatever you encrypt to test), and using your XOR function from the previous exercise to combine them.

# The file here is intelligible (somewhat) when CBC decrypted against "YELLOW SUBMARINE" with an IV of all ASCII 0 (\x00\x00\x00 &c)

using AES
using Crypto101

function getciphertext(fn)
    Array{UInt8}(base64decode(chomp(readall(fn))))
end

key = b"YELLOW SUBMARINE"
blockcipher = AES.AESBlock(key)
blockmode = AES.Blockmode_CBC(zeros(UInt8, 16)) # IV
padder = Crypto101.PadderPKCS7( AES.blocklength_bytes(blockcipher) )
c = AES.Cipher( blockcipher, blockmode, padder)

ciphertext = getciphertext("10.txt")

plaintext = decipher(c, ciphertext)

println(ascii(plaintext))
