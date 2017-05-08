include("../utils/collatz.jl")

# https://projecteuler.net/problem=14

print("Problem 14: ")

function problem14()
  result = [1,1]
  for i = 1:1000000
    len = length(collatz(i))
    if len > result[2]
      result[1] = i
      result[2] = len
    end
  end
  return result
end

println(problem14())