using HDF5

function load_imgnet_features(h5dir)
  # h5dir="D:/imgnet/jlimgnet/data"
  filefeatures="$h5dir/features.h5"
  filelabels="$h5dir/labels.h5"

  tic()
  println("opening $filefeatures")
  features=h5read(filefeatures,"data/features")
  println("opening $filelabels")
  labels=h5read(filelabels,"data/labels")
  print("loading ")
  toc()

  if size(features, 1) != length(labels)
    error("number of instances and labels not equal!")
  end

  (features, labels)
end
