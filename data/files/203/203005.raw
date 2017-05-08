using MachineLearning

data_path = joinpath(ENV["DataPath"], "Kaggle", "digit-recognizer")
data, header = readcsv(joinpath(data_path, "train.csv"), Float64, has_header=true)
x_train = data[:,2:size(data,2)]
y_train = vec(data[:,1])
data, header  = readcsv(joinpath(data_path, "test.csv"), Float64, has_header=true)
x_test = data
net = train(x_train, y_train, neural_net_options(stop_criteria=StopAfterIteration(100)))
predictions = predict(net, x_test)
f = open(joinpath(data_path, "submission.csv"), "w")
writecsv(f, ["ImageId" "Label"])
writecsv(f, [row[i] for row=zip(1:length(predictions), predictions), i=1:2])
close(f)