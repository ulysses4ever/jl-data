function fib(n)
  if n == 1 || n == 2 || n == 3
    return n
  else
    return fib(n - 1) + fib(n - 2)
  end
end

function evenFibsUnderX(x)
  i = 1
  sum = 0
  while (y = fib(i)) < x
    if y & 0x1 == 0
      sum += y
    end
    i += 1
  end
  return sum
end

value = evenFibsUnderX(4000000)