# scalar multiplication
function * (lhs::Number, rhs::Function)
  return (x...) -> lhs * rhs(x...)
end

# scalar multiplication
function * (lhs::Function, rhs::Number)
  return (x...) -> lhs(x...) * rhs
end

# functional addition
function + (lhs::Function, rhs::Function)
  return (x...) -> lhs(x...) + rhs(x...)
end

# functional subtraction
function - (lhs::Function, rhs::Function)
  return (x...) -> lhs(x...) - rhs(x...)
end

# h(x, y, z) = f(g(x, y, z), g(x, y, z), g(x, y, z))

f(x, y, z) = 2
g(x, y, z) = x*z

println(((-1im)*g)(3, 4, 6))
# println((h)(3, 4, 6))