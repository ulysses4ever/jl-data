#using HDF5, JLD

#fucntion that times how long it takes to output a string of data 
#to the common output 
function time_STDOUT(my_data::Array)
	 tic(); 
	 for i in 1:length(data)
	     println(data[i]); 
	 end
	 toc(); 
end 

#function that times the writing to a file of data in ASCII
function time_file_write_ASCII(my_data::Array,file_name = "my_data.txt"::String)
	 file_name = *(file_name,".txt"); 
	 tic()
	 writecsv(file_name,my_data); 
	 toc()
end 

#fucntion that times the read from a file of data in ASCII
function time_file_read_ASCII(file_name = "my_data"::String)
	 file_name = *(file_name,".txt"); 
	 tic(); 
	 readcsv(file_name);
	 toc(); 
end



