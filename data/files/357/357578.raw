include("../utils/prime.jl")

# https://projecteuler.net/problem=10

print("Problem 10: ")

function problem10()
  primeFinder = nextPrime()
  primeSum = 0
  maximumPrime = 2000000
  while true
    currentPrime = primeFinder()
    currentPrime > maximumPrime && break
    primeSum += currentPrime
  end
  return primeSum
end

println(problem10())