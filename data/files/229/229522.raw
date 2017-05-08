require("Points.jl")
importall Points

function randomwalk{P<:Point}(::Type{P}, nsteps, filename)
  if isempty(filename)
    output = STDOUT
  else 
    output = open(filename, "w")
  end

  p = zero(P)
  for t in 0:nsteps
    println(output, "$t $(plot_str(p))")
    p = update(p)
  end
end

dim = length(ARGS)>0 ? int(ARGS[1]) : 1
nsteps = length(ARGS)>1 ? int(ARGS[2]) : 1000
filename = length(ARGS)>2 ? ARGS[3] : ""

if dim == 1
  P = Point1D
elseif dim == 2
  P = Point2D
else
  error("dimension error!")
end

randomwalk(P, nsteps, filename)
