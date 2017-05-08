module SysLim

export setrlimit, getrlimit

# Per-process CPU limit, in seconds
const RLIMIT_CPU = Cint(0)

# Largest file that can be created, in bytes
const RLIMIT_FSIZE = Cint(1)

# Maximum size of data segment, in bytes
const RLIMIT_DATA = Cint(2)

# Maximum size of stack segment, in bytes
const RLIMIT_STACK = Cint(3)

# Largest core file that can be created, in bytes
const RLIMIT_CORE = Cint(4)

# Number of open files
const RLIMIT_NOFILE = Cint(7)

# Address space limit
const RLIMIT_AS = Cint(9)

# Number of processes
const RLIMIT_NPROC = Cint(6)

# Maximum number of file locks
const RLIMIT_LOCKS = Cint(10)

# Maximum bytes in POSIX message queues
const RLIMIT_MSGQUEUE = Cint(12)

type SysRlimit
    rlim_cur::Culong
    rlim_max::Culong
end

function Base.show(io::IO, l::SysRlimit)
    println(io, "soft: $(Clong(l.rlim_cur))")
    println(io, "hard: $(Clong(l.rlim_max))")
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

end # module end

