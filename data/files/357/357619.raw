include("prime.jl")

# There is actually a built-in factor method, but I didn't find out about it until I implemented brent
# I'll probably switch to the built-in version in the future
function findFactor(n)
  return brent(n)
end

# http://rosettacode.org/wiki/Factors_of_an_integer#Julia
function findAllFactors(n)
  f = [one(n)]
  for (p,e) in factor(n)
    f = reduce(vcat, f, [f*p^j for j in 1:e])
  end
  return length(f) == 1 ? [one(n), n] : sort!(f)
end


function brent(n)
  n<2 && return n
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
