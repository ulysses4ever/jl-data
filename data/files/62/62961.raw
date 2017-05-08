using Gadfly

xor_oscillation_seed = uint32(123456789)
xorshift_original_seed = uint32(0xACE1)
linear_congruential_generator_seed = uint32(123456789)
linear_feedback_shift_regeister_val = uint16(123456789)
lfsr = uint16(0xACE1)

#Note for non-julia users, the operator '$' is the XOR operation in this language.
#Function found on wiki, modified the seed values slightly.

#	XOR_Oscillation
# Based on the XORShift random number function, I made this a while back for
# a game based research project I worked on.
y = uint32(362436069);
z = uint32(521288629);
w = uint32(88675123);
function xor_oscillation()
	global xor_oscillation_seed
    global y
	global z
	global w

    t = xor_oscillation_seed $ (xor_oscillation_seed << 11);
    xor_oscillation_seed = y; y = z; z = w;
    w = w $ (w >>> 19) $ (t $ (t >>> 8));
    return w;
end


#Most common xorshift
function xorshift_original()
	global xorshift_original_seed

	xorshift_original_seed $= (xorshift_original_seed << 21);
	xorshift_original_seed $= (xorshift_original_seed >>> 35);
	xorshift_original_seed $= (xorshift_original_seed << 4);
	return xorshift_original_seed;
end

#Standard in older versions of java and C#
function linear_congruential_generator()
	global linear_congruential_generator_seed
	#Make a number cloase to a power of two, for a in this case, this is jsut 2^32
	a = uint64(1103515245)
	
	#C is a relatively prime and close to a power of 2
	c = uint64(12345)
	
	#Modulo, also called M works well if this is a power of 2 and close to a prime number.
	modulo = uint64(2^31)
	linear_congruential_generator_seed = ((a * linear_congruential_generator_seed + c) % modulo)# &  0xffffff
	return linear_congruential_generator_seed
end

function linear_feedback_shift_register()
	global linear_feedback_shift_regeister_val
	global lfsr
	linear_feedback_shift_regeister_val  = ((lfsr >> 0) $ (lfsr >> 2) $ (lfsr >> 3) $ (lfsr >> 5) ) & 1;
	lfsr =  (lfsr >> 1) | (linear_feedback_shift_regeister_val << 15);	
	return lfsr
end

function plotRanges()
	max = 100
	xorshift_original_results =  zeros(max)
	xor_oscillation_results = zeros(max)
	lcg_results = zeros(max)
	lfsr_results = zeros(max)
	
	for i = 1:max
		returned_result = xor_oscillation()
		println(returned_result)
		lfsr_results[i] = returned_result
		#lcg_results[i] = linear_congruential_generator()
		#xor_oscillation_results[i] = xor_oscillation()
	end
	
	samplePoints = [1:1:max]
	#plot(x = samplePoints, y = [xor_oscillation_results, lcg_results, xorshift_original_results], color = "", Guide.XLabel("seed #"), Guide.YLabel("Number generated"))
	plot(x = samplePoints, y = lfsr_results,  Guide.XLabel("seed #"), Guide.YLabel("Number generated"))
end

function plotSeedDomains()
	max = 100
	xorshift_original_results =  zeros(max)
	xor_oscillation_results = zeros(max)
	lcg_results = zeros(max)
	
	for i = 1:max
		#xorshift_original_results[i] = xorshift_original(uint32(i))
		#lcg_results[i] = linear_congruential_generator(uint32(i))
		#xor_oscillation_results[i] = xor_oscillation(uint32(i))
		xor_oscillation_seed = xorshift_original_seed = linear_congruential_generator_seed = uint32(123456789)
	end
	
	samplePoints = [1:1:max]
	#plot(x = samplePoints, y = [xor_oscillation_results, lcg_results, xorshift_original_results], color = "", Guide.XLabel("seed #"), Guide.YLabel("Number generated"))
	plot(x = samplePoints, y = lcg_results,  Guide.XLabel("seed #"), Guide.YLabel("Number generated"))
end

plotRanges()