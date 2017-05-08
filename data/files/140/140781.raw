# ========================================= #
# The Second Nucleic Acid
# ========================================= #
# Problem
# --------------
# An RNA string is a string formed from the alphabet containing
# 'A', 'C', 'G', and 'U'.
#
# Given a DNA string t corresponding to a coding strand, its transcribed
# RNA string u is formed by replacing all occurrences of 'T' in t
# with 'U' in u.
#
# Given: A DNA string t having length at most 1000 nt.
#
# Return: The transcribed RNA string of t.
# ==============
#
# Sample Dataset
# GATGGAACTTGACTACGTAAATT
#
# Sample Output
# GAUGGAACUUGACUACGUAAAUU
#
# ========================================= #

function DNA_RNA_file_transcription(f::IOStream)
  a = String[]
  for ln = readdlm(f)
    rna = ""
    for ch = ln
      n = (ch == 'T') ? "U" : ch
      rna*=string(n)
    end
    println(rna)
    push!(a, rna)
  end
  writedlm(f, a, '\n')

  close(f)
end

open(DNA_RNA_file_transcription, "rna.txt", "r+")


# check file for result
