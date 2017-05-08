# Author: Brent Arata
# Date: 10/22/14

using Gadfly
#Note for non-julia users, the operator '$' is the XOR operation in this language.
#Function found on wiki, modified the seed values slightly.

#	XOR_Oscillation
# Based on the XORShift random number function, I made this a while back for
# a game based research project I worked on.
xorshift_seed = uint32(123456789)
#Any positive seeds will do but this will not produce zero ever, large prime numbers close to powers of two work best.
y = uint32(362436069);
z = uint32(52128877);
w = uint32(886751225);
function xorshift()
	global xorshift_seed
    global y
	global z
	global w

    t = xorshift_seed $ (xorshift_seed << 11);
    xorshift_seed = y; y = z; z = w;
    w = w $ (w >>> 19) $ (t $ (t >>> 8));
    return w;
end

linear_congruential_generator_seed = uint32(123456789)
#Standard in older versions of java and C#, not so fast but good for integrating with a utility function.
function linear_congruential_generator()
	global linear_congruential_generator_seed
	#a, c, and modulo must be a relatively prime number and close to a power of two.  The closer the numbers are in value, they converge.
	#to form a linear equation and there is no randomness involved.
	a = uint64(1103515245)
	
	c = uint64(12345)
	
	modulo = uint64(2^31)
	linear_congruential_generator_seed = ((a * linear_congruential_generator_seed + c) % modulo)
	return linear_congruential_generator_seed
end

linear_feedback_shift_regeister_val = uint16(123456789)
lfsr = uint16(0xACE1)
#Standard in newer versions of java and C#, most cryptographically secure.
function linear_feedback_shift_register()
	global linear_feedback_shift_regeister_val
	global lfsr
	linear_feedback_shift_regeister_val  = ((lfsr >> 0) $ (lfsr >> 2) $ (lfsr >> 3) $ (lfsr >> 5) ) & 1;
	lfsr =  (lfsr >> 1) | (linear_feedback_shift_regeister_val << 15);	
	return lfsr
end

function plotRNGs()
	max = 100
	xorshift_oscillation_results = zeros(max)
	lcg_results = zeros(max)
	lfsr_results = zeros(max)
	
	for i = 1:max
		xorshift_oscillation_results[i] = xorshift()
		lcg_results[i] = linear_congruential_generator()
		lfsr_results[i] = linear_feedback_shift_register()
	end
	samplePoints = [1:1:max]
	data = Gadfly.DataFrame(samplePoints = 1:100, results = lcg_results)

	a = Gadfly.DataFrame(x = samplePoints, y = xorshift_oscillation_results, RNG = "XORShift")
	b = Gadfly.DataFrame(x = samplePoints, y = lcg_results, RNG = "Least Congruential generator")
	c = Gadfly.DataFrame(x = samplePoints, y = lfsr_results, RNG = "Linear Feed Back shift generator")
	RNG_Results = vcat(a, b, c)
	p = plot(RNG_Results, x = "x", y = "y", color = "RNG", Geom.point, Scale.discrete_color_manual("blue","red", "green"), Guide.XLabel("Number of Points"), Guide.YLabel("y"))
	#draw(PNG("RNG_All.png",6inch,3inch),p)
end

function plotLCG()
	max = 100
	lcg_results = zeros(max)
	
	for i = 1:max
		lcg_results[i] = linear_congruential_generator()
	end
	samplePoints = [1:1:max]
	data = Gadfly.DataFrame(samplePoints = 1:100, results = lcg_results)

	a = Gadfly.DataFrame(x = samplePoints, y = lcg_results, RNG = "Least Congruential generator")
	p = plot(a, x = "x", y = "y", color = "RNG", Geom.point, Scale.discrete_color_manual("blue","red", "green"), Guide.XLabel("Number of Points"), Guide.YLabel("y"))
	#draw(PNG("RNG_LCG.png",6inch,3inch),p)
end