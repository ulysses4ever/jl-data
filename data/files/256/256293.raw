using FactCheck
using SimpleHttpCommon
const S = SimpleHttpCommon
const TEST_DIR = dirname(@__FILE__)
const CRLF = "\r\n"

function buffer(data = nothing; start=false)
    b = IOBuffer()
    if data != nothing
        write(b, data)
    end

    if start
        seekstart(b)
    end

    b
end

function mk_res()
    HTTPResponse(IOSocket(buffer()))
end

type ExceptionNotRaised <: Exception
    info
end

type NOT_DEFINED end

function fact_catch{T}(fn::Function, extype::Type{T}, einfo=nothing; kwargs...)
    try
        fn()
        throw(ExceptionNotRaised((extype, einfo)))
    catch e
        if !isa(e, extype)
            rethrow()
        end

        for (key, expected_value) in kwargs
            value = get(e.info, key, NOT_DEFINED)
            @fact value --> expected_value string("Key value mismatch ", extype, ".info[", repr(key), "]")
        end
    end
end

fre(fn::Function, einfo=nothing; kwargs...) = fact_catch(fn, S.ResponseException; kwargs...)
frqe(fn::Function, einfo=nothing; kwargs...) = fact_catch(fn, S.RequestException; kwargs...)

const str = UTF8String

function write_crlf(io, data="")
    s = 0
    if data != ""
        s += Base.write(io, data)
    end
    s + Base.write(io, "\r\n")
end

const wclf = write_crlf
