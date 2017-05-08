module USERTime

# CPUTime.jl, and Julia internal functions (@time, @elapsed, tic(), etc...)
# all use the UV library.  @time uses uv_hrtime(),  CPUTime uses user and
# sys CPU time from uv_getrusage.  This module just uses the user CPU time.

using Compat

export
    USERtime_us,
    USERtic,
    USERtoq,
    USERtoc,
    @USERtime,
    @USERelapsed

function USERtime_us()
    # sizeof(uv_rusage_t); this is different from sizeof(rusage)
    @compat rusage = c_malloc(4*sizeof(Clong) + 14*sizeof(Uint64))
    ccall(:uv_getrusage, Cint, (Ptr{Void},), rusage)
    utime = uint64(1000000)*
            unsafe_load(convert(Ptr{Clong}, rusage+0*sizeof(Clong))) + #usr CPU time
            unsafe_load(convert(Ptr{Clong}, rusage+1*sizeof(Clong)))
    c_free(rusage)
    return utime
end

function USERtic()
    t0 = USERtime_us()
    task_local_storage(:USERTIMERS, (t0, get(task_local_storage(), :USERTIMERS, ())))
    return t0
end

function USERtoq()
    t1 = USERtime_us()
    timers = get(task_local_storage(), :USERTIMERS, ())
    if is(timers,())
        error("USERtoc() without USERtic()")
    end
    @compat t0 = timers[1]::Uint64
    task_local_storage(:USERTIMERS, timers[2])
    (t1-t0)/1e6
end

function USERtoc()
    t = USERtoq()
    println("elapsed USER time: ", t, " seconds")
    return t
end

# print elapsed USER time, return expression value
macro USERtime(ex)
    quote
        local t0 = USERtime_us()
        local val = $(esc(ex))
        local t1 = USERtime_us()
        println("elapsed USER time: ", (t1-t0)/1e6, " seconds")
        val
    end
end

# print nothing, return elapsed USER time
macro USERelapsed(ex)
    quote
        local t0 = USERtime_us()
        local val = $(esc(ex))
        (USERtime_us()-t0)/1e6
    end
end

end # module
