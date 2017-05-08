# What is the largest prime factor of the number 600851475143 ?

function facts(n::Int64)
  a = Int64[]
  x::Int64 = 1
  while x < sqrt(n)
    if n % x == 0
      if isprime(x)
        push!(a,x)
      end
    end
    x += 1
  end
  return a
end

factsArray = facts(600851475143)
ans = (length(factsArray) > 0 ? maximum(factsArray) : 0) # If the answer is 0 then the number is prime
