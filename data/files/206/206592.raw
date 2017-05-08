# nicer functions for accessing the hashes from julia
module Hash

import Base

export md4, md5, sha1, sha224, sha256, sha348, sha512, hex

function hex(arr :: Array{Uint8})
    join(map(x -> length(x) == 1 ? "0" * x : x, map(Base.hex, arr)))
end

include("gen/libcrypto_common.jl")

macro make_hasher(our_name, libcrypto_name, hash_length)
    init = symbol(libcrypto_name * "_Init")
    update = symbol(libcrypto_name * "_Update")
    final = symbol(libcrypto_name * "_Final")
    libcrypto_name = symbol(libcrypto_name)

    context_size = 100

    quote
        function $(esc(our_name))(a :: Array{Uint8})
            hash = zeros(Uint8, $hash_length)
            $libcrypto_name(a, length(a), hash)
            hash
        end

        $(esc(our_name))(a :: String) = $(esc(our_name))(convert(Array{Uint8}, a))

        function $(esc(our_name))(a :: IO)
            context = zeros(Uint8, $context_size)
            $init(context)

            buffer = Array(Uint8, 65536)
            read = readbytes!(a, buffer, 65536)
            while read == 65536
                $update(context, buffer, 65536)
                read = readbytes!(a, buffer, 65536)
            end
            $update(context, buffer, read)

            hash = Array(Uint8, $hash_length)
            $(esc(final))(hash, context)
            hash
        end
    end
end

include("gen/md4.h.jl")
@make_hasher(md4, "MD4", 16)

include("gen/md5.h.jl")
@make_hasher(md5, "MD5", 16)

include("gen/mdc2.h.jl")
@make_hasher(mdc2, "MDC2", 16)

include("gen/sha.h.jl")
@make_hasher(sha1, "SHA1", 20)
@make_hasher(sha224, "SHA224", 28)
@make_hasher(sha256, "SHA256", 32)
@make_hasher(sha348, "SHA384", 48)
@make_hasher(sha512, "SHA512", 64)

end # module Hash