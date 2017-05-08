## Benchmarking to analyse performance of algorithms

## Measures
## =======
# KL Divergence is a measure of the information lost when Q is used to approximate P
KL{T}(P::Dict{T, Float64}, Q::Dict{T, Float64}) =
  sum([log(P[i]/Q[i]) * P[i] for i in keys(P)])

function KLsafe{T}(P::Dict{T, Float64}, Q::Dict{T, Float64})
  Qnew::Dict{T,Float64} = [k => haskey(Q,k) ? Q[k] + 1 : 1 for k in keys(P)]
  totalcounts = sum(values(Qnew))
  Qnew = [k => v/totalcounts for (k,v) in Qnew] #renormalise
  KL(P,Qnew)
end