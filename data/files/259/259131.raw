# Wrap common API

function init()
  Result(ccall((:mraa_init, libmraa), Cint, ()))
end

function deinit()
  ccall((:mraa_deinit, libmraa), Void, ())
end

function adc_raw_bits()
  Int32(ccall((:mraa_adc_raw_bits, libmraa), Cuint, ()))
end

function adc_supported_bits()
  Int32(ccall((:mraa_adc_supported_bits, libmraa), Cuint, ()))
end

function set_log_level(p::Int32)
  Result(ccall((:mraa_set_log_level, libmraa), Cint, (Cint,), p))
end

function platform_name()
  unsafe_string(ccall((:mraa_get_platform_name, libmraa), Cstring, ()))
end

function set_priority(p)
  ccall((:mraa_set_priority, libmraa), Cint, (Cuint,), p)
end

function version()
  VersionNumber(unsafe_string(ccall((:mraa_get_version, libmraa), Cstring, ())))
end


function platform_type()
  Platform(ccall((:mraa_get_platform_type, libmraa), Cint, ()))
end

function pin_count()
  Int(ccall((:mraa_get_pin_count, libmraa), Cuint, ()))
end

function pin_mode_test(pin::Int32,mode::PinModes)
  Bool(ccall((:mraa_pin_mode_test, libmraa), Cuint, (Cint,Cint),
    pin,Cint(mode)))
end
