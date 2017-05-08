# Constants and types go here

const portaudio = "libportaudio"
const sndfile = "libsndfile"

type DeviceInfo
    structVersion::Int32
    name::Ptr{Uint8}
    hostApi::Int32
    maxInputChannels::Int32
    maxOutputChannels::Int32
    defaultLowInputLatency::Float64
    defaultLowOutputLatency::Float64
    defaultHighInputLatency::Float64
    defaultHighOutputLatency::Float64
    defaultSampleRate::Float64
end

type StreamParameters
    device::Int32
    channelCount::Int32
    sampleFormat::Uint
    suggestedLatency::Float64
    hostApiSpecificStreamInfo::Ptr{Void}
end

typealias PaStream Ptr{Void}

type SF_INFO
    frames::Int64
    samplerate::Int32
    channels::Int32
    format::Int32
    sections::Int32
    seekable::Int32
end
