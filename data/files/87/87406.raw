#include("data.jl")


function read_data_MSB(file_name_image,file_name_label,size)
	# pretty shity that have the size in there
	#open file and read it
	s = open(file_name_image);
	ss = open(file_name_label);
	#seek correct possition 
	seek(s,16);
	seek(ss,8);		
	#read in data
	input = read(s,Uint8,784,size);
	store_output = read(ss,Uint8,size);
	output = fill(0.0,10,size);
	for n = 1:size
		output[store_output[n]+1,n] = 1.0;
	end
	input = input ./ 255 
	return Data(784,10,size,input,output);

end

