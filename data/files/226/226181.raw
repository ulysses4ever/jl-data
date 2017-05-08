# write an array to file in binary format
function binaryWrite(file,array)
	stream=open(file,"w")

	# write to the file and close file
	serialize(stream,array)
	close(stream)
end

# read an array from file in binary format
function binaryRead(file)
	stream=open(file,"r")

	# read from the file
	retval=deserialize(stream)

	# close the stream and return
	close(stream)
	return retval
end
