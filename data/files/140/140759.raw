# ============================================ #
# Mendel's First Law
# ============================================ #
# Problem
# --------------
# Probability is the mathematical study of randomly occurring phenomena.
# We will model such a phenomenon with a random variable, which is simply a
# variable that can take a number of different distinct outcomes depending on
# the result of an underlying random process.
#
# For example, say that we have a bag containing 3 red balls and 2 blue balls.
# If we let X represent the random variable corresponding to the color of a
# drawn ball, then the probability of each of the two outcomes is given by
# Pr(X=red)=3/5 and Pr(X=blue)=2/5.
#
# Random variables can be combined to yield new random variables. Returning
# to the ball example, let Y model the color of a second ball drawn from the
# bag (without replacing the first ball). The probability of Y being red
# depends on whether the first ball was red or blue. To represent all
# outcomes of X and Y, we therefore use a probability tree diagram. This
# branching diagram represents all possible individual probabilities for X
# and Y, with outcomes at the endpoints ("leaves") of the tree. The
# probability of any outcome is given by the product of probabilities along
# the path from the beginning of the tree; see Figure 2 for an
# illustrative example.
#
# An event is simply a collection of outcomes. Because outcomes are distinct,
# the probability of an event can be written as the sum of the probabilities
# of its constituent outcomes. For our colored ball example, let A be the
# event "Y is blue". Pr(A) is equal to the sum of the probabilities of two
# different outcomes:
#
#   Pr(Y is blue) = Pr(X=blue and Y=blue) + Pr(X=red and Y=blue)
#                 = (3/10) + (1/10)
#                 =  2/5
#
# Given: Three positive integers k, m, and n, representing a population
# containing k + m + n organisms:
#   k individuals are homozygous dominant for a factor,
#   m are heterozygous,
#   and n are homozygous recessive.
#
# Return: The probability that two randomly selected mating organisms will
# produce an individual possessing a dominant allele (and thus displaying
# the dominant phenotype). Assume that any two organisms can mate.
# ==============
#
# Sample Dataset
# 2 2 2
#
# Sample Output
# 0.78333
# ============================================ #
#   k = n(AA)
#   m = n(Aa)
#   n = n(aa)
#   z = k+m+n
#
#
# P(child has A)
#        = P(Aa` OR AA`)
#        = 1 - P(Aa1 OR AA`)
#        = 1 - P(aa`)
#
#  1 - P(aa`)
#         = 1 - (
#           P(aa` | AA_AA) = P(AA_AA) * P(aa`) = P(AA_AA) *    0
#         + P(aa` | AA_Aa) = P(AA_Aa) * P(aa`) = P(AA_Aa) *    0
#         + P(aa` | AA_aa) = P(AA_aa) * P(aa`) = P(AA_aa) *    0
#         + P(aa` | Aa_AA) = P(Aa_AA) * P(aa`) = P(Aa_AA) *    0
#         + P(aa` | Aa_Aa) = P(Aa_Aa) * P(aa`) = P(Aa_Aa) * 0.25
#         + P(aa` | Aa_aa) = P(Aa_aa) * P(aa`) = P(Aa_aa) * 0.50
#         + P(aa` | aa_AA) = P(aa_AA) * P(aa`) = P(aa_AA) *    0
#         + P(aa` | aa_Aa) = P(aa_Aa) * P(aa`) = P(aa_Aa) * 0.50
#         + P(aa` | aa_aa) = P(aa_aa) * P(aa`) = P(aa_aa) * 1.00
#         )
#
#         = 1 - (P(Aa1)P(Aa2)/4 + P(Aa1)P(aa2)/2 + P(Aa2)P(aa1)/2 + P(aa1)P(aa2))
#         = 1 - ( (m/z)(m-1/z-1)/4
#               + (m/z)(n/z-1)/2
#               + (n/z)(m/z-1)/2
#               + (n/z)(n-1/z-1)/1 )
#         = 1 - (  mm-m/(zz-z) *0.25
#               +  2*mn/(zz-z) *0.5
#               +  nn-n/(zz-z)
#         = 1 - ( (mm-m)*0.25
#               + (mn)
#               + (nn-n) ) / (zz-z) )
#         = 1 - (( 0.25(mm-m) + mn + nn - n ) / (zz-z) )
#
# EXAMPLE:= 1 - (( 0.25(4-2) + 4 + 4 - 2 ) / (36-6) )
#         = 1 - (( 0.25(2) + 6) / 30)
#         = 1 - (( 6.5 / 30)
#         = 0.783333333        # ... GRRRRR!!!
#
include("../utils.jl")

function pChildHasDominantPhenotype(k, m, n, z)
  1 - (( 0.25*(m*m-m) + m*n + n*n - n ) / (z*z-z) )
end

function cb(str::String)
  ints = strToIntArray(str, " ")
  # lets take advantage of multiple assignments
  k, m, n = ints
  z = reduce(+, ints)
  println(pChildHasDominantPhenotype(k, m, n, z))
end

openOneLine(cb, "rosalind_iprb.txt")

