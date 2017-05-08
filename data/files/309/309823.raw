# Main functions used for work on MCL with Julia
# Berkeley 2015 - Maxime Legrand

function bern(k,l,p)
  A = rand(k,l)
  B = p*ones(k,l)
  C = A .<= B
  D = convert(Array{Float64,2}, C)
  return D
end

"Sample for 2-SBM"
function mcl_sample_dumb(a,b,p1,p2)
  n = a+b
  G = zeros(n,n)
  G[1:a,1:a] = bern(a,a,p1)
  G[a+1:n,a+1:n] = bern(b,b,p1)
  G[1:a,a+1:n] = bern(a,b,p2)
  G[a+1:n,1:a] = bern(b,a,p2)
  return G
end

"""Sample for SBM
Input : l, vector of the sizes of the wanted clusters
    p, vector of their intra-cluster connection probability
    p0, inter-cluster connection probability
Output : corresponding SBM sample matrix"""
function mcl_sample_sbm(l,p,p0)
  s = size(l,1)
  n = sum(l)
  G = zeros(n,n)
  l0 = cumsum([0; l])
  for i in 1:s
    G[l0[i]+1:l0[i+1],l0[i]+1:l0[i+1]] = bern(l[i],l[i],p[i])
    G[l0[i]+1:l0[i+1],l0[i+1]+1:n] = bern(l[i,1],n-l0[i+1],p0)
    G[l0[i+1]+1:n,l0[i]+1:l0[i+1]] = bern(n-l0[i+1],l[i],p0)
  end
  return G
end

function mcl_norm(A)
  n = length(A)
  As = sum(A,2)
  B = A ./ As
  return B
end

function mcl_expand(A,e)
  B = A^e
  return B
end

function mcl_inflate(A,r)
  B = A .^ r
  return B
end

"""MCL algorithm
Input : A, adjacency matrix
    e, expansion parameter
    r, inflation parameter
    p, number of iterations
Output : corresponding result of MCL algorithm"""
function mcl(A;e=2,r=3,p=20)
  B = mcl_norm(A)
  for i=1:p
    B = mcl_norm(mcl_inflate(mcl_expand(B,e),r))
  end
  return B
end

"""First non-zero
Input : v, vector
Output : first non-zero element of v"""
function fst_non_zero(v)
  n = length(v)
  r = n+1
  for i = 1:n
    if (v[i] != 0) && (i < r)
      r = i
    end
  end
  if r == n+1
    r = 0
  end
  return r
end

"""Element finding in a vector of vectors
Input : k, element to find
    v, vector of vectors
Output : index of the first vector containing k if found, 0 otherwise"""
function vvfind(k,v)
  for i in 1:length(v)
    if length(find(x -> x==k, v[i])) != 0
      return i
    end
  end
  return 0
end

"Returns the first element of each vector of a vectors vector"
function vvfirst(v)
  K = find(x -> length(x) != 0, v)
  if length(K) == 0
    return Any[]
  else
    r = [v[K[1]][1]]
    for k in K[2:end]
      push!(r, v[k][1])
    end
    return r
  end
end

"""Return a vector containing clusters
Input : G, typical output of MCL algorithm
    sort_v, set to true to sort vertices inside clusters
    sort_c, set to true to sort clusters by increasing size
    rev, set to true along with sort_c to sort by decreasing size"""
function mcl_clust(G; sort_v=false, sort_c=false, rev=false)
  # Main part
  n = size(G,1)
  r = Vector[]
  for i = 1:n
    k = fst_non_zero(G[i,:])
    s = vvfind(k,r)
    if s == 0
      if i == k
        push!(r, [i])
      else
        push!(r, [k,i])
      end
    else
      if i != k
        push!(r[s],i)
      end
    end
  end
  # Vertices sorting part
  if sort_v
    for k in 1:size(r,1)
      sort!(r[k])
    end
  end
  # Clusters sorting part
  if sort_c
    p = sortperm(map(length, r), rev=rev)
    r = r[p]
  end
  return r
end

"Return the number of spotted clusters"
function mcl_card(G)
  return length(mcl_clust(G))
end

"Heuristic approximation of the probability of recognizing two clusters generated with mcl_sample_dumb, of size a and b, with T iterations"
function mcl_prob_dumb(a,b,p1,p2,T;e=2,r=3,p=20)
  if a == 0 || b == 0
    return 0.
  else
    result = 0
    for i in 1:T
      G = mcl_sample_dumb(a,b,p1,p2)
      if mcl_card(mcl(G,e,r,p)) == 2
        result += 1
      end
    end
  return result/T
  end
end
