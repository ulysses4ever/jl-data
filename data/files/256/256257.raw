export Response,
       start,
       flush,
       done,
       send,
       sentcl,
       headerssent,
       clean,
       getclean,
       data,
       buffered,
       chunk,
       chuncked,
       file

defaultresponseheaders() = headers([
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
    headers_sent::Bool
    writer::Union(N_TYPE,Function)
    buffer::Union(N_TYPE, IO)
    content_length::Integer
    sent_bytes::Integer
    headers_size::Integer
end

const EMPTY_CL = -1

function startwriter(r::Response, data = N)
    if data != N && !chunked(r) && r.content_length <= 0 && r.buffer == N
        r.content_length = sizeof(data)
    end

    start(r)

    if data != N
        Base.write(r, data)
    end
end

Response(io::AbstractIOSocket, protocol::Protocol) = Response(
    io,
    protocol.default_status.default,
    defaultresponseheaders(),
    N,
    false,
    protocol,
    false,
    startwriter,
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

function sendheaders(r::Response)
    if r.headers_sent
        throw(ResponseException("headers_sent", "headers has be sent"))
    end

    r.headers_sent = true

    h_chunk, h_chunk_value = r.protocol.header_msg_chunk

    if r.content_length != EMPTY_CL
        r.headers[r.protocol.header_msg_size] = str(r.content_length)
    end

    if get(r.headers, h_chunk, "") == h_chunk_value && !chunked(r)
        chunk(r)
    end

    if chunked(r)
        r.headers[h_chunk] = h_chunk_value
    end

    if !(r.status in r.protocol.status_wo_msg) && !chunked(r) && r.content_length == EMPTY_CL
        r.headers[r.protocol.header_msg_size] = "0"
    end

    if haskey(r.headers, r.protocol.header_msg_size)
        r.content_length = integer(r.headers[r.protocol.header_msg_size])
    end

    r.protocol.prepare_res_headers(r)

    writedata(r, string(r.protocol.name, "/", r.protocol.version,
        " ", r.status, " ",
        r.protocol.status_codes[r.status], CRLF))

    for (header, value) in r.headers
        if isa(value, STR_TYPE)
            writedata(r, string(header, ": ", value, CRLF))
        else
            for v in value
                writedata(r, string(header, ": ", v, CRLF))
            end
        end
    end

    writedata(r, CRLF)
    r.headers_size = r.sent_bytes
end

bufferedwriter(r, data) = write(r.buffer, data)

function start(r::Response)
    if r.buffer == N
        sendheaders(r)
        r.writer = chunked(r) ? Chunk.write : (
            r.content_length > 0 ? writedatacheck: writedata
        )
    else
        r.writer = bufferedwriter
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

    if !r.headers_sent
        if !chunked(r) && r.content_length == EMPTY_CL
            r.content_length = sizeof(b)
        end

        sendheaders(r)

        if chunked(r)
            Chunk.write(r, b)
        else
            writedata(r, b)
        end
    elseif chunked(r)
        Chunk.write(r, b)
    else
        writedatacheck(r, b)
    end
end

function done(r::Response)
    if !r.headers_sent
        startwriter(r)
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
        r.sent_bytes += Chunk.done(r.io)
    end
end

clean(r::Response) = (buffer = IOBuffer())
getclean(r::Response) = takebufarray(r.buffer)
data(r::Response) = r.buffer.data
writedata(r::Response, data) = (s = write(r.io.io, data); r.sent_bytes += s; s)
sentcl(r::Response) = r.sent_bytes - r.headers_size

function writedatacheck(r::Response, data)
    left = r.content_length - sentcl(r)
    size = sizeof(data)

    if left - size < 0
        if left <= StreamReader.DEFAULT_PART_SIZE
            writedata(r, repeat("\0", left))
        else
            # the amount remaining to complete the content size is too large.
            # Let's break it small data blocks.
            # the num_parts > 1, because left > StreamReader.DEFAULT_PART_SIZE
            num_parts, parts_size, last_part_size = StreamReader.calculate(left)
            part_data = repeat("\0", parts_size)

            for i in 1:(num_parts-1) # skip last part
                writedata(r, part_data)
            end

            if last_part_size != parts_size
                writedata(r, part_data[1:last_part_size])
            else
                writedata(r, part_data)
            end
        end

        exceeded = size - left

        # args is (cl, size, exceeded)
        throw(ResponseException("exceeded_content_data",
            "the data size exceeded by $exceeded the total size of the content.";
            content_length=r.content_length, data_size=size, exceeded=exceeded,
            data=data))
    end
    writedata(r, data)
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
function file(r::Response, filename::STR_TYPE, bsize::Integer=0; download::Bool=false, dfilename::STR_TYPE="", kwargs...)
    finfo = fileinfo(filename)

    if finfo != N
        io = open(filename)
        ext, mime, fsize = finfo
        r.headers["Content-Type"] = mime

        if download
            if isempty(dfilename)
                dfilename = basename(filename)
            end
            r.headers["Content-Disposition"] = "attachment; filename=\"$dfilename\"";
        end

        if !chunked(r)
            r.content_length = fsize
        end

        r.data = StreamReader.IOReaderIterator(io, fsize, bsize; kwargs...)
    else
        r.status = r.protocol.default_status.not_found
        r.data = "Not Found - file $filename could not be found"
    end
end


Chunk.write(r::Response, data) = (r.sent_bytes += Chunk.write(r.io, data))
