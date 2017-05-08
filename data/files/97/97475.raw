#===============================================================================
# Types
immutable MCPerm{O<:Ordering,M<:AbstractMatrix} <: Ordering
    order::O
    data::M
    keys::Vector{Int}
    dim::Integer
end

MCPerm{O<:Ordering,M<:AbstractMatrix}(o::O,m::M, keys::Vector{Int}, dim::Integer) =
  MCPerm{O,M}(o,m, keys, dim)

#===============================================================================
# Functions
#-------------------------------------------------------------------------------
function mc_lt(o::Ordering, arr::AbstractArray, i::Int, j::Int,
               keys::Vector{Int}, dim::Int)
  if dim == 1
    return mc_lt_cols(o, arr, i, j, keys)
  else
    return mc_lt_rows(o, arr, i, j, keys)
  end
end

#-------------------------------------------------------------------------------
function mc_lt_cols(o::Ordering, arr::AbstractArray, i::Int, j::Int,
               keys::Vector{Int})
  for key in keys
    if arr[i, key] == arr[j, key]
      continue
    else
      return lt(o, arr[i, key], arr[j, key])
    end
  end

    return false
end

#-------------------------------------------------------------------------------
function mc_lt_rows(o::Ordering, arr::AbstractArray, i::Int, j::Int,
                    keys::Vector{Int})
  for key in keys
    if arr[key, i] == arr[key, j]
      continue
    else
      return lt(o, arr[key, i], arr[key, j])
    end
  end

    return false
end

#-------------------------------------------------------------------------------
lt(p::MCPerm, a::Int, b::Int) = mc_lt(p.order, p.data, a, b, p.keys, p.dim)
