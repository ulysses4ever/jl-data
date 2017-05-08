using Points

function mean_var{P<:Point}(ps :: Array{P})
  m = mean(ps)
  ps2 = map(p->abs2(p-m),ps)
  v = sum(ps2)/(length(ps2)-1)
  return m,v
end

function randomwalk{PT<:Point}(P::Type{PT}, num::Integer, nsteps::Integer, filename::String)
  if isempty(filename)
    output = STDOUT
  else 
    output = open(filename, "w")
  end

  ps = zeros(P,num)
  for t in 0:nsteps
    m,v = mean_var(ps)
    println(output, t, " ", v, " ", plot_str(m))
    map!(update, ps)
  end
end

dim = length(ARGS)>0 ? int(ARGS[1]) : 1
num = length(ARGS)>1 ? int(ARGS[2]) : 1000
nsteps = length(ARGS)>2 ? int(ARGS[3]) : 1000
filename = length(ARGS)>3 ? ARGS[4] : ""

if dim == 1
  P = Point1D
elseif dim == 2
  P = Point2D
else
  error("dimension error!")
end

randomwalk(P, num, nsteps, filename)
