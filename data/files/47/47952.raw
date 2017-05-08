using DataFrames
using RDatasets
using DecisionTree

is_train = shuffle([1:42000] .> floor(n* 250))
features, features_test = train[is_train,:], train[!is_train ,:]
features = convert(Array, features[1:size(features,1), 2:785]);
labels = convert(Array, train[1:size(features,1), 1]);

model = build_forest(labels, features, 20, 20)

test = dataset("/home/carlos/Desktop/Recognizer", "test")
test = convert(Array, test)

C = apply_forest(model, test)
C = round(Int64, C)

D = [1:28000 C]

f = open("results4.csv")
writecsv("results4.csv", D)
close(f)

accuracy = nfoldCV_forest(labels, features, 20, 20, 3, 0.5);
println("3 fold accuracy: $(mean(accuracy))")
