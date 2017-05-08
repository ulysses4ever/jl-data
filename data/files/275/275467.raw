# Fabian R Lischka, 2015-05-10, TG 921 (Airbus A380) FRA-BKK -CGK (Jakarta)
# http://cryptopals.com/sets/1/challenges/9/

# Implement PKCS#7 padding
# A block cipher transforms a fixed-sized block (usually 8 or 16 bytes) of plaintext into ciphertext. But we almost never want to transform a single block; we encrypt irregularly-sized messages.

# One way we account for irregularly-sized messages is by padding, creating a plaintext that is an even multiple of the blocksize. The most popular padding scheme is called PKCS#7.

# So: pad any block to a specific block length, by appending the number of bytes of padding to the end of the block. For instance,
# "YELLOW SUBMARINE"
# ... padded to 20 bytes would be:
# "YELLOW SUBMARINE\x04\x04\x04\x04"

using Crypto101

unpaddedText = b"YELLOW SUBMARINE"

p20 = PadderPKCS7(20)

println( pad(p20, unpaddedText) == b"YELLOW SUBMARINE\x04\x04\x04\x04")
println( unpad(p20, pad(p20, unpaddedText)) == unpaddedText )

