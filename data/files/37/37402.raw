#!/usr/bin/env julia

require("Sound")

const BIN_COUNT = 40

function discretize(data, n)
	dist = fill(0.0, n)
	size = length(data)
	lsize = log(size)
	for i = 1:length(data)
		j = max(1, int64(ceil(log(i) / lsize * n)))
		dist[j] += data[i]
	end
	return dist / sum(dist)
end

function analyze(fname)
	tmp = Sound.wavread(fname)
	channel1 = tmp[1][:,1]
	channel2 = tmp[1][:,2]
	srate = tmp[2]

	combined = (channel1 + channel2) / 2.0
	f = abs(fft(combined, 1))

	lowerBound = 1
	upperBound = int64(ceil(length(f) / 2))
	return discretize(f[lowerBound : upperBound], BIN_COUNT)
end

for fname = ARGS
	data = analyze(fname)
	println(join(data, " "))
end

