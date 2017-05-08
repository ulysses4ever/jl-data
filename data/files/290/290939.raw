module common

using Images
using DataFrames

export xTrain, xTest, yTrain, labelsInfoTest

#typeData could be either "train" or "test.
#labelsInfo should contain the IDs of each image to be read
#The images in the trainResized and testResized data files
#are 20x20 pixels, so imageSize is set to 400.
#path should be set to the location of the data files.

function read_data(typeData, labelsInfo, imageSize, path)
	#Intialize x matrix
 	x = zeros(size(labelsInfo, 1), imageSize)

 	for (index, idImage) in enumerate(labelsInfo[:ID]) 
  		#Read image file 
  		nameFile = "$(path)/$(typeData)Resized/$(idImage).Bmp"
  		img = imread(nameFile)

  		#Convert img to float values 
  		temp = separate(img)

  		#Convert color images to gray images
  		#by taking the average of the color scales. 
  		if ndims(temp) == 3
			 temp = mean(temp, 3)
  		end

  		#Transform image matrix to a vector and store 
  		#it in data matrix 
  		x[index, :] = reshape(temp, 1, imageSize)
 	end 
 	return x
end

imageSize = 400 # 20 x 20 pixel

#Set location of data files, folders
path = "."

#Read information about training data , IDs.
labelsInfoTrain = readtable("$(path)/trainLabels.csv")

println("Reading train matrix")
#Read training matrix
xTrain = read_data("train", labelsInfoTrain, imageSize, path)

#Read information about test data ( IDs ).
labelsInfoTest = readtable("$(path)/sampleSubmission.csv")

println("Read test matrix")
#Read test matrix
xTest = read_data("test", labelsInfoTest, imageSize, path)

yTrain = map(x->x[1], labelsInfoTrain[:Class])
yTrain = int(yTrain)

end