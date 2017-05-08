using CPUTime, ProfileView

function horner(list)
  res = 0
  power = 10
  for i in length(list):-1:1
    res *= power
    res += list[i]
  end
  return res
end

function samedigits(l)
  S = Set(l);
  return res = filter(x->length(x)==3,[find(x->x==s,l) for s in S])
end

samedigits(digits(31511))

function combs(l,d)
  res = Int[]
  for i in 0:9
    l[d] = i
    n = horner(l)
    push!(res,n[1])
  end
  return res;
end


function pe51()
  res = 0
  n = 0
  while res == 0
    l = digits(n)
    dupl = samedigits(l)
    if length(dupl) > 0
      if isprime(n)
        # println("Checking $n...")
        for d in dupl
          c = combs(l,d)
          if sum([isprime(e) && ndigits(e)==ndigits(n) for e in c]) == 8
            res = filter(x->isprime(x),c)
          end
        end
      end
    end
    n += 1;
  end
  println(res)
end

@time @CPUtime 1+1
@profile @time @CPUtime pe51()

#ProfileView.view()
