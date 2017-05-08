function update(x::Real, prob::Real = 0.5)
  ifelse( rand() < prob, x+one(x), x-one(x) )
end

function randomwalk(num::Integer, nsteps::Integer; prob::Real=0.5, filename::String="")
  if isempty(filename)
    output = STDOUT
  else 
    output = open(filename, "w")
  end

  xs = zeros(Float64,num)
  for t in 0:nsteps
    println(output, "$t $(mean(xs)) $(var(xs))")
    map!(x -> update(x, prob), xs)
  end

  if output != STDOUT
    close(output)
  end
end

num = length(ARGS)>0 ? int(ARGS[1]) : 1000
nsteps = length(ARGS)>1 ? int(ARGS[2]) : 1000
prob = length(ARGS)>2 ? float(ARGS[3]) : 0.5
filename = length(ARGS)>3 ? ARGS[4] : ""

randomwalk(num, nsteps; prob=prob, filename=filename)
