module DictUtils

function coalesce(args...)
  for arg in args
    if arg != null
      return arg
    end
  end
  return null
end

function combine!{K,V}(f::Function,
                       map1::Dict{K,V},
                       map2::Dict{K,V}) 
  allKeys = Set{K}()
  add_each!(allKeys, keys(map1))
  add_each!(allKeys, keys(map2))
  for k in allKeys
    map1[k] = f(get(map1, k, null), get(map2, k, null))
  end
end

function addDicts!{K,V}(map1::Dict{K,V},
                        map2::Dict{K,V},
                        weight::V)
  combine!((x, y) -> coalesce(x, zero(V)) + weight * coalesce(y, zero(V)), 
           map1, map2)
end

function mapValues!{K,V}(f::Function, m::Dict{K,V})
  for k in keys(m)
    m[k] = f(m[k])
  end
end

function normalizeDict!{K,V<:Number}(m::Dict{K,V})
  s = sum(values(m))
  mapValues!(x -> x/s, m)
end

function sortedHead!{K,V}(f::Function, m::Dict{K,V}, N::Int64)
  if length(m) <= N
    return
  end
  collection = collect(m)
  sort!(f, collection)

  for (k,v) in collection[(N+1):]
    delete!(m, k)
  end
end

function sortedHead!{K,V}(m::Dict{K,V}, N::Int64)
  sortedHead!((x,y) -> x[2] < y[2], m, N)
end

function sortedTail!{K,V}(m::Dict{K,V}, N::Int64, args...)
  sortedHead!((x,y) -> x[2] > y[2], m, N)
end

type CompactRepr
  keySeparator::String
  entrySeparator::String
end

DefaultCompactRepr = CompactRepr(":", ",")

function showCompact{K,V}(m::Dict{K,V}, config::CompactRepr)
  # Note that without the typehint on the Array, this will somehow get
  # converted to nothing on empty input.
  return join(
    Array{String,1}[string(k) * config.keySeparator * string(v)
                    for (k, v) in m], 
    config.entrySeparator
  )
end

function showCompact{K,V}(m::Dict{K,V})
  return showCompact{K,V}(m, DefaultCompactRepr)
end

function parseCompact{K,V}(s::String, config::CompactRepr)
  result = Dict{K,V}()
  if s == ""
    return(result)
  end
  entries = split(s, config.entrySeparator)
  for entry in entries
    parts = split(entry, config.keySeparator)
    @assert length(parts) == 2
    result[K(parts[1])] = V(parts[2])
  end
  return(result)
end

function parseCompact{K,V}(s::String)
  return parseCompact{K,V}(s, DefaultCompactRepr)
end

export coalesce, combine!, addDicts!, mapValues!,
       normalizeDict!, sortedHead!, sortedTail!,
       showCompact, parseCompact, CompactRepr,
       DefaultCompactRepr

end
