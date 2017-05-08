using Base.Test
using Bebop

const duration = 2

const sampRate = 44100f0
const musicFreq = 261.63

const t = [1:duration * 44100] / sampRate
const x = sin(2 * pi * musicFreq * t)

initialize() do
    openStream(sampRate, 1, Float32) do stream
        writeStream(stream, x)
    end
end
