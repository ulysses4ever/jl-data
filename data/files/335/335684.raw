# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective
# http://cryptopals.com/sets/1/challenges/1/

# 1. Convert hex to base64 and back.
# The string:
#  49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
# should produce:
#  SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t


h = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
b_ref = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
b = base64encode(hex2bytes(h))
println(b == b_ref)

