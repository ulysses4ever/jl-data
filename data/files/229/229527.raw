function randomwalk(num, nsteps, filename)
  if isempty(filename)
    output = STDOUT
  else 
    output = open(filename, "w")
  end

  xs = zeros(Float64,num)
  for t in 0:nsteps
    println(output, "$t $(var(xs)) $(mean(xs))")
    map!(x -> rand()<0.5 ? x+one(x) : x-one(x), xs)
  end
end

num = length(ARGS)>0 ? int(ARGS[1]) : 1000
nsteps = length(ARGS)>1 ? int(ARGS[2]) : 1000
filename = length(ARGS)>2 ? ARGS[3] : ""

randomwalk(num, nsteps, filename)
