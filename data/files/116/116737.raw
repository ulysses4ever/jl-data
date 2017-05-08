
function test_func_a(x)

	fittness = 0.0;
	for n=1:size(x,1)
		fittness = fittness + x[n];
	end
	return fittness
end

function test_func_b(x)

	fittness = 0.0;
	for n=1:size(x,1)
		fittness = fittness + x[n]*mod(n,2);
	end
	return fittness
end

function test_func_c(x)

	fittness = 0.0;
	for n=1:size(x,1)
		fittness = fittness + x[n] * (mod(n, 5) - 2);
	end
	return fittness
end

function test_func_d(x)
	fittness = 0.0;
	for n=1:size(x,1)
		fittness = fittness + x[n] * (mod(n, 5) - 2);
	end
	for n=1:size(x,1)
		fittness = fittness + x[n] * (mod(n, 11) - 5);
	end
	for n=1:size(x,1)
		fittness = fittness + x[n] * (mod(n, 3) - 1);
	end
	return fittness
end








