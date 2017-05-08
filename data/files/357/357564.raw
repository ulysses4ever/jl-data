include("../utils/triangle.jl")
include("../utils/factor.jl")

# https://projecteuler.net/problem=12

print("Problem 12: ")

function problem12()
  triangleFinder = nextTriangle()
  while true
    triangleNumber, triangleSum = triangleFinder()
    allFactors = findAllFactors(triangleSum)
    length(allFactors) > 500 && return triangleSum
  end
end

println(problem12())