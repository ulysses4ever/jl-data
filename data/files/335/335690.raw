# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective
# http://cryptopals.com/sets/1/challenges/2/
# 2. Fixed XOR
# Write a function that takes two equal-length buffers and produces
# their XOR sum.
# The string:
# 1c0111001f010100061a024b53535009181c
# ... after hex decoding, when xor'd against:
# 686974207468652062756c6c277320657965
# ... should produce:
# 746865206b696420646f6e277420706c6179

s1 = "1c0111001f010100061a024b53535009181c"
s2 = "686974207468652062756c6c277320657965"
s_ref = "746865206b696420646f6e277420706c6179"
b1 = hex2bytes(s1)
b2 = hex2bytes(s2)
br = b1 $ b2
s = bytes2hex(br)

println(s == s_ref)
