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
  union!(allKeys, keys(map1))
  union!(allKeys, keys(map2))
  for k in allKeys
    map1[k] = f(get(map1, k, null), get(map2, k, null))
  end
end

function addDicts!{K,V}(map1::Dict{K,V},
                        map2::Dict{K,V},
                        weight::V)
  return combine!(
    (x, y) -> coalesce(x, zero(V)) + weight * coalesce(y, zero(V)),
    map1,
    map2
  )
end

function mapValues!{K,V}(f::Function, m::Dict{K,V})
  for k in keys(m)
    m[k] = f(m[k])
  end
end

function normalizeDict!{K,V<:Number}(m::Dict{K,V})
  s = sum(values(m))
  return mapValues!(x -> x/s, m)
end

function sortedHead!{K,V}(f::Function, m::Dict{K,V}, N::Int64)
  if length(m) <= N
    return
  end
  collection = collect(m)
  sort!(f, collection)

  for (k,v) in collection[(N+1):end]
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
    String[string(k) * config.keySeparator * string(v)
           for (k, v) in m],
    config.entrySeparator
  )
end

showCompact{K,V}(m::Dict{K,V}) = showCompact(m, DefaultCompactRepr)

function parsePrimitive{T<:Integer}(::Type{T}, s::String)
  return parse_int(T, s)
end

function parsePrimitive{T<:FloatingPoint}(::Type{T}, s::String)
  return parse_float(T, s)
end

function parsePrimitive{T<:String}(::Type{T}, s::String)
  return s
end

function parseCompact(s::String, K::DataType, V::DataType, config::CompactRepr)
  result = Dict{K,V}()
  if s == ""
    return(result)
  end
  entries = split(s, config.entrySeparator)
  for entry in entries
    parts = split(entry, config.keySeparator)
    @assert length(parts) == 2
    result[parsePrimitive(K, parts[1])] = parsePrimitive(V, parts[2])
  end
  return(result)
end

parseCompact(s::String, K::DataType, V::DataType) =
  parseCompact(s, K, V, DefaultCompactRepr)

export coalesce, combine!, addDicts!, mapValues!,
       normalizeDict!, sortedHead!, sortedTail!,
       CompactRepr, DefaultCompactRepr,
       parsePrimitive, showCompact, parseCompact
end
