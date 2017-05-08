using MachineLearning

data_path = joinpath(ENV["DataPath"], "Kaggle", "digit-recognizer")
data, header = readcsv(joinpath(data_path, "train.csv"), Float64, has_header=true)
x_train = data[:,2:size(data,2)]
y_train = vec(data[:,1])
x_test, header  = readcsv(joinpath(data_path, "test.csv"), Float64, has_header=true)
forest = train(x_train, y_train, random_forest_options(num_trees=100))
for tree=forest.trees
    println(tree)
end
predictions = predict(forest, x_test)
f = open(joinpath(data_path, "forest_submission.csv"), "w")
writecsv(f, ["ImageId" "Label"])
writecsv(f, [row[i] for row=zip(1:length(predictions), predictions), i=1:2])
close(f)