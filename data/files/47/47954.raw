using DataFrames
using RDatasets
using DecisionTree

labelsInfo = collect(1:6283)
labelsInfotest = collect(6284:12503)
A = read_data("train", labelsInfo, 400, "/home/carlos/Desktop/kaggle")
E = read_data("test", labelsInfotest, 400,  "/home/carlos/Desktop/kaggle")
H = readcsv("trainLabels.csv")[2:6284, 2]
features = convert(Array, A);
labels = convert(Array, H);

#10 random features and 10 trees so far the best
model = build_forest(labels, features, 50, 70)

test = convert(Array, E);

C = apply_forest(model, test);

D = [6284:12503 C];

f = open("Submission.csv")
writecsv("Submission.csv", D)
close(f)

#accuracy = nfoldCV_forest(labels, features, 20, 20, 3);
#println("3 fold accuracy: $(mean(accuracy))")
