# write an array to file in ascii format
asciiWrite(file,array)=writedlm(file,array)

# read an array from file in ascii format
#	the default delim is taken to be "\n"
asciiRead(file)=readdlm(file,ASCIIString)

# return a specific element from file
function asciiGet(file,i)
	temp=asciiRead(file);
	return temp[i]
end

# return a specific element from file
function asciiGet(file,i,j)
	temp=asciiRead(file);
	return temp[i,j]
end
