module mraa

const libmraa = Libdl.find_library("libmraa.so.1")

include("enums.jl")

function init()
    Result(ccall((:mraa_init, libmraa), Cint, ()))
end

function deinit()
    ccall((:mraa_deinit, libmraa), Void, ())
end

#mraa_boolean_t mraa_pin_mode_test (int pin, mraa_pinmodes_t mode)

function adc_raw_bits()
    ccall((:mraa_adc_raw_bits, libmraa), Cuint, ())
end

function adc_supported_bits()
    ccall((:mraa_adc_supported_bits, libmraa), Cuint, ())
end

function set_log_level(p)
    Result(ccall((:mraa_set_log_level, libmraa), Cint, (Cint,), p))
end

function platform_name()
    bytestring(ccall((:mraa_get_platform_name, libmraa), Ptr{Uint8}, ()))
end

function set_priority(p)
    ccall((:mraa_set_priority, libmraa), Cint, (Cuint,), p)
end

function version()
    VersionNumber(bytestring(ccall((:mraa_get_version, libmraa), Ptr{Uint8}, ())))
end

function Platform()
    Platform(ccall((:mraa_get_platform_type, libmraa), Cint, ()))
end

function pin_count()
    Int(ccall((:mraa_get_pin_count, libmraa), Cuint, ()))
end

end # module
