using Gadfly

function xor128(x, y, z, w)
    x = uint32(123456789);
    y = uint32(362436069);
    z = uint32(521288629);
    w = uint32(88675123);

    t = x $ (x << 11);
    x = y; y = z; z = w;
    w = w $ (w >> 19) $ (t $ (t >> 8));
    return w;
end

function plotResults()
	
end
