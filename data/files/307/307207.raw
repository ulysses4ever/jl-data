# Basic API for iterated maps

abstract AbstractIteratedMap

type IteratedMap{S,D} <: AbstractIteratedMap
    func::Function
end

# Iterated maps are iterators

# Perhaps one way to do this is to prime the iterator
abstract AbstractIteratedMapIterator

type IteratedMapIterator{S,D} <: AbstractIteratedMapIterator
    start
    func::Function
end

# When you pass a starting value to an IteratedMap,
# you get an IteratedMapIterator ready to go

function Base.call{S,D}(f::IteratedMap{S,D},x)
    @assert length(x) == D
    IteratedMapIterator{S,D}(x,f.func)    
end

function Base.call(f::IteratedMapIterator)
    f.func(f.start)
end

# start needs something to start with
Base.start(f::IteratedMapIterator) = (f.start,1)

# This one is easy
Base.next(f::IteratedMapIterator,state) = (state[1],(f.func(state[1]),state[2]+1))

# done implies that there is a stopping point for the map
Base.done(f::IteratedMapIterator,state) = false

Base.eltype{S,D}(::Type{IteratedMapIterator{S,D}}) = D>1 ? Vector{Float64} : Float64
