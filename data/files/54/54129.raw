using MyLib
using Base.Test

try
    ptms = new_tms()
    println("Start")
    times = libc_times(ptms)
    tms_utime = get_tms_utime(ptms)
    tms_stime = get_tms_stime(ptms)
    tms_cutime = get_tms_cutime(ptms)
    tms_cstime = get_tms_cstime(ptms)
    println("times: ", times)
    println("tms_utime: ", tms_utime)
    println("tms_stime: ", tms_stime)
    println("tms_cutime: ", tms_cutime)
    println("tms_cstime: ", tms_cstime)
    println("End")
    times = libc_times(ptms)
    tms_utime = get_tms_utime(ptms)
    tms_stime = get_tms_stime(ptms)
    tms_cutime = get_tms_cutime(ptms)
    tms_cstime = get_tms_cstime(ptms)
    println("times: ", times)
    println("tms_utime: ", tms_utime)
    println("tms_stime: ", tms_stime)
    println("tms_cutime: ", tms_cutime)
    println("tms_cstime: ", tms_cstime)
    delete_tms(ptms)
catch
    @test false
end

@test true
