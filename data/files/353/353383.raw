include("splay_tree.jl")

module L1DecisionTree

using DataFrames
using Stats
# import DataFrames.DataArray
using BinarySearchTree
import Base: insert!, delete!, median

export DecisionTree, build_tree, predict


abstract DTAbstractNode{T<:Real}

type DTNode{T<:FloatingPoint} <: DTAbstractNode{T}
	split_feat::Uint
	split_val::Real
	left_child::DTAbstractNode{T}
	right_child::DTAbstractNode{T}
end

type DTLeaf{T<:FloatingPoint} <: DTAbstractNode{T}
	value::T
end

type DecisionTree{T<:FloatingPoint}
	head::DTAbstractNode{T}
end

function build_tree{T<:FloatingPoint}(X::DataFrame, Y::Vector{T}, min_leaf_samples::Int=5, max_depth::Int=50, feats_per_split::Int=0)
	if feats_per_split == 0
		feats_per_split = size(X, 2)
	end
	if size(X, 1) != length(Y)
		throw(ArgumentError("X and Y must have the same length"))
	end
	return DecisionTree(build_stump(X, Y, min_leaf_samples, max_depth, feats_per_split))
end

function predict(tree::DecisionTree, X::DataFrame)
	return predict(tree.head, X)
end

function predict{T}(node::DTNode{T}, X::DataFrame)
	y = Array(T, size(X, 1))
	left_mask = X[node.split_feat] .<= node.split_val
	y[left_mask] = predict(node.left_child, X[left_mask, :])
	y[!left_mask] = predict(node.right_child, X[!left_mask, :])
	return y
end

function predict{T}(leaf::DTLeaf{T}, X::DataFrame)
	return ones(T, size(X, 1)) * leaf.value
end

function build_stump{T<:FloatingPoint}(X::DataFrame, Y::Vector{T}, min_leaf_samples::Int, max_depth::Int, n_feats::Int)
	if length(Y) <= min_leaf_samples || max_depth == 0
		return DTLeaf{T}(median(Y)::T)
	else
		split_feat, split_val = get_split(X::DataFrame, Y::Vector, n_feats)
		if split_feat == 0
			return DTLeaf{T}(median(Y)::T)
		end
		left_mask = X[:, split_feat] .<= split_val
		right_mask = X[:, split_feat] .> split_val
		if all(left_mask) || all(right_mask)
			return DTLeaf{T}(median(Y)::T)
		end
		return DTNode{T}(split_feat, split_val,
					  build_stump(X[left_mask, :], Y[left_mask]::Vector{T}, min_leaf_samples, max_depth - 1, n_feats),
					  build_stump(X[right_mask, :], Y[right_mask]::Vector{T}, min_leaf_samples, max_depth - 1, n_feats)
					 )
	end
end

function get_split(X::DataFrame, Y::Vector, n_feats::Integer)
	best_gain = 0.0
	best_feat::Uint = 0
	best_split = 0.0

	if n_feats != size(X, 2)
		feats = Stats.sample(1:size(X, 2), n_feats, replace=false)
	else
		feats = 1:n_feats
	end

	for feat in feats
		split, gain = get_best_gain(X[:, feat], Y)
		if gain > best_gain
			best_gain = gain
			best_feat = feat
			best_split = split
		end
	end

	return best_feat, best_split
end

function get_best_gain(x::DataArray, y::Vector)
	min = minimum(x)
	max = maximum(x)

	split_val = min + rand() * (max - min)

	total_mae = sum(abs(median(y) - y))
	left_indices = x .<= split_val
	if sum(left_indices) > 0
		left_mae = sum(abs(median(y[left_indices]) - y[left_indices]))
	else
		left_mae = 0
	end
	if sum(!left_indices) > 0
		right_mae = sum(abs(median(y[!left_indices]) - y[!left_indices]))
	else
		right_mae = 0
	end


	return split_val, total_mae - left_mae - right_mae
end

end