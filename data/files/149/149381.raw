# Project Euler Problem 7
# 4-13-14, Ben Southgate

# Question:
# What is the 10,001st prime number?

function nth_prime(n::Int64)
  prime_list = [2]
  curr_number = 3
  while length(prime_list) < n
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
    curr_number += 1
  end
  prime_list[end]
end

println(nth_prime(10001)) 