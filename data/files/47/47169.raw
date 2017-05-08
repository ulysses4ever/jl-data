export
  ispos, isneg, iszero, isone, complement, comp, constantly,
  inc, dec, juxt, iterate, mapcat, lmap, lfilter, lmapcat, ltake, ldrop,
  partition, partitionall, interleave, linterleave, separate, splitat

ispos(x::Number) = x > 0
@vectorize_1arg Number ispos

isneg(x::Number) = x < 0
@vectorize_1arg Number isneg

iszero(x::Number) = x == zero(x)
@vectorize_1arg Number iszero

isone(x::Number) = x == one(x)
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
Base.start(it::FilterIterator) = start(it.it)
Base.done(it::FilterIterator, state) = done(it.it, state)
function Base.next(it::FilterIterator, state)
  v, s = next(it.it, state)
  while !it.pred(v)
    v, s = next(it.it, s)
  end
  v, s
end

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
  !applicable(start, it) && error("it must an iterator.")
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
