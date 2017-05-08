#Implementation of KNN to recognize letters/digits taken from Google Street View
println("Importing Images")
using Images
println("Importing DataFrames")
using DataFrames
println("Importing ImageView")
using ImageView
println("Importing Colors")
using Colors
println("Importing DecisionTree")
using DecisionTree
println("Imported all libraries")

function readData(dataType, imageSize, path, labelsInfo)
	println("Reading data from $(path)/$(dataType)Resized/")
	#intialize x matrix
	x = zeros(size(labelsInfo,1), imageSize)
	#read each image
	for (index, imageId) in enumerate(labelsInfo[:ID])
		namefile = "$(path)/$(dataType)Resized/$(imageId).Bmp"

		#read image
		img = imread(namefile)

		#convert to float and scale 0-1
		temp = float32(img)
	
		#convert to bw
		temp = convert(Array{Gray}, temp)

		x[index, :] = reshape(temp, 1, imageSize)
	end
	println("Finished reading images")
	return x
end

function euclideanDistance(a,b)
	if(size(a) != size(b))
		throw(ArgumentError("Size of arguments differ; sizes are
		$(size(a,1)) and $(size(b,1))"))
		return
	end

	distance = 0.0
	for i in 1:size(a,1)
		distance += (a[i] - b[i]) * (a[i] - b[i])
	end
	return distance
end

function findKNN(xMatrix, i, k)
	#It is assumed that in xMatrix, features are rows
	#and each datapoint (image) is a column

	nRows, nCols = size(xMatrix)

	#Make an empty vector then load the image into it 
	imageI = Array(Float32, nRows)
	for index in 1:nRows
		imageI[index] = xMatrix[index, i]
	end

	#Create temporary container for each image we will look at
	imageJ = Array(Float32, nRows)

	#Create vector which will contain distances from the points
	distances = Array(Float32, nCols)

	for j in 1:nCols
		
		#load imageJ
		for index in 1:nRows
			imageJ[index] = xMatrix[index, j]
		end
		#put the distance in the distance vector
		distances[j] = euclideanDistance(imageJ, imageI)
	end

	#Get indices of sorted elements (small to large)
	sortedIndices = sortperm(distances)
	if sortedIndices[1] != i
		println("PROBLEM AT $(i)")
	end
	return sortedIndices[2:k+1]
end

function getMostCommonLabel(xMatrix, labels, k, i)
	#xMatrix - Matrix containing the images/data
	#labels - contains elephants and dragons
	#k - The nearest k neighbors we want
	#i - the datapoint to which we want to find nearest k neigbhors

	neighbors = findKNN(xMatrix, i, k)

	dict = Dict{Int32, Int32}()
	topLabel = 0
	topCount = 0

	for i in neighbors
		label = labels[i]
		if !haskey(dict, label)
			dict[i] = 0
		end
		dict[i] += 1

		if dict[i] > topCount
			topLabel = label
			topCount = dict[i]
		end
	end

	return topLabel
end

println("Reading training and test labels")
path = "/home/shrif/Desktop/julia-code/kaggle-julia/resources"
labelsInfoTrain = readtable("$(path)/trainLabels.csv")
labelsInfoTest = readtable("$(path)/sampleSubmission.csv")
imgSize = 20 * 20

#=println("Performing sanity test for one image before reading the entire dataset")
println("Reading Image")
testImage = imread("$(path)/trainResized/1.Bmp")
view(testImage)

#float32sc is deprecated
println("Converting Image using float32") 
image = float32(testImage)
view(image)

println("Converting to gray")
bwImage = convert(Array{Gray}, image)
view(bwImage)
=#

#Read test and training datasets with corresponding labels
trainingImages = readData("train", imgSize, path, labelsInfoTrain)
trainingLabels = map(x -> x[1], labelsInfoTrain[:Class])
trainingLabels = int(trainingLabels)

#Reading columns is faster in Julia, so we transpose the matrix. 
#Read the part on the julia wiki about performance tips
trainingImages = trainingImages'

predictions = [getMostCommonLabel(trainingImages, trainingLabels, 2, i) for i in
1:size(trainingImages,2)]

LOOFCV_Accuracy = mean(predictions .== trainingLabels)
println("Accuracy: $(LOOFCV_Accuracy)")

#testImages = readData("test", imgSize, path, labelsInfoTest)

#Build random forest
#Takes a very long time to finish :(
#model = build_forest(trainingLabels, trainingImages, 20, 50, 1.0)
#accuracy = nfoldCV_forest(trainingLabels, trainingImages, 20, 50, 4, 1.0)
#println("Accuracy: 4-fold validation accuracy: $(mean(accuracy))")

#=Get predictions
testPredictions = apply_forest(model, testImages)
println("testPredictions")
println(testPredictions)

#Convert predictions to characters
testPredictions = char(testPredictions)
println(testPredictions)
writetable("$(path)/forestPredictions.csv", labelsInfoTest, separator=',',
header=true)=#
