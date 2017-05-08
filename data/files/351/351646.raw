using common
using DataFrames

addprocs(4)

@everywhere function euclidean_distance(a,b)
	distance = 0.0

	for i in 1:size(a,1)
		distance+= (a[i] - b[i])*(a[i] - b[i])
	end

	return distance
end

#This function finds the k nearest neighbors of the ith data point.
@everywhere function get_k_nearest_neighbors(x, i, k)

	nRows, nCols = size(x)

	#Let's initialize a vector image_i. We do this so that 
	#the image ith is accessed only once from the main X matrix.
	#The program saves time because no repeated work is done.
	#Also, creating an empty vector and filling it with each 
	#element at a time is faster than copying the entire vector at once.
	#Creating empty array (vector) of nRows elements of type Float32(decimal)
	imageI = Array(Float32, nRows) 

	for index in 1:nRows
		imageI[index] = x[index, i]
	end

	#For the same previous reasons, we initialize an empty vector 
	#that will contain the jth data point
	imageJ = Array(Float32, nRows)
	 
	#Let's also initialize an empty vector that will contain the distances
	#between the ith data point and each data point in the X matrix.
	distances = Array(Float32, nCols)
	 
	for j in 1:nCols
	  	#The next for loop fills the vector image_j with the jth data point 
	  	#from the main matrix. Copying element one by one is faster
	  	#than copying the entire vector at once.
		for index in 1:nRows
	   		imageJ[index] = x[index, j]
	  	end
	  	#Let's calculate the distance and save the result
	  	distances[j] = euclidean_distance(imageI, imageJ)
	end
	 
	#The following line gives the indices sorted by distances.
	sortedNeighbors = sortperm(distances)
	 
	#Let's select the k nearest neighbors. We start with the 
	#second closest. See explanation below.
	kNearestNeighbors = sortedNeighbors[2:k+1]
	return kNearestNeighbors
end

@everywhere function get_k_nearest_neighbors_test(x,k,test_image)
	nRows, nCols = size(x)

	image = Array(Float32,nRows)
	distances = Array(Float32, nCols)

	for obj in 1:nCols

		for pixel in 1:nRows
			image[pixel] = x[pixel,obj]
		end

		distances[obj] = euclidean_distance(image,test_image)
	end

	sortedNeighbours = sortperm(distances)

	kNearestNeighbors = sortedNeighbours[1:k]
	return kNearestNeighbors
end

#This function assigns a label to the ith point according to
#the labels of the k nearest neighbors. The training
#data is stored in the X matrix, and its labels are stored in y.
@everywhere function assign_label(x, y, k, test_image)
	kNearestNeighbors = get_k_nearest_neighbors_test(x, k, test_image)
	 
	#let's make a dictionary to save the counts of 
	#the labels
	# Dict{}() is also right .
	# Int,Int indicates the dictionary to expect integer values 
	counts = Dict{Int, Int}() 

	#The next two variables keep track of the 
	#label with the highest count.
	highestCount = 0
	mostPopularLabel = 0

	#Iterating over the labels of the k nearest neighbors
	for n in kNearestNeighbors
		labelOfN = y[n]
	  	#Adding the current label to our dictionary
	  	#if it's not already there
	  	if !haskey(counts, labelOfN)
	   		counts[labelOfN] = 0
	  	end
	  	#Add one to the count
	  	counts[labelOfN] += 1 

	  	if counts[labelOfN] > highestCount
	   		highestCount = counts[labelOfN]
	   		mostPopularLabel = labelOfN
	  	end 
	end
	return mostPopularLabel
end

#Similar to function assign_label.
#Only changes are commented
@everywhere function assign_label_each_k(x, y, maxK, i)
	kNearestNeighbors = get_k_nearest_neighbors(x, i, maxK) 

	#The next array will keep the labels for each value of k
	labelsK = zeros(Int, 1, maxK) 

	counts = Dict{Int, Int}()
	highestCount = 0
	mostPopularLabel = 0

	#We need to keep track of the current value of k
	for (k, n) in enumerate(kNearestNeighbors)
		labelOfN = y[n]
	  	if !haskey(counts, labelOfN)
	   		counts[labelOfN] = 0
	  	end
	  	counts[labelOfN] += 1
	  	if counts[labelOfN] > highestCount
	   		highestCount = counts[labelOfN]
	   		mostPopularLabel = labelOfN  
	  	end
	  	#Save current most popular label 
	  	labelsK[k] = mostPopularLabel
	end
	#Return vector of labels for each k
	return labelsK
end


function test_knn_model(xTrain, yTrain, maxK)
	xTrain = xTrain'

	yPredictionsK = @parallel (vcat) for i in 1:size(xTrain, 2)
		assign_label_each_k(xTrain, yTrain, maxK, i)
	end

	bestAccuracy = 0
	bestK = 0

	for k in 1:maxK
		accuracyK = mean(yTrain .== yPredictionsK[:, k])
	 	println("The LOOF-CV accuracy of $(k)-NN is $(accuracyK)")

	 	if accuracyK > bestAccuracy
	 		bestAccuracy = accuracyK
	 		bestK = k
	 	end
	end

	println("Best K is $(bestK) with accuracy $(bestAccuracy)")

	return bestAccuracy, bestK
end

function save_knn_submission(xTrain, yTrain, xTest, labelsInfoTest, k)
	xTrain = xTrain'
	xTest = xTest'

	println("Starting to predict")

	yPredictionsK = @parallel (vcat) for i in 1:size(xTest,2)
		nRows = size(xTest,1)
		test_image = Array(Float32,nRows)
		for r in 1:nRows
			test_image[r] = xTest[r,i]
		end
		assign_label(xTrain,yTrain,k,test_image)
	end

	labelsInfoTest[:Class] = char(yPredictionsK)

	#Set location of data files, folders
	path = "."

	writetable("$(path)/knnSubmission.csv", labelsInfoTest, separator=',', header=true)

	println("Saved")
end

println("Starting knn")

accuracy, k = test_knn_model(xTrain,yTrain,20)
save_knn_submission(xTrain,yTrain,xTest,labelsInfoTest,k)