module mraa

const libmraa = "/usr/local/lib/i386-linux-gnu/libmraa.so.0.6.0"

function platform_name()
    bytestring(ccall((:mraa_get_platform_name, libmraa), Ptr{Uint8}, ()))
end


end # module
