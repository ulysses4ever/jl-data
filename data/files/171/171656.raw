include("derivative.jl")

function quadratic(f)
  # compute the first derivative of f
  f1 = derivative(f)

  # get the y intercept (explictly passing a floating point number)
  c = f(0.0)

  # get the y intercept of the first derivative
  b = f1(0.0)

  a = f(1.0) - b - c

  # Our old friend the quadratic formula
  # Notice how Julia lets you return multiple values
  # Multiple values should be separated by a comma and
  # are returned as a tuple
  # return (-b + sqrt(b^2 -4a*c)) / 2a, (-b - sqrt(b^2 -4a*c)) / 2a

  # That looks great, but what do we do if the roots are complex numbers?
  # Not to worry, Julia has robust support for complex numbers.
  # In this case, the easiest way to deal with complex roots is
  # to simply add 0im to the determinant in our return values.
  # That instructs Julia to treat the determinants as complex number types,
  # and the sqrt function will handle them gracefully if they are negative.

  # The Julia symbol for i, or √−1 is im,
  # and can be prefixed with any numeric type to instantiate an imaginary number.
  # In this example, we add 0im, which instantiates an imaginary number with magnitude 0.
  # In our example, sqrt(b^2 -4a*c) becomes sqrt(b^2 -4a*c + 0im).

  return (-b + sqrt(b^2 -4a*c + 0im)) / 2a, (-b - sqrt(b^2 -4a*c + 0im)) / 2a
end
