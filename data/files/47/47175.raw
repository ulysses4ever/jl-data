export
  ispos, isneg, iszero, isone, complement, comp, constantly,
  inc, dec, juxt, iterate, mapcat, lmap, lfilter, lmapcat, ltake, ldrop,
  partition, partitionall, interleave, separate, splitat

ispos(x::Number) = x > 0
@vectorize_1arg Number ispos

isneg(x::Number) = x < 0
@vectorize_1arg Number isneg

iszero(x::Number) = x == 0
@vectorize_1arg Number iszero

isone(x::Number) = x == 1
@vectorize_1arg Number isone

complement(f::Function) = (xs...) -> !f(xs...)

comp(f::Function, g::Function) = x -> f(g(x))
comp(f::Function, g::Function, h::Function) = x -> f(g(h(x)))
comp(fs::Function...) = x -> reduce((acc, f) -> f(acc), x, reverse(fs))

constantly(x) = () -> x

inc(x::Number) = x + one(x)
@vectorize_1arg Number inc

dec(x::Number) = x - one(x)
@vectorize_1arg Number dec

juxt(f::Function, g::Function) = x -> (f(x), g(x))
juxt(f::Function, g::Function, fs::Function...) =
  x -> map(f->f(x), tuple(f, g, fs...))

function iterate(n::Integer, f::Function, x)
  n < 1 && error("n must be a positive integer.")

  l = Array(typeof(x), n)
  l[1] = x
  for i in 2:n
    l[i] = f(l[i-1])
  end
  l
end

function iterate(f::Function, x)
  IterateGenerator(f, x)
end

immutable IterateGenerator{T}
  f::Function
  x::T
end
Base.start(g::IterateGenerator) = g.x
Base.done(::IterateGenerator, state) = false
Base.next{T}(g::IterateGenerator{T}, state::T) = (state, g.f(state))
Base.eltype{T}(g::IterateGenerator{T}) = T

mapcat{T}(f::Function, cs::AbstractArray{T,1}...) = vcat(map(f, cs...)...)
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
Base.start(it::ConcatIterator) = (ref(1), ref(start(it.its[1])))
function Base.done{T<:Integer}(it::ConcatIterator, state::(Ref{T},Ref))
  nth, s = state
  len = length(it.its)
  partial_done = done(it.its[deref(nth)], deref(s))
  if partial_done
    swap!(nth, inc)
    if deref(nth) <= len
      set!(s, start(it.its[deref(nth)]))
    end
  end
  deref(nth) > len
end
function Base.next{T<:Integer}(it::ConcatIterator, state::(Ref{T},Ref))
  nth, s = state
  v, state = next(it.its[deref(nth)], deref(s))
  (v, (nth, set!(s, state)))
end

lmapcat(f::Function, its...) = lconcat(lmap(f, its...)...)

function ltake(n::Integer, it)
  n < 0 && error("n cannot be negative.")
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
  n < 0 && error("n cannot be negative.")
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

function partition{T}(n::Integer, x::AbstractArray{T,1})
  n < 0 && error("n cannot be negative.")
  [x[(1:n)+((i-1)*n)] for i in 1:div(length(x), n)]
end

partition(n::Integer, it) = PartitionIterator(n, it)

immutable PartitionIterator
  n::Integer
  it
end
Base.start(it::PartitionIterator) = (cell(it.n), ref(start(it.it)))
function Base.done(it::PartitionIterator, state::(Vector{Any},Ref))
  value, state = state
  s = deref(state)
  for i in 1:it.n
    if done(it.it, s)
      return true
    end
    v, s = next(it.it, s)
    value[i] = v
  end
  set!(state, s)
  return false
end
function Base.next(it::PartitionIterator, state::(Vector{Any},Ref))
  value, state = state
  (value, (cell(it.n), state))
end

function partitionall{T}(n::Integer, x::AbstractArray{T,1})
  n < 0 && error("n cannot be negative.")
  res = Array(typeof(x), iceil(length(x)/n))
  psize = div(length(x), n)
  for i in 1:psize
    res[i] = x[(1:n)+((i-1)*n)]
  end
  res[end] = x[n*psize+1:end]
  res
end

partitionall(n::Integer, it) = PartitionAllIterator(n, it)

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

interleave{T}(c::Vector{T}) = c
function interleave{T}(cs::Vector{T}...)
  count = length(cs)
  minlen = minimum(map(length, cs))
  res = Array(T, count * minlen)
  for vind in 0:minlen-1
    for cind in 1:count
      res[vind*count+cind] = cs[cind][vind+1]
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
  [:cind=>0, :donecheck=>true, :cstates=>map(start, [it.its...])]
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

function separate{T}(n::Integer, arr::AbstractArray{T})
  map(1:n) do i
    arr[Bool[(ind-1)%n == (i-1) for ind in 1:endof(arr)]]
  end
end
function separate(n::Integer, it)
  map(1:n) do i
    enumerate(it) |>
    (c -> lfilter(arg -> (arg[1]-1) % n == (i-1), c)) |>
    (c -> lmap(x -> x[2], c))
  end
end
