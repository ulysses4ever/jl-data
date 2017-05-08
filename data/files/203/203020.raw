using MachineLearning

opts = PipelineOptions([ZmuvOptions()], neural_net_options(hidden_layers=[600], stop_criteria=StopAfterIteration(25), display=true, learning_rate=500.0, track_cost=true))

data_path = joinpath(ENV["DataPath"], "Kaggle", "digit-recognizer")
data, header = readcsv(joinpath(data_path, "train.csv"), Float64, has_header=true)
x_train = data[:,2:size(data,2)]
y_train = vec(data[:,1])
x_test, header  = readcsv(joinpath(data_path, "test.csv"), Float64, has_header=true)

pipeline = fit(x_train, y_train, opts)
predictions = predict(pipeline, x_test)
f = open(joinpath(data_path, "submissionNeuralNet.csv"), "w")
writecsv(f, ["ImageId" "Label"])
writecsv(f, [row[i] for row=zip(1:length(predictions), predictions), i=1:2])
close(f)
