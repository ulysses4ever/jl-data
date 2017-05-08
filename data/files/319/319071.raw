a = [1,0,1,1,1]
b = [1,0,1,0,1]
a = rand(0:1,40);
b = rand(0:1,40);


c = ones(2,length(a))
c[1,1] = 0;

function babbage(a,b)
  for i = 2:length(a)
  C = [mod(a[i]+b[i],2) mod(a[i]*b[i],2); 0 1] * c[:,i-1]
  c[1,i]=mod(C[1],2)
  end
  c
end

babbage(a,b)

##parallelize
addprocs(4)
s = zeros(length(a))
function babbageS(a,b,c)
  s[1] = mod(a[1]+b[1],2)
  @parallel (+) for i=2:length(a)
  s[i] = mod(s[i-1]+a[i]+b[i]+c[1,i-1],2)
  end
  s[length(s)]
end
t = @elapsed(babbageS)

##kill slaves
rmprocs(procs()[2:end])

##compare run time with usual for loop

function babbageS_straight(a,b,c)
  s[1] = mod(a[1]+b[1],2)
  for i=2:length(a)
  s[i] = mod(s[i-1]+a[i]+b[i]+c[1,i-1],2)
  end
  s[length(s)]
end
t = @elapsed(babbageS_straight(a,b,c))

##conclude that the parallelization leads to less computing time.
