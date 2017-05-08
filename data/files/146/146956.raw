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
  combine!((x, y) -> coalesce(x, 0) + weight * coalesce(y, 0), 
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

function sortedHead!{K,V}(m::Dict{K,V}, N::Int64, args...)
  if length(m) <= N
    return
  end
  collection = collect(m)
  sort!((x,y) -> x[2] < y[2], collection, args...)

  for (k,v) in collection[(N+1):]
    delete!(m, k)
  end
end

function sortedTail!{K,V}(m::Dict{K,V}, N::Int64, args...)
  sortedHead!(m, N, Sort.Reverse, args)
end

function deserializeMap(serializedMap::String)
  result = Dict{ASCIIString,Float64}()
  if serializedMap == ""
    return(result)
  end
  entries = split(serializedMap, ",")
  for entry in entries
    parts = split(entry, ":")
    assert(length(parts) == 2)
    result[parts[1]] = float(parts[2])
  end
  return(result)
end

function serializeMap(deserializedMap::Dict{ASCIIString,Float64})
  # Note that without the typehint on the Array, this will somehow get
  # converted to nothing on empty input.
  return(join(Array{String,1}[k * ":" * v for (k,v) in deserializedMap], ","))
end


x = ["foo"=>1,"bar"=>2,"baz"=>3]
sortedTail!(x, 4)
print(x)
sortedTail!(x, 2)
print(x)
