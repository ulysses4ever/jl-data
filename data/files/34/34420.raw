cd(string(dirname(@__FILE__)))

function bouncy(n)
  d = digits(n)
  s = sort(d)
  if (d==s) || (d==reverse(s))
    return false
  end
  return true
end

function pe112(p)
  cp = 0
  c = 0
  n = 9
  while cp < p
    n += 1
    if bouncy(n)
      c += 1
    end
    cp = c/n
  end
  return n
end

@time pe112(0.99)

