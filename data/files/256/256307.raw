# HttpServer module
#
# Serve HTTP requests in Julia.
#
module SimpleHttpCommon

if VERSION < v"0.4.0-dev"
    using Docile
    eval(:(@docstrings(manual = ["../README.md"])))
end

import DataStructures: OrderedDict
import Base: readbytes,
             readline,
             readuntil
using HttpCommon: STATUS_CODES,
       GET,
       POST,
       PUT,
       UPDATE,
       DELETE,
       OPTIONS,
       HEAD,
       RFC1123_datetime,
       HttpMethodBitmask,
       HttpMethodBitmasks,
       HttpMethodNameToBitmask,
       HttpMethodBitmaskToName,
       escapeHTML,
       encodeURI,
       decodeURI,
       mimetypes

export STATUS_CODES,
       GET,
       POST,
       PUT,
       UPDATE,
       DELETE,
       OPTIONS,
       HEAD,
       RFC1123_datetime,
       HttpMethodBitmask,
       HttpMethodBitmasks,
       HttpMethodNameToBitmask,
       HttpMethodBitmaskToName,
       escapeHTML,
       encodeURI,
       decodeURI,
       parse_qs,
       parse_qsr,
       mimetypes,
       Request,
       Response,
       RequestData,
       ResponseData,
       Headers,
       new_headers,
       default_headers,
       Protocol,
       event,
       Iterable,
       readuntil,
       readline,
       readybytes,
       write_chunk,
       read_http_headers,
       parse_http_headers,
       CloseClientException,
       body,
       bodys,
       BytesReaderIterator,
       BytesFileIterator,
       LimitedBytesFileIterator

typealias Headers OrderedDict{String,String}

new_headers(args...) =  OrderedDict{String,String}(args...)

default_headers() = new_headers([
    ("Server"            , "Julia/$VERSION"),
    ("Content-Type"      , "text/html; charset=utf-8"),
    ("Content-Language"  , "en"),
    ("Date"              , RFC1123_datetime())
])


# HTTP request
#
# - method   => valid HTTP method string (e.g. "GET")
# - resource => requested resource (e.g. "/hello/world")
# - headers  => HTTP headers
# - data     => request data
# - state    => used to store various data during request processing
# - sock      => The socket
#
typealias RequestData Union(Nothing,String)
typealias PVersion Union(Nothing, VersionNumber)


immutable type Protocol
    name::String
    version::PVersion

    Protocol(name, version) = new(name, version)
    Protocol(name) = Protocol(name, nothing)
end

typealias NothingOrProtocol Union(Nothing,Protocol)

type Request
    method::String
    resource::String
    protocol::NothingOrProtocol
    headers::Headers
    data::RequestData
    sock
    env::Associative{String, Any}
    finished::Bool
    query::String
    q::Associative{String, Any}
    p::Associative{String, Any}
    events::Dict{String, Function}
    ready_bytes::Int
    header_bytes::Int
    l::Associative{Any, Any}
    websocket

    Request(m::String, r::String, pr::NothingOrProtocol, h::Headers, d::RequestData, s,
            e::Associative{String, Any}, f::Bool, qr::String, q::Associative{String, Any},
            p::Associative{String, Any}, evs::Dict{String, Function}) = new(
        m, r, pr, h, d, s, e, f, qr, q, p, evs, 0, 0, Dict{Any,Any}(), nothing)
    Request(m::String, r::String, pr::Protocol, h::Headers, d::RequestData, s,
            e::Associative{String, Any}, f::Bool, qr::String, q::Associative{String, Any},
            p::Associative{String, Any}) = Request(
        m, r, pr, h, d, s, e, f, qr, q, p, Dict{String, Function}())
    Request(s, e::Dict{String, Function}) = Request("", "", nothing, new_headers(), nothing, s, Dict{String,Any}(), false, "", Dict{String,Any}(), Dict{String,Any}(), e)
    Request(s) = Request(s, Dict{String, Function}())
    Request() = Request(nothing)
end


function event(req::Request, event::String, args...)
    haskey(req.events, event) && req.events[event](args...)
end

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
    isa(r.data, String) ? "$(sizeof(r.data)) Bytes in Body" : r.data,
    ", ",
    r.query,
    " Query String,",
    r.read_bytes,
    " Bytes read,",
    r.header_bytes,
    " Header size",
    ")"
)

function r(r::Request, key::String, default=Nothing)
    try
        return r.p[key]
    catch e
        try
            return r.q[key]
        catch e
            if default != Nothing
                return default
            else
                throw(KeyError(key))
            end
        end
    end
end

# HTTP response
#
# - status   => HTTP status code (see: `STATUS_CODES`)
# - headers  => HTTP headers
# - data     => response data
# - finished => indicates that a Response is "valid" and can be converted to an
#               actual HTTP response
#
# If a Response is instantiated with all of these attributes except for
# `finished`, `finished` will default to `false`.
#
# A Response can also be instantiated with an HTTP status code, in which case
# sane defaults will be set:
#
#     Response(200)
#     # => Response(200, "OK", ["Server" => "v\"0.2.0-740.r6df6\""], "200 OK", false)
#
#     function chuncked()
#         produce("1")
#         produce("2")
#         produce("3")
#     end
#
#     Response(chunched)
#     # => Response(200, chuncked, ["Server" => "v\"0.2.0-740.r6df6\""], "200 OK", false)
#

type Iterable
    data::Any
end

Base.start(it::Iterable) = Base.start(it.data)
Base.done(it::Iterable, state) = Base.done(it.data)
Base.next(it::Iterable, state) = Base.next(it.data)

typealias ResponseData Union(String, Array{Uint8}, Task, Iterable, Function)
typealias NothingOrFunction Union(Nothing, Function)
typealias NothingOrRequest Union(Nothing, Request)

type Response
    req::NothingOrRequest
    status::Int
    headers::Headers
    data::ResponseData
    finished::Bool

    Response(r::NothingOrRequest, s::Int, h::Headers, d::ResponseData, f::Bool) = new(r, s, h, d, f)
    Response(s::Int, h::Headers, d::ResponseData, f::Bool) = Response(nothing, s, h, d, f)
    Response(s::Int, h::Headers, d::ResponseData) = Response(s, h, d, false)
    Response(s::Int, h::Headers) = Response(s, h, "")
    Response(s::Int, d::ResponseData) = Response(s, default_headers(), d)
    Response(s::Int) = Response(s, "")
    Response(d::ResponseData) = Response(200, d)
    Response() = Response(200)
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
    isa(r.data, String) ? "$(sizeof(r.data)), Bytes in Body" : r.data,
    ")"
)

function readybytes(req::Request, size::Integer)
    data = Base.readbytes(req.sock, size)
    req.ready_bytes += size
end

function readybytes(req::Request, cb::Function; size=0, buffer=1)
    total = 0

    if size > 0
        total = buffer

        if total > size
            total = size
        end

        while total <= size
            total += buffer
            cb(readybytes(req, buffer))
        end
    else
        while true
            total += buffer
            cb(readybytes(req, buffer))
        end
    end
    total
end

type BytesReaderIterator
    ready::Function
    size::Integer
    buffer::Integer
    ready_size::Integer

    BytesReaderIterator(r::Function, s::Integer, b::Integer) = new(r, s, b > s ? s : b, 0)
    BytesReaderIterator(io::IO, s::Integer, b::Integer) = begin
        BytesReaderIterator(s, b) do size
            Base.readbytes(io, size)
        end
    end
end

Base.start(reader::BytesReaderIterator) = reader.buffer
Base.done(reader::BytesReaderIterator, state) = (state == 0)
Base.next(reader::BytesReaderIterator, state) = begin
    d = reader.ready(state)
    reader.ready_size += state
    new_state = (reader.ready_size + reader.buffer) > reader.size ? (reader.size - reader.ready_size) : reader.buffer
    d, new_state
end

type BytesFileIterator
    io::IO
    buffer::Integer

    BytesFileIterator(io::IO, buffer::Integer=1024) = new(io, buffer)
end

Base.start(it::BytesFileIterator) = it.buffer
Base.done(it::BytesFileIterator, state) = eof(it.io)
Base.next(it::BytesFileIterator, state) = begin
    d = Base.readbytes(it.io, state)
    d, state
end

type LimitedBytesFileIterator
    io::IO
    size::Integer
    buffer::Integer
    ready_size::Integer

    LimitedBytesFileIterator(io::IO, size::Integer, buffer::Integer=1024) = new(io, size, buffer, 0)
end

Base.start(it::LimitedBytesFileIterator) = it.buffer
Base.done(it::LimitedBytesFileIterator, state) = (state == 0)
Base.next(it::LimitedBytesFileIterator, state) = begin
    d = Base.readbytes(it.io, state)
    it.ready_size += state
    new_state = (it.ready_size + it.buffer) > it.size ? (it.size - it.ready_size) : it.buffer
    d, new_state
end

readybytes_it(req::Request, size=0, buffer=1024) = begin
    BytesReaderIterator(size, buffer) do size
      readybytes(req, size)
    end
end

function readybytes(req::Request, size::Integer)
    data = Base.readybytes(req.sock, size)
    req.ready_bytes += sizeof(data)
    data
end

function readuntil{T}(req::Request, delim::T)
    data = Base.readuntil(req.sock, delim)
    req.ready_bytes += sizeof(data)
    data
end

function readline(req::Request)
    data = Base.readline(req.sock)
    req.ready_bytes += sizeof(data)
    data
end

readline_s(req::Request) = bytestring(readline(req))

function body(req::Request)
    cl = parseint(req.headers["Content-Length"])
    readybytes(req, cl)
end

bodys(req::Request) =  bytestring(body(req))


type UploadFile
    tmp_path::String
    io::IO
    name::String
    content_type::String
    size::Int

    UploadFile(t::String, i::IO, n::String, ct::String, s::Integer) = new (t, i, n, ct, s)
    UploadFile(t::String, i::IO, n::String, ct::String) = UploadFile(t, i, n, ct, 0)
end


#function parse_multi_party(req::Request)
#    ct = req.headers["Content-Type"]
#    boundary = search(ct, "boundary=")
#    if boundary.start > 0
#        boundaryend = search(ct, ";", boundary.start)
#        if boundaryend.end > -1
#            boundary = ct[boundary.start+9:boundaryend]
#        else
#            boundary = ct[boundary.start+9:end]
#        end
#    else
#        throw(HTTPParserHeaderException("Invalid Boundary"))
#    end
#
#    invalid_line = () -> throw(HTTPParserHeaderException("Invalid Line"))
#
#    cl = parseint(req.headers["Content-Length"])
#    rb = 0
#
#    d = Dict{String, Any}()
#
#    rboundary = () -> begin
#      line = readline_s(req)
#      rb += sizeof(line)
#
#      if line[1:end-2] != boundary
#        invalid_line()
#      end
#    end
#
#    rboundary()
#
#    while rb < cl
#      line = readline_s(req)
#      content_disposition = line[22:end-2] # skip Content-Disposition and remove CRLF
#      parts = content_disposition.split("; ")
#      if parts[1] != "form-data"
#        invalid_line()
#      end
#      ld = Dict{String,String}()
#      l_name = ""
#
#      for p in parts[2:end]
#        p_name, p_value = split(p, "=")
#        p_value = p_value[2:end-2] # remove quotes
#
#        if p_name == "name"
#          l_name = p_name
#        else
#          ld[p_name] = p_value
#        end
#      end
#
#      if haskey(ld, "filename")
#        fct = readline_s(req)[1:end-2] # remove CRLF
#        parts = fct.split(": ")
#
#        if parts[1] != "Content-Type"
#          invalid_line()
#        end
#
#        tmp_path, f_io = mktemp()
#       ufile = UploadFile(tmp_path, f_io, ld["filename"], parts[2])
#       d[p_value] = ufile
#
#
#     else
#
#    end
#   end
#end

function parse_qs(query::String)
    if !('=' in query)
        return throw("Not a valid query string: $query, must contain at least one key=value pair.")
    end

    q = Dict{String,Any}()

    for set in split(query, "&")
        key, val = split(set, "=")
        val = decodeURI(val)
        key = decodeURI(key)

        if haskey(q, key)
            push!(q[key], val)
        else
            q[key] = Any[val]
        end
    end

    q
end

function parse_qsr(allq::Associative{String, Any})
    akeys = reverse(sort(collect(keys(allq))))

    q = OrderedDict{String,Any}()

    for key in akeys
        skeys = split(key, ".")
        d = q
        pkeys = skeys[1:end-1]

        if !isempty(pkeys)
            for (i, k) in enumerate(pkeys)
                if !haskey(d, k)
                    d[k] = OrderedDict{String,Any}()
                end
                d = d[k]
            end
        end

        k = skeys[end]
        d[k] = allq[key]
    end
    q
end

parse_qsr(query::String) = parse_qsr(parse_qs(query))

function write_chunk(io::IO, data::Any)
    write(io, @sprintf "%x\r\n" sizeof(data))
    write(io, data)
    write(io, "\r\n")
end

function read_http_headers(req::Request)
    headers = new_headers()

    while isopen(req.sock)
        line = readline(req)
        if line == "\r\n"
            break
        else
            # remove CRLF
            line = line[1:end-2]
            key, value = split(line, ": ", 2)
            headers[key] = value
        end
    end

    headers
end

type CloseClientException <: Exception
end

parse_http_headers_fle() = throw(HTTPParserHeaderException("First line not contains expected format 'METHOD RESOURCE( PROTOCOL/VERSION)?')", line))

function parse_http_headers(req::Request)
    first_line = readline(req)

    if isempty(first_line)
        throw(CloseClientException())
    end

    first_line = first_line[1:end-2]

    if first_line == "quit"
        throw(CloseClientException())
    end

    parts = split(first_line, " ", 3)
    http_method = resource = protocol = nothing

    if length(parts) == 3
        http_method, resource, protocol = parts
    elseif length(parts) == 2
        http_method, resource = parts
    else
        parse_http_headers_fle()
    end

    req.method = http_method

    if resource[1] == '/' # is path
        # get query string
        query_pos = search(resource, '?')

        if query_pos > 0
            req.query = resource[query_pos+1:end]
            resource = resource[1:query_pos-1]
        end
    end

    req.resource = resource

    if protocol != nothing
        parts = split(protocol, "/", 2)

        if length(parts) == 2
            req.protocol = Protocol(parts[1], convert(VersionNumber, parts[2]))
        elseif length(parts) == 1
            req.protocol = Protocol(parts[1])
        else
            parse_http_headers_fle()
        end
    end

    headers = read_http_headers(req)
    req.headers = headers
    req.header_bytes = req.ready_bytes
end

end # module
