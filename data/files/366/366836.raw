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

"Sample for SBM"
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

"Apply MCL algorithm with expansion parameter e, inflation parameter r and p iterations"
function mcl(A;e=2,r=3,p=20)
  B = mcl_norm(A)
  for i=1:p
    B = mcl_norm(mcl_inflate(mcl_expand(B,e),r))
  end
  return B
end

"Return the first non-zero element of a vector `v`, and `0` if there is none."
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

"""Search a element in a vector of vectors :
 - returns 0 if not found
 - returns the index of the first vector containing it otherwise"""
function vvfind(k,v)
  for i in 1:length(v)
    if length(find(x -> x==k, v[i])) != 0
      return i
    end
  end
  return 0
end

r = Vector[]
push!(r, [1,2,3])
push!(r, [4,5])
push!(r, [6])
map(k -> vvfind(k,r), [1,2,3,4,5,6])

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

"Return a vector containing clusters"
function mcl_clust(G)
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
