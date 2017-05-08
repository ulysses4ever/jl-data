# Quadratic Equation Solver
# Given a second order polynomial, return its roots
function quadratic(f)
  # Compute the first derivative of f
  f1 = derivative(f)

  # Get the y-intercept
  # - this works since y = ax^2 + bx + c
  # - so setting x to 0 gives: 0 + 0 + c
  c = f(0.0) # explicitly pass in floating point 0

  # Get the y-intercept of the first derivative
  # - this works since y' = 2ax + b
  # - so setting x to 0 gives: 0 + b
  b = f1(0.0)

  # Now that we know b and c, compute a
  a = f(1.0) - b - c

  # Now use the quadratic formula to get the roots
  # Julia lets you return multiple values
  # The 0im is to tell Julia to treat the return values as
  # imaginary numbers if necessary to handle negative roots gracefully
  return (-b + sqrt(b^2 - 4a*c + 0im)) / 2a, (-b - sqrt(b^2 - 4a*c + 0im)) / 2a
end

function derivative(f)
  # compute the derivative of the passed in function
  # using the approximation: (f(x+h) - f(x)) / h
  return function(x)
    # h needs to be sufficiently small for an accurate result.
    # also due to limitations of floating point arithmetic, we need to take
    # the machine epsilon into account to get accurate results. 
    # (see http://en.wikipedia.org/wiki/Numerical_differentiation#Practical_considerations_using_floating_point_arithmetic)
    h = (x == 0 ? sqrt(eps(Float64)) : sqrt(eps(Float64)) * x)

    f1 = f(x + h)
    f0 = f(x)

    return (f1 - f0) / h
  end
end

