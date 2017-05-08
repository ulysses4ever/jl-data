using Lens
using DynamicAnalysis
import DynamicAnalysis: benchmark, Problem, Algorithm

immutable SortingProblem <: Problem
  data::Vector{Int}
end

"""Bubble Sort"""
function bubblesort!{T}(x::AbstractArray{T})

  for i in 2:length(x)
    for j in 1:length(x)-1
      if x[j] > x[j+1]
          tmp = x[j]
          x[j] = x[j+1]
          x[j+1] = tmp
      end
    end
  end

  return x
end

immutable BubbleSort <: Algorithm
  captures::Vector{Symbol}
end

function benchmark(a::BubbleSort, p::SortingProblem)
  function  f()
    val, el_time, bytes, gc_time, counters = @timed bubblesort!(p.data)
    lens(:runtime, el_time)
    lens(:bytes, bytes)
    return val
  end
  value, results = capture(f, a.captures)
  return results
end

"Pancake Sort"
function pancakesort!{T<:Real}(a::Array{T,1})
    len = length(a)
    if len < 2
        return a
    end
    for i in len:-1:2
        j = indmax(a[1:i])
        i != j || continue
        a[1:j] = reverse(a[1:j])
        a[1:i] = reverse(a[1:i])
    end
    return a
end

immutable PancakeSort <: Algorithm
  captures::Vector{Symbol}
end

function benchmark(a::PancakeSort, p::SortingProblem)
  function  f()
    val, el_time, bytes, gc_time, counters = @timed pancakesort!(p.data)
    lens(:runtime, el_time)
    lens(:bytes, bytes)
    return val
  end
  value, results = capture(f, a.captures)
  return results
end

## Run analysis
nproblems = 10
problems = [SortingProblem([rand(-100:100) for i in 1:10]) for i = 1:nproblems]
bs = BubbleSort([:runtime, :bytes])
ps = PancakeSort([:runtime, :bytes])
record([bs, ps], problems; exceptions = false)
