module MvDecisionTrees

export Leaf, Node, Ensemble, BuildTreeParameters, print_tree, depth,
       build_stump, build_tree, build_tree_covariance, apply_tree, nfoldCV_tree,
       build_forest, build_forest_covariance, apply_forest, nfoldCV_forest,
       majority_vote, 
       mean_squared_error, R2, _int

if VERSION.minor >= 4
    typealias Range1{Int} Range{Int}
    _int(x) = round(Int, x)
else
    _int(x) = int(x)
end

const NO_BEST=(0,0)

immutable Leaf
    majority::Any
    values::Matrix # rows are samples
end

immutable Node
    featid::Int # id of the feature we use to split
    featval::Any # value over which we split
    left::Union(Leaf, Node)
    right::Union(Leaf, Node)
end

immutable Ensemble
    trees::Vector{Node}
end

type BuildTreeParameters
    nsubfeatures::Int # number of candidate features to select for split; 0 will use all
    max_depth::Int # will only split if above this depth (depth of just a leaf is 0)
    min_samples_split::Int # minimum number of samples requried in a node to split
    min_samples_leaves::Int # minimum number of samples in newly created leaves
    min_split_improvement::Float64 # will only split if loss(split(leaf)) > loss(leaf) + min_split_improvement
    loss_function::Symbol # ∈ [:mse, :logl]

    function BuildTreeParameters(;
        nsubfeatures::Int=0,
        max_depth::Int=typemax(Int),
        min_samples_split::Int=5,
        min_samples_leaves::Int=0,
        min_split_improvement::Float64=-Inf,
        loss_function::Symbol=:mse
        )

        @assert(nsubfeatures ≥ 0)
        @assert(max_depth ≥ 0)
        @assert(min_samples_split ≥ 0)
        @assert(min_samples_leaves ≤ min_samples_split/2)
        @assert(in(loss_function, [:mse, :logl]))

        new(nsubfeatures, max_depth, min_samples_split, min_samples_leaves, min_split_improvement, loss_function)
    end
end

Base.convert(::Type{Node}, x::Leaf) = Node(0, nothing, x, Leaf(nothing,[nothing]'))
Base.promote_rule(::Type{Node}, ::Type{Leaf}) = Node
Base.promote_rule(::Type{Leaf}, ::Type{Node}) = Node

Base.length(::Leaf) = 1
Base.length(tree::Node) = length(tree.left) + length(tree.right)
Base.length(ensemble::Ensemble) = length(ensemble.trees)

depth(::Leaf) = 0
depth(tree::Node) = 1 + max(depth(tree.left), depth(tree.right))

_nsamples_labels(labels::Matrix{Float64}) = size(labels,2)
_nobservations(labels::Matrix{Float64}) = size(labels,1)

function print_tree(leaf::Leaf, depth::Integer=-1, indent::Integer=0)
    # NOTE(tim): I think this only works for classification
    matches = find(leaf.values .== leaf.majority)
    ratio = string(length(matches)) * "/" * string(length(leaf.values))
    print("    " ^ indent * "R-> ")
    println("$(leaf.majority) : $(ratio)")
end

function print_tree(tree::Node, depth::Integer=-1, indent::Integer=0)
    if depth == indent
        println()
        return
    end
    println("Feature $(tree.featid), Threshold $(tree.featval)")
    print("    " ^ indent * "L-> ")
    print_tree(tree.left, depth, indent + 1)
    print("    " ^ indent * "R-> ")
    print_tree(tree.right, depth, indent + 1)
end

function _hist_add!{T}(counts::Dict{T,Int}, labels::Vector{T}, region::Range1{Int})
    for i in region
        lbl = labels[i]
        counts[lbl] = get(counts, lbl, 0) + 1
    end
    return counts
end

function _hist_sub!{T}(counts::Dict{T,Int}, labels::Vector{T}, region::Range1{Int})
    for i in region
        lbl = labels[i]
        counts[lbl] -= 1
    end
    return counts
end

function _hist_shift!{T}(counts_from::Dict{T,Int}, counts_to::Dict{T,Int}, labels::Vector{T}, region::Range1{Int})
    for i in region
        lbl = labels[i]
        counts_from[lbl] -= 1
        counts_to[lbl] = get(counts_to, lbl, 0) + 1
    end
    return nothing
end

_hist{T}(labels::Vector{T}, region::Range1{Int} = 1:endof(labels)) = 
    _hist_add!(Dict{T,Int}(), labels, region)

function majority_vote(labels::Vector)
    if length(labels) == 0
        return nothing
    end
    counts = _hist(labels)
    top_vote = labels[1]
    top_count = -1
    for (k,v) in counts
        if v > top_count
            top_vote = k
            top_count = v
        end
    end
    return top_vote
end

apply_tree(leaf::Leaf, feature::Vector) = leaf.majority

function apply_tree(tree::Node, features::Vector)
    if tree.featval == nothing
        return apply_tree(tree.left, features)
    elseif features[tree.featid] < tree.featval
        return apply_tree(tree.left, features)
    else
        return apply_tree(tree.right, features)
    end
end

function apply_tree(tree::Union(Leaf,Node), features::Matrix)
    N = size(features,1)
    predictions = Array(Any,N)
    for i in 1:N
        predictions[i] = apply_tree(tree, squeeze(features[i,:],1))
    end
    if typeof(predictions[1]) <: FloatingPoint
        return float(predictions)
    elseif typeof(predictions[1]) <: Vector && eltype(predictions[1]) <: FloatingPoint
        retval = Array(Vector{Float64}, length(predictions))
        for i = 1 : N
            retval[i] = float(predictions[i])
        end
        return retval
    else
        return predictions
    end
end

function apply_forest(forest::Ensemble, features::Vector)
    ntrees = length(forest)
    votes = Array(Any,ntrees)
    for i in 1:ntrees
        votes[i] = apply_tree(forest.trees[i],features)
    end
    if typeof(votes[1]) <: FloatingPoint
        return mean(votes)
    elseif typeof(votes[1]) <: Vector && eltype(votes[1]) <: FloatingPoint
        return mean(votes)
    elseif typeof(votes[1]) <: Matrix && eltype(votes[1]) <: FloatingPoint
        return mean(votes)
    else
        return majority_vote(votes)
    end
end

function apply_forest(forest::Ensemble, features::Matrix)
    N = size(features,1)
    predictions = Array(Any,N)
    for i in 1:N
        predictions[i] = apply_forest(forest, squeeze(features[i,:],1))
    end
    if typeof(predictions[1]) <: FloatingPoint
        return float(predictions)
    elseif typeof(predictions[1]) <: Vector && eltype(predictions[1]) <: FloatingPoint
        retval = Array(Vector{Float64}, length(predictions))
        for i = 1 : N
            retval[i] = float(predictions[i])
        end
        return retval
    elseif typeof(predictions[1]) <: Matrix && eltype(predictions[1]) <: FloatingPoint
        retval = Array(Matrix{Float64}, length(predictions))
        for i = 1 : N
            retval[i] = float(predictions[i])
        end
        return retval
    else
        return predictions
    end
end

### Regression ###
function _select_random_subfeature_indeces(nsubfeatures::Int, nfeatures::Int)
    if nsubfeatures > 0
        r = randperm(nfeatures)
        inds = r[1:nsubfeatures]
    else
        inds = 1:nfeatures
    end
end

function _mse_loss{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Vector{U}, thresh)

    # mse loss for a vector is tr{E{(y-p)(y-p)ᵀ}}
    # where y is the label
    # and p is the prediction - the average of labels on that side of the threshold

    n, m = size(labels) # n_samples, n_outcomes
    loss = 0.0
    nl = nr = 0

    for i = 1 : n
        s_l, s_r = 0.0, 0.0
        nl = nr = 0
        for j = 1 : m
            l = labels[i,j]
            loss += l*l
            if features[j] < thresh
                s_l += l
                nl += 1
            else
                s_r += l
                nr += 1
            end
        end
        loss -= s_l*s_l / nl
        loss -= s_r*s_r / nr
    end

    return (-loss, nl, nr)
end
function _mse_loss{T<:FloatingPoint}(labels::Matrix{T})

    # mse loss for a vector is tr{E{(y-p)(y-p)ᵀ}}
    # where y is the label
    # and p is the prediction - the average of labels on that side of the threshold

    n, m = size(labels) # n_samples, n_outcomes
    loss = 0.0

    for i = 1 : n
        s = 0.0
        for j = 1 : m
            l = labels[i,j]
            loss += l*l
            s += l
        end
        loss -= s*s / m
    end

    return -loss
end

function _logl_loss{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Vector{U}, thresh)

    # labels is n_samples × n_outcomes and contains the distance from the mean, x-μ
    # we want to predict the covariance matrix Σ, which is determined by the covariance
    # of the samples in a leaf

    n, m = size(labels)
    
    Σ_l = zeros(n,n)
    Σ_r = zeros(n,n)

    nl, nr = 0, 0

    # solve for upper triangle of symmetric matrix
    for i = 1 : m
        if features[i] < thresh
            for a = 1 : n
                l = labels[a,i]
                for b = a : n
                    Σ_l[a,b] += l*labels[b,i]
                end
            end
            nl += 1
        else
            for a = 1 : n
                l = labels[a,i]
                for b = a : n
                    Σ_r[a,b] += l*labels[b,i]
                end
            end
            nr += 1
        end
    end
    Σ_l ./= (nl-1)
    Σ_r ./= (nr-1)

    # NOTE(tim): force at least two samples on each side to ensure proper covariance matrix
    if nl < 2 || nr < 2
        return (-Inf, nl, nr)
    end

    # move copy over symmetric component
    for a = 2:n
        for b = 1:a-1
            Σ_l[a,b] = Σ_l[b,a]
            Σ_r[a,b] = Σ_r[b,a]
        end
    end

    logdetΣ_l = log(max(det(Σ_l), 1e-20))
    logdetΣ_r = log(max(det(Σ_r), 1e-20))

    # compute log likelihood (we seek to maximize it)
    # NOTE: ignores constant components
    logl = 0.0
    for i = 1 : m
        if features[i] < thresh
            logl -= logdetΣ_l
            for a = 1 : n
                subval = 0.0
                for b = 1 : n
                    subval += Σ_l[a,b]*labels[b,i]
                end
                logl -= subval*labels[a,i]
            end
        else
            logl -= logdetΣ_r
            for a = 1 : n
                subval = 0.0
                for b = 1 : n
                    subval += Σ_r[a,b]*labels[b,i]
                end
                logl -= subval*labels[a,i]
            end
        end
    end

    return (logl, nl, nr)
end
function _logl_loss{T<:FloatingPoint}(labels::Matrix{T})

    # labels is n_samples × n_outcomes and contains the distance from the mean, x-μ
    # we want to predict the covariance matrix Σ, which is determined by the covariance
    # of the samples in a leaf

    n, m = size(labels)
    Σ = zeros(n,n)

    # NOTE(tim): force at least two samples to ensure proper covariance matrix
    if m < 2
        return -Inf
    end

    # solve for upper triangle of symmetric matrix
    for i = 1 : m
        for a = 1 : n
            l = labels[a,i]
            for b = a : n
                Σ[a,b] += l*labels[b,i]
            end
        end
    end
    Σ ./= (m-1)

    # copy over symmetric component
    for a = 2:n
        for b = 1:a-1
            Σ[a,b] = Σ[b,a]
        end
    end

    logdetΣ = log(max(det(Σ), 1e-20))

    # compute log likelihood (we seek to maximize it)
    # NOTE: ignores constant components
    logl = 0.0
    for i = 1 : m
        logl -= logdetΣ
        for a = 1 : n
            subval = 0.0
            for b = 1 : n
                subval += Σ[a,b]*labels[b,i]
            end
            logl -= subval*labels[a,i]
        end
    end
    return logl
end

function _split{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, nsubfeatures::Int;
    min_samples_leaves::Int=0,
    min_split_improvement::Float64=-Inf,
    loss_function::Symbol=:mse
    )

    # labels is [n_observations × n_rows]

    loss = loss_function == :mse ? _mse_loss : _logl_loss

    nr, nf = size(features)
    best = NO_BEST
    best_val = loss(labels) + min_split_improvement

    for i in _select_random_subfeature_indeces(nsubfeatures, nf)
        if nr > 100
            features_i = features[:,i]
            domain_i = quantile(features_i, linspace(0.01, 0.99, 99))
            labels_i = labels
        else
            ord = sortperm(features[:,i])
            features_i = features[ord,i]
            domain_i = features_i
            labels_i = labels[:,ord]
        end
        for thresh in domain_i[2:end]
            value, num_left, num_right = loss(labels_i, features_i, thresh)
            if value > best_val && num_left ≥ min_samples_leaves && num_right ≥ min_samples_leaves
                best_val = value
                best = (i, thresh)
            end
        end
    end
    return best
end

function build_stump{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U})
    S = _split_mse(labels, features, 0)
    if S == NO_BEST
        return Leaf(mean(labels, 1), labels)
    end
    id, thresh = S
    thesplit = features[:,id] .< thresh
    return Node(id, thresh,
                Leaf(mean(labels[thesplit,:], 1), labels[thesplit,:]),
                Leaf(mean(labels[!thesplit,:], 1), labels[!thesplit,:]))
end
function build_tree{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, params::BuildTreeParameters=BuildTreeParameters(); _depth=0)
    
    if _depth ≥ params.max_depth || _nsamples_labels(labels) < params.min_samples_split
        return Leaf(mean(labels,2), labels)
    end

    S = _split(labels, features, params.nsubfeatures, 
               min_samples_leaves=params.min_samples_leaves,
               min_split_improvement=params.min_split_improvement,
               loss_function=params.loss_function)
    if S == NO_BEST
        return Leaf(mean(labels,2), labels)
    end

    id, thresh = S
    splits = features[:,id] .< thresh
    return Node(id, thresh,
                build_tree(labels[:,splits], features[splits,:], params, _depth=_depth+1),
                build_tree(labels[:,!splits], features[!splits,:], params, _depth=_depth+1))
end
function build_tree_covariance{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, params::BuildTreeParameters=BuildTreeParameters(loss_function=:logl); _depth=0)
    
    if _nsamples_labels(labels) ≤ 2
        return Leaf(eye(_nobservations(labels)), labels)
    elseif _depth ≥ params.max_depth || _nsamples_labels(labels) < params.min_samples_split
        Σ = cov(labels') + diagm(fill(1e-20, size(labels,1)))
        return Leaf(Σ, labels)
    end

    S = _split(labels, features, params.nsubfeatures, 
               min_samples_leaves=params.min_samples_leaves,
               min_split_improvement=params.min_split_improvement,
               loss_function=params.loss_function)
    if S == NO_BEST
        Σ = cov(labels') + diagm(fill(1e-20, size(labels,1)))
        return Leaf(Σ, labels)
    end

    id, thresh = S
    thesplit = features[:,id] .< thresh
    return Node(id, thresh,
                build_tree_covariance(labels[:,thesplit], features[thesplit,:], params, _depth=_depth+1),
                build_tree_covariance(labels[:,!thesplit], features[!thesplit,:], params, _depth=_depth+1))
end

function build_forest{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, ntrees::Integer, params::BuildTreeParameters=BuildTreeParameters(), partialsampling::Float64=0.7)
    partialsampling = partialsampling > 1.0 ? 1.0 : partialsampling
    Nlabels = _nsamples_labels(labels)
    Nsamples = _int(partialsampling * Nlabels)
    forest = @parallel (vcat) for i in 1:ntrees
        inds = rand(1:Nlabels, Nsamples)
        build_tree(labels[:,inds], features[inds,:], params)
    end
    return Ensemble([forest;])
end
function build_forest_covariance{T<:FloatingPoint, U<:Real}(
    labels::Matrix{T},
    features::Matrix{U},
    ntrees::Integer,
    params::BuildTreeParameters=BuildTreeParameters(loss_function=:logl),
    partialsampling::Float64=0.7
    )
    
    partialsampling = partialsampling > 1.0 ? 1.0 : partialsampling
    Nlabels = size(labels,2)
    Nsamples = _int(partialsampling * Nlabels)
    forest = @parallel (vcat) for i in 1:ntrees
        inds = rand(1:Nlabels, Nsamples)
        build_tree_covariance(labels[:,inds], features[inds,:], params)
    end
    return Ensemble([forest;])
end

function mean_squared_error(actual, predicted)
    @assert length(actual) == length(predicted)
    return mean((actual - predicted).^2)
end
function mean_squared_error(actual::Matrix, predicted::Vector)
    @assert size(actual,1) == length(predicted)
    tot = 0.0
    m,n = size(actual)
    for i = 1 : n
        for j = 1 : m
            Δ = actual[j,i] - predicted[j][i]
            tot += Δ*Δ
        end
    end
    return tot / m
end
function mean_squared_error(actual::Matrix, predicted::Matrix)
    @assert size(actual) == size(predicted)
    tot = 0.0
    m,n = size(actual)
    for i = 1 : n
        for j = 1 : m
            Δ = actual[j,i] - predicted[j,i]
            tot += Δ*Δ
        end
    end
    return tot / m
end

function R2(actual, predicted)
    @assert length(actual) == length(predicted)
    ss_residual = sum((actual - predicted).^2)
    ss_total = sum((actual .- mean(actual)).^2)
    return 1.0 - ss_residual/ss_total
end
function R2(actual::Matrix, predicted::Vector)
    @assert size(actual,1) == length(predicted)
    ss_residual = mean_squared_error(actual, predicted)
    ss_total = mean_squared_error(actual, repmat(mean(actual, 1), size(actual, 1), 1))
    return 1.0 - ss_residual/ss_total
end

function _nfoldCV{T<:FloatingPoint, U<:Real}(regressor::Symbol, labels::Matrix{T}, features::Matrix{U}, args...)
    nfolds = args[end]
    if nfolds < 2
        return nothing
    end
    if regressor == :tree
        maxlabels = args[1]
    elseif regressor == :forest
        nsubfeatures = args[1]
        ntrees = args[2]
        maxlabels = args[3]
        partialsampling = args[4]
    end
    N = size(labels,1)
    ntest = _int(floor(N / nfolds))
    inds = randperm(N)
    R2s = zeros(nfolds)
    for i in 1:nfolds
        test_inds = falses(N)
        test_inds[(i - 1) * ntest + 1 : i * ntest] = true
        train_inds = !test_inds
        test_features = features[inds[test_inds],:]
        test_labels = labels[inds[test_inds], :]
        train_features = features[inds[train_inds],:]
        train_labels = labels[inds[train_inds], :]
        if regressor == :tree
            model = build_tree(train_labels, train_features, maxlabels, 0)
            predictions = apply_tree(model, test_features)
        elseif regressor == :forest
            model = build_forest(train_labels, train_features, nsubfeatures, ntrees, maxlabels, partialsampling)
            predictions = apply_forest(model, test_features)
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

function nfoldCV_tree{T<:FloatingPoint, U<:Real}(
    labels::Matrix{T},
    features::Matrix{U},
    nfolds::Integer,
    maxlabels::Integer=5) 

    _nfoldCV(:tree, labels, features, maxlabels, nfolds)
end
function nfoldCV_forest{T<:FloatingPoint, U<:Real}(
    labels::Matrix{T},
    features::Matrix{U},
    nsubfeatures::Integer,
    ntrees::Integer,
    nfolds::Integer,
    maxlabels::Integer=5,
    partialsampling=0.7)

    _nfoldCV(:forest, labels, features, nsubfeatures, ntrees, maxlabels, partialsampling, nfolds)
end

end # end module

# function build_car_model{T<:FloatingPoint, U<:Real}(
#     labels::Matrix{T}, # n_samples × n_observations
#     features::Matrix{U}, # n_samples × n_features
#     nsubfeatures::Integer,
#     ntrees::Integer,
#     maxlabels=0.5,
#     partialsampling=0.7
#     )

    # μ = build_forest(labels,features, nsubfeatures, ntrees, maxlabels, partialsampling)
    # Δ = deepcopy(labels)
    # for i = 1 : size(labels, 1)
    #     Δ[i,:] -= apply_forest(μ, vec(features[i,:]))
    # end
    # # Σ = build_tree_covariance(Δ, features, maxlabels, nsubfeatures)
    # # Σ = build_forest_covariance(Δ, features, nsubfeatures, ntrees, maxlabels, partialsampling)

#     (μ, Σ)
# end


# using DecisionTree

# n, m = 10^3, 5
# features = randn(n, m)
# weights = rand(-2:2, m, 2)
# labels = features * weights
# labels += randn(size(labels)).*0.01

# μ, Σ = build_car_model(labels, features, 3, 20)

# # train regression forest, using 2 random features, 10 trees, 3 folds,
# # averaging of 5 samples per leaf (optional), 0.7 of samples per tree (optional)
# n_random_features = 3
# n_trees = 20
# samples_per_leaf = 0.5
# samples_per_tree = 0.7
# model = build_forest(labels,features, n_random_features, n_trees, samples_per_leaf, samples_per_tree)

# # apply learned model
# apply_forest(model, [-0.9,3.0,5.1,1.9,0.0])

# # run n-fold cross validation on regression forest
# # using 2 random features, 10 trees, 3 folds, averaging of 5 samples/leaf (optional),
# # and 0.7 porition of samples per tree (optional)
# # returns array of coefficients of determination (R^2)
# n_folds = 3
# r2 = nfoldCV_forest(labels, features, n_random_features, n_trees, n_folds, samples_per_leaf, samples_per_tree)