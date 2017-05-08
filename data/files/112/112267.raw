module btclustering 

import Base.length, Base.convert, Base.promote_rule, Base.show, Rmath.qf

export Leaf, Node, print_tree, Tree2Collection, Tree2Centers, ss, ss_by_col, RSquare, 
       build_stump, build_tree, prune_tree, apply_tree, nfoldCV_tree,
       build_forest, apply_forest, nfoldCV_forest,
       build_adaboost_stumps, apply_adaboost_stumps, nfoldCV_stumps,
       summary_vote, ConfusionMatrix, confusion_matrix

include("measures.jl")
#include("Clustering.jl")

type Leaf
    summary::Any
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
        matches = find(tree.values .== tree.summary)
        ratio = string(length(matches)) * "/" * string(length(tree.values))
        println("$(tree.summary) : $(ratio)")
    else
        println("Feature $(tree.featid), Threshold $(tree.featval)")
        print("    " ^ indent * "L-> ")
        print_tree(tree.left, indent + 1)
        print("    " ^ indent * "R-> ")
        print_tree(tree.right, indent + 1)
    end
end
print_tree(tree::Union(Leaf,Node)) = print_tree(tree, 0)



#####################################################

# my _split
function _split{T <: FloatingPoint, V <: FloatingPoint}(responses::Matrix{T}, features::Matrix{V}, nsubfeatures::Integer)
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
    sum_total = mapslices(sum, responses, 1)
    for i in 1:nf
        domain_i = sort(unique(features[:,inds[i]]))
        if length(domain_i) < 2
            continue
        end
        member_in_left = falses(nobs)
        size_in_left = 0
        sum_in_left = zeros(eltype(sum_total), (1, nresponses))
        for d in domain_i[2:]
            tmp = features[:, inds[i]] .< d
            new_member_in_left = (!member_in_left) & tmp
            member_in_left = copy(tmp)
            size_in_left = sum(member_in_left)
            
            sum_new = mapslices(sum, responses[new_member_in_left, :], 1)
            sum_in_left = sum_in_left .+ sum_new
            value = sum((sum_in_left) .^ 2) / size_in_left + sum((sum_total .- sum_in_left) .^ 2) / (nobs - size_in_left) 
            
            if value > best_val
                best_val = value
                best = (inds[i], d)
            end
        end
    end
    return best
end

#my _split for category data
function _split{T <: Integer, V <: Integer}(responses::Matrix{T}, features::Matrix{V}, nsubfeatures::Integer)
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
        if(length(domain_i) < 2)
            continue
        end
        for d in domain_i
            
            value = ss_ratio(responses, features[:, inds[i]] .== d)
            
            if value > best_val
                best_val = value
                best = (inds[i], d)
            end
        end
    end
    return best
end



#My build_stump 
function build_stump{T <: Real, V <: Real}(responses::Matrix{T}, row_no::Vector{Integer}, features::Matrix{V})
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
function build_tree{T <: FloatingPoint, V <: FloatingPoint}(responses::Matrix{T}, row_no::Vector, features::Matrix{V}, nsubfeatures::Integer, max_leaf_size::Integer)
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

function build_tree{T <: Integer, V <: Integer}(responses::Matrix{T}, row_no::Vector, features::Matrix{V}, nsubfeatures::Integer, max_leaf_size::Integer)
     S = _split(responses, features, 0)
    (nobs, nresponses) = size(responses)
    if S == None
        return Leaf(0, row_no)
    end
    id, thresh = S
    split = features[:,id] .==  thresh
    row_no_left = row_no[split]
    row_no_right = row_no[!split]
    pure_left = length(row_no_left) < max_leaf_size
    pure_right = length(row_no_right) < max_leaf_size
    if pure_right && pure_left
        return Node(id, thresh,
                    Leaf(0, row_no_left),
                    Leaf(0, row_no_right))
    elseif pure_left
        return Node(id, thresh,
                    Leaf(0, row_no_left),
                    build_tree(responses[!split, :],row_no_right, features[!split,:], nsubfeatures, max_leaf_size))
    elseif pure_right
        return Node(id, thresh,
                    build_tree(responses[split, :],row_no_left, features[split,:], nsubfeatures, max_leaf_size),
                    Leaf(0, row_no_right))
    else
        return Node(id, thresh,
                    build_tree(responses[split, :],row_no_left, features[split,:], nsubfeatures, max_leaf_size),
                    build_tree(responses[!split, :],row_no_right, features[!split,:], nsubfeatures, max_leaf_size))
    end
end
    

#my own prune_tree


function _prune_run{T <: FloatingPoint}(tree::Union(Leaf,Node), imp_thresh::Float64, responses::Matrix{T})
    N = length(tree)
    if N == 1        ## a Leaf
        return tree
    elseif N == 2    ## a stump

        all_no = [tree.left.values, tree.right.values]
        all_ss = ss_by_col(responses[all_no, :])

        imp = all_ss / (tree.left.summary + tree.right.summary) - 1
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

function prune_tree{T <: FloatingPoint}(tree::Union(Leaf,Node), imp_thresh::Float64, responses::Matrix{T})
    pruned = _prune_run(tree, imp_thresh, responses)
    while length(pruned) < length(tree)
        tree = pruned
        pruned = _prune_run(tree, imp_thresh, responses)
    end
    return pruned
end


function _prune_run{T <: Integer}(tree::Union(Leaf,Node), imp_thresh::Real, responses::Matrix{T})
    N = length(tree)
    if N == 1        ## a Leaf
        return tree
    elseif N == 2    ## a stump

        all_no = [tree.left.values, tree.right.values]
        split = falses(length(all_no))
        split[1:length(tree.left.values)] = true
        println(ss_ratio(responses[all_no, :], split))
        all_ss = ss_ratio(responses[all_no, :], split) 

        imp = all_ss / (1 - all_ss)
        if imp <= qf(imp_thresh, 1, length(table(all_no)) - 1) 
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

function prune_tree{T <: Integer}(tree::Union(Leaf,Node), imp_thresh::Real, responses::Matrix{T})
    pruned = _prune_run(tree, imp_thresh, responses)
    while length(pruned) < length(tree)
        tree = pruned
        pruned = _prune_run(tree, imp_thresh, responses)
    end
    return pruned
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

function Tree2Centers{T <: Real}(tree::Union(Leaf, Node), responses::Matrix{T})
    mycoll = Tree2Collection(tree, {})

    centers = similar(responses, (length(mycoll), size(responses, 2)))
    for i in 1:length(mycoll)
        centers[i, :] = mapslices(mean, responses[mycoll[i], :], 1) 
    end
    centers
end

function RSquare{T <: Real}(tree::Union(Leaf, Node), responses::Matrix{T}, rsquare::Array{Float64, 1})
    if typeof(tree) == Leaf    
        rsquare[1] += ss_by_col(responses[tree.values, :]) 
    else
        RSquare(tree.left, responses, rsquare)
        RSquare(tree.right, responses, rsquare)
    end
    rsquare[1] / ss_by_col(responses)
end


end # module

