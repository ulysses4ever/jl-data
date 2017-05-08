type ConfusionMatrix
    classes::Vector
    matrix::Matrix{Int}
    accuracy::FloatingPoint
    kappa::FloatingPoint
end

function show(io::IO, cm::ConfusionMatrix)
    print(io, "Classes:  ")
    show(io, cm.classes)
    print(io, "\nMatrix:   ")
    show(io, cm.matrix)
    print(io, "\nAccuracy: ")
    show(io, cm.accuracy)
    print(io, "\nKappa:    ")
    show(io, cm.kappa)
end

function _set_entropy(labels::Vector)
    N = length(labels)
    counts = Dict()
    for i in labels
        counts[i] = get(counts, i, 0) + 1
    end
    entropy = 0
    for i in counts
        v = i[2]
        if v > 0
            entropy += v * log(v)
        end
    end
    entropy /= -N
    entropy += log(N)
    return entropy
end

function _info_gain(labels0::Vector, labels1::Vector)
    N0 = length(labels0)
    N1 = length(labels1)
    N = N0 + N1
    H = - N0/N * _set_entropy(labels0) - N1/N * _set_entropy(labels1)
    return H
end

function _neg_z1_loss{T<:Real}(labels::Vector, weights::Vector{T})
    missmatches = labels .!= majority_vote(labels)
    loss = sum(weights[missmatches])
    return -loss
end

function _weighted_error{T<:Real}(actual::Vector, predicted::Vector, weights::Vector{T})
    mismatches = actual .!= predicted
    err = sum(weights[mismatches]) / sum(weights)
    return err
end

function majority_vote(labels::Vector)
    counts = Dict()
    for i in labels
        counts[i] = get(counts, i, 0) + 1
    end
    top_vote = None
    top_count = -Inf
    for i in collect(counts)
        if i[2] > top_count
            top_vote = i[1]
            top_count = i[2]
        end
    end
    return top_vote
end

function confusion_matrix(actual::Vector, predicted::Vector)
    @assert length(actual) == length(predicted)
    N = length(actual)
    _actual = zeros(Int,N)
    _predicted = zeros(Int,N)
    classes = sort(unique([actual, predicted]))
    N = length(classes)
    for i in 1:N
        _actual[actual .== classes[i]] = i
        _predicted[predicted .== classes[i]] = i
    end
    CM = zeros(Int,N,N)
    for i in zip(_actual, _predicted)
        CM[i[1],i[2]] += 1
    end
    accuracy = trace(CM) / sum(CM)
    prob_chance = (sum(CM,1) * sum(CM,2))[1] / sum(CM)^2
    kappa = (accuracy - prob_chance) / (1.0 - prob_chance)
    return ConfusionMatrix(classes, CM, accuracy, kappa)
end

function _nfoldCV(classifier::Symbol, labels, features, args...)
    nfolds = args[end]
    if nfolds < 2
        return
    end
    if classifier == :tree
        pruning_purity = args[1]
    elseif classifier == :forest
        nsubfeatures = args[1]
        ntrees = args[2]
    elseif classifier == :stumps
        niterations = args[1]
    end
    N = length(labels)
    ntest = ifloor(N / nfolds)
    inds = randperm(N)
    accuracy = zeros(nfolds)
    for i in 1:nfolds
        test_inds = falses(N)
        test_inds[(i - 1) * ntest + 1 : i * ntest] = true
        train_inds = !test_inds
        test_features = features[inds[test_inds],:]
        test_labels = labels[inds[test_inds]]
        train_features = features[inds[train_inds],:]
        train_labels = labels[inds[train_inds]]
        if classifier == :tree
            model = build_tree(train_labels, train_features, 0)
            if pruning_purity < 1.0
                model = prune_tree(model, pruning_purity)
            end
            predictions = apply_tree(model, test_features)
        elseif classifier == :forest
            model = build_forest(train_labels, train_features, nsubfeatures, ntrees)
            predictions = apply_forest(model, test_features)
        elseif classifier == :stumps
            model, coeffs = build_adaboost_stumps(train_labels, train_features, niterations)
            predictions = apply_adaboost_stumps(model, coeffs, test_features)
        end
        cm = confusion_matrix(test_labels, predictions)
        accuracy[i] = cm.accuracy
        println("\nFold ", i)
        println(cm)
    end
    println("\nMean Accuracy: ", mean(accuracy))
    return accuracy
end

nfoldCV_tree(labels::Vector, features::Matrix, pruning_purity::Real, nfolds::Integer)                       = _nfoldCV(:tree, labels, features, pruning_purity, nfolds)
nfoldCV_forest(labels::Vector, features::Matrix, nsubfeatures::Integer, ntrees::Integer, nfolds::Integer)   = _nfoldCV(:forest, labels, features, nsubfeatures, ntrees, nfolds)
nfoldCV_stumps(labels::Vector, features::Matrix, niterations::Integer, nfolds::Integer)                     = _nfoldCV(:stumps, labels, features, niterations, nfolds)


##########################################################
function ss{T <: Real}(y::Array{T})
        y | x -> (x .- mean(x)) .^ 2 | sum
end

function ss_by_col(responses::Matrix)
    mapslices(ss, responses, 1) | sum
end



function table{T <: Integer}(label::Vector{T}, mykeys::Vector{T})
    key_length = length(mykeys)
    counts = zeros(Int64, key_length)
    for i in label[1:length(label)]
        for j in 1:key_length
            if i == mykeys[j]
                counts[j] += 1
                break
            end
        end
    end
    (mykeys, counts)

end

function table{T <: Integer}(label::Vector{T})
    mykeys = unique(label)
    key_length = length(mykeys)
    counts = zeros(Int64, key_length)

    
    for i in label[1:length(label)]
        for j in 1:key_length
            if i == mykeys[j]
                counts[j] += 1
                break
            end
        end
    end
    (mykeys, counts)
end


function ss_ratio{T <: Integer}(v1::Vector{T}, v2::BitArray{1}, mykeys::Vector{T}) 
    d_value = table(v1, mykeys)[2]
    d1_value = table(v1[v2], mykeys)[2]
    d2_value = table(v1[!v2], mykeys)[2]
    n_true = sum(v2)
    n_false = sum(!v2)
    all_ss = 0.0
    for i in 1:length(mykeys) 
        if d_value[i] != 0
            all_ss += (d1_value[i] ^ 2 / n_true + d2_value[i] ^ 2 / n_false) / d_value[i]
        end
    end
    all_ss / length(mykeys)
end
ss_ratio{T <: Integer}(v1::Vector{T}, v2::BitArray{1}) = ss_ratio(v1, v2, unique(v1)) 

function ss_ratio{T <: Integer}(m1::Matrix{T}, v2::BitArray{1}, mykeys::Vector{T})
    ratio_sum = 0.0
    for i in 1:size(m1, 2)
        ratio_sum += ss_ratio(m1[:, i], v2, mykeys) 
    end
    ratio_sum / size(m1, 2)
end


function ss_ratio{T <: Integer}(m1::Matrix{T}, v2::BitArray{1})
    np = size(m1, 2)
    mykeys = unique(m1[:, 1])
    for i in randperm(np)[1:min(10, np)]
        tmp = unique(m1[:, i])
        if length(tmp) > length(mykeys)
            mykeys = tmp
        end
    end
    ss_ratio(m1, v2, mykeys)
end








