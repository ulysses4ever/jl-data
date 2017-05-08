using MachineLearning

function zmuv(x::Array{Float64,2})
    zm = broadcast(-, x, mean(x,1))
    res = broadcast(/, zm, std(zm,1))
    res[isnan(res)]=0.0
    res
end

data_path = joinpath(ENV["DataPath"], "Kaggle", "digit-recognizer")
data, header = readcsv(joinpath(data_path, "train.csv"), Float64, has_header=true)
x_train = zmuv(data[:,2:size(data,2)])
y_train = vec(data[:,1])
data, header  = readcsv(joinpath(data_path, "test.csv"), Float64, has_header=true)
x_test = zmuv(data)
opts = neural_net_options(hidden_layers=[200,100,50], stop_criteria=StopAfterIteration(50), display=true, learning_rate=500.0) 
net = fit(x_train, y_train, opts)
predictions = predict(net, x_test)
f = open(joinpath(data_path, "submissionNeuralNet.csv"), "w")
writecsv(f, ["ImageId" "Label"])
writecsv(f, [row[i] for row=zip(1:length(predictions), predictions), i=1:2])
close(f)