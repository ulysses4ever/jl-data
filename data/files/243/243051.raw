function bitrev(x, bits)
	
	ind = [0:(length(x)-1);];
	new_ind = zeros(size(ind));
	out = zeros(Int64,size(x));
	
	for k=1:length(ind)
		new_ind[k] = parse(Int64,bin(ind[k],bits)[end:-1:1],2);
		#println(new_ind[k])
		out[k] = x[ Int(new_ind[k]+1) ];
	end
	return out;
end

# function main()
#
# 	x = [0:15;]#[0  8  4  5  8  4  9  3  7  9  8  4  7  2  0  6];
# 	y = bitrev(x,Int(log2(length(x))));
# 	println(x);
# 	println(y);
# end
#
# main();