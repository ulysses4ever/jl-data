
module StatefulIterators

export StatefulIterator, ArrayIterator, peek, available, reset!

import Base: start, next, done, read, read!, readbytes, 
             position, seek, seekstart, seekend, skip, 
             eof, copy, eltype,
             readuntil, readline


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

compatible(U, T) = U == Any || eltype(T) <: U

function read!{T,S,U}(s::StatefulIterator{T,S}, a::Array{U})
    n = length(a)
    if compatible(U, T)
        @limited_loop s i n x begin
            @inbounds a[i] = x
        end
    else
        b = reinterpret(eltype(T), a)
        m = length(b)
        @limited_loop s i m x begin
            @inbounds b[i] = x
        end
        t, u = sizeof(eltype(T)), sizeof(U)
        if t > u
            # need to fill in the Us that didn't cover an entire eltype(T)
            nn = fld(m * t, u)
            if n > nn
                c = read(s, U, n-nn)
                for i in 1:(n-nn)
                    a[nn+i] = c[i]
                end
            end
        end
    end
end

function readbytes(s::StatefulIterator, nb=typemax(Int))
    b = Array(UInt8, 0)
    readbytes!(s, b, nb)
    b
end

function readbytes!{T,S}(s::StatefulIterator{T,S}, b::Array{UInt8}, nb=tyemax(Int))
    try
        n = min(nb, available(s, UInt8))
        if length(b) < n
            resize!(b, n)
        end
        a = reinterpret(eltype(T), a)
        m = length(a)
        @limited_loop s i m x begin
            @inbounds a[i] = x
        end
    catch  # available failed
        t = sizeof(eltype(T))
        i, a = 0, Array(UInt8, t)
        while !done(s) && i < nb
            read!(s, a)
            j = 0
            while i < nb && j < t
                i += 1
                j += 1
                if i > length(b)
                    push!(b, a[j])
                else
                    b[i] = a[j]
                end
            end
        end
    end
end

"""the next() value, without advancing the state.  similar to next(),
it should be used with done() or you will get an error when reading
past the end of the collection."""
peek(s::StatefulIterator) = (assertNotDone(s); next(s.iter, s.state)[1])

position(s::StatefulIterator) = s.state

seek{T,S}(s::StatefulIterator{T,S}, p::S) = s.state = p

seekstart(s::StatefulIterator) = s.state = start(s.iter)

function seekend(s::StatefulIterator)
    @unlimited_loop s i _ begin end
end

"""the number of read() values remaining."""
function available(s::StatefulIterator)
    @preserving_state s begin
        @unlimited_loop s i _ begin end
        i
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
    if compatible(U, T)
        read(s)
    else
        n = cld(sizeof(U), sizeof(eltype(T)))
        reinterpret(U, read(s, n))[1]
    end
end

function read{T,S,U}(s::StatefulIterator{T,S}, ::Type{U}, dims...)
    if compatible(U, T)
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

function available{T,S,U}(s::StatefulIterator{T,S}, ::Type{U})
    if compatible(U, T)
        available(s)
    else
        t, u = sizeof(eltype(T)), sizeof(U)
        fld(available(s) * t, u)
    end
end

function skip{T,S,U}(s::StatefulIterator{T,S}, ::Type{U}, offset)
    if compatible(U, T)
        skip(s, offset)
    else
        t, u = sizeof(eltype(T)), sizeof(U)
        skip(s, offset * cld(u, t))
    end
end


# --- optimisations for known types

typealias LinearIndexed Union{Array, LinSpace, UnitRange, ASCIIString}

seekend{T<:LinearIndexed,S<:Integer}(s::StatefulIterator{T,S}) = s.state = length(s.iter) + 1

seekend{T<:UnitRange,S<:Integer}(s::StatefulIterator{T,S}) = s.state = s.iter.stop + 1

endof(r::StepRange) = r.start + r.step * (fld(r.stop - r.start, r.step) + 1)

seekend{T<:StepRange,S<:Integer}(s::StatefulIterator{T,S}) = s.state = endof(s.iter)

available{T<:LinearIndexed,S<:Integer}(s::StatefulIterator{T,S}) = length(s.iter) - s.state + 1

available{T<:UnitRange,S<:Integer}(s::StatefulIterator{T,S}) = s.iter.stop - s.state + 1

available{T<:StepRange,S<:Integer}(s::StatefulIterator{T,S}) = fld(s.iter.stop - s.state, s.iter.step) + 1

limit(n, lim) = n > lim ? throw(EOFError()) : n

skip{T<:LinearIndexed,S<:Integer}(s::StatefulIterator{T,S}, offset) = s.state = limit(s.state + offset, length(s.iter) + 1)

skip{T<:UnitRange,S<:Integer}(s::StatefulIterator{T,S}, offset) = s.state = limit(s.state + offset, s.iter.stop + 1)

skip{T<:StepRange,S<:Integer}(s::StatefulIterator{T,S}, offset) = s.state = limit(s.state + offset * s.iter.step, endof(s.iter))

# we don't need to add the versions with an explicit type - like
# skip(s, type, offset) - because the implementations earlier will
# delegate to these optimized versions.


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


# --- text-specific routines

# julia-0.4/base/io.jl
function readuntil{T<:AbstractString,S}(s::StatefulIterator{T,S}, t::AbstractString)
    l = length(t)
    if l == 0
        return ""
    elseif l > 40
        warn("readuntil(SteatfulIterator,AbstractString) will perform poorly with a long string")
    end
    out = IOBuffer()
    m = Array(Char, l)  # last part of stream to match
    t = collect(t)
    i = 0
    while !eof(s)
        i += 1
        c = read(s, Char)
        write(out, c)
        if i <= l
            m[i] = c
        else
            m[1:l-1] = m[2:l]
            m[l] = c
        end
        if i >= l && m == t
            break
        end
    end
    return takebuf_string(out)
end

readline{T<:AbstractString,S}(s::StatefulIterator{T,S}) = readuntil(s, "\n")


end
