module mraa

const libmraa = find_library(["libmraa"])

function platform_name()
    bytestring(ccall((:mraa_get_platform_name, libmraa), Ptr{Uint8}, ()))
end


end # module
