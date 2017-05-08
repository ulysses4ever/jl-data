include("../utils/fibonacci.jl")

# https://projecteuler.net/problem=2

print("Problem 2: ")

function problem2()
  n = 4000000
  sum = 0
  fibIterator = nextFib()
  currentFib = fibIterator()
  while currentFib < n
    currentFib % 2 == 0 && (sum += currentFib)
    currentFib = fibIterator()
  end
  return sum
end

println(problem2())
