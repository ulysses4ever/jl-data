import DataStructures: OrderedDict

import Iterators: chain
import Dates

export headers,
    header,
    parseqs,
    parseqsr,
    params,
    fileinfo,
    isiter,
    RFC1123_datetime

function emptyfn(args...; kwargs...)
end

const str = string

RFC1123_datetime(t::Dates.DateTime) = Dates.format(t, Dates.RFC1123Format) * " GMT"
RFC1123_datetime() = RFC1123_datetime(Dates.now(Dates.UTC))


typealias Headers{K<:STR_TYPE, V<:Union(STR_TYPE, Array{STR_TYPE})} Associative{K, V}


headers(args...) =  OrderedDict{STR_TYPE,Union(STR_TYPE,Array{STR_TYPE})}(args...)
params(args...) = OrderedDict{STR_TYPE,Any}(args...)

function header(h::Headers, key::STR_TYPE, value::STR_TYPE)
    if haskey(h, key)
        if isa(h[key], STR_TYPE)
            h[key] = String[h[key], value]
        else
            push!(h[key], value)
        end
    else
        h[key] = value
    end
end

isiter(obj) = method_exists(Base.next, (typeof(obj), Integer))


function fileinfo(filename::STR_TYPE)
    if isfile(filename)
        (_, ext) = splitext(filename)

        mime = "application/octet-stream"

        if length(ext) > 1
            ext = ext[2:end]
            if haskey(mimetypes,ext)
                mime = mimetypes[ext]
            end
        end

        return ext, mime, filesize(filename)
    end
    return N
end


function parseqs(query::STR_TYPE)
    if !('=' in query)
        return throw("Not a valid query string: $query, must contain at least one key=value pair.")
    end

    q = Dict{STR_TYPE,Any}()

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

function parseqsr(allq::Associative{STR_TYPE, Any})
    akeys = reverse(sort(collect(keys(allq))))

    q = OrderedDict{STR_TYPE,Any}()

    for key in akeys
        skeys = split(key, ".")
        d = q
        pkeys = skeys[1:end-1]

        if !isempty(pkeys)
            for (i, k) in enumerate(pkeys)
                if !haskey(d, k)
                    d[k] = OrderedDict{STR_TYPE,Any}()
                end
                d = d[k]
            end
        end

        k = skeys[end]
        d[k] = allq[key]
    end
    q
end

parseqsr(query::STR_TYPE) = parseqsr(parseqs(query))


import Base.mktemp

if !method_exists(mktemp, (STR_TYPE,))
    # Create and return the name of a temporary file along with an IOStream
    function mktemp(parent::STR_TYPE)
        b = joinpath(parent, "tmpXXXXXX")
        p = ccall(:mkstemp, Int32, (Ptr{UInt8},), b) # modifies b
        systemerror(:mktemp, p == -1)
        return (b, fdio(p, true))
    end
end

if !method_exists(mktemp, (Function,))
    function mktemp(fn::Function, parent=tempdir())
        (tmp_path, tmp_io) = mktemp(parent)
        try
            fn(tmp_path, tmp_io)
        finally
            close(tmp_io)
            rm(tmp_path)
        end
    end
end

export Event, add, pop, target, targets, listener, trigger, Events

type Event
    name::STR_TYPE
    target
    args
    kwargs
    stop::Bool
    data
end

Event(name::STR_TYPE; args=(), kwargs...) = Event(name, N, args, kwargs, false, Dict())

add(e::Event, target) = (e.target = (e.target, target); e)
pop(e::Event) = (e.target = e.target[1]; e)
target(e::Event) = e.target[2]

function targets(e::Event)
    local targets = {}
    t = e.target
    while t != N
        push!(t)
        t = t[1]
    end
    targets
end

immutable type Events
    listeners
end

Events(args::(Union(STR_TYPE,Symbol), Union(Array{Function}, Function))...; kwargs...) = begin
    evs = Events(Dict{STR_TYPE, Array{Function}}())

    for (key, cb) in chain(args, kwargs)
        if isa(cb, Function)
            listener(evs, key, cb)
        else
            for c in cb
                listener(evs, key, c)
            end
        end
    end
    evs
end

function listener(events::Events, key::Union(Symbol,STR_TYPE), cb::Function)
    key = string(key)
    l = get(events.listeners, key, N)
    if l == N
        l = Function[]
        events.listeners[key] = l
    end
    push!(l, cb)
    events
end

function trigger(events::Events, event::Event, target)
    add(event, target)
    try
        if haskey(events.listeners, event.name)
            for cb in events.listeners[event.name]
                cb(event, event.args...; event.kwargs...)
                if event.stop
                    break
                end
            end
        end
        event.data
    catch e
        event.data[:targets] = targets(event)
        rethrow()
    finally
        pop(event)
    end
    event.data
end
