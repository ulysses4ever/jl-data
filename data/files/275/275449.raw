# Fabian R Lischka, 2015-04-17, Indonesia, Bali, Nusa Lembongan, Bunga Bungalow
# http://cryptopals.com/sets/1/challenges/7
# finished own decryption: 2015-06-13, Philippines, Cebu, Bantayan, Santa Fe, Balikpayan Resto

# one way: put this on command line
# openssl aes-128-ecb -d -in "7.data" -K 59454c4c4f57205355424d4152494e45

using AES
using Crypto101

function getciphertext(fn)
    Array{UInt8}(base64decode(chomp(readall(fn))))
end

key = b"YELLOW SUBMARINE"

blockcipher = AES.AESBlock(key)
blockmode = AES.Blockmode_ECB()
padder = Crypto101.PadderPKCS7( AES.blocklength_bytes(blockcipher) )

c = AES.Cipher( blockcipher, blockmode, padder)

ciphertext = getciphertext("7.txt")

println("length: ", length(ciphertext))

plaintext = AES.decipher(c, ciphertext)

println(ascii(plaintext))
