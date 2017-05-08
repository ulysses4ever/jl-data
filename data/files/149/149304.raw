# Project Euler Problem 3
# 4-10-14, Ben Southgate

# QUESTION:
# What is the largest prime factor of the number 600851475143 ?

# May have gotten a little help from here: 
# http://math.stackexchange.com/questions/389675/largest-prime-factor-of-600851475143

function largest_prime_factor(n::Int64)
  # current divisor
  b::Int64 = 2
  # While the number being examined isn't == to the divisor
  while n != b
    # If we can evenly divide the number by the divisor
    if n%b == 0
      # Do so
      n /= b
      # Reset the divisor
      b = 2
    else 
      # Otherwise, increment the divisor and try again
      b += 1
    end
  end
  return n
end

println(largest_prime_factor(600851475143))
