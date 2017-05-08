import Base: eltype, show, push!, delete!, start, next, done

type WeakSet{T}
  inner::Set{WeakRef}
  WeakSet() = new(Set{WeakRef}())
end

WeakSet() = WeakSet{Any}()

function WeakSet{T}(xs::AbstractVector{T})
  s = WeakSet{T}()
  for x in xs
    push!(s, x)
  end
  return s
end

eltype{T}(s::WeakSet{T}) = T

function show(io::IO, s::WeakSet)
  print(io, "WeakSet")
  eltype(s) ≠ Any && print(io, "{$(eltype(s))}")
  print(io, "({")
  print_joined(io, s, ", ")
  print(io, "})")
end

function push!{T}(s::WeakSet{T}, obj)
  ref = WeakRef(convert(T, obj))
  push!(s.inner, ref)
  finalizer(obj, obj -> delete!(s.inner, ref))
  return s
end

function delete!(s::WeakSet, obj)
  delete!(s.inner, WeakRef(obj))
  return s
end

start(s::WeakSet) = start(s.inner)
done(s::WeakSet, state) = done(s.inner, state)

function next{T}(s::WeakSet{T}, state)
  item, state = next(s.inner, state)
  item.value::T, state
end
