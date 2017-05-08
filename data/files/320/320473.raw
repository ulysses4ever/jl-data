# Constants and types go here

const portaudio = "libportaudio"

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
