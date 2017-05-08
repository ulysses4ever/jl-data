include("prime.jl")

function findFactor(n)
  return brent(n)
end

function findAllFactors(n)
  factors = [1, n]
  while true
    currentFactor = findFactor(n)
    currentFactor == n && (currentFactor = findFactor(n))
    currentFactor == n && (currentFactor = findFactor(n))
    if isPrime(currentFactor)
      push!(factors, currentFactor)
    else
      append!(factors, findAllFactors(currentFactor))
    end
    currentFactor == n && break
    n /= currentFactor
  end
  sort!(factors)
  return factors
end


function brent(n)
  n%2==0 && return 2

  y,c,m = rand(1:n-1),rand(1:n-1),rand(1:n-1)
  g,r,q = 1,1,1
  ys,x = 1,1

  while g==1
    x = y
    for i = 1:r
      y = ((y*y)%n+c)%n
    end
    k = 0
    while k<r && g==1
      ys = y
      for i = 1:(min(m,r-k))
        y = ((y*y)%n+c)%n
        q = q*(abs(x-y))%n
      end
      g = gcd(int(q),int(n))
      k = k + m
    end
    r = r*2
  end
  if g==n
    while true
      ys = ((ys*ys)%n+c)%n
      g = gcd(int(abs(x-ys)),int(n))
      if g>1
        break
      end
    end
  end
  return g
end
