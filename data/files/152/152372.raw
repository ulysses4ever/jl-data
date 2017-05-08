dataset = open("./winequality-red.csv", "r")

dataset = readall(dataset)
dataset = filter(data -> length(data)>0, split(dataset, '\n'))
dataset = map(data -> split(data, ';'), dataset)
titles = dataset[1]
dataset = map(data -> (map(float64, data[1:end-1]), int(data[end])+1), dataset[2:end])

type PassiveAggresive
    numClass::Int
    numFeature::Int
    weight::Array
    function PassiveAggresive(numClass, numFeature)
        weight = rand(numClass, numFeature)
        return new(numClass, numFeature, weight)
    end
end


function train(passiveAggresive::PassiveAggresive, features::Array, label::Int)
    losses = passiveAggresive.weight * features
    r = label
    s = -1
    for (index, loss) in enumerate(losses)
        if index == label continue end
        if s == -1 || loss > losses[s] s = index end
    end
    loss = max(0.0, 1.0 - (losses[r] - losses[s]))
    if loss > 0
        z = zeros(passiveAggresive.numClass)
        z[r] = 1
        z[s] = -1
        z = z*features'
        n = sum(map(a -> a*a, z))
        #tau = loss/n
        tau = loss/(n + 1.0/4.0) # PA-2
        passiveAggresive.weight += tau*z
    end
end

function predict(passiveAggresive::PassiveAggresive, features::Array)
    losses = passiveAggresive.weight * features
    return indmax(losses)
end

function main()
    # pre-processing
    numFeature = length(dataset[1][1])
    means = zeros(Float64, numFeature)

    for (features, label) in dataset
        means = means + features
    end

    means = means / length(dataset)

    vars = zeros(Float64, numFeature)

    for (features, label) in dataset
        tmp = features - means
        vars = tmp .* tmp
    end

    vars = vars / length(dataset)


    dataset = map(data -> (append!((data[1]- means)./sqrt(vars), [1.0]), data[2]), dataset)

    # create passive aggresive instance
    numClass = 10
    numFeature = length(dataset[1][1])

    passiveAggresive = PassiveAggresive(numClass, numFeature)

    # train
    for i in 1:30
        shuffle!(dataset)
        for (features, label) in dataset
            train(passiveAggresive, features, label)
        end
    end

    # test
    correct = 0.0
    for (features, label) in dataset
        predictLabel = predict(passiveAggresive, features)
        if predictLabel == label correct += 1 end
        #println(predictLabel, " ", label)
    end

    println(100.0*correct/length(dataset), "%")


end

