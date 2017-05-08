using FactCheck
using SimpleHttpCommon
const S = SimpleHttpCommon
const N = S.N
const N_TYPE = S.N_TYPE
const TEST_DIR = dirname(@__FILE__)
const CRLF = S.CRLF
const STR_TYPE = S.STR_TYPE

function buffer(data = N; start=false)
    b = IOBuffer()
    if data != N
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

function fact_catch{T}(fn::Function, extype::Type{T}, einfo=N; kwargs...)
    try
        fn()
        throw(ExceptionNotRaised((extype, einfo)))
    catch e
        if !isa(e, extype)
            rethrow()
        end

        for (key, expected_value) in kwargs
            value = get(e.info, key, NOT_DEFINED)
            @fact value --> expected_value string("Key value mismatch $extype.info[$(repr(key))]. Info is: $(repr(e.info))")
        end
    end
end

fre(fn::Function, einfo=N; kwargs...) = fact_catch(fn, S.ResponseException; kwargs...)
frqe(fn::Function, einfo=N; kwargs...) = fact_catch(fn, S.RequestException; kwargs...)

const str = UTF8String

function write_crlf(io, data="")
    s = 0
    if data != ""
        s += Base.write(io, data)
    end
    s + Base.write(io, "\r\n")
end

const wclf = write_crlf
