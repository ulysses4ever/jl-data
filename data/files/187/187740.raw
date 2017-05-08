#
#
function func (x)
  return x*x*x
end

#
#
function finite_diff (f)
  h = 0.0000001
  diff(x) = return (f(x+h) - f(x-h))/2.0/h
  return diff
end

#
#
function complex_diff (f)
  h = 0.0000000001
  diff(x) = return imag(f(complex(x, h))/h)
  return diff
end

z(x) = finite_diff(func)(x)
y(x) = complex_diff(func)(x)

println(z(3))
println(y(3))