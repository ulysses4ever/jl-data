
module StatefulIterators

export StatefulIterator, ArrayIterator, peek, available, reset!

import Base: start, next, done, read, position, seek, seekstart,
             seekend, skip, eof, copy, eltype


# --- the type + basic operations

type StatefulIterator{T,S}
    iter::T
    state::S
end

StatefulIterator(iter) = StatefulIterator(iter, start(iter))
StatefulIterator(s::StatefulIterator) = StatefulIterator(s.iter, s.state)

copy(s::StatefulIterator) = StatefulIterator(s)

eltype{T,S}(::StatefulIterator{T,S}) = eltype(T) 

macro unlimited_loop(s, i, x, block)
    quote
        $(esc(i)) = 0
        for $(esc(x)) in $(esc(s))
            $(esc(i)) += 1
            $(esc(block))
        end
    end
end

macro limited_loop(s, i, n, x, block)
    quote
        $(esc(i)) = 0
        if $(esc(n)) > 0
            for $(esc(x)) in $(esc(s))
                $(esc(i)) += 1
                $(esc(block))
                $(esc(i)) >= $(esc(n)) && break
            end
            $(esc(i)) < $(esc(n)) && throw(EOFError())
        end
    end
end

macro preserving_state(s, block)
    quote
        save = $(esc(s)).state
        try
            $(esc(block))
        finally
            $(esc(s)).state = save
        end
    end
end


# --- iter protocol

start(s::StatefulIterator) = s

next{T,S}(s::StatefulIterator{T,S}, ::StatefulIterator{T,S}) = next(s)
function next(s::StatefulIterator)
    item, s.state = next(s.iter, s.state)
    item, s
end

done(s::StatefulIterator, ::StatefulIterator) = done(s)
done(s::StatefulIterator) = done(s.iter, s.state)



# --- basic stream-like extensions

assertNotDone(s::StatefulIterator) = done(s) && throw(EOFError())

"""read is like next() but returns only the value.  similar to next(),
it should be used with done() or you will get an error when reading
past the end of the collection.  the error is EOFError to be
consistent with streams."""
read(s::StatefulIterator) = (assertNotDone(s); next(s)[1])

"""the next() value, without advancing the state.  similar to next(),
it should be used with done() or you will get an error when reading
past the end of the collection."""
peek(s::StatefulIterator) = (assertNotDone(s); next(s.iter, s.state)[1])

position(s::StatefulIterator) = s.state

seek{T,S}(s::StatefulIterator{T,S}, p::S) = s.state = p

seekstart(s::StatefulIterator) = s.state = start(s.iter)

function seekend(s::StatefulIterator)
    @unlimited_loop s i _ begin end
    i
end

"""the number of read() values remaining."""
function available(s::StatefulIterator)
    @preserving_state s begin
        seekend(s)
    end
end

function skip(s::StatefulIterator, offset)
    @limited_loop s i offset x begin end
end

# we do not support mark / unmark / reset

eof(s::StatefulIterator) = done(s)

# TODO - support serialize / deserialize


# --- arbitrary types and arrays of data

function read(s::StatefulIterator, dims::Int...)
    a = Array(eltype(s), dims)
    n = prod(dims)
    @limited_loop s i n x begin
        @inbounds a[i] = x
    end
    a
end

function read{T,S,U}(s::StatefulIterator{T,S}, ::Type{U})
    if U in (Any, eltype(T))
        read(s)
    else
        n = cld(sizeof(U), sizeof(eltype(T)))
        reinterpret(U, read(s, n))[1]
    end
end

function read{T,S,U}(s::StatefulIterator{T,S}, ::Type{U}, dims...)
    if U in (Any, eltype(T))
        read(s, dims...)
    else
        m = prod(dims)
        n = cld(m * sizeof(U), sizeof(eltype(T)))
        reshape(resize!(reinterpret(U, read(s, n)), m), dims)
    end
end

function peek(s::StatefulIterator, dims::Int...)
    @preserving_state s begin
        read(s, dims...)
    end
end

function peek(s::StatefulIterator, t::Type)
    @preserving_state s begin
        read(s, t)
    end
end

function peek(s::StatefulIterator, t::Type, dims...)
    @preserving_state s begin
        read(s, t, dims...)
    end
end

function seekend{T,S,U}(s::StatefulIterator{T,S}, ::Type{U})
    if U in (Any, eltype(T))
        seekend(s)
    else
        # pre-calculate to get error on non bits types before changing
        # state
        t, u = sizeof(eltype(T)), sizeof(U)
        fld(seekend(s) * t, u)
    end
end

function available{T,S,U}(s::StatefulIterator{T,S}, ::Type{U})
    if U in (Any, eltype(T))
        available(s)
    else
        t, u = sizeof(eltype(T)), sizeof(U)
        fld(available(s) * t, u)
    end
end

function skip{T,S,U}(s::StatefulIterator{T,S}, ::Type{U}, offset)
    if U in (Any, eltype(T))
        skip(s, offset)
    else
        t, u = sizeof(eltype(T)), sizeof(U)
        skip(s, offset * cld(u, t))
    end
end


# --- optimisations for known tyoes

typealias LinearIndexed Union{Array, LinSpace, UnitRange, ASCIIString}

available{T<:LinearIndexed,S<:Integer}(s::StatefulIterator{T,S}) = length(s.iter) - s.state + 1

available{T<:UnitRange,S<:Integer}(s::StatefulIterator{T,S}) = s.iter.stop - s.state + 1

available{T<:StepRange,S<:Integer}(s::StatefulIterator{T,S}) = fld(s.iter.stop - s.state, s.iter.step) + 1

skip{T<:LinearIndexed,S<:Integer}(s::StatefulIterator{T,S}, offset) = s.state += offset

skip{T<:UnitRange,S<:Integer}(s::StatefulIterator{T,S}, offset) = s.state += offset

skip{T<:StepRange,S<:Integer}(s::StatefulIterator{T,S}, offset) = s.state += offset * s.iter.step


# --- avoid known bad types

# we cannot peek iters that are themselves stateful (because the state
# is not actually a separate state).
for X in (Task, StatefulIterator)
    msg = "$X lacks explicit state"
    @eval copy{T<:$X,S}(s::StatefulIterator{T,S}) = error($msg)
    @eval peek{T<:$X,S}(s::StatefulIterator{T,S}, args...) = error($msg)
    @eval position{T<:$X,S}(s::StatefulIterator{T,S}) = error($msg)
    @eval seek{T<:$X,S}(s::StatefulIterator{T,S}, p) = error($msg)
    @eval seekstart{T<:$X,S}(s::StatefulIterator{T,S}) = error($msg)
    @eval available{T<:$X,S}(s::StatefulIterator{T,S}, args...) = error($msg)
end


end
