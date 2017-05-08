# Problem 4
#
# A palindromic number reads the same both ways. The largest palindrome made 
# from the product of two 2-digit numbers is 9009 = 91 × 99.
#
# Find the largest palindrome made from the product of two 3-digit numbers.

ispalendrome(n) = string(n) == reverse(string(n))

products = map(prod, combinations([ 100:999 ], 2))
largest = maximum(filter(ispalendrome, products))

println(largest)
# 906609
