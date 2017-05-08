using Gadfly

#Note for non-julia users, the operator '$' is the XOR operation in this language.
function xor128(x)
    #x = uint32(123456789);
    y = uint32(362436069);
    z = uint32(521288629);
    w = uint32(88675123);

    t = x $ (x << 11);
    x = y; y = z; z = w;
    w = w $ (w >>> 19) $ (t $ (t >>> 8));
    return w;
end

function xorshift_original(x)
	x $= (x << 21);
	x $= (x >>> 35);
	x $= (x << 4);
	return x;
end

#Same random function in C#, Java, and javascript
function linear_congruential_generator(seed)
	#Make a number cloase to a power of two, for a in this case, this is jsut 2^32
	a = 2^32 + 31
	
	c = 2^12
	
	#Modulo, also called M works well if this is a power of 2 and close to a prime number.
	modulo = 2^32
	return (a * seed + c) % modulo
end

function plotResults()
	max = 100
	xorshift_original_results =  zeros(max)
	xor_oscillation_results = zeros(max)
	lcg_results = zeros(max)
	
	
	for i = 1:max
		xorshift_original_results[i] = xor_oscillation(uint32(i))
		lcg_results[i] = linear_congruential_generator(uint32(i))
		xor_oscillation_results[i] = xor_oscillation(uint32(i)) 
	end
	
	samplePoints = [1:1:max]
	plot(x = samplePoints, y = xorshift_original_results)
	plot(x = samplePoints, y = xor_oscillation_results)
end

plotResults()