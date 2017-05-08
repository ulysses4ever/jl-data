# Results class
type Results
  scalars::Array{Float64, 2}
  N::Int64			# Number of elements in scalars
end

# Constructor
function Results()
  return Results(zeros(1000000, 2), 0)
end

function add!(results::Results, keep::Array{Float64, 2})
  num = size(keep)[1]
  results.scalars[results.N+1:results.N+num, :] = keep
  results.N += num
end

# Evaluate (an estimate of) logX
function logX(s::Array{Float64, 1}, results::Results)
  # Calculate fraction of mass that is above wrt all scalars
  above = 0
  N = results.N
  for i in 1:results.N
    if all(vec(results.scalars[i, :]) .> s)
      above += 1
    end
    if all(vec(results.scalars[i, :]) .== s)
      N -= 1
    end
  end
  return log(above/N)
end

