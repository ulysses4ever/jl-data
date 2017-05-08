# compatiblestreamingmodetest.jl
using PicoScope
using Base.Test

println("testing compatable streaming mode...")
handle = ps3000_open_unit()
println("handle = ",handle)
enabled = true
dc_coupling = true
ps3000_set_channel(handle, PS3000Channel.A, enabled, dc_coupling, PS3000Range.V1)
sample_interval_ms = 10
max_samples = 1000 # size of buffer for ps3000_run_streaming
windowed = 0 # only return values since last call
number_of_samples = 100
vbuffer = ValueBuffer(number_of_samples)
ps3000_run_streaming(handle, sample_interval_ms, max_samples, windowed)
wait(Timer(1))
(values_per_channel_returned, overflow) = 
  ps3000_get_values!(handle,vbuffer,number_of_samples)
# @test values_per_channel_returned<100
ps3000_stop(handle)
# ps3000_close_unit(handle)  # does not return from close when in compatable streaming mode
println("done")