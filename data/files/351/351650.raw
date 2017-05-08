using common
using DecisionTree

#Set location of data files, folders
path = "."

println("Starting to build the model")
model = build_forest(yTrain,xTrain, 20, 50, 1.0)

println("Starting to predict")
predTest = apply_forest(model, xTest)

labelsInfoTest[:Class] = char(predTest)

writetable("$(path)/juliaSubmission.csv", labelsInfoTest, separator=',', header=true)

accuracy = nfoldCV_forest(yTrain, xTrain, 20, 50, 4, 1.0);
println ("4 fold accuracy: $(mean(accuracy))")