function productorFib()
  f0 = 0
  produce(f0)
  f1 = 1
  produce(f1)
  produce(100000000)

  for i=1:100
    aux = f0
    f0 = f1
    f1= aux + f1
    produce(f1)

  end

end
int(sqrt(5))
function primoAMano(n)
  for i = 2:(n-1)
    if (mod(n, i) == 0)
      return false
    end
  end
  true
end
primoAMano(4)
mod(2,2)


addprocs(5)
rmprocs(2:6)
nprocs()
t =Task(productorFib)

consume(t)
addprocs(4)
@everywhere function consumidor()
  @sync begin
        for i in Task(productorFib)
          @async begin

           resul =primoAMano(i)

           println("Lei :$i _ es primo :$resul")
          end
        end
  end
end
consumidor()
1+1
