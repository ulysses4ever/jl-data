function biggest(x, y)
  return (x > y)? x: y
end


function isPrime(n)
  if n < 2
    return false
  end
  # maior divisor de n (até n -1)
  divider = 1

  for i in [1:biggest(n - 1, div(n, 2))]
    if n % i == 0
      divisor = i
    end
  end
  if divider == 1
    return true
  else
    return false
  end
end

isPrime(600851475143)
function largestPrimeFactor(x)
  factor = 0
  for i in [1:floor(sqrt(x))]
    if isPrime(i)
      factor = i
    end
  end
  return factor
end

largestPrimeFactor(600851475143)