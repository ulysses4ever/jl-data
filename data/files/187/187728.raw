# ..
# ..
type TestFailed <: Exception
  message :: String
end

# ..
# ..
function posmod (n, mod)
  val = n % mod
  if val < 0
    val = (val + mod) % mod
  end
  return val
end

# ..
# ..
function test_most (input, test, throw_exception = true)
  results  = map(test, input)
  all_true = reduce((a, b) -> a && b, results)
  if throw_exception && !all_true
    throw(TestFailed(""))
  end
  return all_true
end

# ..
# ..
f(x) = posmod(5*x+1, 23) === 13
g(x) = posmod(5*x+1, 26) === 13
h(x) = posmod(9*x, 5) === 3
j(x) = posmod(5*x, 6) === 1

# ..
# ..
res = test_most(
  map(q -> -1 + 6*q, -100:100),
  x -> posmod(3+5*x, 6) === 1
)

# ..
# ..
println(res)