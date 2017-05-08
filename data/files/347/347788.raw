# convert binary into HDF5 data

using HDF5
using Images

srand(12345678)


path = "data/"

datasets = ["train" => ["trainLabels.csv","trainResized"]
           ,"test" => ["sampleSubmission.csv","testResized"]]

for key in keys(datasets)
  label_fn, data_fn = datasets[key]
  label_f = readcsv(path*label_fn,header=true,String)[1]

#  data_f  = readcsv(data_fn)

#  label_header = label_f[1]
#  @assert ntoh(label_header[1]) == 2049

  n_label = label_f[1,2]
  println(n_label)
#  data_header = read(data_f, Int32, 4)
#  @assert ntoh(data_header[1]) == 2051
#  println(data_header[1])
#  n_data = int(ntoh(data_header[2]))
###  @assert n_label == n_data

   aFile = "$(path*key)Resized/$(int(label_f[1])).Bmp" 
   println(aFile)
   img = imread(aFile)
   #Convert img to float values 
   temp = float32(img)
   myMatrix = convert(Array{Gray},temp) 
    
  h = 20 # int(ntoh(data_header[3]))
  w = 20 # int(ntoh(data_header[4]))
#  println(n_data)
  n_batch = 1
  n_data =  size(label_f)[1]
  rp = randperm(n_data)
  class = int(map(first,label_f[:,2]))
#  @assert n_data % n_batch == 0
#  batch_size = int(n_data / n_batch)
  println("Exporting $n_data digits of size $h x $w")
  h5open("$(path*key).hdf5", "w") do h5
    dset_data = d_create(h5, "data", datatype(Float32), dataspace(w, h, 1, n_data))
    dset_label = d_create(h5, "label", datatype(Float32), dataspace(1, n_data))
    for i = 1:n_data 
        #Read image file  
 #       println(label_f[i])
        nameFile = "$(path*key)Resized/$(int(label_f[i])).Bmp" 
        img = imread(nameFile)
        #Convert img to float values 
        temp = float32(img)
        myMatrix = convert(Array{Gray},temp)
        r_idx = rp[i] 
        dset_data[:,:,1,i] =  reshape(myMatrix, 1, h * w)
        dset_label[1,i] = class[i]
    end
  end


  #close(label_f)
  #close(data_f)

end

