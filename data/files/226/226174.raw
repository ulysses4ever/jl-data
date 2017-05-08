using HDF5,JLD;

# Write data to binary file using HDF5 format
function hdf5Write(f,array)
	jldopen(f, "w") do ff
	@write ff array
	end
end

# Read data from binary file using HDF5 format
function hdf5Read(f)
    c = jldopen(f, "r") do ff
	read(ff,"array")
	end
end

# return a specific element from file
function hdf5Get(f,i)
	temp=hdf5Read(f);
	return temp[i]
end

# return a specific element from file
function hdf5Get(f,i,j)
	temp=hdf5Read(f);
	return temp[i,j]
end
