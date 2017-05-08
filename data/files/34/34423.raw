using Digits

function reversible(n)
  if n%10 == 0
    return false
  end
  r = reversedigits(n)
  d = digits(n+r)
  if all(map(isodd,d))
    return true
  end
  return false
end

function pe145(limit)
  c = 0
  for n = 1:limit
    if reversible(n)
      c += 1
    end
  end
  return c
end

@time pe145(1000)
@time pe145(10000)
@time pe145(100000)
@time pe145(1000000)

