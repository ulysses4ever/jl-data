
function Tree2Collection(tree::Union(Leaf, Node), coll::Array{Any, 1})
    if typeof(tree) == Leaf
        push!(coll, tree.values)
    else
        Tree2Collection(tree.left, coll)
        Tree2Collection(tree.right, coll)
    end
    coll
end


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
function ss{T <: Real}(y::Array{T})
        y | x -> (x .- mean(x)) .^ 2 | sum
end

function ss_by_col(responses::Matrix)
    mapslices(ss, responses, 1) | sum
end


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


