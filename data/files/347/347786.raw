using HDF5, Images, DataFrames;

datasets = [("train", ["$i.Bmp" for i in 1:6000]),
            ("test",  ["$i.Bmp" for i in 6001:6283])]

const width    = 20
const height   = 20
const channels = 3

path = pwd()

for (key, sources) in datasets
    h5open("data/$key.hdf5", "w") do h5
        dset_data = d_create(h5, "data", datatype(Float32), 
            dataspace(width, height, channels, length(sources)))
        dset_label = d_create(h5, "label", datatype(Float32), 
            dataspace(1, length(sources)))
        
        label = float32(map(x -> x[1], readtable("$(path)/data/trainLabels.csv")[:Class]))
        if key == "train"
            idx = 1:6000
        else
            idx = 6001:6283
        end

        
        for n = 1:length(sources)
            fn  = "$(path)/data/trainResized/$(sources[n])"
            img = imread(fn)
            temp = reinterpret(Float32, float32(img))
            dset_data[:,:,:,n] = temp
            dset_label[1,n] = label[n]
        end
    end
end
