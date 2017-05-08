using Bebop
using Base.Test

if length(ARGS) < 1
    error("missing argument")
end

const duration = 5

openFile(ARGS[1]) do file
    sampRate = file.sfinfo.samplerate
    channels = file.sfinfo.channels
    frames = readFrames(file, sampRate * duration)
    letsjam(sampRate, channels, Int16) do
        play(frames)
    end
end
