using Base.Test
using Bebop

const sampRate = 44100
const duration = 5.0

initialize() do
    openStream(sampRate, 2, Int16) do stream
        record = readStream(stream, duration)
        sleep(1)
        writeStream(stream, record)
    end
end
