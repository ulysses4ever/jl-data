using Base.Test
using Bebop

const sampRate = 44100.0
const duration = 15.0

initialize() do
    openStream(sampRate, 1, Int16) do stream
        record = readStream(stream, duration)
        writeStream(stream, record)
    end
end
