#typeData could be either "train" or "test.
#labelsInfo should contain the IDs of each image to be read
#The images in the trainResized and testResized data files
#are 20x20 pixels, so imageSize is set to 400.
#path should be set to the location of the data files.

using Images

function read_data(typeData, labelsInfo, imageSize, path)
 #Intialize x matrix
 x = zeros(size(labelsInfo, 1), imageSize);

 temp = zeros(20,20,3);

 for (index, idImage) in enumerate(labelsInfo)
  #Read image file
  nameFile = "$(path)/$(typeData)Resized/$(idImage).Bmp"
  img = load(nameFile);

  #Convert img to float values

  temp[:,:,1] = Colors.red(img);

  temp[:,:,2] = Colors.green(img);

  temp[:,:,3] = Colors.blue(img);

  #Convert color images to gray images
  #by taking the average of the color scales.

  t2 = mean(temp, 3);

  #Transform image matrix to a vector and store
  #it in data matrix

  x[index, :] = reshape(t2, 1, imageSize);

  #print("\b\b\b\b\b $(index)");

 end
 return x
end
