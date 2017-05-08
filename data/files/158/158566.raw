module CHM

# CHMLib constants
const CHM_UNCOMPRESSED = 0
const CHM_COMPRESSED   = 1

const CHM_MAX_PATHLEN = 512

const CHM_PARAM_MAX_BLOCKS_CACHED = 0

const CHM_RESOLVE_SUCCESS = 0
const CHM_RESOLVE_FAILURE = 1

const CHM_ENUMERATE_NORMAL    = 1
const CHM_ENUMERATE_META      = 2
const CHM_ENUMERATE_SPECIAL   = 4
const CHM_ENUMERATE_FILES     = 8
const CHM_ENUMERATE_DIRS      = 16
const CHM_ENUMERATE_ALL       = 31
const CHM_ENUMERATOR_FAILURE  = 0
const CHM_ENUMERATOR_CONTINUE = 1
const CHM_ENUMERATOR_SUCCESS  = 2

typealias CHMFile Ptr{Void}

cchars = Expr(:block)
for i in 1:(CHM_MAX_PATHLEN+1)
    push!(cchars.args, :($(gensym())::Cchar))
end

eval(quote
    type CHMUnitInfo
        start::Culonglong
        length::Culonglong
        space::Cint
        flags::Cint
        $cchars
    end
end)

"Open a file with CHMLib."
function open(path::ASCIIString)
    ccall((:chm_open, "ChmLib"), CHMFile, (Ptr{UInt8},), path)
end

"Close a file with CHMLib."
function close(ptr::CHMFile)
    ccall((:chm_open, "ChmLib"), Void, (CHMFile,), ptr)
end

function d(ptr::Ptr{Void})
    a = []
    enumdir_c = cfunction(enumdir(a), Cint, (CHMFile, Ptr{CHMUnitInfo}, Ptr{Void}))
    ccall((:chm_enumerate_dir, "ChmLib"), Cint,
        (CHMFile, Cint, Ptr{Void}, Ptr{Void}),
        ptr, CHM_ENUMERATE_ALL, enumdir_c, C_NULL)
    a
end

function enumdir(a::AbstractArray)
    return (f::CHMFile, u::Ptr{CHMUnitInfo}, context::Ptr{Void})->begin
        io = IOBuffer()
        for i in (1:(CHM_MAX_PATHLEN+1)) + 4
            write(io, u.(i))
        end
        push!(a, takebuf_string(io))
        return convert(Cint, CHM_ENUMERATOR_CONTINUE)::Cint
    end
end

end # module
