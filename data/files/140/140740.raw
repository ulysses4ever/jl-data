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
# Condidional Probability! Yay!
#   k = n(AA)
#   m = n(Aa)
#   n = n(aa)
#   z = k+m+n
#
#
# P(child has A)
#        = P(Aa` OR AA`)
#        = P(Aa`) + P(AA`) - P(Aa` and AA`)            # last one is impossible!
#
#  P(?A) = P(?A | AA_AA) = P(Aa` | AA_AA) = P(AA_AA) * P(Aa`) = (P(AA) * P(AA)) * P(Aa`)= ((k/z * k/z) *    0) = 0
#                        + P(AA` | AA_AA) = P(AA_AA) * P(AA`) = (P(AA) * P(AA)) * P(AA`)= ((k/z * k/z) * 1.00) = (2k)/(  z^2)
#        + P(?A | AA_Aa) = P(Aa` | AA_Aa) = P(AA_Aa) * P(Aa`) = (P(AA) * P(Aa)) * P(Aa`)= ((k/z * m/z) * 0.50) = (km)/(2 z^2)
#                        + P(AA` | AA_Aa) = P(AA_Aa) * P(AA`) = (P(AA) * P(Aa)) * P(AA`)= ((k/z * m/z) * 0.50) = (km)/(2 z^2)
#        + P(?A | AA_aa) = P(Aa` | AA_aa) = P(AA_aa) * P(Aa`) = (P(AA) * P(aa)) * P(Aa`)= ((k/z * n/z) * 1.00) = (kn)/(  z^2)
#                        + P(AA` | AA_aa) = P(AA_aa) * P(AA`) = (P(AA) * P(aa)) * P(AA`)= ((k/z * n/z) *    0) = 0
#        + P(?A | Aa_AA) = P(Aa` | Aa_AA) = P(Aa_AA) * P(Aa`) = (P(Aa) * P(AA)) * P(Aa`)= ((m/z * k/z) * 0.50) = (km)/(2 z^2)
#                        + P(AA` | Aa_AA) = P(Aa_AA) * P(AA`) = (P(Aa) * P(AA)) * P(AA`)= ((m/z * k/z) * 0.50) = (km)/(2 z^2)
#        + P(?A | Aa_Aa) = P(Aa` | Aa_Aa) = P(Aa_Aa) * P(Aa`) = (P(Aa) * P(Aa)) * P(Aa`)= ((m/z * m/z) * 0.50) = (mm)/(2 z^2)
#                        + P(AA` | Aa_Aa) = P(Aa_Aa) * P(AA`) = (P(Aa) * P(Aa)) * P(AA`)= ((m/z * m/z) * 0.25) = (mm)/(4 z^2)
#        + P(?A | Aa_aa) = P(Aa` | Aa_aa) = P(Aa_aa) * P(Aa`) = (P(Aa) * P(aa)) * P(Aa`)= ((m/z * n/z) * 0.50) = (mn)/(2 z^2)
#                        + P(AA` | Aa_aa) = P(Aa_aa) * P(AA`) = (P(Aa) * P(aa)) * P(AA`)= ((m/z * n/z) *    0) = 0
#        + P(?A | aa_AA) = P(Aa` | aa_AA) = P(aa_AA) * P(Aa`) = (P(aa) * P(AA)) * P(Aa`)= ((n/z * k/z) * 1.00) = (kn)/(  z^2)
#                        + P(AA` | aa_AA) = P(aa_AA) * P(AA`) = (P(aa) * P(AA)) * P(AA`)= ((n/z * k/z) *    0) = 0
#        + P(?A | aa_Aa) = P(Aa` | aa_Aa) = P(aa_Aa) * P(Aa`) = (P(aa) * P(Aa)) * P(Aa`)= ((n/z * m/z) * 0.50) = (mn)/(2 z^2)
#                        + P(AA` | aa_Aa) = P(aa_Aa) * P(AA`) = (P(aa) * P(Aa)) * P(AA`)= ((n/z * m/z) *    0) = 0
#        + P(?A | aa_aa) = P(Aa` | aa_aa) = P(aa_aa) * P(Aa`) = (P(aa) * P(aa)) * P(Aa`)= ((n/z * n/z) *    0) = 0
#                        + P(AA` | aa_aa) = P(aa_aa) * P(AA`) = (P(aa) * P(aa)) * P(AA`)= ((n/z * n/z) *    0) = 0
#
#        = (2k)/(  z^2) + (4km)/(2 z^2) + (2kn)/(  z^2) + (3mm)/(4 z^2) + (2mn)/(2 z^2)
#        = (8k)/(4 z^2) + (8km)/(4 z^2) + (8kn)/(4 z^2) + (3mm)/(4 z^2) + (4mn)/(4 z^2)
#        = (8k + 8km + 8kn + 3mm + 4mn)/(4 z^2)
#        = (2k + 2km + 2kn + mn)/(z^2) + (3mm / 4z^2)
#
# EXAMPLE: (4 + 8 + 8 + 4)/(36) + (12/(4*36))
#        = 24/36 + 12/114
#        = 0.6667 + 0.1053
#        = 0.7770                             # nope!
#
#






