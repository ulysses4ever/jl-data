using LIBLINEAR

# init random generator to reproduce results
srand(0);

# load data from hdf5 files
include("load_h5_data.jl")

h5dir = "/home/lizz/data"
(features, labels) = load_imgnet_features(h5dir);

totalInstances = size(features, 1)
totalFeatures = size(features, 2)
totalClasses = maximum(labels)

println("we have total $totalClasses classes, $totalInstances instances, each has $totalFeatures features.")

include("svm_test.jl")

# how many classes to use
nClasses = 10 # configure
filter = labels .<= nClasses
nInstances = sum(filter);
instances = features[filter, :]
labels = labels[filter]

println("we use $nClasses classes, $nInstances instances, each has $nFeatures features.")

order = randperm(nInstances);
batch_size = 100 # configure
