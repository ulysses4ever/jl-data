
module StatefulIterators

export StatefulIterator

import Base: start, next, done, read


abstract StatefulIterator


type IterIterator <: StatefulIterator
    iter
    state
    IterIterator(iter) = new(iter, start(iter))
end

type ArrayIterator{T} <: StatefulIterator
    iter::Vector{T}
    state
    function ArrayIterator(a::Array{T})
        s = size(a)
        if length(s) > 1
            a = reshape(a, prod(s))
        end
        new(a, start(a))
    end
end


StatefulIterator(x) = IterIterator(x)
StatefulIterator{T}(x::Array{T}) = ArrayIterator{T}(x)


start(i::StatefulIterator) = i

function next(i::StatefulIterator, s::StatefulIterator)
    item, state = next(i.iter, i.state)
    i.state = state
    item, i
end

done(i::StatefulIterator, s::StatefulIterator) = done(i.iter, i.state)

read(s::StatefulIterator) = next(s, s)[1]

function read(s::StatefulIterator, dims...)
    reshape(collect(take(s, prod(dims))), dims)
end


function read(s::ArrayIterator)
    i, s.state = s.state, s.state+1
    return s.iter[i]
end

function read(s::ArrayIterator, dims...)
    n = prod(dims)
    i, s.state = s.state, s.state+n
    reshape(s.iter[1:n], dims)
end

function read(s::ArrayIterator, t::Type) 
    reinterpret(t, read(s, sizeof(t)))[1]
end

function read{T}(s::ArrayIterator, t::Type{T}, dims...)
    reshape(reinterpret(T, read(s, prod(dims) * sizeof(T))), dims)
end


end
