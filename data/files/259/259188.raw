module mraa

const libmraa = find_library(["/usr/local/lib/i386-linux-gnu/libmraa.so.0.6.0", "/usr/local/lib/libmraa.so.0.6.0"])

include("enums.jl")

function set_priority(p)
    Int(ccall((:mraa_set_priority, libmraa), Cint, (Cuint,), p))
end

function platform_name()
    bytestring(ccall((:mraa_get_platform_name, libmraa), Ptr{Uint8}, ()))
end

function set_priority(p)
    Int(ccall((:mraa_set_priority, libmraa), Cint, (Cuint,), p))
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
