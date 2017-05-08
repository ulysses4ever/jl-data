# ========================================= #
# Wascally Wabbits
# ========================================= #
# Problem
# --------------
# Given positive integers n ≤ 40 and k ≤ 5.
#
# Return the nth value of a recurrence sequence which increments by k's
# instead of 1's (as is the case in fibb's). In short return:
#     a_(n+1) = a_(n) + k*a_(n-1)
# ==============
#
# Sample Dataset
# 5 3
#
# Sample Output
# 19
#
# ========================================= #
# let's check that thing I wrote:
# F_1 = 1
# F_2 = 1
# F_3 = F_2 + F_1 * 3 = 1 + 1*3 = 4
# F_4 = F_3 + F_2 * 3 = 4 + 1*3 = 7
# F_5 = F_4 + F_3 * 3 = 7 + 4*3 = 19
#
# good! now lets write it out:
include("../utils.jl")

function cb(str::String)
  n, k = strToIntArray(str, " ")
  println(recurrenceRel(5, 3))
end

function recurrenceRel(n::Int64, k::Int64)
  a, b = 1, 0
  for i = 1:n-1
    a, b = a+(b*k), a
  end
  return a
end

openOneLine(cb, "rosalind_fib.txt")
