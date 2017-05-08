# Fabian R Lischka, 2015-04-10, Indonesia, Bali, Onion Collective
# http://cryptopals.com/sets/1/challenges/5/

# Implement repeating-key XOR
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


# note: b"hello" creates an array of bytes (UInt8), UTF-8 encoded (thus coinciding with ASCII on lower 127)

using Crypto101

key_b = b"ICE"
pt_b = b"Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
ct_hex_ref = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"

ct_hex = bytes2hex(encryptxor(pt_b, key_b))

println(ct_hex == ct_hex_ref)

