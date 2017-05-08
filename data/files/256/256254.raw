export Response,
       start,
       flush,
       done,
       send,
       sent_content_length,
       headers_sent,
       clean,
       getclean,
       data,
       buffered,
       chunk,
       chuncked,
       file,
       content_length,
       content_length!

default_response_headers() = headers([
    ("Server"            , "Julia/$(Base.VERSION) at $NAME/$VERSION"),
    ("Content-Type"      , "text/html; charset=utf-8"),
    ("Date"              , RFC1123_datetime())
])

type ResponseException <: Exception
    info
end

ResponseException(key::Union(STR_TYPE, (STR_TYPE...)), message::STR_TYPE; kwargs...) = begin
    all = append!(Any[(:key, key), (:message, message)], kwargs)
    ResponseException(Dict{Any, Any}(all))
end

type Response
    io::AbstractIOSocket
    status::Integer
    headers::Headers
    data
    finished::Bool
    protocol::Protocol
    _headers_sent::Bool
    writer::Union(N_TYPE,Function)
    buffer::Union(N_TYPE, IO)
    content_length::Integer
    _sent_bytes::Integer
    _headers_size::Integer
end

headers_size(r::Response) = r._headers_size
sent_bytes(r::Response) = r._sent_bytes

const EMPTY_CL = -1

function start_writer(r::Response, data = N)
    if data != N && !chunked(r) && r.content_length <= 0 && r.buffer == N
        content_length(r, sizeof(data))
    end

    start(r)

    if data != N
        Base.write(r, data)
    end
end

Response(io::AbstractIOSocket, protocol::Protocol) = Response(
    io,
    protocol.default_status,
    default_response_headers(),
    N,
    false,
    protocol,
    false,
    start_writer,
    N,
    EMPTY_CL,
    0,
    0
)

chunked(r::Response) = isa(r.io, Chunk.IOChunked)

function chunk(r::Response)
    if chunked(r)
        throw(ResponseException("chunk_enabled",
          "The Response.chunk has be previously enabled."))
    end
    r.io = Chunk.IOChunked(r.io.io; original=r.io)
    r
end

content_length(r::Response, value::Integer = -1) = begin
    if value != -1
        r.content_length = value
    end
    r.content_length
end

content_length!(r::Response, value::Integer) = begin
    if r.content_length == EMPTY_CL
        r.content_length = 0
    end

    r.content_length += value
    r.content_length
end

headers_sent(r::Response) = r._headers_sent

function send_headers(r::Response)
    if headers_sent(r)
        throw(ResponseException("headers_sent", "headers has be sent"))
    end

    r._headers_sent = true

    h_chunk, h_chunk_value = r.protocol.header_msg_chunk

    if content_length(r) != EMPTY_CL
        r.headers[r.protocol.header_msg_size] = str(content_length(r))
    end

    if get(r.headers, h_chunk, "") == h_chunk_value && !chunked(r)
        chunk(r)
    end

    if chunked(r)
        r.headers[h_chunk] = h_chunk_value
    end

    if !(r.status in r.protocol.status_wo_msg) && !chunked(r) && content_length(r) == EMPTY_CL
        r.headers[r.protocol.header_msg_size] = "0"
    end

    if haskey(r.headers, r.protocol.header_msg_size)
        r.content_length = integer(r.headers[r.protocol.header_msg_size])
    end

    r.protocol.prepare_res_headers(r)

    write_data(r, string(r.protocol.name, "/", r.protocol.version,
        " ", r.status, " ",
        r.protocol.status_codes[r.status], CRLF))

    for (header, value) in r.headers
        if isa(value, STR_TYPE)
            write_data(r, string(header, ": ", value, CRLF))
        else
            for v in value
                write_data(r, string(header, ": ", v, CRLF))
            end
        end
    end

    write_data(r, CRLF)
    r._headers_size = r._sent_bytes
end

buffered_writer(r, data) = write(r.buffer, data)

function start(r::Response)
    if r.buffer == N
        send_headers(r)
        r.writer = chunked(r) ? Chunk.write : (
            r.content_length > 0 ? write_data_check: write_data
        )
    else
        r.writer = buffered_writer
    end
end

Base.write(r::Response, data::STR_TYPE) = r.writer(r, data)
Base.write(r::Response, data::Array{Uint8}) = r.writer(r, data)

<<(r::Response, data::STR_TYPE) = r.writer(r, data)
<<(r::Response, data::Array{Uint8}) = r.writer(r, data)

>>(data::STR_TYPE, r::Response) = r.writer(r, data)
>>(data::Array{Uint8}, r::Response) = r.writer(r, data)


Base.flush(r::Response) = begin
    b = takebuf_array(r.buffer)

    if !headers_sent(r)
        if !chunked(r) && r.content_length == EMPTY_CL
            content_length(r, sizeof(b))
        end

        send_headers(r)

        if chunked(r)
            Chunk.write(r, b)
        else
            write_data(r, b)
        end
    elseif chunked(r)
        Chunk.write(r, b)
    else
        write_data_check(r, b)
    end
end

function done(r::Response)
    if !headers_sent(r)
        start_writer(r)
    end

    if r.buffer != N
        flush(r)
    end

    if r.data != N
        data = r.data
        r.data = N

        if isa(data, Union(STR_TYPE, Array{Uint8}))
            write(r, data)
        elseif isiter(data)
            for d in data
                write(r, d)
            end
        else
            throw(ResponseException("data_field", "Invalid Response.data 
                type '$(typeof(data))'"), data=data)
        end
    end

    if chunked(r)
        r._sent_bytes += Chunk.done(r.io)
    end
end

function clean(r::Response)
    r.buffer = IOBuffer()
end

getclean(r::Response) = takebuf_array(r.buffer)

data(r::Response) = r.buffer.data

write_data(r::Response, data) = (s = write(r.io.io, data); r._sent_bytes += s; s)

sent_content_length(r::Response) = r._sent_bytes - r._headers_size

function write_data_check(r::Response, data)
    left = r.content_length - sent_content_length(r)
    size = sizeof(data)

    if left - size < 0
        if left <= StreamReader.DEFAULT_PART_SIZE
            write_data(r, repeat("\0", left))
        else
            # the amount remaining to complete the content size is too large.
            # Let's break it small data blocks.
            # the num_parts > 1, because left > StreamReader.DEFAULT_PART_SIZE
            num_parts, parts_size, last_part_size = StreamReader.calculate(left)
            part_data = repeat("\0", parts_size)

            for i in 1:(num_parts-1) # skip last part
                write_data(r, part_data)
            end

            if last_part_size != parts_size
                write_data(r, part_data[1:last_part_size])
            else
                write_data(r, part_data)
            end
        end

        exceeded = size - left

        # args is (cl, size, exceeded)
        throw(ResponseException("exceeded_content_data",
            "the data size exceeded by $exceeded the total size of the content.";
            content_length=r.content_length, data_size=size, exceeded=exceeded,
            data=data))
    end
    write_data(r, data)
end

function sender(f::Function, r::Response, chunk::Bool = false)
    if chunk
        chunked(r) = true
    end

    start(r)
    f()
    done(r)
end

function buffered(r::Response)
    if r.buffer == N
        r.buffer = IOBuffer()
    end
end

show(io::IO, r::Response) = print(
    io,
    "Response(",
    r.status,
    " ",
    STATUS_CODES[r.status],
    ", ",
    length(r.headers),
    " Headers, ",
    isa(r.data, STR_TYPE) ? "$(sizeof(r.data)), Bytes in Body" : typeof(r.data),
    ")"
)

header(r::Response, key::STR_TYPE, value::STR_TYPE) = header(r.headers, key, value)

"""
Download file on Respose

flags:
  :fdw - Force File Download
"""
function file(r::Response, filename::STR_TYPE, bsize::Integer=0; flags=(), kwargs...)
    finfo = fileinfo(filename)

    if finfo != N
        io = open(filename)
        ext, mime, fsize = finfo
        r.headers["Content-Type"] = mime

        if !chunked(r)
            content_length(r, fsize)
        end

        r.data = StreamReader.IOReaderIterator(io, fsize, bsize; kwargs...)
    else
        r.status = 404
        r.data = "Not Found - file $filename could not be found"
    end
end


Chunk.write(r::Response, data) = r._sent_bytes += Chunk.write(r.io, data)
