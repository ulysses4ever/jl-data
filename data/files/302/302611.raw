const OPUS_APPLICATION_VOIP                = int32(2048)
const OPUS_APPLICATION_AUDIO               = int32(2049)
const OPUS_APPLICATION_RESTRICTED_LOWDELAY = int32(2051)

const libopus = "libopus"
const opus_encoder_create_func = (:opus_encoder_create,libopus)
const opus_encoder_destroy_func = (:opus_encoder_destroy,libopus)

function encoder_create(fs::Integer, channels::Integer)
    err::Int32 = 0;
    enc = ccall(opus_encoder_create_func,Ptr{Void},
        (Int32,Int32,Int32,Ptr{Int32}),
        fs,channels,OPUS_APPLICATION_AUDIO,err)
    enc
end

function encoder_destroy(enc::Ptr{Void})
    ccall(opus_encoder_destroy_func,Void,(Ptr{Void},),enc)
end
