function SR (f, a, b, n)

  if n%2!=0
    n += 1
  end
  h = (b-a)/n
  aprox = (f(a) + f(b) + 4f(a+h))
  for i=2:2:n-1
    x = a + i*h
    aprox += 2f(x) + 4f(x+h)
  end
  return aprox*(h/3)


end
