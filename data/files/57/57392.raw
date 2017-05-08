include("Dataset.jl")

type AMM
    numClass
    weightsList
    function AMM(numClass, numFeature)
        weightsList = Array[]
        for i in [1:numClass]
            push!(weightsList, Array[])
        end
        return new(numClass, weightsList)
    end
end

function getMaxDot(weights, feature)
    res = -1e9
    for i in [1:length(weights)] res = max(res, dot(weights[i], feature)) end
    return res
end

function train(amm::AMM, feature, label, lambda = 1e-1)
    # calculate i_t
    i_t = None
    dots = map(weights -> getMaxDot(weights, feature), amm.weightsList)
    for i in [1:amm.numClass]
        if i == label continue end
        if i_t == None || dots[i_t] < dots[i]
            i_t = i
        end
    end

    # calculate j_t
    dots = map(weight -> dot(weight, feature), amm.weightsList[i_t])
    j_t = None
    for j in [1:length(dots)]
        if j_t == None || (dots[j_t] > 0 && dots[j_t] < dots[j])
            j_t = j
        end
    end

    # calculate z_t
    dots = map(weight -> dot(weight, feature), amm.weightsList[label])
    z_t = None
    for z in [1:length(dots)]
        if z_t == None || (dots[z_t] > 0 && dots[z_t] < dots[z])
            z_t = z
        end
    end

    # regularize weights
    for c in [1:amm.numClass]
        for i in [1:length(amm.weightsList[c])]
            amm.weightsList[c][i] -= lambda*amm.weightsList[c][i]
        end
    end

    # add new weight or update old weight
    if j_t == None
        push!(amm.weightsList[i_t], deepcopy(feature))
    else
        amm.weightsList[i_t][j_t] += feature
    end

    if z_t == None
        push!(amm.weightsList[label], -1 * deepcopy(feature))
    else
        amm.weightsList[label][z_t] -= feature
    end

    # TODO: delete zero weights
end

function main()
    (numClass, numFeature, train_dataset) = getCombinedScaleTestData()


    amm = AMM(numClass, numFeature)
    for i in [1:100]
        train(amm, train_dataset[i][1], train_dataset[i][2])
    end

end

main()
