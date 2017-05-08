function getCombinedScaleTrainData()

    dataset = open("./combined_scale")
    dataset = readall(dataset)
    dataset = filter(data -> length(data)>0, split(dataset, '\n'))
    dataset = map(data -> split(data, ' '), dataset)

    len = length(dataset)

    train_dataset = (Array{Float64,1}, Int64)[]

    for i in 1:len
        data = dataset[i]
        label = int(data[1])
        features = zeros(Float64, 100)
        for feature in data[2:end]
            if length(feature) == 0 continue end
            dim, val = split(feature, ':')
            features[int(dim)] = float64(val)
        end
        data = (features, label)
        push!(train_dataset, data)
    end

    # create passive aggresive instance
    numClass = 3
    numFeature = length(train_dataset[1][1])

    return (numClass, numFeature, train_dataset)
end

function getCombinedScaleTestData()

    dataset = open("./combined_scale.t")
    dataset = readall(dataset)
    dataset = filter(data -> length(data)>0, split(dataset, '\n'))
    dataset = map(data -> split(data, ' '), dataset)

    len = length(dataset)

    train_dataset = (Array{Float64,1}, Int64)[]

    for i in 1:len
        data = dataset[i]
        label = int(data[1])
        features = zeros(Float64, 100)
        for feature in data[2:end]
            if length(feature) == 0 continue end
            dim, val = split(feature, ':')
            features[int(dim)] = float64(val)
        end
        data = (features, label)
        push!(train_dataset, data)
    end

    # create passive aggresive instance
    numClass = 3
    numFeature = length(train_dataset[1][1])

    return (numClass, numFeature, train_dataset)
end
