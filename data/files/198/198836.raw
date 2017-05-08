#projecteuler.net
#problem 1: multiples of 3 and 5

#code
function sum_multiples_3_5(below::Int)
#f(g()...) is the same as apply(f, g())
  sum(union(map(m -> [j*m for j in 1:div(below-1,m)], [3, 5])...))
end

#tests

#If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
sum_multiples_3_5(10)

#Find the sum of all the multiples of 3 or 5 below 1000
sum_multiples_3_5(1000)

