#   Project Euler
#   Problem:    3
#   Author:     Ben Hobbs
#   Date:       27/5/2015
#   Desc:       The prime factors of 13195 are 5, 7, 13 and 29.
#
#               What is the largest prime factor of the number 600851475143?

addprocs(4)
require("problem_3_functions.jl")

num = 600851475143

max_factor = round(num/2)   #figure out how to round up

lower_first_quartile, upper_first_quartile = 1, round(max_factor * 0.25)
lower_second_quartile, upper_second_quartile = upper_first_quartile + 1, round(max_factor * 0.5)
lower_third_quartile, upper_third_quartile = upper_second_quartile + 1, round(max_factor* 0.75)
lower_forth_quartile, upper_forth_quartile = upper_third_quartile + 1, max_factor

samples_pmap = pmap(factors,{lower_first_quartile,lower_second_quartile,lower_third_quartile,lower_forth_quartile},{upper_first_quartile,upper_second_quartile,upper_third_quartile,upper_forth_quartile},{num,num,num,num})

a = Int64[]
for f in samples_pmap
    append!(a,f)
end

for f in a
    @printf "%d : %s\n" f isPrime(f)
end

