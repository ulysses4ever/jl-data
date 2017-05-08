import Bebop

const duration = 2

const sampRate = 44100f0
const musicFreq = 261.63

const t = [1:duration * 44100] / sampRate
const x = sin(2 * pi * musicFreq * t)

Bebop.initialize() do
    stream = Bebop.openStream(sampRate, 1, Float32)
    Bebop.writeStream(stream, x)
    Bebop.closeStream(stream)
end
