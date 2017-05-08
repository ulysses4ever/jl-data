function SR (f, a, b, n)

  if n%2!=0

    n += 1

    end
  
  aprox = (f(a) + f(b))

  
  h = (b-a)/n


  for (i=2:2:n-1)

    x = a + i*h

    aprox += 2f(x)
    
    end


  for (i=1:2:n-1)

    x = a + i*h

    aprox += 4f(x)

    end


  return aprox*(h/3)


  end
