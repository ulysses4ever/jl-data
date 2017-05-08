# Problem 5
#
# 2520 is the smallest number that can be divided by each of the numbers from 1 
# to 10 without any remainder.
#
# What is the smallest positive number that is evenly divisible by all of the 
# numbers from 1 to 20?

facts = [ 1:20 ]

isfactor(x) = y -> x % y == 0
ismultiple(n) = all(map(isfactor(n), facts))

step = smallest = prod(filter(isprime, facts))
while !ismultiple(smallest)
  smallest += step
end

println(smallest)
# 232792560
