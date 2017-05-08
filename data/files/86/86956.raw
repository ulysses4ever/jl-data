using HDF5
using ZipFile

train_file = ARGS[1]
test_file  = ARGS[2]
hdf5_dir    = ARGS[3]

r = ZipFile.Reader(train_file)
for f in r.files
    data = readcsv(f, Float64, skipstart=1)
    sess = f.name[1:end-4]
    h5write(joinpath(hdf5_dir, "Train", sess*".h5"), "bci/data", data)
end
close(r)
