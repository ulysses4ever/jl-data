#!/usr/bin/env julia

require("Sound")

const PART_SIZE = 4096
const NORM_SIZE = 32
const ALPHA = 0.54
const BETA = 1 - ALPHA
const EPSILON = 1e-10

function calcWindow()
	result = Array(Float64, PART_SIZE)
	for n = 1:PART_SIZE
		result[n] = ALPHA - BETA * cos((2 * pi * (n - 1)) / (PART_SIZE - 1))
	end
	return result
end

const window = calcWindow()

function analyze(fname)
	tmp = Sound.wavread(fname)
	channel1 = tmp[1][:,1]
	channel2 = tmp[1][:,2]
	srate = tmp[2]

	combined = (channel1 + channel2) / 2.0
	parts = int64(floor(length(combined) / PART_SIZE))
	result = Array(Float64, int64(PART_SIZE / 2))
	n = 0
	for p = 1:parts
		pstart = 1 + (p-1) * PART_SIZE
		pend = p * PART_SIZE
		part = combined[pstart:pend]

		# apply window function
		part .* window

		f = fft(part, 1)
		result += 20 .* log10(abs(f[1:PART_SIZE/2]) ./ PART_SIZE .+ EPSILON)
		n = (n + 1) % NORM_SIZE
		if n == 0
			println(join(result ./ NORM_SIZE, " "))
			result = Array(Float64, int64(PART_SIZE / 2))
		end
	end
end

for fname = ARGS
	analyze(fname)
end

