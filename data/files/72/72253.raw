include("Population.jl")
function testFunction()
  size = 100
  dim = 30
  gen = 1000
  testPop = Population(size, dim)
  println(minItem(testPop).fitness)
  evolve(testPop, gen)
  println(minItem(testPop).fitness)
end

testFunction()
@time testFunction()
