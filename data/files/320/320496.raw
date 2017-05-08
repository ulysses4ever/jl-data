using Base.Test
using Bebop

const duration = 2

const sampRate = 44100
# the A above middle C
const musicFreq = 440.0

const t = [1:duration * 44100] / float32(sampRate)
const xmono = sin(2 * pi * musicFreq * t)
const xstereo = [xmono'; xmono']

initialize() do
    openStream(sampRate, 1, Float32) do stream
        writeStream(stream, xmono)
    end
    openStream(sampRate, 2, Float32) do stream
        writeStream(stream, xstereo)
    end
end
