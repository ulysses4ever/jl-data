@everywhere include("para-cogen.jl")
@everywhere using SimpleRandom

"""
`clique_sizes(nv,reps)` find the sizes of random cographs with `nv`
vertices (repeat `reps` times) and return the answers as a list.
"""
function clique_sizes(nv::Int, reps::Int=1000)
  result = Vector{Int}(reps)
  for k=1:reps
    result[k] = clique(nv)
  end
  return result
end

function concat{T}(x::Vector{T},y::Vector{T})
  nx = length(x)
  ny = length(y)
  result = Vector{T}(nx+ny)
  for i=1:nx
    @inbounds result[i] = x[i]
  end
  for i=1:ny
    @inbounds result[i+nx] = y[i]
  end
  return result
end


"""
`para_clique_sizes(nv, chunk, reps)` find the sizes of random cographs
with `nv` vertices in batches of size `chunk` repeatedly (`reps` times)
and return the results (as a list of size `reps*chunk`).
"""
function para_clique_sizes(nv::Int, chunk::Int=1000, reps::Int=1000)
  result = @parallel (concat) for i=1:reps
      clique_sizes(nv,chunk)
  end
  return result
end
