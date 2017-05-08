module TweetNaCl

import BinDeps

type SignatureFailure <: Exception end

#@BinDeps.load_dependencies
if( isfile(joinpath(dirname(@__FILE__), "..", "deps", "deps.jl")) )
    include("../deps/deps.jl")
else
    error("TweetNaCl not properly built.  Please run Pkg.build(\"TweetNaCl\").")
end

nacl_sign_public_key_length = 0;
nacl_sign_secret_key_length = 0;
nacl_sign_max_extra_length  = 0;

function __init__()
    global nacl_sign_public_key_length,
           nacl_sign_secret_key_length,
           nacl_sign_max_extra_length

    retval = ccall( (:init_randombytes, tweetnacl), Cint, () )
    if retval != 0
        error("Failed to initialise cryptographic PRNG.")
    end

    nacl_sign_public_key_length = ccall(
        (:nacl_get_sign_pk_length, tweetnacl), Cint, () )

    nacl_sign_secret_key_length = ccall(
        (:nacl_get_sign_sk_length, tweetnacl), Cint, () )

    nacl_sign_max_extra_length = ccall(
        (:nacl_get_sign_sig_extra_length, tweetnacl), Cint, () )

end

function randombytes!(str::Array{UInt8})
    ccall( (:randombytes, TweetNaCl.tweetnacl), Void, (Ptr{UInt8}, Culonglong), str, length(str))
end

function randombytes(count::Int64)
    str = Array(UInt8, count)
    randombytes!(str)
    return str
end

function crypto_sign_keypair()
    public_key = Array(UInt8, nacl_sign_public_key_length)
    secret_key = Array(UInt8, nacl_sign_secret_key_length)

    ccall( (:crypto_sign_ed25519_tweet_keypair, TweetNaCl.tweetnacl), Cint,
           (Ptr{UInt8}, Ptr{UInt8}), public_key, secret_key)

    return public_key, secret_key
end

function crypto_sign(message::AbstractString, secret_key)

    if(length(secret_key) != TweetNaCl.nacl_sign_secret_key_length)
        error("crypto_sign: Secret key is of incorrect length.")
    end
    
    signature = zeros(UInt8, length(message)+nacl_sign_max_extra_length)
    signature_length = zeros(UInt64, 1)

    ccall( (:crypto_sign_ed25519_tweet, TweetNaCl.tweetnacl), Cint,
           (Ptr{UInt8}, Ptr{Culonglong}, Ptr{UInt8}, Culonglong, Ptr{UInt8}),
           signature, signature_length, message, length(message), secret_key)
    
    return signature[1:signature_length[1]]
end

function crypto_sign_open(signature::Array{UInt8}, public_key)

    if(length(public_key) != TweetNaCl.nacl_sign_public_key_length)
        error("crypto_sign_open: Public key is of incorrect length.")
    end
        
    message = zeros(UInt8, length(signature))
    message_length = zeros(UInt64, 1)

    result = ccall( (:crypto_sign_ed25519_tweet_open, TweetNaCl.tweetnacl), Cint,
           (Ptr{UInt8}, Ptr{Culonglong}, Ptr{UInt8}, Culonglong, Ptr{UInt8}),
           message, message_length, signature, length(signature), public_key)

    if result != 0
        throw(SignatureFailure())
    end

    return message[1:message_length[1]]

end

end # module
