function randindex{T<:Integer}(truth::Vector{T}, pred::Vector{T})
    # See Hubert and Arabie 1985 "Comparing Partitions"
    @assert  length(truth) == length(pred)

    n_samples = length(truth)
    classes = unique(truth)
    clusters = unique(pred)
    # Special limit cases: no clustering since the data is not split;
    # or trivial clustering where each document is assigned a unique cluster.
    # These are perfect matches hence return 1.0.
    if length(classes) == length(clusters) == 1 ||
            length(classes) == length(clusters) == 0 ||
            length(classes) == length(clusters) == length(truth)
        1.0
    else
        contingency = contingencymatrix(truth, pred)
        1 + (sum(contingency.^2) -
                (1/2) * (sum(sum(contingency, 1).^2) +
                         sum(sum(contingency, 2).^2))) / binomial(n_samples, 2)
    end
end

function randindex{T<:Integer}(truths::Vector{Vector{T}}, pred::Vector{T})
    mean([randindex(truth, pred) for truth in truths])
end

randindex{T<:Integer}(truth::Matrix{T}, pred::Matrix{T}) = randindex(truth[:], pred[:])

function randindex{T<:Integer}(truths::Vector{Matrix{T}}, pred::Matrix{T})
    mean([randindex(truth, pred) for truth in truths])
end

function randindex(cmat::Matrix{Int})
    N = sum(cmat)
    return 1 + (sum(cmat.^2) - (1/2) * (sum(sum(cmat, 1).^2) + sum(sum(cmat, 2).^2))) / binomial(N, 2)
end

randerror(truth, pred) = 1 - randindex(truth, pred) # randerror convenience function

function contingencymatrix{T<:Integer}(truth::Vector{T}, pred::Vector{T})
    # classes are the clusters according to truth
    # clusters are those according to the prediction
    # thus contingency matrix has truth along rows and preds along cols

    classes = sort(unique(truth))
    class_idx = [searchsortedfirst(classes, v) for v in truth]

    clusters = sort(unique(pred))
    cluster_idx = [searchsortedfirst(clusters, v) for v in pred]

    n_classes = length(classes)
    n_clusters = length(clusters)

    full(sparse(class_idx, cluster_idx, ones(Int, length(class_idx)), n_classes, n_clusters))
end
