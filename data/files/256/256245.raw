# HTTP request
#
# - method   => valid HTTP method string (e.g. "GET")
# - resource => requested resource (e.g. "/hello/world")
# - headers  => HTTP headers
# - data     => request data
# - state    => used to store various data during request processing
# - sock      => The socket
#

export Request,
       Reader,
       save,
       loadedcl,
       leftcl,
       StringReader,
       event,
       event!,
       CloseRequestException,
       init,
       readinfo,
       readheaders,
       parsedata,
       param,
       body,
       bodes

using JSON

type UploadFile
    name::STR_TYPE
    content_type::STR_TYPE
    size::Integer
    io::IO
    path::STR_TYPE
    headers::Associative{STR_TYPE, STR_TYPE}
end

UploadFile(n::STR_TYPE, c::STR_TYPE, s::Integer, io::IO; headers=Dict{STR_TYPE,STR_TYPE}()) = UploadFile(n, c, s, io, "", headers)


type RequestException <: Exception
    info
end

RequestException(key::Union(STR_TYPE, (STR_TYPE...)), message::STR_TYPE; kwargs...) = begin
    all = append!(Any[(:key, key), (:message, message)], kwargs)
    RequestException(Dict{Any, Any}(all))
end

type Request
    io::AbstractIOSocket
    protocol::Union(N_TYPE,Protocol)
    method::Union(N_TYPE,STR_TYPE)
    resource::Union(N_TYPE,STR_TYPE)
    headers::Headers
    data::Union(N_TYPE,STR_TYPE)
    env::Associative{Union(STR_TYPE,Symbol), Any}
    finished::Bool
    query::Union(N_TYPE,STR_TYPE)
    get::Associative{STR_TYPE, Any}
    post::Associative{STR_TYPE, Any}
    events::Events
    read_bytes::Integer
    header_size::Integer
    l::Associative{Any, Any}
    websocket
    content_length::Integer
    chunk::Bool
    files::Union(N_TYPE,Array{UploadFile})
    content_type::Union(N_TYPE, STR_TYPE)
end

Request(io::AbstractIOSocket) = Request(
    io, N, N, N, headers(), N, Dict{Union(STR_TYPE,Symbol),Any}(), false,
    N, params(), params(), Events(),
    0, 0, Dict{Any,Any}(), N, 0, false, N, N
)

"""
Return number of loaded bytes of content length
"""
loadedcl(r::Request) = r.read_bytes - r.header_size

"""
Return left loaded bytes of content length
"""
leftcl(r::Request) = r.content_length - loadedcl(r)

trigger(r::Request, e::Event) = trigger(r.events, e, r)
listener(r::Request, key::Union(Symbol,STR_TYPE), cb::Function) = listener(r.events, key, cb)

show(io::IO, r::Request) = print(
    io,
    "Request(",
    r.method,
    " ",
    r.resource,
    ", ",
    length(r.headers),
    " Headers, ",
    length(r.env),
    " Enviroment, ",
    isa(r.data, STR_TYPE) ? "$(sizeof(r.data)) Bytes in Body" : r.data,
    ", ",
    r.query,
    " Query STR_TYPE,",
    r.read_bytes,
    " Bytes read,",
    r.header_bytes,
    " Header size",
    ")"
)

soma(a::Integer, b::Integer) = (a + b; true)

function soma(a::Integer, b::Integer)
    a + b
    true
end

header(r::Request, key::STR_TYPE, value::STR_TYPE) = header(r.headers, key, value)

Base.read{T}(r::Request, datatype::Type{T}, size::Integer) = begin
    data = Base.read(r.io.io, datatype, size)
    r.read_bytes += size
    data
end

Base.read(r::Request, size::Integer) = Base.read(r, BYTE_TYPE, size)

Base.readuntil(r::Request, delim) = begin
    data = Base.readuntil(r.io.io, delim)
    r.read_bytes += sizeof(data)
    data
end

Base.readline(r::Request) = readline(r.io)

using StreamReader

function Reader{T,D}(r::Request, bp::PartsIterator; read_type::Type{T} = BYTE_TYPE,
    datatype::Type{D} = N_TYPE, prestart::Union(N_TYPE,Function) = N,
    kwargs...)
    ReaderIterator(bp; kwargs...) do ri
        ri.read = (size) -> Base.read(r, read_type, size)

        if datatype != N_TYPE
            setdatatype(ri, datatype)
        end

        if prestart != N
            prestart(ri)
        end
    end
end

Reader(r::Request, len::Integer, bsize::Integer=0; kwargs...) = Reader(r,
    PartsIterator(len, bsize); kwargs...)

function save(r::Request, out::IO, len::Integer, bsize::Integer=0;
    cb::Function = emptyfn, kwargs...)
    r = Reader(r, len, bsize; kwargs...)
    for data in
        cb(r)
        Base.write(out, data)
    end
end

save(r::Request, out::IO, bsize::Integer=0; kwargs...) = save(r, out, r.content_length, bsize; kwargs...)

>>(i::ReaderIterator, o::IO) = begin
    for data in i
        Base.write(o, data)
    end
end

function StringReader{D<:STR_TYPE}(r::Request, pi::PartsIterator;
    datatype::Type{D} = UTF8String, kwargs...)
    Reader(io, pi; datatype=datatype, kwargs...)
end

StringReader(r::Request, len::Integer, bsize::Integer=0; kwargs...) = StringReader(io,
    StreamReader.PartsIterator(len, bsize); kwargs...)


body(req::Request) = read(req, req.content_length)
bodys(req::Request) =  bytestring(body(req))

function readfirstline(io::AbstractIOSocket)
    line = readlinebarestr(io)
    s = sizeof(line) + 2
    
    if line == ""
        throw(RequestException("invalid_header", "Empty first line."; line_size=s, line=line))
    end

    s, line
end

function readheaders(io::AbstractIOSocket, lnum::Integer=0; h::Headers=headers())
    s = Integer[0]

    lnum += eachline(io, :s!) do itr, line
        s[1] += sizeof(line) + 2 # + CRLF

        if isempty(line)
            # end headers
            stop()
        end

        parts = split(line, ": ", 2)

        if length(parts) != 2
            throw(RequestException(("invalid_header", "invalid_format"), "Header " *
                repr(line) * ", in line " * string(linum+iter.count) *
                ", not contains a valid format."; ready_bytes=s, line_number=(lnum + itr.count), line=line, line_size=ls))
        end

        key, value = parts
        header(h, key, value)
    end

    s[1], lnum, h
end


function readheaders(r::Request)
    s, lines, r.headers = readheaders(r.io)
    r.read_bytes += s
    r.header_size = s

    cl = get(r.headers, r.protocol.header_msg_size, N)

    if cl != N
        r.content_length = parseint(cl)
    end

    ct = get(r.headers, r.protocol.header_msg_type, N)

    if ct != N
        r.content_type = ct
    end

    r
end

type CloseRequestException <: Exception
    info
end


"""Parse HTTP info on first line:

    METHOD RESOURCE PROTOCOL/PROTOCOL_VERSION

Example:

    GET /index.html
    GET /index.html HTTP/1.1
    GET /directory%20name/file.txt HTTP/1.1
"""
function parseinfo(line::STR_TYPE, default_protocol::Union(N_TYPE, (STR_TYPE, STR_TYPE))=N)
    parts = split(line, " ")
    method = resource = protocol = N

    if length(parts) < 2 || length(parts) > 3
        throw(RequestException(("invalid_header_info", "invalid_format"), "Header " *
            repr(line) * ", not contains a valid format."; line=line))
    elseif length(parts) == 2
        if default_protocol == N
            throw(RequestException(("invalid_header_info", "protocol_not_informed"),
                "Protocol isn't informed."; line=line))
        else
            protocol = default_protocol
            method, resource = parts
        end
    else
        method, resource, protocol = parts
        parts = split(protocol, "/")

        if length(parts) != 2
            throw(RequestException(("invalid_header_info", "invalid_protocol_format"), "Invalid PROTOCOL format " *
                repr(protocol) * "."; protocol=protocol))
        end

        protocol = parts
    end

    method, resource, protocol
end

function readinfo(io::AbstractIOSocket, protocols::Protocols,
    default_protocol::Union(N_TYPE, (STR_TYPE, STR_TYPE))=N)
    line = readlinebarestr(io)
    s = sizeof(line) + 2

    if line == "quit"
        throw(CloseRequestException("close command recieved."))
    end

    method, resource, protoc = parseinfo(line, default_protocol)
    query = ""

    if resource[1] == '/' # is path
        # get query string
        query_pos = search(resource, '?')

        if query_pos > 0
            query = resource[query_pos+1:end]
            resource = resource[1:query_pos-1]
        end
    end

    if protoc != N
        protoc = protocol(protocols, tuple(protoc...))
    end

    (s, method, resource, protoc, query)
end

function readinfo(r::Request, protocols::Protocols,
    default_protocol::Union(N_TYPE, (STR_TYPE, STR_TYPE))=N)
    (r.read_bytes, r.method, r.resource, r.protocol, r.query) = readinfo(r.io,
        protocols, default_protocol)
    r
end


function init(r::Request, protocols, default_protocol::Union(Protocol, N_TYPE)=N)
    readinfo(r, protocols, default_protocol != N? key(default_protocol) : N)
    readheaders(r)

    if r.query != N
        r.get = parseqsr(r.query)
    end

    r.protocol.req_post_init(r)

    res = Response(r.io, r.protocol)
    res.protocol.res_post_init(res)

    trigger(r, Event("post_init"; args=(r, res)))

    r, res
end

"""
Parse content data if content-type is "application/x-www-form-urlencoded",
"application/json" or "multipart/form-data". If parsed, return ``true``,
otherwise, ``false``.
"""
function parsedata(r::Request)
    if r.content_type != N
        ct = r.content_type
        if search(ct, "application/x-www-form-urlencoded").start > 0
            r.post = parseqsr(bodys(r))
        elseif search(ct, "application/json").start > 0
            r.post = JSON.parse(bodys(r))
        elseif search(ct, "multipart/form-data").start > 0
            parsempfd(r)
        end
        return true
    end
    false
end

"""
Return a request param. If ``key`` exists in ``Request.get``, return it, otherwise
``key`` exists in ``Request.post``, return it, otherwise, return ``default``.
For default, value of ``default`` is ``N``.
"""
param(r::Request, key::STR_TYPE, default=N) = (haskey(r.get, key) ? 
    r.get[key] : (haskey(r.post, key) ? r.post[key] : default))

"""
Extract multipart boundary of content type.
Returns tuple of ``(boundary, eof_boundary)``.


Example:


.. doctest::

    julia> multipartboundary("multipart/form-data; boundary=AxdFtg1")
    ("AxdFtg1", "AxdFtg1--")

"""
function multipartboundary(content_type::STR_TYPE)
    d = content_type
    b_pos = search(d, "boundary=")
    e_pos = search(d, "; ", b_pos.stop)
    pose = e_pos.start > 0 ? e_pos.start - 1: sizeof(d)
    boundary = d[b_pos.stop+1:pose]
    boundary = string("--", boundary)
    boundary, string(boundary, "--")
end

function parsecontentdisposition(s::STR_TYPE)
    d = Dict{STR_TYPE, STR_TYPE}
    disposition, s = split(s, ";", 2)

    name_p = search(s, " name=\"")
    name_end = search(s, "; ", name_p.stop)

    if name_end.start == 0
        name = s[name_p.stop+1:end-1]
    else
        name = s[name_p.stop+1:name_end.start-2]
    end

    filename = ""

    fname_p = search(s, " filename=\"")

    if fname_p.start > 0
        fname_end = search(s, "; ", fname_p.stop)
        if fname_end.start == 0
            filename = s[fname_p.stop+1:end-1]
        else
            filename = s[fname_p.stop+1:fname_end.start-2]
        end
    end

    disposition, name, filename
end


typealias BoundaryTuple (Array{BYTE_TYPE}, Array{BYTE_TYPE})

function boundarywriter(io::AbstractIOSocket, boundaryd::BoundaryTuple)
    oio = IOBuffer()
    prev_line = BYTE_TYPE[]
    stop = false
    s = 0

    while true
        next_line = readline(io)
        s += sizeof(next_line)

        if next_line == boundaryd[1]
            # write previous line without CRLF
            write(oio, prev_line[1:end-2])
            # stop
            break
        elseif next_line == boundaryd[2]
            # write previous line without CRLF
            write(oio, prev_line[1:end-2])
            stop = true
            # stop
            break
        end

        write(oio, prev_line)
        prev_line = next_line
    end

    seekstart(oio)
    s, stop, oio
end

function parsempfdpart(io::AbstractIOSocket, boundaryd::BoundaryTuple, encoding::STR_TYPE, d, files)
   s, lnum, h = readheaders(io; h=Dict{STR_TYPE, STR_TYPE}())
   stop = true

   if length(h) > 0
        disposition, name, filename = parsecontentdisposition(h["Content-Disposition"])

        if !haskey(d, name)
            values = d[name] = {}
        else
            values = d[name]
        end

        if haskey(h, "Content-Type")
            ls, stop, mio = boundarywriter(io, boundaryd)
            s += ls
            value = UploadFile(filename, h["Content-Type"], sizeof(mio.data), mio; headers=h)
            push!(files, value)
            push!(values, value)
        else
            ls, stop, mio = boundarywriter(io, boundaryd)
            s += ls
            value = takebuf_array(mio)

            if !isempty(encoding)
                value = decode(value, encoding)
            end

            push!(values, value)
        end
    end

    s, stop
end


function parsempfd(io::AbstractIOSocket, boundary::(STR_TYPE, STR_TYPE), encoding::STR_TYPE="")
    # read boundary on first content line
    line = readlinebare(io)
    s = sizeof(line) + 2
    line == boundary[1].data || throw(RequestException("parse_multipart",
        "Expected boundary data.", (s, [:boundary => boundary[1], :line => line])))

    d = params()
    files = UploadFile[]
    boundaryd = tuple(Array{BYTE_TYPE}[(_ * CRLF).data for _ in boundary]...)
    stop = false

    while !stop
        ls, stop = parsempfdpart(io, boundaryd, encoding, d, files)
        s += ls
    end

    s, d, files
end

"""
Parse multipart form data content into ``Request.post`` and ``Request.files``.
"""
function parsempfd!(r::Request)
    # the temporary
    io = IOBuffer()
    # read all content into BUFFER
    write(io, body(r))
    seekstart(io)

    parse = (io) -> begin
        boundary = S.multipartboundary(r.headers["Content-Type"])
        encoding = ""
        s, r.post, r.files = S.parsempfd(IOSocket(io), boundary, encoding)
        # discard read size...
        r.post, r.files # dict of parameters, files list
    end

    parse(io)
end
