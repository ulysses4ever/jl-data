# function to get index
function getindex_matlab(A,b)
	# returns a minimum index i s.t. A(i)>=b
	# if length(b)!=1
	# 	error('b should be a scalar...')
	# end
	temp  = A-b;
	temp_ind = temp.>=0;
	temp  = 1 : length(A);
	index = minimum(temp[temp_ind]);
end



