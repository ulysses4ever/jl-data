function update(x::Integer,p::Real=0.5)
  if rand() < p
    return x+one(x)
  else
    return x-one(x)
  end
end

function randomwalk(nsteps::Integer,prob::Real = 0.5)
  x = 0
  for t in 0:nsteps
    println("$t $x")
    x = update(x,prob)
  end
end

nsteps = length(ARGS)>0 ? int(ARGS[1]) : 1000
prob = length(ARGS)>1 ? float(ARGS[1]) : 0.5

randomwalk(nsteps,prob)

