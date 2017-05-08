w = 0
N = 0
p = 0.0
delta = 1
E = 0

for n = 1:100
  for i = 1:1e6
    pp = sum(rand(1:4,9))
    cc = sum(rand(1:6,6))
    N += 1
    if pp > cc
      w += 1
    end
    p = w/N
  end
  E -= (E-p)/n
  if n%10 == 0
    println("Wahrscheinlichkeit: ",p,";   Neuer Erwartungswert:",E)
  end
end

function pe()
  w = 0
  N = 0
  p = 0.0
  delta = 1
  while delta > 1e-8 || p==0 || p==1
    pp = sum(rand(1:4,9))
    cc = sum(rand(1:6,6))
    N += 1
    if pp > cc
      w += 1
    end
    tmp = w/N
    delta = abs(p-tmp)
    p = w/N
  end
  return p
end

@time pe()

