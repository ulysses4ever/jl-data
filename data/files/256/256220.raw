module Chunk

using SimpleHttpIO

export IOChunked,
       done,
       size,
       data,
       block,
       iterator,
       ChunkIterator

const N = SimpleHttpIO.N
const N_TYPE = SimpleHttpIO.N_TYPE

type IOChunked <: AbstractIOSocket
    io::IO
    env::Associative
end

IOChunked(io::IO; kwargs...) = IOChunked(io, Dict{Any, Any}(kwargs))

write(io::IOChunked, data) = (isempty(data) ? 0 : writeln(io, hex(sizeof(data))) + writeln(io, data))
done(io::IOChunked) = writeln(io, hex(0)) + writeln(io)

type ChunkException <: Exception
    info
end

function size(io::IOChunked, loop=true)
    # read first char
    byte = readbyte(io)

    if byte == '\r'
        byte = readbyte(io)
        byte == '\n' || throw(ChunkException([:keys => ("parse_error", "unexpected_byte"),
                              :msg => "Expected \\n byte after \\r.", :byte => byte]))
        N
    else
        d = UTF8String(append!(BYTE_TYPE[byte], readlinebare(io)))
        # parse hex data
        s = parseint(d, 16)

        if loop
            while s == 0
                # read next block
                s = size(io, false)
            end
        end

        s
    end
end

function data(io::IOChunked, size::Integer)
    d = readbytes(io, size)
    # read CRLF
    readbytes(io, 2)
    # return data
    d
end


function block(io::IOChunked)
    s = size(io)
    if s != N
        data(io, s)
    end
    N
end


type ChunkIterator
    io::IOChunked
end

const iterator = ChunkIterator

Base.start(r::ChunkIterator) = size(r.io)
Base.done(r::ChunkIterator, state) = state == N
Base.next(r::ChunkIterator, state) = begin
    d = data(r.io, state)
    new_state = size(r.io)
    d, new_state
end

end
