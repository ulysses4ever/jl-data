#
#
type functional 
  f::Function
  function functional (fync, from, to)
    new(fync)
  end
  function functional (fync)
    f = fync
    new(fync)
  end
end

#
#
function + (lhs::functional, rhs::functional)
  # f(x) = lhs.f(x) + rhs.f(x)
  return functional(x -> lhs.f(x) + rhs.f(x))
end

#
#
function at (f::functional, x)
  return f.f(x)
end


f = functional(x -> 2*x, Integer, Real)
g = functional(x -> 3*x)

f = f+g


println(at(f, 3))