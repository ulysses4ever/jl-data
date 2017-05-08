#loads the data from file and split train/validation sets
function load_train(path, split::Float64)
    dataset = DataFrames.readtable(path,header=true);

    #split label from data
    y = convert(Vector{Int64}, vec(dataset[:,1]));
    X = convert(Matrix{Float64}, dataset[:,2:end]);

    # Generate train/test split
    n = length(y);
    is_train = shuffle([1:n] .> floor(n * split));

    X_train,X_test = X[is_train,:],X[!is_train,:];
    y_train,y_test = y[is_train],y[!is_train];

    # Print dataset general stats before training
    println("Total number of observations: ",n);
    println("Training set size: ", sum(is_train));
    println("Test set size: ", sum(!is_train));

    return X_train, X_test, y_train, y_test;
end

#load test dataset
function load_test(path)
    dataset = DataFrames.readtable(path,header=true);

    #split label from data
    X = convert(Matrix{Float64}, dataset);
    return X;
end
