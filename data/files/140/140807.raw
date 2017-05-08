# ========================================= #
# A Rapid Introduction to Molecular Biology
# ========================================= #
# Problem
# --------------
# A string is simply an ordered collection of symbols selected from some
# alphabet and formed into a word; the length of a string is the number of
# symbols that it contains.
#
# An example of a length 21 DNA string (whose alphabet contains the symbols
# 'A', 'C', 'G', and 'T') is "ATGCTTCAGAAAGGTCTTACG."
#
# Given: A DNA string s of length at most 1000 nt.
#
# Return: Four integers (separated by spaces) counting the respective number of
# times that the symbols 'A', 'C', 'G', and 'T' occur in s.
# ==============
#
# Sample Dataset:
# AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC
#
# Sample Output:
# 20 12 17 21
#
# ========================================= #

function is_prime(n::Int64)
if n <= 3
  return true
end

if n % 2 == 0
  return false
end

i = 3
while i <=sqrt(n)
  if n % i == 0
    return false
  end
  i += 2
end

return true
end

println(is_prime(1))
println(is_prime(2))
println(is_prime(3))
println(is_prime(4))
println(is_prime(5))
println(is_prime(6))
println(is_prime(7))
println(is_prime(8))
println(is_prime(9))
println(is_prime(10))
