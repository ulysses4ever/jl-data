include("cogen.jl")
using SimpleTools
using ProgressMeter
using PyPlot

function deg_count(n::Int)
  ds = degseq(n)
  c = Counter(Int)
  for d in ds
    c[d]+=1
  end
  return c
end


function multi_deg_count(n::Int,reps::Int = 1000)
  PM = Progress(reps,1)
  C = Counter(Int)
  for _=1:reps
    C += deg_count(n)
    next!(PM)
  end
  return C
end


function overlaps(n::Int)
  c = deg_count(n)
  total = 0
  for d in keys(c)
    total += binomial(c[d],2)
  end
  return total
end

function prob_equal(n::Int, reps::Int = 1000)
  total = 0
  PM = Progress(reps,1)
  for k=1:reps
    total += overlaps(n)
    next!(PM)
  end
  return total / reps / binomial(n,2)
end

function prob_equal_parallel(n::Int, reps::Int = 10_000)
  total = @parallel (+)  for k=1:reps
    overlaps(n)
  end
  return total / reps / binomial(n,2)
end
