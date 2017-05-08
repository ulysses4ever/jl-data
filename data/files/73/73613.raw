function primefactor(x, n)
  if x==1
    return n
  elseif x % n ==0
    return primefactor(x/n, n)
  else
    return primefactor(x, n+1)
  end
end
 
println(primefactor(600851475143, 2))

