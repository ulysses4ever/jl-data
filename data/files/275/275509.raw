# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective
# http://cryptopals.com/sets/1/challenges/4/

# One of the 60-character strings in this file has been encrypted by single-character XOR.
# Find it.

# http://cryptopals.com/static/challenge-data/4.txt

using Crypto101
using Base.Collections, Base.Order

fn = "4.txt"

ln = 1
candidate_heap = fill((Inf,zero(UInt8),UInt8[],ln), 1)
for l in open(readlines,fn)
    ciphertext_b = hex2bytes(chomp(l))
    s,b,pt = collectNBestXor(ciphertext_b)[1]
    heappushpop!(candidate_heap,(s,b,pt,ln), Reverse)
    ln += 1
end

sm,bm,ptbm,ln = heappeek(candidate_heap)
println("Line $ln, xor with $bm (\"$(Char(bm))\"), score of $sm, plaintext:\n",ascii(ptbm))
# Line 171, xor with 53 ("5"), score of -1.4441432527780258, plaintext:
# Now that the party is jumping
