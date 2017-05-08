module CryptoRandom

@windows_only cryptprov = Array(Ptr{Void}, 1)

function __init__()
    @windows_only begin
        retval = ccall((:CryptAcquireContextA, "Advapi32"), Cint,
                          (Ptr{Ptr{Void}}, Ptr{UInt8}, Ptr{UInt8},
                           UInt32, UInt32),
                          cryptprov, C_NULL, C_NULL, 1 ,0) # 1 = PROV_RSA_FULL

        if retval == 0
            error("Failed to acquire crypt context.")
        end
    end
 
end

function random(len)
    str = Array(UInt8, len)
    retval = ccall((:CryptGenRandom, "Advapi32"), Cint,
                   (Ptr{Void}, Cuint, Ptr{UInt8}),
                   cryptprov[1], len, str)
    if retval == 0
        error("Failed to get random data.")
    else
        str
    end
end

end # module
