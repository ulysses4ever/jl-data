srand(42); 
data = randn(1024);

#fucntion that times how long it takes to output a string of data 
#to the common output 
function time_STDOUT(my_data::Array)
	 tic(); 
	 for i in 1:length(data)
	     println(data[i]); 
	 end
	 toc(); 
end 

#function which writes an array of data to file separated by commas 
function time_file_write(my_data::Array)
	 println("Is my data file open?");
	 tic()
	 writecsv("data_test1.txt",my_data); 
	 toc()
end 

#time_STDOUT(data); 

writecsv("Desktop/HPC/HW3/my_data_test.txt",data); 

