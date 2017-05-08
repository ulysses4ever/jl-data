import DataStructures: OrderedDict

import Iterators: chain

export headers,
    header,
    parse_qs,
    parse_qsr,
    params,
    fileinfo,
    isiter

function empty_fn(args...; kwargs...)
end

const str = string

const N = nothing


typealias Headers{K<:String, V<:Union(String, Array{String})} Associative{K, V}


headers(args...) =  OrderedDict{String,Union(String,Array{String})}(args...)
params(args...) = OrderedDict{String,Any}(args...)

function header(h::Headers, key::String, value::String)
    if haskey(h, key)
        if isa(h[key], String)
            h[key] = String[h[key], value]
        else
            push!(h[key], value)
        end
    else
        h[key] = value
    end
end

isiter(obj) = method_exists(Base.next, (typeof(obj), Integer))


function fileinfo(filename::String)
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
    return nothing
end


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


import Base.mktemp

if !method_exists(mktemp, (String,))
    # Create and return the name of a temporary file along with an IOStream
    function mktemp(parent::String)
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
    name::String
    target
    args
    kwargs
    stop::Bool
    data
end

Event(name::String; args=(), kwargs...) = Event(name, nothing, args, kwargs, false, Dict())

add(e::Event, target) = (e.target = (e.target, target); e)
pop(e::Event) = (e.target = e.target[1]; e)
target(e::Event) = e.target[2]

function targets(e::Event)
    local targets = {}
    t = e.target
    while t != nothing
        push!(t)
        t = t[1]
    end
    targets
end

immutable type Events
    listeners
end

Events(args::(Union(String,Symbol), Union(Array{Function}, Function))...; kwargs...) = begin
    evs = Events(Dict{String, Array{Function}}())

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

function listener(events::Events, key::Union(Symbol,String), cb::Function)
    key = string(key)
    l = get(events.listeners, key, nothing)
    if l == nothing
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
