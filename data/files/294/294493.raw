#Scale Dataset
function Scale!(ds)
    norm = (maximum(ds) - minimum(ds))
    ds = ds ./ norm  # normalize to [0..1]
    return ds, norm
end

function Scale!(ds, norm)
    return ds ./ norm  # normalize to [0..1]
end

function getPredictions(ann::ANN.ArtificialNeuralNetwork, pred::Matrix{Float64})
    s=size(pred)[1];
    #Convert prediction to mnist digit
    y_pred = Array(Int64,s)
    for i in 1:s
        # must translate class index to label
        y_pred[i] = ann.classes[indmax(pred[i,:])];
    end
    return y_pred;
end
