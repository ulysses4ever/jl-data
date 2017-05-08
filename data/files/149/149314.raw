# Project Euler Problem 5
# 4-12-14, Ben Southgate

# Question:
# What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

# Starting from the largest number, I simply include numbers in the range
# That had factors not already included in previous numbers
b = 20*19*18*17*14*13*11
check(x) = all(map((a)->x%a==0,1:20))
println(b," ",check(b))

