using HDF5
using ZipFile

train_file = ARGS[1]
test_file  = ARGS[2]
hdf5_file  = ARGS[3]

h5open(hdf5_file, "w") do file
    g_train = g_create(file, "train")

	r = ZipFile.Reader(train_file)
	for f in r.files
	    sess = f.name[1:end-4]
	    println("Train ", sess)
	    data = readcsv(f, Float64, skipstart=1)
	    g_train[sess] = data
	end
	close(r)

    g_test = g_create(file, "test")

	r = ZipFile.Reader(test_file)
	for f in r.files
	    sess = f.name[1:end-4]
	    println("Test  ", sess)
	    data = readcsv(f, Float64, skipstart=1)
	    g_test[sess] = data
	end
	close(r)
end
