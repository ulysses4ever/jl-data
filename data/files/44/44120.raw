# Code for generating data for random cographs (without creating graphs)
@everywhere import SimpleRandom.binom_rv

"""
`cogen_val(n,x0,x1,sum_func,join_func)` generates the value of `X(G)`
where `G` is an `n`-vertex random cograph.

The parameters are as follows:

+ `n`: number of vertices
+ `x0`: Value of `X` for a `0`-vertex graph.
+ `x1`: Value of `X` for a `1`-vertex graph.
+ `sum_func(a,b,xa,xb)`: function giving `X` if the two pieces are of size
`a` and `b` with `X`-values `xa` and `xb` respectively, when we disjoint union
the two subgraphs.
+ `join_func(a,b,xa,xb)`: likewise for joining the two subgraphs.
"""
function cogen_val(n::Int, x0, x1, sum_func::Function, join_func::Function)

  # basis cases
  if n==0
    return x0
  end
  if n==1
    return x1
  end

  # choose random a between 0 and n (strictly). [Is "strictly" necessary?]
  # We are splitting the vertex set into parts of size a and b where a+b==n.
  a = 0
  while a==0 || a==n
    a = binom_rv(n)
  end
  b = n-a

  # recursion step
  xa = cogen_val(a,x0,x1,sum_func,join_func)
  xb = cogen_val(b,x0,x1,sum_func,join_func)

  # Flip a coin to decide sum or join
  if rand() < 0.5
    return sum_func(a,b,xa,xb)
  end
  return join_func(a,b,xa,xb)
end


# Clique size functions
clique_sum(a::Int,b::Int,xa::Int,xb::Int) = max(xa,xb)
clique_join(a::Int,b::Int,xa::Int,xb::Int) = xa+xb
clique(n::Int) = cogen_val(n,0,1,clique_sum,clique_join)

# Number of edges functions
numedge_sum(a::Int,b::Int,xa::Int,xb::Int) = xa + xb
numedge_join(a::Int,b::Int,xa::Int,xb::Int) = xa + xb + a*b
numedge(n::Int) = cogen_val(n,0,0,numedge_sum,numedge_join)

# number of components functions
num_comps_join(a::Int,b::Int,xa::Int, xb::Int) =  1
num_comps_sum(a::Int,b::Int,xa::Int,xb::Int) = xa+xb
num_comps(n::Int) = cogen_val(n,0,1,num_comps_sum,num_comps_join)


# degree of vertex 1
deg1_sum(a::Int, b::Int, xa::Int, xb::Int) = xb
deg1_join(a::Int, b::Int, xa::Int, xb::Int) = xb + a
deg1(n::Int) = cogen_val(n,1,0,deg1_sum,deg1_join)

# number of isolated vertices
iso_sum(a::Int, b::Int, xa::Int, xb::Int) = xa + xb
iso_join(a::Int, b::Int, xa::Int, xb::Int) = 0
iso(n::Int) = cogen_val(n,0,1,iso_sum,iso_join)
