module SysLim

export setrlimit, getrlimit

# Per-process CPU limit, in seconds
const RLIMIT_CPU = convert(Cint, 0)

# Largest file that can be created, in bytes
const RLIMIT_FSIZE = convert(Cint, 1)

# Maximum size of data segment, in bytes
const RLIMIT_DATA = convert(Cint, 2)

# Maximum size of stack segment, in bytes
const RLIMIT_STACK = convert(Cint, 3)

# Largest core file that can be created, in bytes
const RLIMIT_CORE = convert(Cint, 4)

# Number of open files
const RLIMIT_NOFILE = convert(Cint, 7)

# Address space limit
const RLIMIT_AS = convert(Cint, 9)

# Number of processes
const RLIMIT_NPROC = convert(Cint, 6)

# Maximum number of file locks
const RLIMIT_LOCKS = convert(Cint, 10)

# Maximum bytes in POSIX message queues
const RLIMIT_MSGQUEUE = convert(Cint, 12)

if isless(Base.VERSION, v"0.4.0-")
    function getrlimit(resource::Cint)
        limit = Culong[0,0]
        ret = ccall(:getrlimit, Cint, (Cint, Ptr{Void}), resource, pointer(limit))
        (ret == 0) || error("Error getting rlimit: $ret")
        limit
    end

    function setrlimit(resource::Cint, soft::Integer, hard::Integer=soft)
        limit = Culong[soft, hard]
        ret = ccall(:setrlimit, Cint, (Cint, Ptr{Void}), resource, pointer(limit))
        (ret == 0) || error("Error setting rlimit: $ret")
        newlimit = getrlimit(resource)
        ((limit[1] == newlimit[1]) && (limit[2] == newlimit[2])) || error("Could not set rlimits. Limits are now $(newlimit[1]), $(newlimit[2])")
        nothing
    end
else
    type SysRlimit
        rlim_cur::Culong
        rlim_max::Culong
    end

    function Base.show(io::IO, l::SysRlimit)
        println(io, "soft: $(convert(Clong, l.rlim_cur))")
        println(io, "hard: $(convert(Clong, l.rlim_max))")
        nothing
    end

    function setrlimit(resource::Cint, soft::Integer, hard::Integer=soft)
        limit = SysRlimit(soft, hard)
        ret = ccall(:setrlimit, Cint, (Cint, Ptr{Void}), resource, pointer_from_objref(limit))
        (ret == 0) || error("Error setting rlimit: $ret")
        newlimit = getrlimit(resource)
        ((limit.rlim_cur == newlimit.rlim_cur) && (limit.rlim_max == newlimit.rlim_max)) || error("Could not set rlimits. Limits are now $(newlimit.rlim_cur), $(newlimit.rlim_max)")
        nothing
    end

    function getrlimit(resource::Cint)
        limit = SysRlimit(0, 0)
        ret = ccall(:getrlimit, Cint, (Cint, Ptr{Void}), resource, pointer_from_objref(limit))
        (ret == 0) || error("Error getting rlimit: $ret")
        limit
    end
end

end # module end

