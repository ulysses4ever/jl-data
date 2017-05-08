module MyLib

include("../deps/deps.jl")
export delete_tms, get_tms_cstime, get_tms_cutime, get_tms_stime, get_tms_utime, libc_times, new_tms

function delete_tms(ptms)
    return ccall((:delete_tms, mylib), Void, (Ptr{Void},), ptms)
end

function get_tms_cstime(ptms)
    return ccall((:get_tms_cstime, mylib), Int32, (Ptr{Void},), ptms)
end

function get_tms_cutime(ptms)
    return ccall((:get_tms_cutime, mylib), Int32, (Ptr{Void},), ptms)
end

function get_tms_stime(ptms)
    return ccall((:get_tms_stime, mylib), Int32, (Ptr{Void},), ptms)
end

function get_tms_utime(ptms)
    return ccall((:get_tms_utime, mylib), Int32, (Ptr{Void},), ptms)
end

function libc_times(ptms)
    return ccall((:times, "libc"), Int32, (Ptr{Void},), ptms)
end

function new_tms()
    return ccall((:new_tms, mylib), Ptr{Void}, ())
end

end #module
