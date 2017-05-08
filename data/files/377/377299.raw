export Stream, openStream, closeStream, writeStream, readStream

const TypeToSampleFormat = {Float32 => 0x1, Int32 => 0x2, Int16 => 0x8, 
                            Int8 => 0x10, Uint8 => 0x20}

type Stream
    pastream::PaStream
    channels::Int32
    sampleRate::Float64
    framesPerBuffer::Uint
    dtype::DataType
end

function InputStreamParameters(device::Integer, numChannels::Integer, 
                               dtype::DataType)
    devinfo = DeviceInfo(device)
    return StreamParameters(convert(Int32, device), convert(Int32, numChannels), 
                            convert(Uint, TypeToSampleFormat[dtype]),
                            devinfo.defaultHighInputLatency, 
                            convert(Ptr{None}, C_NULL))
end

function OutputStreamParameters(device::Integer, numChannels::Integer, 
                                   dtype::DataType)
    devinfo = DeviceInfo(device)
    return StreamParameters(convert(Int32, device), 
                            convert(Int32, numChannels), 
                            convert(Uint, TypeToSampleFormat[dtype]),
                            devinfo.defaultHighOutputLatency, 
                            convert(Ptr{None}, C_NULL))
end


function openStream(inputId::Integer, outputId::Integer,
                       sampleRate::Integer, numChannels::Integer, 
                       framesPerBuffer::Integer, dtype::DataType)
    pastream = Array(PaStream, 1)
    inputParams = InputStreamParameters(inputId, numChannels, dtype)
    outputParams = OutputStreamParameters(outputId, numChannels, dtype)

    err = ccall((:Pa_OpenStream, portaudio), Int32, 
                (Ptr{PaStream}, Ptr{StreamParameters}, Ptr{StreamParameters},
                 Float64, Uint, Uint, Ptr{Void}, Ptr{Void}),
                pastream, &inputParams, &outputParams, 
                sampleRate, framesPerBuffer, 0, C_NULL, C_NULL)
    check_pa_error(err)
    return Stream(pastream[], 
                  convert(Int32, numChannels), 
                  convert(Float64, sampleRate),
                  convert(Uint, framesPerBuffer),
                  dtype)
end

function openStream(sampleRate::Integer, numChannels::Integer, dtype::DataType)
    openStream(defaultInputDevice(), defaultOutputDevice(),
               sampleRate, numChannels, 1024, dtype)
end

function openStream(f::Function, args...)
    stream = openStream(args...)
    f(stream)
    closeStream(stream)
end

function closeStream(stream::Stream)
    err = ccall((:Pa_CloseStream, portaudio), Int32, (PaStream,), stream.pastream)
    check_pa_error(err)
end

function startStream(f::Function, stream::Stream)
    err = ccall((:Pa_StartStream, portaudio), Int32, (PaStream,), stream.pastream)
    check_pa_error(err)
    f()
    err = ccall((:Pa_StopStream, portaudio), Int32, (PaStream,), stream.pastream)
    check_pa_error(err)
end

function writeStream{T}(stream::Stream, data::Array{T})
    if stream.dtype != T
        error("Type mismatch: expected $(stream.dtype), got $T")
    end
    startStream(stream) do
        err = ccall((:Pa_WriteStream, portaudio), Int32, 
                    (PaStream, Ptr{Void}, Uint),
                    stream.pastream, data, length(data) / stream.channels)
        check_pa_error(err)
    end
end

function readStream(stream::Stream, nframes::Integer)
    println("Now recording. Speak clearly into the microphone.")
    arr = (stream.channels == 1) ? 
            Array(stream.dtype, nframes) : 
            Array(stream.dtype, stream.channels, nframes)
    startStream(stream) do
        err = ccall((:Pa_ReadStream, portaudio), Int32, (PaStream, Ptr{Void}, Uint), 
                    stream.pastream, arr, nframes)
        check_pa_error(err)
    end
    println("Finished recording")
    return arr
end

function readStream(stream::Stream, duration::FloatingPoint)
    nframes = int(duration * stream.sampleRate)
    return readStream(stream, nframes)
end
