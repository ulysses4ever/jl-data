# Fabian R Lischka, 2015-04-09, Indonesia, Bali, Onion Collective
# http://cryptopals.com/sets/1/challenges/4/

# One of the 60-character strings in this file has been encrypted by single-character XOR.
# Find it.

# http://cryptopals.com/static/challenge-data/4.txt

using crypto101

fn = "4.txt"
sm = 100
bm = 9999 # remove later
ptbm = "" # remove later
ln = 1
for l in open(readlines,fn)
  ciphertext_b = hex2bytes(chomp(l))
  for b = 1:255
    plaintext_b = ciphertext_b $ b
    s = chi2score(plaintext_b)
    if s < sm
      println("line: $ln, b: $b, s = $s")
      bm = b
      ptbm = plaintext_b
      sm = s
    end
  end
  ln += 1
end
println("xor with $bm, score of $sm, plaintext:\n",ascii(ptbm))
# xor with 53, score of 1.4441432527780258, plaintext:
# Now that the party is jumping
