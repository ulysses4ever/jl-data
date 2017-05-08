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

abstract LossFunction
type LossFunction_MSE<:LossFunction end # mean squared error loss function
type LossFunction_LOGL<:LossFunction end # log likelihood loss function

immutable Leaf
    majority::Any
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

type BuildTreeParameters{F<:LossFunction}
    nsubfeatures::Int # number of candidate features to select for split; 0 will use all
    max_depth::Int # will only split if above this depth (depth of just a leaf is 0)
    min_samples_split::Int # minimum number of samples requried in a node to split
    min_samples_leaves::Int # minimum number of samples in newly created leaves
    min_split_improvement::Float64 # will only split if loss(split(leaf)) > loss(leaf) + min_split_improvement
    loss_function::Type{F}
end
function build_tree_parameters{F<:LossFunction}(;
    nsubfeatures::Int=0,
    max_depth::Int=typemax(Int),
    min_samples_split::Int=5,
    min_samples_leaves::Int=0,
    min_split_improvement::Float64=-Inf,
    loss_function::Type{F}=LossFunction_LOGL
    )

    @assert(nsubfeatures ≥ 0)
    @assert(max_depth ≥ 0)
    @assert(min_samples_split ≥ 0)
    @assert(min_samples_leaves ≤ min_samples_split/2)

    BuildTreeParameters{loss_function}(nsubfeatures, max_depth, min_samples_split, min_samples_leaves, min_split_improvement, loss_function)
end

function Base.print(io::IO, params::BuildTreeParameters)
    println(io, "BuildTreeParameters:")
    @printf(io, "\tnsubfeatures:          %8d\n", params.nsubfeatures)
    @printf(io, "\tmax_depth:             %8d\n", params.max_depth)
    @printf(io, "\tmin_samples_split:     %8d\n", params.min_samples_split)
    @printf(io, "\tmin_samples_leaves:    %8d\n", params.min_samples_leaves)
    @printf(io, "\tmin_split_improvement: %8.3f\n", params.min_split_improvement)
    @printf(io, "\tloss_function:         %8s\n", string(params.loss_function))
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
function _select_random_subfeature_indeces!(indeces::Vector{Int}, nfeatures::Int)

    # performs Reservoir Sampling to obtain k elements from features
    # runtime: O(nfeatures)
    # https://en.wikipedia.org/wiki/Reservoir_sampling

    k = length(indeces)

    if nfeatures == 0
        nfeatures = k
    end

    for i = 1 : k
        indeces[i] = i
    end

    for i = k+1 : nfeatures
        j = rand(1:i)
        if j ≤ k
            indeces[j] = i
        end
    end

    indeces
end

function _calc_covariance!{T<:FloatingPoint}(
    Σ::Matrix{T},
    labels::Matrix{T},
    assignment::Vector{Int},
    assignment_id::Int,
    )

    o, n = size(labels)

    n_for_id = 0
    for i = 1 : n
        if assignment[i] == assignment_id
            for a = 1 : o
                l = labels[a,i]
                for b = a : o
                    Σ[a,b] += l*labels[b,i]
                end
            end
            n_for_id += 1
        end
    end
    for i = 1 : o*o
        Σ[i] /= (n_for_id-1)
    end
    for i = 1 : o
        Σ[i,i] += 1e-20
    end
    for a = 2:o
        for b = 1:a-1
            Σ[a,b] = Σ[b,a]
        end
    end

    Σ
end

function loss{T<:FloatingPoint, U<:Real}(
    ::Type{LossFunction_MSE},
    labels::Matrix{T}, # [n_observations × n_rows]
    features::Matrix{U}, # [n_rows × n_features]
    feature_index::Integer,
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,
    thresh::T,
    Σ_l::Matrix{T},
    Σ_r::Matrix{T},
    )

    # mse loss for a vector is tr{E{(y-p)(y-p)ᵀ}}
    # where y is the label
    # and p is the prediction - the average of labels on that side of the threshold

    n, m = size(labels) # n_samples, n_outcomes
    mse = 0.0
    nl = nr = 0

    for i = 1 : n
        if assignment[i] == assignment_id
            s_l, s_r = 0.0, 0.0
            nl = nr = 0
            for j = 1 : m
                l = labels[i,j]
                mse += l*l
                if features[j,feature_index] < thresh
                    s_l += l
                    nl += 1
                else
                    s_r += l
                    nr += 1
                end
            end
            mse -= s_l*s_l / nl
            mse -= s_r*s_r / nr
        end
    end

    return (-mse, nl, nr)
end
function loss{T<:FloatingPoint}(
    ::Type{LossFunction_MSE},
    labels::Matrix{T},
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,
    Σ::Matrix{T}
    )

    # mse loss for a vector is tr{E{(y-p)(y-p)ᵀ}}
    # where y is the label
    # and p is the prediction - the average of labels on that side of the threshold

    n, m = size(labels) # n_samples, n_outcomes
    mse = 0.0

    for i = 1 : n
        if assignment[i] == assignment_id
            s = 0.0
            for j = 1 : m
                l = labels[i,j]
                mse += l*l
                s += l
            end
            mse -= s*s / m
        end
    end

    return -mse
end

function loss{T<:FloatingPoint, U<:Real}(
    ::Type{LossFunction_LOGL},
    labels::Matrix{T}, # [n_observations × n_rows]
    features::Matrix{U}, # [n_rows × n_features]
    feature_index::Integer,
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,
    thresh::T,
    Σ_l::Matrix{T}, # n×n
    Σ_r::Matrix{T}, # n×n
    )

    # labels is n_samples × n_outcomes and contains the distance from the mean, x-μ
    # we want to predict the covariance matrix Σ, which is determined by the covariance
    # of the samples in a leaf

    n, m = size(labels)

    nl, nr = 0, 0

    # solve for upper triangle of symmetric matrix
    for i = 1 : n*n
        Σ_l[i] = 0
        Σ_r[i] = 0
    end

    for i = 1 : m
        if assignment[i] == assignment_id
            if features[i,feature_index] < thresh
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
    end
    for i = 1 : n*n
        Σ_l[i] /= (nl-1)
        Σ_r[i] /= (nr-1)
    end

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

    detΣ_l = let
        if n == 1
            Σ_l[1]
        elseif n == 2
            Σ_l[1]*Σ_l[4] - Σ_l[2]*Σ_l[3]
        elseif n == 3
            Σ_l[1]*Σ_l[5]*Σ_l[9] + Σ_l[4]*Σ_l[8]*Σ_l[3] + Σ_l[7]*Σ_l[2]*Σ_l[6] -
                Σ_l[7]*Σ_l[5]*Σ_l[3] - Σ_l[4]*Σ_l[2]*Σ_l[9] - Σ_l[1]*Σ_l[8]*Σ_l[6]
        else
            det(Σ_l)
        end
    end
    detΣ_r = let
        if n == 1
            Σ_r[1]
        elseif n == 2
            Σ_r[1]*Σ_r[4] - Σ_r[2]*Σ_r[3]
        elseif n == 3
            Σ_r[1]*Σ_r[5]*Σ_r[9] + Σ_r[4]*Σ_r[8]*Σ_r[3] + Σ_r[7]*Σ_r[2]*Σ_r[6] -
                Σ_r[7]*Σ_r[5]*Σ_r[3] - Σ_r[4]*Σ_r[2]*Σ_r[9] - Σ_r[1]*Σ_r[8]*Σ_r[6]
        else
            det(Σ_r)
        end
    end

    logdetΣ_l = log(max(detΣ_l, 1e-20))
    logdetΣ_r = log(max(detΣ_r, 1e-20))

    # compute log likelihood (we seek to maximize it)
    # NOTE: ignores constant components
    logl = 0.0
    for i = 1 : m
        if assignment[i] == assignment_id
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
    end

    return (logl, nl, nr)
end
function loss{T<:FloatingPoint}(
    ::Type{LossFunction_LOGL},
    labels::Matrix{T}, # [n_observations × n_rows]
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,
    Σ::Matrix{T},
    )

    # labels is n_samples × n_outcomes and contains the distance from the mean, x-μ
    # we want to predict the covariance matrix Σ, which is determined by the covariance
    # of the samples in a leaf

    n, m = size(labels)

    for i = 1 : n*n
        Σ[i] = 0
    end

    # solve for upper triangle of symmetric matrix

    m_assigned = 0
    for i = 1 : m
        if assignment[i] == assignment_id
            m_assigned += 1
            for a = 1 : n
                l = labels[a,i]
                for b = a : n
                    Σ[a,b] += l*labels[b,i]
                end
            end
        end
    end
    if m_assigned ≤ 2
        return -Inf
    end

    for i = 1 : n*n
        Σ[i] /= (m_assigned-1)
    end

    # copy over symmetric component
    for a = 2:n
        for b = 1:a-1
            Σ[a,b] = Σ[b,a]
        end
    end


    detΣ = let
        if n == 1
            Σ[1]
        elseif n == 2
            Σ[1]*Σ[4] - Σ[2]*Σ[3]
        elseif n == 3
            Σ[1]*Σ[5]*Σ[9] + Σ[4]*Σ[8]*Σ[3] + Σ[7]*Σ[2]*Σ[6] -
                Σ[7]*Σ[5]*Σ[3] - Σ[4]*Σ[2]*Σ[9] - Σ[1]*Σ[8]*Σ[6]
        else
            det(Σ)
        end
    end
    logdetΣ = log(max(detΣ, 1e-20))

    # compute log likelihood (we seek to maximize it)
    # NOTE: ignores constant components
    logl = 0.0
    for i = 1 : m
        if assignment[i] == assignment_id
            logl -= logdetΣ
            for a = 1 : n
                subval = 0.0
                for b = 1 : n
                    subval += Σ[a,b]*labels[b,i]
                end
                logl -= subval*labels[a,i]
            end
        end
    end
    logl
end

function _split{F<:LossFunction, T<:FloatingPoint, U<:Real}(
    labels::Matrix{T}, # [n_observations × n_rows]
    features::Matrix{U}, # [n_rows × n_features]
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,

    min_samples_leaves::Int,
    min_split_improvement::Float64,
    loss_function::Type{F},
    Σ_l::Matrix{T}, # n×n
    Σ_r::Matrix{T}, # n×n
    subfeature_indeces::Vector{Int},
    )

    # returns a tuple: (index_of_feature_we_split_over, threshold)

    nrow, nfeatures = size(features)
    best = NO_BEST
    best_loss = loss(loss_function, labels, assignment, assignment_id, Σ_l) + min_split_improvement
    n_thresholds = min(nrow-1, 10)

    _select_random_subfeature_indeces!(subfeature_indeces, nfeatures)

    for i in subfeature_indeces

        f_lo = Inf
        f_hi = -Inf
        for j in 1 : nrow
            if assignment[j] == assignment_id
                v = features[j,i]
                if v < f_lo
                    f_lo = v
                elseif v > f_hi
                    f_hi = v
                end
            end
        end

        for j in 1 : n_thresholds

            thresh = f_lo + (f_hi - f_lo)*(j/(n_thresholds+1))

            value, num_left, num_right = loss(loss_function, labels, features, i, assignment, assignment_id, thresh, Σ_l, Σ_r)

            if value > best_loss && num_left ≥ min_samples_leaves && num_right ≥ min_samples_leaves
                best_loss = value
                best = (i, thresh)
            end
        end
    end

    best
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
function _build_tree{T<:FloatingPoint, U<:Real}(
    labels::Matrix{T},
    features::Matrix{U},
    assignment::Vector{Int}, # [n_rows+1], last element contains the max id
    assignment_id::Int,
    params::BuildTreeParameters,
    Σ_l::Matrix{T}, # n×n
    Σ_r::Matrix{T}, # n×n
    subfeature_indeces::Vector{Int},
    _depth::Int=0,
    )

    n = _nsamples_labels(labels)
    n_for_id = 0
    for i = 1 : n
        n_for_id += assignment[i] == assignment_id
    end

    if _depth ≥ params.max_depth || n_for_id < params.min_samples_split
        o = _nobservations(labels)
        m = zeros(T, o)
        for i = 1 : n
            if assignment[i] == assignment_id
                for j = 1 : o
                    m[j] += labels[j,i]
                end
            end
        end
        for j = 1 : o
            @inbounds m[j] /= n_for_id
        end

        return Leaf(m)
    end

    id, thresh = _split(labels, features, assignment, assignment_id,
                        params.min_samples_leaves,
                        params.min_split_improvement,
                        params.loss_function,
                        Σ_l, Σ_r, subfeature_indeces
                        )

    if id == 0
        o = _nobservations(labels)
        m = zeros(T, o)
        for i = 1 : n
            if assignment[i] == assignment_id
                for j = 1 : o
                    m[j] += labels[j,i]
                end
            end
        end
        for j = 1 : o
            @inbounds m[j] /= n_for_id
        end

        return Leaf(m) # TODO(tim): fix this
    end


    next_id = assignment[end]+1
    assignment[end] = next_id

    for i in 1 : n
        if assignment[i] == assignment_id && features[i,id] < thresh
            assignment[i] = next_id
        end
    end

    return Node(id, thresh,
                _build_tree(labels, features, assignment, next_id,       params, Σ_l, Σ_r, subfeature_indeces, _depth+1),
                _build_tree(labels, features, assignment, assignment_id, params, Σ_l, Σ_r, subfeature_indeces, _depth+1))
end
function build_tree{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, params::BuildTreeParameters)

    o = size(labels,1)
    Σ_l = zeros(o,o)
    Σ_r = zeros(o,o)

    nfeatures = size(features,2)
    nsubfeatures = params.nsubfeatures > 0 ? min(params.nsubfeatures, nfeatures) : nfeatures
    subfeature_indeces = Array(Int, nsubfeatures)
    assignment = ones(Int, n+1)

    _build_tree(
        labels, features, assignment, 1,
        params, Σ_l, Σ_r, subfeature_indeces
        )
end
function _build_tree_covariance{T<:FloatingPoint, U<:Real}(
    labels::Matrix{T},
    features::Matrix{U},
    assignment::Vector{Int}, # [n_rows+1], last element contains the max id
    assignment_id::Int,
    params::BuildTreeParameters,
    Σ_l::Matrix{T}, # n×n
    Σ_r::Matrix{T}, # n×n
    subfeature_indeces::Vector{Int},
    _depth::Int=0,
    )

    n = _nsamples_labels(labels)
    o = _nobservations(labels)
    n_for_id = 0
    for i = 1 : n
        n_for_id += assignment[i] == assignment_id
    end

    if n_for_id ≤ 2
        return Leaf(eye(o))
    elseif _depth ≥ params.max_depth || n_for_id < params.min_samples_split
        Σ = _calc_covariance!(zeros(T, o, o), labels, assignment, assignment_id)
        return Leaf(Σ)
    end

    id, thresh = _split(labels, features, assignment, assignment_id,
                        params.min_samples_leaves,
                        params.min_split_improvement,
                        params.loss_function,
                        Σ_l, Σ_r, subfeature_indeces
                        )

    if id == 0
        Σ = _calc_covariance!(zeros(T, o, o), labels, assignment, assignment_id)
        return Leaf(Σ)
    end


    next_id = assignment[end]+1
    assignment[end] = next_id

    for i in 1 : n
        if assignment[i] == assignment_id && features[i,id] < thresh
            assignment[i] = next_id
        end
    end

    return Node(id, thresh,
                _build_tree_covariance(labels, features, assignment, next_id,       params, Σ_l, Σ_r, subfeature_indeces, _depth+1),
                _build_tree_covariance(labels, features, assignment, assignment_id, params, Σ_l, Σ_r, subfeature_indeces, _depth+1))
end
function build_tree_covariance{T<:FloatingPoint, U<:Real}(
    labels::Matrix{T},
    features::Matrix{U},
    params::BuildTreeParameters,
    )

    o = size(labels,1)
    Σ_l = zeros(o,o)
    Σ_r = zeros(o,o)

    nfeatures = size(features,2)
    nsubfeatures = params.nsubfeatures > 0 ? min(params.nsubfeatures, nfeatures) : nfeatures
    subfeature_indeces = Array(Int, nsubfeatures)
    assignment = ones(Int, n+1)

    _build_tree_covariance(
        labels, features, assignment, 1,
        params, Σ_l, Σ_r, subfeature_indeces
        )
end

function build_forest{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, ntrees::Integer, params::BuildTreeParameters, partialsampling::Float64=0.7)
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
    params::BuildTreeParameters,
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
    maxlabels::Integer=5
    )

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