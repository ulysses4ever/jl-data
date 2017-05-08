# Project Euler Problem 9
# 4-13-14, Ben Southgate

# Question:
# Find the sum of all the primes below two million.

function primes_below(n::Int64)
  prime_list::Array{Int64,1} = [2]
  curr_number::Int64 = 3
  while (curr_number < n)
      number_is_prime = true
      for num in prime_list
        if curr_number % num == 0
          number_is_prime = false
          break
        end
      end
      if number_is_prime
        prime_list = push!(prime_list, curr_number)
      end   
    curr_number += 2
  end
  return prime_list
end

println(sum(primes_below(2000000)))
