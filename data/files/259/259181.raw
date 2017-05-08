module mraa

const libmraa = find_library(["libmraa"])

include("enums.jl")

function platform_name()
    bytestring(ccall((:mraa_get_platform_name, libmraa), Ptr{Uint8}, ()))
end

function platform_type()
    Platform(ccall((:mraa_get_platform_type, libmraa), Cint, ()))
end

end # module
