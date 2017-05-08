using Bebop
using Base.Test

if length(ARGS) < 1
    error("missing argument")
end

const duration = 5

initialize() do
    openFile(ARGS[1]) do file
        sampRate = file.sfinfo.samplerate
        channels = file.sfinfo.channels
        frames = readFrames(file, sampRate * duration)
        openStream(sampRate, channels, Int16) do stream
            writeStream(stream, frames)
        end
    end
end
