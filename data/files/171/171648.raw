function derivative(f)
  # this line below will simply return the function you just passed.
  # return f

  # this is another way to define and pass the funnctions in julia
  # return function(x)
  #   put some stuff here
  # end

  # Is it clear what we're doing there?
  # When you call derivative, the function you pass in will be stored in a "closure".
  # In other words, it will be stored so it can be called later.
  # Derivative then returns another function, which takes x as an argument.
  # The result of calling derivative will be a function,
  # defined in terms of one variable, x.
  # When that function gets called, it will use the stored function, f,
  # to approximate the derivative at value, x. Let's fill in the gaps

  return function(x)
    # pick a small value for h
    h = x == 0 ? sqrt(eps(Float64)) : sqrt(eps(Float64)) * x

    # floating point arithmetic gymnastics
    xph = x + h
    dx = xph - x

    # evaluate f at x + h
    f1 = f(xph)

    # evaluate f at x
    f0 = f(x)

    # divide the difference by h
    return (f1 - f0) / dx
  end
end
