module mraa

const libmraa = "/usr/local/lib/libmraa.so.0.6.0"

function platform_name()
    bytestring(ccall((:mraa_get_platform_name, libmraa), Ptr{UInt8}, ()))
end


end # module
