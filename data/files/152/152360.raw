include("PassiveAggresive.jl")
include("Dataset.jl")

function main()
    (numClass, numFeature, train_dataset) = getCombinedScaleTrainData()

    passiveAggresive = PassiveAggresive(numClass, numFeature)

    # train
    for i in 1:5
        println("epoch: ", i)
        shuffle!(train_dataset)
        for (features, label) in train_dataset
            train(passiveAggresive, features, label)
        end
    end

    # test
    (numClass, numFeature, test_dataset) = getCombinedScaleTestData()

    correct = 0.0
    for (features, label) in test_dataset
        predictLabel = predict(passiveAggresive, features)
        if predictLabel == label correct += 1 end
    end

    println("correct ratio: ", 100.0*correct/length(test_dataset), "%")
end

main()
