# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective
# http://cryptopals.com/sets/1/challenges/3/

# Single-byte XOR cipher
# The hex encoded string:
# 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
# ... has been XOR'd against a single character. Find the key, decrypt the message.
# You can do this by hand. But don't: write code to do it for you.
# How? Devise some method for "scoring" a piece of English plaintext. Character frequency is a good metric. Evaluate each output and choose the one with the best score.
# ETAOIN SHRDLU

using crypto101

cthex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
ctb = hex2bytes(cthex)

s,b,pt = collectNBestXor(ctb)[1]

println("xor with $b (\"$(Char(b))\"), score of $(-s), plaintext:\n",ascii(pt))
# xor with 88 ("X"), score of 1.2357727124823528, plaintext:
# Cooking MC's like a pound of bacon


