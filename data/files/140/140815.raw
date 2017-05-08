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
function quadratic (f)
  f1 = derivative(f)
  c = f(0.0)
  b = f1(0.0)
  a = f(1.0) - b - c
  answer = (sign) -> (-b + sqrt(b^2 + sign*4a*c + 0im))/ 2a
  return answer(1) , answer(-1)
end
function derivative(f)
    return function(x)
        h = 0.00001
        f1 = f(x + h)
        f0 = f(x)
        return (f1 - f0) / h
    end
end
derivative((x) -> x^2 + 2x + 3)

