N = 1024
T = 1024
xs = zeros(Float64,N)
for t in 0:T
  println("$t $(mean(xs)) $(var(xs))")
  map!(x->rand()<0.5?x+1:x-1,xs)
  map!(xs) do x
    rand() < 0.5 ? x+1 : x-1
  end
end
