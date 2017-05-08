module StatefulIterators_

export StatefulIterator, available, peek, reset!
import Base: eltype, start, next, done, read, copy

type StatefulIterator{T, S}
    iter::T
    state::S
end
StatefulIterator(itr) = StatefulIterator(itr, start(itr))
StatefulIterator(s::StatefulIterator) = StatefulIterator(s.iter, s.state)
copy(s::StatefulIterator) = StatefulIterator(s)

eltype{T,S}(::StatefulIterator{T,S}) = eltype(T) 
eltype{T,S}(::Base.Take{StatefulIterator{T,S}}) = eltype(T)

start(s::StatefulIterator) = s
function next{T,S}(s::StatefulIterator{T,S}, ::StatefulIterator{T,S})
    (item, s.state) = next(s.iter, s.state)
    return item, s
end
done(s::StatefulIterator) = done(s.iter, s.state)
done{T,S}(s::StatefulIterator{T,S}, ::StatefulIterator{T,S}) = done(s)

function read(s::StatefulIterator)
    for v in s
        return v  # just return the first value
    end
end

function read(s::StatefulIterator, dims::Int...)
    a = Array(eltype(s), dims)
    M = prod(dims)
    if M == 0
        return a
    end
    i = 0
    for x in s
        @inbounds a[i+=1] = x
        if i == M
            return a
        end
    end
    return resize!(a, i) # Should possibly be an error. Asked for too many elements.
end

peek{T, S<:Void}(s::StatefulIterator{T,S}, dims::Int...) = nothing # or throw exception?
# throw(ErrorException("peek() is not supported for iterators with state of type $(S)."))
peek{T, S}(s::StatefulIterator{T,S}) = next(s.iter, s.state)[1]
function peek{T, S}(s::StatefulIterator{T,S}, dims::Int...)
    state = s.state
    a = read(s, dims...)
    s.state = state
    return a
end

available{T<:Base.Cycle, S}(::StatefulIterator{T, S}) = Inf  # cycles are never finished
available{T, S<:Void}(::StatefulIterator{T, S}) = nothing  # This is the case for tasks
@generated function available{T, S}(s::StatefulIterator{T,S})
    # Returns the number of remaining bytes in stream.
    if isbits(eltype(T)) && method_exists(length, Tuple{T}) && S <: Integer
        if T <: Union{Array, LinSpace, UnitRange, ASCIIString}
            # fastest algorithm for iterators that support it
            return :((length(s.iter) - s.state + 1) * sizeof(eltype(T)))    
        elseif T <: Range && S <: eltype(T)
            # sometimes state is unreliable, e.g. for StepRanges
            return :(done(s.iter, s.state) ? 0 : 
                (length(s.iter) - findfirst(s.iter, s.state) + 1) * sizeof(eltype(T)))
        end
    end
    # fallback algorithm
    return quote
        state = s.state
        siz = 0
        for x in s
            siz += sizeof(x)
        end
        s.state = state
        return siz
    end
end

function read{U}(s::StatefulIterator, ::Type{U})
    N = cld(sizeof(U), sizeof(eltype(s)))
    return reinterpret(U, read(s, N))[1]
end
function peek{U}(s::StatefulIterator, ::Type{U})
    N = cld(sizeof(U), sizeof(eltype(s)))
    return reinterpret(U, peek(s, N))[1]
end
function read{U}(s::StatefulIterator, ::Type{U}, dims...)
    M = prod(dims)
    N = cld(M * sizeof(U), sizeof(eltype(s)))
    return reshape(resize!(reinterpret(U, read(s, N)), M), dims)
end
function peek{U}(s::StatefulIterator, ::Type{U}, dims...)
    M = prod(dims)
    N = cld(M * sizeof(U), sizeof(eltype(s)))
    return reshape(resize!(reinterpret(U, peek(s, N)), M), dims)
end

reset!(s::StatefulIterator) = (s.state = start(s.iter))

end
