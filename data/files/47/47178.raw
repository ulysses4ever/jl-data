export
  is_pos, is_neg, is_zero, is_one, complement, comp, constantly,
  inc, dec, juxt, iterate, mapcat, lmap, lfilter, lconcat, lmapcat, ltake,
  ldrop, partition, partition_all, interleave, separate, split_at

is_pos(x::Number) = x > 0
@vectorize_1arg Number is_pos

is_neg(x::Number) = x < 0
@vectorize_1arg Number is_neg

is_zero(x::Number) = x == 0
@vectorize_1arg Number is_zero

is_one(x::Number) = x == 1
@vectorize_1arg Number is_one

complement(f::Function) = (xs...) -> !f(xs...)

comp(f::Function, g::Function) = x -> f(g(x))
comp(f::Function, g::Function, h::Function) = x -> f(g(h(x)))
comp(fs::Function...) = x -> reduce((r, f) -> f(r), x, reverse(fs))

constantly(x) = () -> x

inc(x::Number) = x + one(x)
@vectorize_1arg Number inc

dec(x::Number) = x - one(x)
@vectorize_1arg Number dec

juxt(f::Function, g::Function) = x -> (f(x), g(x))
juxt(f::Function, g::Function, fs::Function...) =
  x -> map(f -> f(x), tuple(f, g, fs...))

function iterate(n::Integer, f::Function, x)
  n < 1 && ArgumentError("n must be a positive integer.")

  l = Array(typeof(x), n)
  l[1] = x
  for i in 2:n
    l[i] = f(l[i-1])
  end
  l
end

iterate(f::Function, x) = IterateIterator(f, x)

immutable IterateIterator{T}
  f::Function
  x::T
end

Base.start{T}(it::IterateIterator{T}) = (it.x, false)

Base.done{T}(::IterateIterator{T}, ::(T,Bool)) = false

function Base.next{T}(it::IterateIterator{T}, state::(T,Bool))
  x, apply = state
  apply ?
    let x = it.f(x)
      (x, (x, true))
    end :
    (x, (x, true))
end

Base.eltype{T}(it::IterateIterator{T}) = T

mapcat(f::Function, its...) = vcat(map(f, its...)...)

lmap(f::Function, its...) = MapIterator(f, its)

immutable MapIterator
  f::Function
  its
end

Base.start(it::MapIterator) = map(start, it.its)

function Base.done(it::MapIterator, state::(Any...))
  n = reduce(+, map(done, it.its, state))
  0 < n < length(it.its) && error("lengths of collections don't match.")
  n != 0
end

function Base.next(it::MapIterator, state::(Any...))
  values, state = map(next, it.its, state) |> vs -> map(tuple, vs...)
  (it.f(values...), state)
end

lfilter(pred::Function, it) = FilterIterator(pred, it)

immutable FilterIterator
  pred::Function
  it
end

Base.start(it::FilterIterator) =
  (Symbol=>Any)[:value=>nothing, :state=>start(it.it)]

function Base.done(it::FilterIterator, state::Dict{Symbol,Any})
  s = state[:state]
  while !done(it.it, s)
    v, s = next(it.it, s)
    if it.pred(v)
      state[:value] = v
      state[:state] = s
      return false
    end
  end
  true
end

Base.next(it::FilterIterator, state::Dict{Symbol,Any}) = (state[:value], state)

lconcat(its...) = ConcatIterator(its)

immutable ConcatIterator
  its
end

Base.start(it::ConcatIterator) =
  (Symbol=>Any)[:nth=>1, :state=>start(it.its[1])]

function Base.done(it::ConcatIterator, state::Dict{Symbol,Any})
  nth, s = state[:nth], state[:state]
  len = length(it.its)
  partial_done = done(it.its[nth], s)
  if partial_done
    nth = inc(nth)
    state[:nth] = nth
    if nth <= len
      state[:state] = start(it.its[nth])
    end
  end
  nth > len
end

function Base.next(it::ConcatIterator, state::Dict{Symbol,Any})
  nth, s = state[:nth], state[:state]
  v, s = next(it.its[nth], s)
  state[:state] = s
  (v, state)
end

lmapcat(f::Function, its...) = lconcat(lmap(f, its...)...)

function ltake(n::Integer, it)
  n < 0 && ArgumentError("n cannot be negative.")
  TakeIterator(n, it)
end

immutable TakeIterator
  n::Integer
  it
end

Base.start(it::TakeIterator) = (1, start(it.it))

Base.done(it::TakeIterator, state::(Integer,Any)) =
  state[1] > it.n || done(it.it, state[2])

function Base.next(it::TakeIterator, state::(Integer,Any))
  v, s = next(it.it, state[2])
  (v, (inc(state[1]), s))
end

Base.length(it::TakeIterator) = it.n

function ldrop(n::Integer, it)
  n < 0 && ArgumentError("n cannot be negative.")
  DropIterator(n, it)
end

immutable DropIterator
  n::Integer
  it
end

function Base.start(it::DropIterator)
  state = start(it.it)
  for i in 1:it.n
    if !done(it.it, state)
      _, state = next(it.it, state)
    end
  end
  state
end

Base.done(it::DropIterator, state) = done(it.it, state)

Base.next(it::DropIterator, state) = next(it.it, state)

function partition{T}(n::Integer, a::AbstractArray{T,1})
  n < 1 && ArgumentError("n must be a positive integer.")
  [a[(1:n)+((i-1)*n)] for i in 1:div(length(a), n)]
end

function partition(n::Integer, it)
  n < 1 && ArgumentError("n must be a positive integer.")
  PartitionIterator(n, it)
end

immutable PartitionIterator
  n::Integer
  it
end

Base.start(it::PartitionIterator) =
  (Symbol=>Any)[:value=>cell(it.n), :state=>start(it.it)]

function Base.done(it::PartitionIterator, state::Dict{Symbol,Any})
  value, s = state[:value], state[:state]
  for i in 1:it.n
    if done(it.it, s)
      return true
    end
    v, s = next(it.it, s)
    value[i] = v
  end
  state[:state] = s
  return false
end

function Base.next(it::PartitionIterator, state::Dict{Symbol,Any})
  value = state[:value]
  state[:value] = cell(it.n)
  (value, state)
end

function partition_all{T}(n::Integer, a::AbstractArray{T,1})
  n < 1 && ArgumentError("n must be a positive integer.")
  res = Array(typeof(a), iceil(length(a)/n))
  psize = div(length(a), n)
  for i in 1:psize
    res[i] = a[(1:n)+((i-1)*n)]
  end
  res[end] = a[n*psize+1:end]
  res
end

function partition_all(n::Integer, it)
  n < 1 && ArgumentError("n must be a positive integer.")
  PartitionAllIterator(n, it)
end

immutable PartitionAllIterator
  n::Integer
  it
end

function Base.start(it::PartitionAllIterator)
  state = start(it.it)
  (done(it.it, state), state)
end

Base.done(it::PartitionAllIterator, state::(Bool,Any)) = state[1]

function Base.next(it::PartitionAllIterator, state::(Bool,Any))
  value = Any[]
  _, state = state
  for i in 1:it.n
    v, state = next(it.it, state)
    push!(value, v)
    if done(it.it, state)
      return (value, (true, state))
    end
  end
  (value, (false, state))
end

interleave{T}(a::AbstractArray{T,1}) = a

function interleave{T}(as::AbstractArray{T,1}...)
  count = length(as)
  minlen = minimum(map(length, as))
  res = Array(T, count * minlen)
  for vind in 0:minlen-1
    for cind in 1:count
      res[vind*count+cind] = as[cind][vind+1]
    end
  end
  res
end

interleave(it) = it
interleave(its...) = InterleaveIterator(its)

immutable InterleaveIterator
  its
end

Base.start(it::InterleaveIterator) =
  (Symbol=>Any)[:cind=>0, :donecheck=>true, :cstates=>map(start, [it.its...])]

function Base.done(it::InterleaveIterator, state::Dict{Symbol,Any})
  if state[:donecheck]
    state[:donecheck] = false
    reduce(+, map(done, it.its, state[:cstates])) > 0
  else
    false
  end
end

function Base.next(it::InterleaveIterator, state::Dict{Symbol,Any})
  i = state[:cind] + 1
  v, cstate = next(it.its[i], state[:cstates][i])
  ncind = i % length(it.its)
  if ncind == 0
    state[:donecheck] = true
  end
  state[:cind] = ncind
  state[:cstates][i] = cstate
  (v, state)
end

function separate{T}(n::Integer, a::AbstractArray{T,1})
  n < 1 && ArgumentError("n must be a positive integer.")
  map(1:n) do i
    a[Bool[(ind-1)%n == (i-1) for ind in 1:endof(a)]]
  end
end

function separate(n::Integer, it)
  n < 1 && ArgumentError("n must be a positive integer.")
  map(1:n) do i
    enumerate(it) |>
    (c -> lfilter(arg -> (arg[1]-1) % n == (i-1), c)) |>
    (c -> lmap(x -> x[2], c))
  end
end

function split_at{T}(n::Integer, a::AbstractArray{T,1})
  n < 0 && ArgumentError("n cannot be negative.")
  typeof(a)[a[1:n], a[n+1:end]]
end

function split_at(n::Integer, it)
  n < 0 && ArgumentError("n cannot be negative.")
  (ltake(n, it), ldrop(n, it))
end
