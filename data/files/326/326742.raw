
module StatefulIterators

export StatefulIterator

import Base: start, next, done, read, copy


abstract StatefulIterator


type IterIterator <: StatefulIterator
    iter
    state
    IterIterator(iter) = new(iter, start(iter))
    IterIterator(i::IterIterator) = new(i.iter, i.state)
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
    ArrayIterator(a::ArrayIterator{T}) = new(a.iter, a.state)
end


StatefulIterator(x) = IterIterator(x)
StatefulIterator{T}(x::Array{T}) = ArrayIterator{T}(x)

copy(i::IterIterator) = IterIterator(i)
copy{T}(a::ArrayIterator{T}) = ArrayIterator{T}(a)

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
    reshape(s.iter[i:i+n-1], dims)
end

function read{T,U}(s::ArrayIterator{T}, ::Type{U}) 
    reinterpret(U, read(s, Int(ceil(sizeof(U) / sizeof(T)))))[1]
end

function read{T,U}(s::ArrayIterator{T}, ::Type{U}, dims...)
    reshape(reinterpret(U, read(s, Int(ceil(prod(dims) * sizeof(U) / sizeof(T))))), dims)
end


end
