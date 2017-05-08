# Problem 15
#
# Starting in the top left corner of a 2×2 grid, and only being able to move to 
# the right and down, there are exactly 6 routes to the bottom right corner.
#
# How many such routes are there through a 20×20 grid?

d = Dict()
cache!(f, k...) = haskey(d, k) ? d[k] : (d[k] = f())

function routes(x, y)
  if 0 in (x, y)
    1
  elseif x > y
    routes(y, x)
  else
    cache!(x, y) do
      routes(x - 1, y) + routes(x, y - 1)
    end
  end
end

numroutes = routes(20, 20)

println(numroutes)
# 137846528820
