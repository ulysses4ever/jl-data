export mid_point
export open_formula

function mid_point(f, a, b; n = 500)
  h = (b - a)/n
  sum = f(a + h/2)
  for i = 1:n-1
    sum += f(a + h/2 + i*h)
  end
  approx = h*sum
  return approx
end

function open_formula(f, a, b; n = 500)
  h = (b - a)/n
  approx = 3/2(f(a + h) + f(b - h))

  for i = 2:n - 2
    approx += f(a + i*h)
  end
  return h*approx
 end