# faststreamingmode.jl

using PicoScope
using Base.Test

print("testing ps3000_open_unit...")
handle = ps3000_open_unit()
@test handle != 0
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
fast_streaming_buffer = zeros(Int16,(8,100))
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
max_samples = 10
auto_stop = true
no_of_samples_to_aggergate = 1
print("  call ps3000_runStreaming_ns...")
ps3000_runStreaming_ns(handle, time_units, max_samples, auto_stop,
                       no_of_samples_to_aggergate) 
println("return")
print("  call ps3000_get_streaming_last_values...")
number_of_data_values_per_channel = 
  ps3000_get_streaming_last_values(handle, get_overview_buffers_c)
println("return")



print("  call ps3000_stop...")
ps3000_stop(handle)
println("return")
println("done fast streaming mode")
