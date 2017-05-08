type ASFRequest
    kws::Dict{AbstractString,AbstractString}
    ASFRequest(kws::Dict{AbstractString,AbstractString}) = new(kws)
end


function ASFRequest(args...)
    kws = Dict{AbstractString,AbstractString}()
    for a in args
        param = replace(string(typeof(a)),r"{.*}","")
        param = lcfirst(replace(param,r"ASF\.",""))
        value = string(a)
        kws[param] = value
    end
    ASFRequest(kws)
end

Requests.get(a::ASFRequest) = get(apiurl,query=a.kws)
