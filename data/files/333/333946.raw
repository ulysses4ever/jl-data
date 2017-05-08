dir="D:/imgnet/jlimgnet/data/features/"
savedir="D:/imgnet/jlimgnet/data"

# read data as vector (105s)
tic()
data=map(x->map(y->map(z->float64(z),split(y,' ')[2:end]),x),map(x->readlines(open("$dir$x")),readdir(dir)))
toc()

# get total number of imgs
N=sum(map(x->size(x,1),data))
features=Array(Float64,N,1024)
labels=Array(Int64,1,N)

# change them into matrices
tic()
acc=1
for i=1:size(data,1)
  for j=1:size(data[i],1)
    features[acc,:]=data[i][j]
    labels[acc]=i
    acc+=one(acc)
  end
end
toc()

using HDF5

filefeatures="$savedir/features.h5"
filelabels="$savedir/labels.h5"

isfile(filefeatures)?rm(filefeatures):0
h5write(filefeatures,"data/features",features)
isfile(filelabels)?rm(filelabels):0
h5write(filelabels,"data/labels",labels)
