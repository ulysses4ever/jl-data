# localtests.jl

# need scope attached for these

using PicoScope
using Base.Test

# ps3000_open_unit_async() cannot be called after 
# handle = ps3000_open_unit(); ps3000_close_unit(handle)
# need to restart julia session.  do not know why.
print("testing ps3000_open_unit_async, ps3000_open_unit_progress...")
open_async_status = ps3000_open_unit_async()
if open_async_status == 0
  println()
  println("there is a previous open operation in progress")
  @test open_async_status == 0
end
progress_percent = 0x0000
handle = 0x0000
while progress_percent<100
  (handle, progress_percent) = ps3000_open_unit_progress()
#  println(handle,"    ",progress_percent)
  wait(Timer(0.5))
end
ps3000_close_unit(handle)
println("done")

print("testing ps3000_open_unit, ps3000_close_unit...")
handle = ps3000_open_unit()
@test handle != 0
ps3000_close_unit(handle)
println("done")

print("opening scope for multiple tests...")
handle = ps3000_open_unit()
# make sure scope closes even if we have errors
close_unit_atexit() = ps3000_close_unit(handle)
atexit(close_unit_atexit)
println("done")

print("testing ps3000_flash_led...")
ps3000_flash_led(handle)
println("done")

println("testing ps3000_get_unit_info...")
unitinfo = ps3000_get_unit_info(handle)
println("  PS3000_DRIVER_VERSION   : ",unitinfo[1])
println("  PS3000_USB_VERSION      : ",unitinfo[2])
println("  PS3000_HARDWARE_VERSION : ",unitinfo[3])
println("  PS3000_VARIANT_INFO     : ",unitinfo[4])
println("  PS3000_BATCH_AND_SERIAL : ",unitinfo[5])
println("  PS3000_CAL_DATE         : ",unitinfo[6])
println("  PS3000_ERROR_CODE       : ",unitinfo[7])
println("testing ps3000_get_unit_info, done")

print("testing ps3000_set_channel...")
enabled = true
dc_coupling = true
ps3000_set_channel(handle, PS3000Channel.A, enabled, dc_coupling, PS3000Range.V1)
println("done")

# only 3204, 3205, 3206 support ETS
if in(unitinfo[4] ,Set(["3204","3205","3206"]))
  println("testing ps3000_set_ets...")
  ets_interleave = 10
  ets_cycles = 4*ets_interleave
  effective_sample_time = ps3000_set_ets(handle, PS3000ETSMode.SLOW, ets_cycles,
                                         ets_interleave)
  println("effective sample time : ",effective_sample_time,"ps")
  println("testing ps3000_set_ets, done")
end

print("testing ps3000_set_trigger...")
threshold = 0
delay = -50
autotriggerms = 100
ps3000_set_trigger(handle, PS3000Source.CHANNEL_A, threshold,
                    PS3000Direction.RISING, delay, autotriggerms)
println("done")

print("testing ps3000_set_trigger2...")
delay = -50.0  # float for ps3000_set_trigger2
# both calls shoud be the same
ps3000_set_trigger(handle, PS3000Source.CHANNEL_A, threshold,
                    PS3000Direction.RISING, delay, autotriggerms)
ps3000_set_trigger2(handle, PS3000Source.CHANNEL_A, threshold,
                    PS3000Direction.RISING, delay, autotriggerms)
println("done")

print("testing ps3000_get_timebase...")
timebase = 5 #  0 is fastest timebase, 1 is 2x period of 0, etc.
number_of_samples = 1000
oversample = 2
(time_interval, time_units, max_samples) =
  ps3000_get_timebase(handle, timebase, number_of_samples, oversample)
println("done")

println("tetsing ps3000_run_block...")
time_for_adc_to_collect_data_ms = 
  ps3000_run_block(handle, number_of_samples, timebase, oversample)
println("  time for ADC to collect data = ",time_for_adc_to_collect_data_ms,"ms")
println("tetsing ps3000_run_block, done")

print("testing ps3000_ready...")
while ~ps3000_ready(handle); end
println("done")

print("testing ps3000_get_values!...")
vbuffer = ValueBuffer(number_of_samples)
(values_per_channel_returned, overflow) = 
  ps3000_get_values!(handle,vbuffer,number_of_samples)
if overflow != 0
  print(" overflow! ")
end
@test values_per_channel_returned == number_of_samples
println("done")

print("testing ps3000_get_times_and_values!...")
time_for_adc_to_collect_data_ms = 
  ps3000_run_block(handle, number_of_samples, timebase, oversample)
while ~ps3000_ready(handle); end
vtbuffer = TimesAndValuesBuffer(number_of_samples)
(values_per_channel_returned, overflow) = 
  ps3000_get_times_and_values!(handle, vtbuffer, time_units, number_of_samples)
if overflow != 0
  print(" overflow! ")
end
@test values_per_channel_returned == number_of_samples
println("done")





print("closing scope...")
ps3000_close_unit(handle)
println("done")





@test 1 == 1