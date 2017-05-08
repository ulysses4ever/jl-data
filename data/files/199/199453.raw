# faststreamingmode.jl

using PicoScope
using Base.Test

print("testing ps3000_open_unit...")
handle = ps3000_open_unit()
@test handle != 0
# make sure scope closes even if we have errors
close_unit_atexit() = ps3000_close_unit(handle)
atexit(close_unit_atexit)
println("done")

print("testing ps3000_set_channel...")
enabled = true
dc_coupling = true
ps3000_set_channel(handle, PS3000Channel.A, enabled, dc_coupling, PS3000Range.V1)
println("done")

print("testing ps3000_set_trigger...")
threshold = 0
delay = -50
autotriggerms = 100
ps3000_set_trigger(handle, PS3000Source.CHANNEL_A, threshold,
                    PS3000Direction.RISING, delay, autotriggerms)
println("done")

println("testing fast streaming mode...")
fast_streaming_buffer = zeros(Int16,(8,10000))
function get_overview_buffers(overviewbuffers::Ptr{Ptr{Int16}},
                              overflow::Int16,
                              triggeredat::UInt32,
                              triggered::Int16,
                              auto_stop::Int16,
                              nvalues::UInt32)
  fast_streaming_buffer = unsafe_load(overviewbuffers)
  return nothing
end
const get_overview_buffers_c = 
  cfunction(get_overview_buffers, Void,
  (Ptr{Ptr{Int16}},Int16,UInt32,Int16,Int16,UInt32))
sample_interval = 10 
time_units = PS3000TimeUnits.MS  # miliseconds
max_samples = 1000
auto_stop = true
no_of_samples_to_aggergate = 1
overview_buffer_size = 15000
print("  call ps3000_runStreaming_ns...")
ps3000_run_streaming_ns(handle, sample_interval, time_units, max_samples,
                        auto_stop, no_of_samples_to_aggergate, overview_buffer_size) 
println("return")
print("  call ps3000_get_streaming_last_values...")
number_of_data_values_per_channel = 
  ps3000_get_streaming_last_values(handle, get_overview_buffers_c)
println("return")
print("  call ps3000_overview_buffer_status...")
  @test ~ps3000_overview_buffer_status(handle)
println("  return")




print("  call ps3000_stop...")
ps3000_stop(handle)
println("return")
println("done fast streaming mode")

print("closing scope...")
ps3000_close_unit(handle)
println("done")
