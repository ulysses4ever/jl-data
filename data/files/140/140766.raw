# ============================================ #
# The Secondary and Tertiary Structures of DNA
# ============================================ #
# Problem
# --------------
# In DNA strings, symbols 'A' and 'T' are complements of each other,
# as are 'C' and 'G'.
#
# The reverse complement of a DNA string s is the string sc formed
# by reversing the symbols of s, then taking the complement of each
# symbol (e.g., the reverse complement of "GTCA" is "TGAC").
#
# Given: A DNA string s of length at most 1000 bp.
#
# Return: The reverse complement sc of s.
# ==============
#
# Sample Dataset
# AAAACCCGGT
#
# Sample Output
# ACCGGGTTTT
# ============================================ #


function DNA_reverse_compliment(f::IOStream)
  compliment = (Char=>Char)[
    'A' => 'T',
    'C' => 'G',
    'G' => 'C',
    'T' => 'A'
  ]
  a = String[]

  for ln = readdlm(f)
    rna = Char[]
    for ch = ln
      unshift!(rna, compliment[ch])
    end
    push!(a, join(rna))
  end
  writedlm(f, a, '\n')

  close(f)
end
open(DNA_reverse_compliment, "rosalind_revc.txt", "r+")


# check file for result

