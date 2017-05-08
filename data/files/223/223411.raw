# Problem 14
#
# The following iterative sequence is defined for the set of positive integers:
#
#   n → n/2 (n is even)
#   n → 3n + 1 (n is odd)
#
# Using the rule above and starting with 13, we generate the following sequence:
#
#   13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
#
# It can be seen that this sequence (starting at 13 and finishing at 1) 
# contains 10 terms. Although it has not been proved yet (Collatz Problem), it 
# is thought that all starting numbers finish at 1.
#
# Which starting number, under one million, produces the longest chain?
#
# NOTE: Once the chain starts the terms are allowed to go above one million.

cache = [ 1 => 1 ]
cache!(f, k) = haskey(cache, k) ? cache[k] : (cache[k] = f())

next(n) = iseven(n) ? div(n, 2) : (3n + 1)
collatz(n) = cache!(n) do
  collatz(next(n)) + 1
end

max(a, b) = a[2] >= b[2] ? a : b
maxkey(pairs) = reduce(max, pairs)[1]

pairs = map(1:1000000) do n
  (n, collatz(n))
end
start = maxkey(pairs)

println(start)
# 837799
