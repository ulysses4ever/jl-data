function is_prime(n::Int64)
  if n <= 3
    return true
  end

  if n % 2 == 0
    return false
  end

  i = 3
  while i <= sqrt(n)
    if is_divisable(n, i)
      return false
    end
    i += 2
  end

  return true
end

function is_divisable(n, i)
  return n % i == 0
end
