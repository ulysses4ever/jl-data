type ConfusionMatrix
  classes::Vector
  matrix::Matrix{Int}
  accuracy::FloatingPoint
  kappa::FloatingPoint
end

function show(io::IO, cm::ConfusionMatrix)
  print(io, "Classes: ")
  show(io, cm.classes)
  print(io, "\nMatrix: ")
  display(cm.matrix)
  print(io, "\nAccuracy: ")
  show(io, cm.accuracy)
  print(io, "\nκ: ")
  show(io, cm.kappa)
end

## measures ##

function confusion_matrix(actual::Vector, predicted::Vector)
    @assert length(actual) == length(predicted)
    N = length(actual)
    _actual = zeros(Int,N)
    _predicted = zeros(Int,N)
    classes = sort(unique([actual; predicted]))
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

function mean_squared_error(actual, predicted)
    @assert length(actual) == length(predicted)
    return mean((actual - predicted).^2)
end

function R2(actual, predicted)
    @assert length(actual) == length(predicted)
    ss_residual = sum((actual - predicted).^2)
    ss_total = sum((actual .- mean(actual)).^2)
    return 1.0 - ss_residual/ss_total
end

## helper functions ##

function _kfoldCV{T<:FloatingPoint, U<:Real}(regressor::Symbol, labels::Vector{T}, features::Matrix{U}, nfolds::Integer,
                                             n_components::Integer, nferns::Integer)
    N = length(labels)
    ntest = _int(floor(N / nfolds))
    inds = randperm(N)
    R2s = zeros(nfolds)
    for i in 1:nfolds
        test_inds = falses(N)
        test_inds[(i - 1) * ntest + 1 : i * ntest] = true
        train_inds = !test_inds
        test_features = features[inds[test_inds],:]
        test_labels = labels[inds[test_inds]]
        train_features = features[inds[train_inds],:]
        train_labels = labels[inds[train_inds]]
        if regressor == :fern
            model = build_fern(train_labels, train_features, n_components)
            predictions, w = apply_fern(model, test_features)
        elseif regressor == :ensemble
            model = build_ensemble(train_labels, train_features, n_components, nferns)
            predictions = apply_ensemble(model, test_features)
        end

        err = mean_squared_error(test_labels, predictions)
        corr = cor(test_labels, predictions)
        r2 = R2(test_labels, predictions)
        R2s[i] = r2

        println("\nFold ", i)
        println("Mean Squared Error:     ", err)
        println("Correlation Coeff:      ", corr)
        println("Coeff of Determination: ", r2)
    end
    println("\nMean Coeff of Determination: ", mean(R2s))
    return R2s
end

kfoldCV_fern{T<:FloatingPoint, U<:Real}(labels::Vector{T}, features::Matrix{U}, nfolds::Integer, n_components::Integer)      = _kfoldCV(:fern, labels, features, nfolds, n_components, 1)
kfoldCV_fernEnsemble{T<:FloatingPoint, U<:Real}(labels::Vector{T}, features::Matrix{U}, nfolds::Integer, n_components::Integer, n_ferns::Integer)  = _kfoldCV(:ensemble, labels, features, nfolds, n_components, n_ferns)
