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
       rp,
       Reader,
       save,
       content_length,
       loaded_content_length,
       content_type,
       StringReader,
       event,
       event!,
       CloseRequestException,
       init,
       read_info,
       read_headers,
       parse_data

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
    _read_bytes::Integer
    _header_size::Integer
    l::Associative{Any, Any}
    websocket
    _content_length::Integer
    chunk::Bool
    files::Union(N_TYPE,Array{UploadFile})
    _content_type::Union(N_TYPE, STR_TYPE)
end

Request(io::AbstractIOSocket) = Request(
    io, N, N, N, headers(), N, Dict{Union(STR_TYPE,Symbol),Any}(), false,
    N, params(), params(), Events(),
    0, 0, Dict{Any,Any}(), N, 0, false, N, N
)


ready_bytes(r::Request) = r._ready_bytes
header_size(r::Request) = r._header_size
content_length(r::Request) = r._content_length
loaded_content_length(r::Request) = r._content_length - r._read_bytes - r._header_size
content_type(r::Request) = r._content_type

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
    r._read_bytes,
    " Bytes read,",
    r._header_bytes,
    " Header size",
    ")"
)

soma(a::Integer, b::Integer) = (a + b; true)

function soma(a::Integer, b::Integer)
    a + b
    true
end

header(r::Request, key::STR_TYPE, value::STR_TYPE) = header(r.headers, key, value)

Base.read{T}(r::Request, data_type::Type{T}, size::Integer) = begin
    data = Base.read(r.io.io, data_type, size)
    r._read_bytes += size
    data
end

Base.read(r::Request, size::Integer) = Base.read(r, BYTE_TYPE, size)

Base.readuntil(r::Request, delim) = begin
    data = Base.readuntil(r.io.io, delim)
    r._read_bytes += sizeof(data)
    data
end

Base.readline(r::Request) = readline(r.io)

using StreamReader

function Reader{T,D}(r::Request, bp::PartsIterator; read_type::Type{T} = BYTE_TYPE,
    data_type::Type{D} = N_TYPE, pre_start::Union(N_TYPE,Function) = N,
    kwargs...)
    ReaderIterator(bp; kwargs...) do ri
        ri.read = (size) -> Base.read(r, read_type, size)

        if data_type != N_TYPE
            set_data_type(ri, data_type)
        end

        if pre_start != N
            pre_start(ri)
        end
    end
end

Reader(r::Request, len::Integer, bsize::Integer=0; kwargs...) = Reader(r,
    PartsIterator(len, bsize); kwargs...)

function save(r::Request, out::IO, len::Integer, bsize::Integer=0;
    cb::Function = empty_fn, kwargs...)
    r = Reader(r, len, bsize; kwargs...)
    for data in
        cb(r)
        Base.write(out, data)
    end
end

save(r::Request, out::IO, bsize::Integer=0; kwargs...) = save(r, out, r._content_length, bsize; kwargs...)

>>(i::ReaderIterator, o::IO) = begin
    for data in i
        Base.write(o, data)
    end
end

function StringReader{D<:STR_TYPE}(r::Request, pi::PartsIterator;
    data_type::Type{D} = UTF8String, kwargs...)
    Reader(io, pi; data_type=data_type, kwargs...)
end

StringReader(r::Request, len::Integer, bsize::Integer=0; kwargs...) = StringReader(io,
    StreamReader.PartsIterator(len, bsize); kwargs...)


body(req::Request) = read(req, req._content_length)
bodys(req::Request) =  bytestring(body(req))

function read_first_line(io::AbstractIOSocket)
    line = readline_bare_str(io)
    s = sizeof(line) + 2
    
    if line == ""
        throw(RequestException("invalid_header", "Empty first line."; line_size=s, line=line))
    end

    s, line
end

function read_headers(io::AbstractIOSocket, lnum::Integer=0; h::Headers=headers())
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


function read_headers(r::Request)
    s, lines, r.headers = read_headers(r.io)
    r._read_bytes += s
    r._header_size = s

    cl = get(r.headers, r.protocol.header_msg_size, N)

    if cl != N
        r._content_length = parseint(cl)
    end

    ct = get(r.headers, r.protocol.header_msg_type, N)

    if ct != N
        r._content_type = ct
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
function parse_info(line::STR_TYPE, default_protocol::Union(N_TYPE, (STR_TYPE, STR_TYPE))=N)
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

function read_info(io::AbstractIOSocket, protocols::Protocols,
    default_protocol::Union(N_TYPE, (STR_TYPE, STR_TYPE))=N)
    line = readline_bare_str(io)
    s = sizeof(line) + 2

    if line == "quit"
        throw(CloseRequestException("close command recieved."))
    end

    method, resource, protoc = parse_info(line, default_protocol)
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

function read_info(r::Request, protocols::Protocols,
    default_protocol::Union(N_TYPE, (STR_TYPE, STR_TYPE))=N)
    (r._read_bytes, r.method, r.resource, r.protocol, r.query) = read_info(r.io,
        protocols, default_protocol)
    r
end


function init(r::Request, protocols, default_protocol::Union(Protocol, N_TYPE)=N)
    read_info(r, protocols, default_protocol != N? key(default_protocol) : N)
    read_headers(r)

    if r.query != N
        r.get = parse_qsr(r.query)
    end

    r.protocol.req_post_init(r)

    res = Response(r.io, r.protocol)
    res.protocol.res_post_init(res)

    trigger(r, Event("post_init"; args=(r, res)))

    r, res
end


function parse_data(r::Request)
    if r._content_type != N
        ct = r._content_type
        if search(ct, "application/x-www-form-urlencoded").start > 0
            r.post = parse_qsr(bodys(r))
        elseif search(ct, "application/json").start > 0
            r.post = JSON.parse(bodys(r))
        elseif search(ct, "multipart/form-data").start > 0
            parse_multipart_formdata(r)
        end
        return true
    end
    false
end


param(r::Request, key::STR_TYPE, default=N) = (haskey(r.get, key) ? 
    r.get[key] : (haskey(r.post, key) ? r.post[key] : default))

function multipart_boundary(content_type::STR_TYPE)
    d = content_type
    b_pos = search(d, "boundary=")
    e_pos = search(d, "; ", b_pos.stop)
    pose = e_pos.start > 0 ? e_pos.start - 1: sizeof(d)
    boundary = d[b_pos.stop+1:pose]
    boundary = string("--", boundary)
    boundary, string(boundary, "--")
end

function parse_content_disposition(s::STR_TYPE)
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

function boundary_writer(io::AbstractIOSocket, boundaryd::BoundaryTuple)
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

function parse_multipart_formdata_part(io::AbstractIOSocket, boundaryd::BoundaryTuple, encoding::STR_TYPE, d, files)
   s, lnum, h = read_headers(io; h=Dict{STR_TYPE, STR_TYPE}())
   stop = true

   if length(h) > 0
        disposition, name, filename = parse_content_disposition(h["Content-Disposition"])

        if !haskey(d, name)
            values = d[name] = {}
        else
            values = d[name]
        end

        if haskey(h, "Content-Type")
            ls, stop, mio = boundary_writer(io, boundaryd)
            s += ls
            value = UploadFile(filename, h["Content-Type"], sizeof(mio.data), mio; headers=h)
            push!(files, value)
            push!(values, value)
        else
            ls, stop, mio = boundary_writer(io, boundaryd)
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


function parse_multipart_formdata(io::AbstractIOSocket, boundary::(STR_TYPE, STR_TYPE), encoding::STR_TYPE="")
    # read boundary on first content line
    line = readline_bare(io)
    s = sizeof(line) + 2
    line == boundary[1].data || throw(RequestException("parse_multipart",
        "Expected boundary data.", (s, [:boundary => boundary[1], :line => line])))

    d = params()
    files = UploadFile[]
    boundaryd = tuple(Array{BYTE_TYPE}[(_ * CRLF).data for _ in boundary]...)
    stop = false

    while !stop
        ls, stop = parse_multipart_formdata_part(io, boundaryd, encoding, d, files)
        s += ls
    end

    s, d, files
end

function parse_multipart_formdata(r::Request)
    io = IOBuffer()
    # read all content into BUFFER
    write(io, body(r))
    seekstart(io)
    boundary = S.multipart_boundary(r.headers["Content-Type"])
    encoding = ""
    s, r.p, r.files = S.parse_multipart_formdata(IOSocket(io), boundary, encoding)
    # discard read size...
    r.p, r.files # dict of parameters, files list
end