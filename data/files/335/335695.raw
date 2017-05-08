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

function collectNBestXor{T<:Unsigned}(cleartext_bytes::Array{T}, N = 1)
  candidate_heap = fill((Inf,zero(T),""), N)
  for b::T = 1:255
    plaintext_bytes = ctb $ b
    s   = chi2score(pts)
    heapreplace!(candidate_heap, (s,b,plaintext_bytes))
  end
  candidate_heap
end

println("xor with $bm, score of $sm, plaintext:\n",)


