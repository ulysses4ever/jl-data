export letsjam, play

function letsjam(f::Function,
                 samprate::Integer = 44100,
                 channels::Integer = 1,
                 dtype::DataType = Float32)
    global jamstream
    initialize()
    jamstream = openStream(samprate, channels, dtype)
    f()
    closeStream(jamstream)
    jamstream = Nothing()
    terminate()
end

function play(data::Array)
    global jamstream
    if typeof(jamstream) != Nothing
        writeStream(jamstream, data)
    else
        error("play can only be called within a letsjam statement")
    end
end
