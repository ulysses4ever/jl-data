# Julia allows you to define the same function multiple times with different argument types

function is_divisible(n, i)
  return n % i == 0
end

function is_prime(n::Int64)
  if n <= 3
    return true
  end

  if is_divisible(n,2)
    return false
  end

  # Initialize a counter variable
  i = 3

  while i <= sqrt(n)
    if is_divisible(n,i)
      return false
    end

    i += 2
  end

  return true
end

# function is_prime(n::Int32)
  # insert magic here
# end

# function is_prime(n::Float64)
  # insert magic here
# end

println(is_prime(32341))
