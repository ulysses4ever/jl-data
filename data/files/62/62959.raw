using Gadfly

function xor128(x, y, z, w)
    #x = uint32(123456789);
    #y = uint32(362436069);
    #z = uint32(521288629);
    #w = uint32(88675123);

    t = x $ (x << 11);
    x = y; y = z; z = w;
    w = w $ (w >> 19) $ (t $ (t >> 8));
    return w;
end

function plotResults()
	results =  fill(xor128(5,5,5,5), 10000)
	for i = 1:10000
		results[i] = xor128(uint32(i), uint32(362436069), uint32(521288629), uint32(88675123))
	end
	
	samplePoints = [1:1:1000]
	plot(x = [1:1:10000], y  = results, Guide.XLabel("Index"), Guide.YLabel("Step"))
end

plotResults()