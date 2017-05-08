module DecisionTree

import Base.length, Base.convert, Base.promote_rule, Base.show, Rmath.qf

export Leaf, Node, print_tree, Tree2Collection, Tree2Centers, ss, ss_by_col, RSquare, 
       build_stump, build_tree, prune_tree, apply_tree, nfoldCV_tree,
       build_forest, apply_forest, nfoldCV_forest,
       build_adaboost_stumps, apply_adaboost_stumps, nfoldCV_stumps,
       majority_vote, ConfusionMatrix, confusion_matrix

include("measures.jl")
#include("Clustering.jl")

type Leaf
    majority::Any
    values::Vector
end

type Node
    featid::Integer
    featval::Any
    left::Union(Leaf,Node)
    right::Union(Leaf,Node)
end

convert(::Type{Node}, x::Leaf) = Node(0, nothing, x, Leaf(nothing,[nothing]))
promote_rule(::Type{Node}, ::Type{Leaf}) = Node
promote_rule(::Type{Leaf}, ::Type{Node}) = Node

function length(tree::Union(Leaf,Node))
    s = split(string(tree), "Leaf")
    return length(s) - 1
end

function print_tree(tree::Union(Leaf,Node), indent::Integer)
    if typeof(tree) == Leaf
        matches = find(tree.values .== tree.majority)
        ratio = string(length(matches)) * "/" * string(length(tree.values))
        println("$(tree.majority) : $(ratio)")
    else
        println("Feature $(tree.featid), Threshold $(tree.featval)")
        print("    " ^ indent * "L-> ")
        print_tree(tree.left, indent + 1)
        print("    " ^ indent * "R-> ")
        print_tree(tree.right, indent + 1)
    end
end
print_tree(tree::Union(Leaf,Node)) = print_tree(tree, 0)




function _split(labels::Vector, features::Matrix, nsubfeatures::Integer, weights::Vector)
    nf = size(features,2)
    best = None
    best_val = -Inf
    if nsubfeatures > 0
        inds = randperm(nf)[1:nsubfeatures]
        nf = nsubfeatures
    else
        inds = [1:nf]
    end
    for i in 1:nf
        domain_i = sort(unique(features[:,inds[i]]))
        for d in domain_i[2:]
            cur_split = features[:,inds[i]] .< d
            if weights == [0]
                value = _info_gain(labels[cur_split], labels[!cur_split])
            else
                value = _neg_z1_loss(labels[cur_split], weights[cur_split]) + _neg_z1_loss(labels[!cur_split], weights[!cur_split])
            end
            if value > best_val
                best_val = value
                best = (inds[i], d)
            end
        end
    end
    return best
end



function build_stump(labels::Vector, features::Matrix, weights::Vector)
    S = _split(labels, features, 0, weights)
    if S == None
        return Leaf(majority_vote(labels), labels)
    end
    id, thresh = S
    split = features[:,id] .< thresh
    return Node(id, thresh,
                Leaf(majority_vote(labels[split]), labels[split]),
                Leaf(majority_vote(labels[!split]), labels[!split]))
end
build_stump(labels::Vector, features::Matrix) = build_stump(labels, features, [0])



function build_tree(labels::Vector, features::Matrix, nsubfeatures::Integer)
    S = _split(labels, features, nsubfeatures, [0])
    if S == None
        return Leaf(majority_vote(labels), labels)
    end
    id, thresh = S
    split = features[:,id] .< thresh
    labels_left = labels[split]
    labels_right = labels[!split]
    pure_left = all(labels_left .== labels_left[1])
    pure_right = all(labels_right .== labels_right[1])
    if pure_right && pure_left
        return Node(id, thresh,
                    Leaf(labels_left[1], labels_left),
                    Leaf(labels_right[1], labels_right))
    elseif pure_left
        return Node(id, thresh,
                    Leaf(labels_left[1], labels_left),
                    build_tree(labels_right,features[!split,:], nsubfeatures))
    elseif pure_right
        return Node(id, thresh,
                    build_tree(labels_left,features[split,:], nsubfeatures),
                    Leaf(labels_right[1], labels_right))
    else
        return Node(id, thresh,
                    build_tree(labels_left,features[split,:], nsubfeatures),
                    build_tree(labels_right,features[!split,:], nsubfeatures))
    end
end
build_tree(labels::Vector, features::Matrix) = build_tree(labels, features, 0)


function prune_tree(tree::Union(Leaf,Node), purity_thresh::Real)
    function _prune_run(tree::Union(Leaf,Node), purity_thresh::Real)
        N = length(tree)
        if N == 1        ## a Leaf
            return tree
        elseif N == 2    ## a stump
            all_labels = [tree.left.values, tree.right.values]
            majority = majority_vote(all_labels)
            matches = find(all_labels .== majority)
            purity = length(matches) / length(all_labels)
            if purity >= purity_thresh
                return Leaf(majority, all_labels)
            else
                return tree
            end
        else
            return Node(tree.featid, tree.featval,
                        _prune_run(tree.left, purity_thresh),
                        _prune_run(tree.right, purity_thresh))
        end
    end
    pruned = _prune_run(tree, purity_thresh)
    while length(pruned) < length(tree)
        tree = pruned
        pruned = _prune_run(tree, purity_thresh)
    end
    return pruned
end
prune_tree(tree::Union(Leaf,Node)) = prune_tree(tree, 1.0) ## defaults to 100% purity pruning


function apply_tree(tree::Union(Leaf,Node), features::Vector)
    if typeof(tree) == Leaf
        return tree.majority
    elseif tree.featval == nothing
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
    return predictions
end

function build_forest(labels::Vector, features::Matrix, nsubfeatures::Integer, ntrees::Integer)
    Nlabels = length(labels)
    Nsamples = int(0.7 * Nlabels)
    forest = @parallel (vcat) for i in [1:ntrees]
        inds = rand(1:Nlabels, Nsamples)
        build_tree(labels[inds], features[inds,:], nsubfeatures)
    end
    return [forest]
end

function apply_forest{T<:Union(Leaf,Node)}(forest::Vector{T}, features::Vector)
    ntrees = length(forest)
    votes = Array(Any,ntrees)
    for i in 1:ntrees
        votes[i] = apply_tree(forest[i],features)
    end
    return majority_vote(votes)
end

function apply_forest{T<:Union(Leaf,Node)}(forest::Vector{T}, features::Matrix)
    N = size(features,1)
    predictions = Array(Any,N)
    for i in 1:N
        predictions[i] = apply_forest(forest, squeeze(features[i,:],1))
    end
    return predictions
end

function build_adaboost_stumps(labels::Vector, features::Matrix, niterations::Integer)
    N = length(labels)
    weights = ones(N) / N
    stumps = Node[]
    coeffs = FloatingPoint[]
    for i in 1:niterations
        new_stump = build_stump(labels, features, weights)
        predictions = apply_tree(new_stump, features)
        err = _weighted_error(labels, predictions, weights)
        new_coeff = 0.5 * log((1.0 + err) / (1.0 - err))
        matches = labels .== predictions
        weights[!matches] *= exp(new_coeff)
        weights[matches] *= exp(-new_coeff)
        weights /= sum(weights)
        push!(coeffs, new_coeff)
        push!(stumps, new_stump)
        if err < 1e-6
            break
        end
    end
    return (stumps, coeffs)
end

function apply_adaboost_stumps{T<:Union(Leaf,Node)}(stumps::Vector{T}, coeffs::Vector{FloatingPoint}, features::Vector)
    nstumps = length(stumps)
    counts = Dict()
    for i in 1:nstumps
        prediction = apply_tree(stumps[i], features)
        counts[prediction] = get(counts, prediction, 0.0) + coeffs[i]
    end
    top_prediction = None
    top_count = -Inf
    for i in collect(counts)
        if i[2] > top_count
            top_prediction = i[1]
            top_count = i[2]
        end
    end
    return top_prediction
end

function apply_adaboost_stumps{T<:Union(Leaf,Node)}(stumps::Vector{T}, coeffs::Vector{FloatingPoint}, features::Matrix)
    N = size(features,1)
    predictions = Array(Any,N)
    for i in 1:N
        predictions[i] = apply_adaboost_stumps(stumps, coeffs, squeeze(features[i,:],1))
    end
    return predictions
end

#####################################################

# my _split
function _split(responses::Matrix, features::Matrix, nsubfeatures::Integer)
    nf = size(features,2)
    (nobs, nresponses) = size(responses)
    best = None
    best_val = -Inf
    if nsubfeatures > 0
        inds = randperm(nf)[1:nsubfeatures]
        nf = nsubfeatures
    else
        inds = [1:nf]
    end
    sum_total = reshape(mapslices(sum, responses, 1), nresponses)
    for i in 1:nf
        domain_i = sort(unique(features[:,inds[i]]))
        if length(domain_i) < 2
            continue
        end
        member_in_left = falses(nobs)
        size_in_left = 0
        sum_in_left = zeros(eltype(sum_total), nresponses)
        for d in domain_i[2:]
            tmp = features[:, inds[i]] .< d
            new_member_in_left = (!member_in_left) & tmp
            member_in_left = copy(tmp)
            size_in_left = sum(member_in_left)
            
            sum_new = reshape(mapslices(sum, responses[new_member_in_left, :], 1), nresponses)
            sum_in_left += sum_new
            value = sum((sum_in_left) .^ 2) / size_in_left + sum((sum_total .- sum_in_left) .^ 2) / (nobs - size_in_left) 
            
            if value > best_val
                best_val = value
                best = (inds[i], d)
            end
        end
    end
    return best
end




#My build_stump 
function build_stump(responses::Matrix, row_no::Vector, features::Matrix)
    S = _split(responses, features, 0)
    (nobs, nresponses) = size(responses)
    if S == None
        return Leaf(ss_by_col(responses[row_no, :]), row_no)
    end
    id, thresh = S
    split = features[:,id] .< thresh
    return Node(id, thresh,
                Leaf(ss_by_col(responses[split, :]), row_no[split]),
                Leaf(ss_by_col(responses[!split, :]), row_no[!split]))
end


#my own build_tree
function build_tree(responses::Matrix, row_no::Vector, features::Matrix, nsubfeatures::Integer, max_leaf_size::Integer)
     S = _split(responses, features, 0)
    (nobs, nresponses) = size(responses)
    if S == None
        return Leaf(ss_by_col(responses[row_no, :]), row_no)
    end
    id, thresh = S
    split = features[:,id] .< thresh
    row_no_left = row_no[split]
    row_no_right = row_no[!split]
    pure_left = length(row_no_left) < max_leaf_size
    pure_right = length(row_no_right) < max_leaf_size
    if pure_right && pure_left
        return Node(id, thresh,
                    Leaf(ss_by_col(responses[split, :]), row_no_left),
                    Leaf(ss_by_col(responses[!split, :]), row_no_right))
    elseif pure_left
        return Node(id, thresh,
                    Leaf(ss_by_col(responses[split, :]), row_no_left),
                    build_tree(responses[!split, :],row_no_right, features[!split,:], nsubfeatures, max_leaf_size))
    elseif pure_right
        return Node(id, thresh,
                    build_tree(responses[split, :],row_no_left, features[split,:], nsubfeatures, max_leaf_size),
                    Leaf(ss_by_col(responses[!split, :]), row_no_right))
    else
        return Node(id, thresh,
                    build_tree(responses[split, :],row_no_left, features[split,:], nsubfeatures, max_leaf_size),
                    build_tree(responses[!split, :],row_no_right, features[!split,:], nsubfeatures, max_leaf_size))
    end
end


#my own prune_tree


function prune_tree(tree::Union(Leaf,Node), imp_thresh::Float64, responses::Matrix)
    function _prune_run(tree::Union(Leaf,Node), imp_thresh::Float64, responses::Matrix)
        N = length(tree)
        if N == 1        ## a Leaf
            return tree
        elseif N == 2    ## a stump

            all_no = [tree.left.values, tree.right.values]
            all_ss = ss_by_col(responses[all_no, :])

            imp = all_ss / (tree.left.majority + tree.right.majority) - 1
            if imp <= qf(imp_thresh, 1, length(all_no)) 
                println(imp)
                return Leaf(all_ss, all_no)
            else
                return tree
            end
        else
            return Node(tree.featid, tree.featval,
                        _prune_run(tree.left, imp_thresh, responses),
                        _prune_run(tree.right, imp_thresh, responses))
        end
    end
    pruned = _prune_run(tree, imp_thresh, responses)
    while length(pruned) < length(tree)
        tree = pruned
        pruned = _prune_run(tree, imp_thresh, responses)
    end
    return pruned
end


function ss{T <: Real}(y::Array{T})
        y | x -> (x .- mean(x)) .^ 2 | sum
end

function ss_by_col(responses::Matrix)
    mapslices(ss, responses, 1) | sum
end


function Tree2Collection(tree::Union(Leaf, Node), coll::Array{Any, 1})
    if typeof(tree) == Leaf
        push!(coll, tree.values)
    else
        Tree2Collection(tree.left, coll)
        Tree2Collection(tree.right, coll)
    end
    coll
end

function Tree2Centers(tree::Union(Leaf, Node), responses::Matrix)
    mycoll = Tree2Collection(tree, {})

    centers = similar(responses, (length(mycoll), size(responses, 2)))
    for i in 1:length(mycoll)
        centers[i, :] = mapslices(mean, responses[mycoll[i], :], 1) 
    end
    centers
end

function RSquare(tree::Union(Leaf, Node), responses::Matrix, rsquare::Array{Float64, 1})
    if typeof(tree) == Leaf    
        rsquare[1] += tree.majority
    else
        RSquare(tree.left, responses, rsquare)
        RSquare(tree.right, responses, rsquare)
    end
    rsquare[1] / ss_by_col(responses)
end


end # module

