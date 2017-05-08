module CHM

# Make sure we can find the .dylib file on OS X.
@osx_only push!(Libdl.DL_LOAD_PATH, joinpath(Pkg.dir("CHM"), "deps"))

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

"""
Custom type for dispatching only. Not needed by user.
"""
type CHMFile end

global names = ASCIIString[]
global flags = Cint[]

cchars = Expr(:block)
for i in 1:(CHM_MAX_PATHLEN+1)
    push!(cchars.args, :($(gensym())::Cchar))
end

eval(CHM, quote
    type CHMUnitInfo
        start::Culonglong
        length::Culonglong
        space::Cint
        flags::Cint
        $cchars
    end
end)

CHMUnitInfo() = CHMUnitInfo(0,0,0,0,repeat([Cchar(0)],inner=[513])...)

docstr = """
Julia type wrapper for a C struct from CHMLib that contains information on
metadata for an object within the .chm file.
"""

@doc docstr CHMUnitInfo

"""
`open(path::ASCIIString)`

Open a file with CHMLib.
"""
function open(path::ASCIIString)
    ccall((:chm_open, "ChmLib"), Ptr{CHMFile}, (Ptr{UInt8},), path)
end

"""
`close(ptr::Ptr{CHMFile})`

Close a file with CHMLib.
"""
function close(ptr::Ptr{CHMFile})
    ccall((:chm_close, "ChmLib"), Void, (Ptr{CHMFile},), ptr)
end

"""
`resolve(ptr::Ptr{CHMFile}, path::ASCIIString)`

Returns `true` if `path` in the .chm file resolves to a file, else `false`.
"""
function resolve(ptr::Ptr{CHMFile}, path::ASCIIString)
    u = CHMUnitInfo()
    result = ccall((:chm_resolve_object, "ChmLib"), Cint,
        (Ptr{CHMFile}, Ptr{UInt8}, Ref{CHMUnitInfo}), ptr, path, Ref{CHMUnitInfo}(u))
    return (result != CHM_RESOLVE_FAILURE)
end

"""
`unitinfo(ptr::Ptr{CHMFile}, path::ASCIIString)`

Returns a `CHMUnitInfo` object for the file at `path` within the .chm file.
"""
function unitinfo(ptr::Ptr{CHMFile}, path::ASCIIString)
    !resolve(ptr, path) && error("Could not resolve path.")
    u = CHMUnitInfo()
    result = ccall((:chm_resolve_object, "ChmLib"), Cint,
        (Ptr{CHMFile}, Ptr{UInt8}, Ref{CHMUnitInfo}), ptr, path, Ref{CHMUnitInfo}(u))
    return u
end

"""
`retrieve(ptr::Ptr{CHMFile}, path::ASCIIString)`

Returns a string containing the contents of a text file at `path` within the .chm file.
"""
function retrieve(ptr::Ptr{CHMFile}, path::ASCIIString)
    stuff = []

    bufsize = 32768
    buffer = Array{Cuchar,1}(bufsize)
    offset = Culonglong(0)
    io = IOBuffer()

    !resolve(ptr, path) && error("Could not resolve path.")
    u = unitinfo(ptr, path)
    remain = u.length
    while remain > 0
        len = ccall((:chm_retrieve_object, "ChmLib"), Clonglong,
            (Ptr{CHMFile}, Ref{CHMUnitInfo}, Ptr{Cuchar}, Culonglong, Clonglong),
            ptr, Ref{CHMUnitInfo}(u), buffer, offset, bufsize)

        if len > 0
            write(io, buffer[1:len]...)
            offset += len
            remain -= len
        else
            error("Incomplete file.")
        end
    end
    ASCIIString(takebuf_array(io))
end

"""
`readdir(ptr::Ptr{CHMFile}, path::ASCIIString)`

Read the contents of a given directory in the CHM file.
Use UNIX path conventions. Root level is "/".
Returns the file and directory names.
"""
function readdir(ptr::Ptr{CHMFile}, path::ASCIIString)
    global names = ASCIIString[]
    global flags = Cint[]
    enumdir_c = cfunction(enumdir, Cint, (Ptr{CHMFile}, Ptr{CHMUnitInfo}, Ptr{Void}))
    ccall((:chm_enumerate_dir, "ChmLib"), Cint,
        (Ptr{CHMFile}, Ptr{UInt8}, Cint, Ptr{Void}, Ptr{Void}),
        ptr, path, CHM_ENUMERATE_ALL, enumdir_c, C_NULL)
    names
end

# When closures are c-callable, this could be re-written to avoid the global.
function enumdir(f::Ptr{CHMFile}, pu::Ptr{CHMUnitInfo}, context::Ptr{Void})
    global names
    global flags
    u = unsafe_load(pu)
    io = IOBuffer()
    for i in (1:(CHM_MAX_PATHLEN+1)) + 4
        if u.(i) == '\0'
            break
        end
        write(io, u.(i))
    end
    push!(names, takebuf_string(io))
    push!(flags, u.flags)
    return convert(Cint, CHM_ENUMERATOR_CONTINUE)::Cint
end

end # module
