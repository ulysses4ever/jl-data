module mraa

const libmraa = find_library(["/usr/local/lib/i386-linux-gnu/libmraa.so.0.6.0", "/usr/local/lib/libmraa.so.0.6.0"])

include("enums.jl")

function platform_name()
    bytestring(ccall((:mraa_get_platform_name, libmraa), Ptr{Uint8}, ()))
end

function Base.VersionNumber(::mraa)
    VersionNumber(bytestring(ccall((:mraa_get_version, libmraa), Ptr{Uint8}, ())))
end

function platform_type()
    Platform(ccall((:mraa_get_platform_type, libmraa), Cint, ()))
end

function pin_count()
    ccall((:mraa_get_pin_count, libmraa), Cuint, ())
end

end # module
