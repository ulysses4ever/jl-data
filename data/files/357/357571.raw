function collatz(n)
  sequence = [n]
  while n > 1
    if isodd(int(n))
      n = 3n+1
    else
      n = n/2
    end
    push!(sequence, n)
  end
  return sequence
end