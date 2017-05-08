

function read_data(file_name)
	#open file and read it
	s = open(file_name);
	stuff = readlines(s);
	#get size of input and output
	dumby = split(stuff[1],' ');
	dumby = float(dumby);		
	#dumby[1] is number of data cases, dumby[2] is input size, dumby[3] is output size
	#make input and out put matrixes
	input = fill(0.0,int(dumby[2]),int(dumby[1]));
	output = fill(0.0,int(dumby[3]),int(dumby[1]));
	for n = 1:int(dumby[1])
		input[:,n] = float(split(stuff[2*n]))
		output[:,n] = float(split(stuff[2*n+1]))
	end
	return Data(int(dumby[2]),int(dumby[3]),int(dumby[1]),input,output);

end

