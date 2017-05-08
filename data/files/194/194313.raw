module MvDecisionTrees

export
    LossFunction,
    LossFunction_MSE,
    LossFunction_LOGL,
    LossFunction_LOGL_MEAN_SUBTRACTED,

    Leaf,
    MeanVecLeaf,
    CovLeaf,
    MvNormLeaf,

    InternalNode,
    Ensemble,
    BuildTreeParameters,

    depth,
    print_tree,
    apply_tree,
    apply_forest!,

    build_leaf,
    build_tree,
    build_forest,
    build_tree_parameters

import Distributions: MvNormal

if VERSION.minor >= 4
    typealias Range1{Int} Range{Int}
    _int(x) = round(Int, x)
else
    _int(x) = int(x)
end

abstract LossFunction
type LossFunction_MSE<:LossFunction end # mean squared error loss function
type LossFunction_LOGL<:LossFunction end # log likelihood loss function
type LossFunction_LOGL_MEAN_SUBTRACTED<:LossFunction end # log likelihood loss function where labels already has predicted mean subtracted

abstract Leaf
immutable MeanVecLeaf{T<:FloatingPoint} <: Leaf
    μ::Vector{T}
end
immutable CovLeaf{T<:FloatingPoint} <: Leaf
    Σ::Matrix{T}
end
immutable MvNormLeaf <: Leaf
    m::MvNormal
end

immutable InternalNode{T<:Any, LeafType<:Leaf}
    featid::Int # id of the feature we use to split
    featval::T # value over which we split
    left::Union(LeafType, InternalNode)
    right::Union(LeafType, InternalNode)
end

immutable Ensemble{LeafType<:Leaf}
    trees::Vector{Union(InternalNode, LeafType)}
end

type BuildTreeParameters{F<:LossFunction, LeafType<:Any}
    nsubfeatures::Int # number of candidate features to select for split; 0 will use all
    max_depth::Int # will only split if above this depth (depth of just a leaf is 0)
    min_samples_split::Int # minimum number of samples requried in a node to split
    min_samples_leaves::Int # minimum number of samples in newly created leaves
    min_split_improvement::Float64 # will only split if loss(split(leaf)) > loss(leaf) + min_split_improvement
    loss_function::Type{F}
    leaf_type::Type{LeafType} # the type used for the leaf
end
function build_tree_parameters{F<:LossFunction, LeafType<:Leaf}(;
    nsubfeatures::Int=0,
    max_depth::Int=typemax(Int),
    min_samples_split::Int=5,
    min_samples_leaves::Int=0,
    min_split_improvement::Float64=-Inf,
    loss_function::Type{F}=LossFunction_MSE,
    leaf_type::Type{LeafType}=MeanVecLeaf,
    )

    @assert(nsubfeatures ≥ 0)
    @assert(max_depth ≥ 0)
    @assert(min_samples_split ≥ 0)
    @assert(min_samples_leaves ≤ min_samples_split/2)

    BuildTreeParameters{F, LeafType}(nsubfeatures, max_depth, min_samples_split,
               min_samples_leaves, min_split_improvement, loss_function, leaf_type)
end

type PreallocatedLearningMemory{T<:FloatingPoint}
    μ_l::Vector{T} # n
    μ_r::Vector{T} # n
    Σ_l::Matrix{T} # n×n
    Σ_r::Matrix{T} # n×n
    subfeature_indeces::Vector{Int}
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

Base.length(::Leaf) = 1
Base.length(tree::InternalNode) = length(tree.left) + length(tree.right)
Base.length(ensemble::Ensemble) = length(ensemble.trees)

depth(::Leaf) = 0
depth(tree::InternalNode) = 1 + max(depth(tree.left), depth(tree.right))

_nsamples_labels(labels::Matrix{Float64}) = size(labels,2)
_nobservations(labels::Matrix{Float64}) = size(labels,1)

function print_tree(leaf::Leaf, depth::Integer=-1, indent::Integer=0)
    # NOTE(tim): I think this only works for classification
    print("    " ^ indent * "R-> ")
    println(leaf)
end
function print_tree(tree::InternalNode, depth::Integer=-1, indent::Integer=0)
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

apply_tree(leaf::Leaf, feature::Array) = leaf
function apply_tree(tree::InternalNode, features::Vector)
    if features[tree.featid] < tree.featval
        apply_tree(tree.left, features)
    else
        apply_tree(tree.right, features)
    end
end

function apply_forest!{T<:Any}(μ::Vector{T}, forest::Ensemble{MeanVecLeaf}, features::Vector)

    # return the mean among tree's observations

    ntrees = length(forest)
    o = length(μ)

    for i in 1 : o
        μ[i] = 0.0
    end
    for i in 1 : ntrees
        leaf = apply_tree(forest.trees[i], features)::MeanVecLeaf
        for j in 1 : o
            μ[j] += leaf.μ[j]
        end
    end
    for i in 1 : o
        μ[i] /= ntrees
    end
    μ
end
function apply_forest!{T<:Any}(Σ::Matrix{T}, forest::Ensemble{CovLeaf}, features::Vector)

    # return the mean covariance matrix among the tree's covariances

    ntrees = length(forest)
    len = length(Σ)

    for i in 1 : len
        Σ[i] = 0.0
    end
    for i in 1 : ntrees
        leaf = apply_tree(forest.trees[i], features)::CovLeaf
        for j in 1 : len
            Σ[j] += leaf.Σ[j]
        end
    end
    for i in 1 : len
        Σ[i] /= ntrees
    end

    Σ
end

### Regression ###
function _reservoir_sample!(indeces::Vector{Int}, n::Int, k::Int=length(indeces))

    # performs Reservoir Sampling to obtain k elements from [1:n]
    #  indeces = input array
    #  n       = length of set of indeces to choose from (ie, we select from [1:n])
    #  k       = number of samples to choose and place in first k elements of indeces
    # runtime: O(n)
    # https://en.wikipedia.org/wiki/Reservoir_sampling

    if n == 0
        n = k
    end

    for i = 1 : k
        indeces[i] = i
    end

    for i = k+1 : n
        j = rand(1:i)
        if j ≤ k
            indeces[j] = i
        end
    end

    indeces
end

function _calc_covariance_mean_subtracted!{T<:FloatingPoint}(
    Σ::Matrix{T},
    labels::Matrix{T},
    assignment::Vector{Int},
    assignment_id::Int,
    )

    # NOTE(tim): this assumes that the mean has already been subtracted from the data

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

    if n_for_id < 2
        for i = 1 : o
            Σ[i,i] = 1.0
        end
        return Σ
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

function _fast_det{T<:FloatingPoint}(M::AbstractMatrix{T})
    n = size(M,1)
    if n == 1
        M[1]
    elseif n == 2
        M[1]*M[4] - M[2]*M[3]
    elseif n == 3
        M[1]*M[5]*M[9] + M[4]*M[8]*M[3] + M[7]*M[2]*M[6] -
            M[7]*M[5]*M[3] - M[4]*M[2]*M[9] - M[1]*M[8]*M[6]
    else
        det(M)
    end
end

function loss{T<:FloatingPoint, U<:Real}(
    ::Type{LossFunction_MSE},
    labels::Matrix{T}, # [n_observations × n_rows]
    features::Matrix{U}, # [n_rows × n_features]
    feature_index::Integer,
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,
    thresh::T,
    mem::PreallocatedLearningMemory,
    )

    # mse loss for a vector is tr{E{(y-p)(y-p)ᵀ}}
    # where y is the label
    # and p is the prediction - the average of labels on that side of the threshold

    Σ_l = mem.Σ_l
    Σ_r = mem.Σ_r

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
    mem::PreallocatedLearningMemory,
    )

    # mse loss for a vector is tr{E{(y-p)(y-p)ᵀ}}
    # where y is the label
    # and p is the prediction - the average of labels on that side of the threshold

    Σ = mem.Σ_l
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
    mem::PreallocatedLearningMemory,
    )

    μ_l = mem.μ_l
    μ_r = mem.μ_r
    Σ_l = mem.Σ_l
    Σ_r = mem.Σ_r

    n, m = size(labels)
    nl, nr = 0, 0

    # compute the mean
    for i = 1 : n
        μ_l[i] = 0.0
        μ_r[i] = 0.0
    end
    for i = 1 : m
        if assignment[i] == assignment_id
            if features[i,feature_index] < thresh
                nl += 1
                for a = 1 : n
                    μ_l[a] += labels[a,i]
                end
            else
                nr += 1
                for a = 1 : n
                    μ_r[a] += labels[a,i]
                end
            end
        end
    end
    if nl < 2 || nr < 2
        # NOTE(tim): force at least two samples on each side to ensure proper covariance matrix
        return (-Inf, nl, nr)
    end
    for i = 1 : n
        μ_l[i] /= nl
        μ_r[i] /= nr
    end

    # solve for upper triangle of symmetric covariance matrix
    for i = 1 : n*n
        Σ_l[i] = 0.0
        Σ_r[i] = 0.0
    end
    for i = 1 : m
        if assignment[i] == assignment_id
            if features[i,feature_index] < thresh
                for a = 1 : n
                    l = labels[a,i] - μ_l[a]
                    for b = a : n
                        Σ_l[a,b] += l*(labels[b,i] - μ_l[b])
                    end
                end
            else
                for a = 1 : n
                    l = labels[a,i] - μ_r[a]
                    for b = a : n
                        Σ_r[a,b] += l*(labels[b,i] - μ_r[b])
                    end
                end
            end
        end
    end
    for i = 1 : n*n
        Σ_l[i] /= (nl-1)
        Σ_r[i] /= (nr-1)
    end
    for a = 2:n
        # copy over symmetric component
        for b = 1:a-1
            Σ_l[a,b] = Σ_l[b,a]
            Σ_r[a,b] = Σ_r[b,a]
        end
    end

    logdetΣ_l = log(max(_fast_det(Σ_l), 1e-20))
    logdetΣ_r = log(max(_fast_det(Σ_r), 1e-20))

    # compute log likelihood score under gaussian distribution
    # NOTE: does not compute the true logl likelihood
    #       computation ignores constant components
    logl = 0.0
    for i = 1 : m
        if assignment[i] == assignment_id
            if features[i] < thresh
                logl -= logdetΣ_l
                for a = 1 : n
                    subval = 0.0
                    for b = 1 : n
                        subval += Σ_l[a,b]*(labels[b,i] - μ_l[b])
                    end
                    logl -= subval*(labels[a,i] - μ_l[a])
                end
            else
                logl -= logdetΣ_r
                for a = 1 : n
                    subval = 0.0
                    for b = 1 : n
                        subval += Σ_r[a,b]*(labels[b,i] - μ_r[b])
                    end
                    logl -= subval*(labels[a,i] - μ_r[a])
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
    mem::PreallocatedLearningMemory,
    )

    μ = mem.μ_l
    Σ = mem.Σ_l

    n, m = size(labels)
    m_assigned = 0

    # compute the sample mean
    for i = 1 : n
        μ[i] = 0.0
    end
    for i = 1 : m
        if assignment[i] == assignment_id
            m_assigned += 1
            for a = 1 : n
                μ[a] += labels[a,i]
            end
        end
    end
    if m_assigned ≤ 2
        # insufficient entries to split
        return -Inf
    end
    for i = 1 : n
        μ[i] /= m_assigned
    end

    # compute covariance matrix

    for i = 1 : n*n
        Σ[i] = 0.0
    end
    for i = 1 : m
        if assignment[i] == assignment_id
            for a = 1 : n
                l = labels[a,i] - μ[a]
                for b = a : n
                    Σ[a,b] += l*(labels[b,i] - μ[b])
                end
            end
        end
    end
    for i = 1 : n*n
        Σ[i] /= (m_assigned-1)
    end
    for a = 2:n
        # copy over symmetric component
        for b = 1:a-1
            Σ[a,b] = Σ[b,a]
        end
    end

    logdetΣ = log(max(_fast_det(Σ), 1e-20))

    # compute log likelihood score under gaussian distribution
    # NOTE: does not compute the true logl likelihood
    #       computation ignores constant components
    logl = 0.0
    for i = 1 : m
        if assignment[i] == assignment_id
            logl -= logdetΣ
            for a = 1 : n
                subval = 0.0
                for b = 1 : n
                    subval += Σ[a,b]*(labels[b,i] - μ[b])
                end
                logl -= subval*(labels[a,i] - μ[a])
            end
        end
    end
    logl
end

function loss{T<:FloatingPoint, U<:Real}(
    ::Type{LossFunction_LOGL_MEAN_SUBTRACTED},
    labels::Matrix{T}, # [n_observations × n_rows]
    features::Matrix{U}, # [n_rows × n_features]
    feature_index::Integer,
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,
    thresh::T,
    mem::PreallocatedLearningMemory,
    )

    # labels is n_samples × n_outcomes and contains the distance from the mean, x-μ
    # we want to predict the covariance matrix Σ, which is determined by the covariance
    # of the samples in a leaf

    Σ_l = mem.Σ_l
    Σ_r = mem.Σ_r

    n, m = size(labels)

    nl, nr = 0, 0

    # solve for upper triangle of symmetric matrix
    for i = 1 : n*n
        Σ_l[i] = 0.0
        Σ_r[i] = 0.0
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

    # copy over symmetric component
    for a = 2:n
        for b = 1:a-1
            Σ_l[a,b] = Σ_l[b,a]
            Σ_r[a,b] = Σ_r[b,a]
        end
    end

    logdetΣ_l = log(max(_fast_det(Σ_l), 1e-20))
    logdetΣ_r = log(max(_fast_det(Σ_r), 1e-20))

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
    ::Type{LossFunction_LOGL_MEAN_SUBTRACTED},
    labels::Matrix{T}, # [n_observations × n_rows]
    assignment::Vector{Int}, # [n_rows]
    assignment_id::Int,
    mem::PreallocatedLearningMemory,
    )

    # labels is n_samples × n_outcomes and contains the distance from the mean, x-μ
    # we want to predict the covariance matrix Σ, which is determined by the covariance
    # of the samples in a leaf

    Σ = mem.Σ_l
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

    logdetΣ = log(max(_fast_det(Σ), 1e-20))

    # compute log likelihood score under gaussian distribution
    # NOTE: does not compute the true logl likelihood
    #       computation ignores constant components
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
    mem::PreallocatedLearningMemory,
    )

    # returns a tuple: (index_of_feature_we_split_over, threshold)

    nrow, nfeatures = size(features)
    best = (0,0)
    best_loss = loss(loss_function, labels, assignment, assignment_id, mem) + min_split_improvement
    n_thresholds = min(nrow-1, 10)

    _reservoir_sample!(mem.subfeature_indeces, nfeatures)

    for i in mem.subfeature_indeces

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

            value, num_left, num_right = loss(loss_function, labels, features, i, assignment, assignment_id, thresh, mem)

            if value > best_loss && num_left ≥ min_samples_leaves && num_right ≥ min_samples_leaves
                best_loss = value
                best = (i, thresh)
            end
        end
    end

    best
end

function build_leaf{T<:FloatingPoint}(
    ::Type{MeanVecLeaf},
    labels::Matrix{T},
    assignment::Vector{Int},
    assignment_id::Int,
    )

    #=
    Construct a leaf whose payload is the mean vector of samples within it
    =#

    o, n = size(labels)
    leaf_mean = zeros(T, o)

    n_for_id = 0
    for i = 1 : n
        if assignment[i] == assignment_id
            n_for_id += 1
            for j = 1 : o
                leaf_mean[j] += labels[j,i]
            end
        end
    end
    for j = 1 : o
        @inbounds leaf_mean[j] /= n_for_id
    end

    MeanVecLeaf(leaf_mean)
end
function build_leaf{T<:FloatingPoint}(
    ::Type{CovLeaf},
    labels::Matrix{T},
    assignment::Vector{Int},
    assignment_id::Int,
    )

    #=
    Construct a leaf whose payload is the covariance matrix for all samples within it
    =#
    o = _nobservations(labels)
    CovLeaf(_calc_covariance_mean_subtracted!(zeros(T, o, o), labels, assignment, assignment_id))
end
function build_leaf{T<:FloatingPoint}(
    ::Type{MvNormLeaf},
    labels::Matrix{T},
    assignment::Vector{Int},
    assignment_id::Int,
    )

    #=
    Construct a leaf whose payload is the mvnormal for all samples within it
    =#

    o, n = size(labels)
    leaf_mean = zeros(T, o)

    n_for_id = 0
    for i = 1 : n
        if assignment[i] == assignment_id
            n_for_id += 1
            for j = 1 : o
                leaf_mean[j] += labels[j,i]
            end
        end
    end
    for j = 1 : o
        @inbounds leaf_mean[j] /= n_for_id
    end

    # calc covariance

    Σ = zeros(T, o, o)

    for i = 1 : n
        if assignment[i] == assignment_id
            for a = 1 : o
                l = labels[a,i] - leaf_mean[a]
                for b = a : o
                    Σ[a,b] += l*(labels[b,i]-leaf_mean[b])
                end
            end
        end
    end

    if n_for_id < 2
        warn("MvDecisionTrees.build_leaf{MvNormLeaf}: Not enough samples ($n_for_id) to build a covariance matrix")
        for i = 1 : o
            Σ[i,i] = 1.0
        end
    else
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
    end

    MvNormLeaf(MvNormal(leaf_mean, Σ))
end

function _build_tree{T<:FloatingPoint, U<:Real}(
    labels::Matrix{T},
    features::Matrix{U},
    assignment::Vector{Int}, # [n_rows+1], last element contains the max id
    assignment_id::Int,
    params::BuildTreeParameters,
    mem::PreallocatedLearningMemory,
    _depth::Int=0,
    )

    n = _nsamples_labels(labels)
    n_for_id = 0
    for i = 1 : n
        n_for_id += int(assignment[i] == assignment_id)
    end

    # println("size(assignment): ", size(assignment))
    # println(assignment[1:20])
    # println("assignment_id:    ", assignment_id)
    # println("n_for_id: ", n_for_id)
    # println("_depth ≥ params.max_depth   ", _depth ≥ params.max_depth)
    # println("n_for_id < params.min_samples_split:   ", n_for_id < params.min_samples_split)

    if _depth ≥ params.max_depth || n_for_id < params.min_samples_split
        return build_leaf(params.leaf_type, labels, assignment, assignment_id)
    end

    id, thresh = _split(labels, features, assignment, assignment_id,
                        params.min_samples_leaves,
                        params.min_split_improvement,
                        params.loss_function,
                        mem
                        )

    # println("split id:      ", id)
    # println("split thresh:  ", thresh)

    if id == 0
        return build_leaf(params.leaf_type, labels, assignment, assignment_id)
    end


    next_id = assignment[end]+1
    assignment[end] = next_id

    for i in 1 : n
        if assignment[i] == assignment_id && features[i,id] < thresh
            assignment[i] = next_id
        end
    end

    return InternalNode{T, params.leaf_type}(id, thresh,
                _build_tree(labels, features, assignment, next_id,       params, mem, _depth+1),
                _build_tree(labels, features, assignment, assignment_id, params, mem, _depth+1))
end
function build_tree{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, params::BuildTreeParameters)

    o, n = size(labels)
    μ_l = Array(T, o)
    μ_r = Array(T, o)
    Σ_l = Array(T, o,o)
    Σ_r = Array(T, o,o)

    nfeatures = size(features,2)
    nsubfeatures = params.nsubfeatures > 0 ? min(params.nsubfeatures, nfeatures) : nfeatures
    subfeature_indeces = Array(Int, nsubfeatures)
    assignment = ones(Int, n+1)

    mem = PreallocatedLearningMemory{T}(μ_l, μ_r, Σ_l, Σ_r, subfeature_indeces)

    _build_tree(labels, features, assignment, 1, params, mem)
end

function _build_forest_parallel{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, ntrees::Integer, params::BuildTreeParameters, partialsampling::Float64)
    nlabels = _nsamples_labels(labels)
    nsamples = _int(partialsampling * nlabels)

    forest = @parallel (vcat) for i in 1:ntrees
        inds = rand(1:nlabels, nsamples)
        build_tree(labels[:,inds], features[inds,:], params)
    end
    Ensemble{params.leaf_type}(convert(Vector{Union(InternalNode, params.leaf_type)}, forest))
end
function _build_forest_serial{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, ntrees::Integer, params::BuildTreeParameters, partialsampling::Float64)

    o, nlabels = size(labels)
    μ_l = Array(T, o)
    μ_r = Array(T, o)
    Σ_l = Array(T, o,o)
    Σ_r = Array(T, o,o)

    nfeatures = size(features,2)
    nsubfeatures = params.nsubfeatures > 0 ? min(params.nsubfeatures, nfeatures) : nfeatures
    subfeature_indeces = Array(Int, nsubfeatures)
    assignment = ones(Int, nlabels+1)
    nsamples = _int(partialsampling * nlabels)

    chosen_samples = Array(Int, nsamples)

    mem = PreallocatedLearningMemory{T}(μ_l, μ_r, Σ_l, Σ_r, subfeature_indeces)

    forest = Array(Union(InternalNode, params.leaf_type), ntrees)
    for i = 1 : ntrees

        # select nsamples
        _reservoir_sample!(chosen_samples, nlabels)
        for j = 1:nlabels
            assignment[j] = 0 # remove labels that we are not considering
        end
        for j in chosen_samples
            assignment[j] = 1
        end
        assignment[end] = 1


        # build the tree
        forest[i] = _build_tree(labels, features, assignment, 1, params, mem)
    end

    Ensemble{params.leaf_type}(forest)
end
function build_forest{T<:FloatingPoint, U<:Real}(labels::Matrix{T}, features::Matrix{U}, ntrees::Integer, params::BuildTreeParameters, partialsampling::Float64=0.7)

    @assert(0.0 < partialsampling ≤ 1.0)
    if nprocs() == 1
        _build_forest_serial(labels, features, ntrees, params, partialsampling)
    else
        _build_forest_parallel(labels, features, ntrees, params, partialsampling)
    end
end

end # end module